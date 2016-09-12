#include "Computer/FileSystem/Fat32.hpp"

Fat32::Fat32()
{
	this->initialized = false;
}

Fat32::Fat32(VDisk disk)
{
	this->disk = disk;

	this->rootSize = disk.getBlockSize() / (filenameLength + firstBlockDigits + 2);
	this->fatSize = (disk.getNumBlocks() * (FATdigits + 1)) / disk.getBlockSize();

	std::string rootBuffer;
	disk.getBlock(1, rootBuffer);

	//check to see if the root block exists,
	//if not, the disk does not have a filesystem on it
	bool createFileSys = false;
	int counter = 0;
	for(int i = 0; i < disk.getBlockSize(); ++i) {
		if(rootBuffer[i] == '#') {
			counter++;
		}
	}
	if(counter == disk.getBlockSize()) {
		createFileSys = true;
	}

	if(createFileSys) {
		std::string defaultFilename = this->constructDefaultFilename();
		for(int i = 0; i < this->rootSize; ++i) {
			this->filenames.push_back(defaultFilename);
			this->firstBlock.push_back(0);
		}

		//firstblock = FATsize + 2
		this->fat.push_back(this->fatSize + 2);

		//root block
		this->fat.push_back(1);

		//fat blocks
		for(int i = 0; i < this->fatSize; ++i) {
			this->fat.push_back(1);
		}

		//the fat list
		for(int i = this->fat[0]; i < disk.getNumBlocks(); ++i) {
			this->fat.push_back(i+1);
		}
		this->fat.push_back(0);
	} else {
		std::istringstream instream;
		instream.str(rootBuffer);

		std::string file;
		int block;

		for(int i = 0; i < this->rootSize; ++i) {
			instream>>file>>block;
			this->filenames.push_back(file);
			this->firstBlock.push_back(block);
		}

		std::string fatBuffer;
		std::string tempFat;
		for(int i = 2; i < this->fatSize + 2; ++i) {
			disk.getBlock(i, fatBuffer);
			tempFat = tempFat + fatBuffer;
		}

		instream.clear();
		instream.str(tempFat);
		for(int i = 0; i < disk.getNumBlocks(); ++i) {
			instream>>block;
			this->fat.push_back(block);
		}
	}

	this->fssynch();
	this->initialized = true;
}

int Fat32::fsclose()
{
	return this->fssynch();
}

int Fat32::fssynch()
{
	std::ostringstream outstream;
	for(int i = 0; i < this->rootSize; ++i) {
		outstream<<this->filenames[i]<<" "<<this->firstBlock[i]<<" ";
	}
	
	std::vector<std::string> rootBlock = string::block(outstream.str(), disk.getBlockSize());
	if(!disk.putBlock(1,rootBlock[0])) {
		//error writing out root block
		return 0;
	}

	std::ostringstream fatStream;
	for(int i = 0; i < disk.getNumBlocks(); ++i) {
		fatStream<<this->fat[i]<<" ";
	}
	std::vector<std::string> blocks = string::block(fatStream.str(), disk.getBlockSize());
	for(unsigned int i = 0; i < blocks.size(); ++i) {
		if(!disk.putBlock(2 + i, blocks[i])) {
			//error writing blocks
			return 0;
		}
	}
	return 1;
}

int Fat32::newFile(std::string file)
{
	for(int i = 0; i < this->rootSize; ++i) {
		if(this->filenames[i] == file) {
			return 0;
		}
	}

	std::string defaultFilename = constructDefaultFilename();

	bool emptyFileFound = false;
	for(int i = 0; i < this->rootSize; ++i) {
		if(this->filenames[i] == defaultFilename) {
			emptyFileFound = true;

			this->filenames[i] = file;
			this->firstBlock[i] = 0;
			this->fssynch();
			break;
		}
	}

	if(!emptyFileFound) {
		return 0;
	} else {
		return 1;
	}
}

int Fat32::rmFile(std::string file)
{
	std::string defaultFilename = this->constructDefaultFilename();
	for(int i = 0; i < this->rootSize; ++i) {
		if( this->filenames[i] == file) {
			if(this->firstBlock[i] == 0) {
				this->filenames[i] = defaultFilename;
				return this->fssynch();
			} else {
				//file not empty
				return 0;
			}
		}
	}
	//file not found
	return 0;
}

int Fat32::getFirstBlock(std::string file)
{
	for(int i = 0; i < this->rootSize; ++i) {
		if(this->filenames[i] == file) {
			return this->firstBlock[i];
		}
	}
	//file not found
	return -1;
}

