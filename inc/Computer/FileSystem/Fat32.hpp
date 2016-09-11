#ifndef FILESYS_HPP
#define FILESYS_HPP

#include <sstream>
#include <vector>
#include <string>

#include "lib/StrFunc.hpp"
#include "Computer/FileSystem/VDisk.hpp"

class Fat32
{
public:
	Fat32();
	Fat32(VDisk disk);

	int fsclose();
	int fssynch();
	int newFile(std::string file);
	int rmFile(std::string file);
	int getFirstBlock(std::string file);
	int addBlock(std::string file, std::string block);
	int delBlock(std::string file, int blockNumber);
	int readBlock(std::string file, int blockNumber, std::string &buffer);
	int writeBlock(std::string file, int blockNumber, std::string &buffer);
	int nextBlock(std::string file, int blockNumber);

	std::vector<std::string> getRoot();

private:
	const static int filenameLength = 5;
	const static int firstBlockDigits = 5;
	const static int FATdigits = 5;

	std::string constructDefaultFilename();

	bool initialized;

	VDisk disk;
	int rootSize;						//number of entries in root
	int fatSize;						//number of blocks occupied by FAT
	std::vector<std::string> filenames;	//filenames in root
	std::vector<int> firstBlock;		//first block in root
	std::vector<int> fat;				//FAT
};

#endif //FILESYS_HPP
