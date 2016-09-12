#include "Computer/FileSystem/VDisk.hpp"

VDisk::VDisk()
{
	this->initialized = false;	
}

VDisk::VDisk(std::string diskName)
{
	this->initialized = false;
	this->init(diskName, 128, 128);
}

VDisk::VDisk(std::string diskName, unsigned int numBlocks, unsigned int blockSize)
{
	this->initialized = false;
	this->init(diskName, numBlocks, blockSize);
}

void VDisk::init(std::string diskName, unsigned int numBlocks, unsigned int blockSize)
{
	this->diskName = diskName;
	this->numBlocks = numBlocks;
	this->blockSize = blockSize;

	std::string spcFile = diskName + ".spc";
	
	std::ifstream infile;
	infile.open(spcFile.c_str());

	if( infile.good() ) {
		//this disk already exists
		infile>>this->numBlocks>>this->blockSize;
	} else {
		//this disk does not exist
		std::fstream outfile;
		outfile.open(spcFile.c_str(), std::ios::out);

		outfile<<this->numBlocks<<" "<<this->blockSize;
		outfile.close();

		std::string datFile = diskName + ".dat";
		outfile.open(datFile.c_str(), std::ios::out);
		for(unsigned int i = 0; i < this->blockSize * this->numBlocks; ++i) {
			outfile.put(EMPTY_CHAR);
		}
		outfile.close();
	}
	infile.close();
	this->initialized = true;
}

int VDisk::getBlock(unsigned int blockNumber, std::string &buffer)
{
	if( !this->initialized ) {
		return 0;
	}

	buffer = "";
	std::ifstream inFile;
	std::string datFile = this->diskName + ".dat";
	inFile.open(datFile.c_str());
	if(inFile.good()) {
		inFile.seekg(blockNumber * this->blockSize);

		char x = inFile.get();
		for(unsigned int i = 0; i < this->blockSize; ++i) {
			if(inFile.good()) {
				buffer.push_back(x);
				inFile.get(x);
			} else {
				//some error happened while reading the file
				return 0;
			}
		}
	} else {
		//some error happened while opening the file
		return 0;
	}
	return 1;
}

int VDisk::putBlock(unsigned int blockNumber, std::string buffer)
{
	if( !this->initialized ) {
		return 0;
	}

	std::fstream outFile;
	std::string datFile = this->diskName + ".dat";
	outFile.open(datFile.c_str(), std::ios::in | std::ios::out);
	if(outFile.good()) {
		outFile.seekp(blockNumber * this->blockSize);
		for(unsigned int i = 0; i < this->blockSize; ++i) {
			if(outFile.good()) {
				outFile.put(buffer[i]);
			} else {
				//some error happened while writing the file
				return 0;
			}
		}
	} else {
		//some error happened while opening the file
		return 0;
	}
	return 1;
}


std::string VDisk::getDiskName()
{
	return this->diskName;
}

int VDisk::getNumBlocks()
{
	return this->numBlocks;
}

int VDisk::getBlockSize()
{
	return this->blockSize;
}
