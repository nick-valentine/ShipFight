#ifndef VDISK_HPP
#define VDISK_HPP

#include <string>
#include <fstream>

class VDisk
{
public:
	VDisk();
	VDisk(std::string diskName);
	VDisk(std::string diskName, unsigned int numBlocks, unsigned int blockSize);

	int getBlock(unsigned int blockNumber, std::string &buffer);
	int putBlock(unsigned int blockNumber, std::string buffer);
private:
	static const char EMPTY_CHAR = '#';
	void init(std::string diskName, unsigned int numBlocks, unsigned int blockSize);

	bool initialized;
	std::string diskName;
	unsigned int numBlocks;
	unsigned int blockSize;
};

#endif