int Fat32::addBlock(std::string file, std::string buffer)
{
	if(this->fat[0] == 0) {
		//file system full
		return -1;
	} else {
		for(int i = 0; i < this->rootSize; ++i) {
			if(this->filenames[i] == file) {
				int currentBlock = this->firstBlock[i];

				if(currentBlock == 0) {
					this->firstBlock[i] = this->fat[0];
					this->fat[0] = this->fat[this->fat[0]];
					disk.putBlock(this->firstBlock[i], buffer);
					this->fat[firstBlock[i]] = 0;
					this->fssynch();
					return firstBlock[i];
				} else {
					while(this->fat[currentBlock] != 0) {
						currentBlock = this->fat[currentBlock];
					}

					int temp = this->fat[this->fat[0]];
					this->fat[currentBlock] = this->fat[0];
					this->fat[0] = temp;

					disk.putBlock(currentBlock,buffer);
					this->fat[this->fat[currentBlock]] = 0;
					this->fssynch();
					return currentBlock;
				}
			}
		}
	}
	//file does not exist
	return 0;
}

int Fat32::delBlock(std::string file, int blockNumber)
{
	for(int i = 0; i < this->rootSize; ++i) {
		if(this->filenames[i] == file) {
			if(this->firstBlock[i] == blockNumber) {
				this->firstBlock[i] = this->fat[this->firstBlock[i]];
			} else {
				int currentBlock = this->firstBlock[i];
				int lastBlock = currentBlock;
				while(this->fat[currentBlock] != blockNumber) {
					lastBlock = currentBlock;
					currentBlock = this->fat[currentBlock];

					if(this->fat[currentBlock] == 0) {
						//end of file reached and block not found
						return 0;
					}
				}
				this->fat[lastBlock] = this->fat[this->fat[currentBlock]];
			}

			if(this->fat[0] > blockNumber) {
				this->fat[blockNumber] = this->fat[0];
				this->fat[0] = blockNumber;
				return this->fssynch();
			} else {
				int i = this->fat[0];
				while(this->fat[i] < blockNumber) {
					i = this->fat[i];
				}
				this->fat[blockNumber] = this->fat[i];
				this->fat[i] = blockNumber;
				return this->fssynch();
			}
		}
	}
	return 0;
}

int Fat32::readBlock(std::string file, int blockNumber, std::string &buffer)
{
	for(int i = 0; i < this->rootSize; ++i) {
		if(this->filenames[i] == file) {
			if(this->firstBlock[i] == blockNumber) {
				return disk.getBlock(blockNumber,buffer);
			} else {
				int i = this->firstBlock[i];
				while(this->fat[i] != 0) {
					if(i == blockNumber) {
						return disk.getBlock(blockNumber, buffer);
					}
					i = this->fat[i];
				}
			}
		}
	}
	return 0;
}

int Fat32::writeBlock(std::string file, int blockNumber, std::string &buffer)
{
	for(int i = 0; i < this->rootSize; ++i) {
		if(this->filenames[i] == file) {
			if(this->firstBlock[i] == blockNumber) {
				return disk.putBlock(blockNumber, buffer);
			} else {
				int i = this->firstBlock[i];
				while(this->fat[i] != 0) {
					if(i == blockNumber) {
						return disk.putBlock(blockNumber, buffer);
					}
					i = this->fat[i];
				}
			}
		}
	}
	return 0;
}

int Fat32::nextBlock(std::string file, int blockNumber)
{
	for(int i = 0; i < this->rootSize; ++i) {
		if(this->filenames[i] == file) {
			if(this->firstBlock[i] == blockNumber) {
				return this->fat[firstBlock[i]];
			} else {
				int i = this->firstBlock[i];
				while(this->fat[i] != 0) {
					if(i == blockNumber) {
						return this->fat[this->fat[i]];
					}
					i = this->fat[i];
				}
			}
		}
	}
	return 0;
}

std::vector<std::string> Fat32::getRoot()
{
	return this->filenames;
}

std::string Fat32::constructDefaultFilename()
{
	std::string defaultFilename;
	for(int i = 0; i < filenameLength; ++i) {
		defaultFilename.push_back('X');
	}
	return defaultFilename;
}


int Fat32::getBlockSize()
{
	return this->disk.getBlockSize();
}

int Fat32::getNumBlocks()
{
	return this->disk.getNumBlocks();
}
