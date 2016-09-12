#ifndef ABSTRACTFILESYSTEM_HPP
#define ABSTRACTFILESYSTEM_HPP

class AbstractFileSystem
{
public:
	AbstractFileSystem(){};
	virtual ~AbstractFileSystem(){};

	virtual int fsclose() = 0;
	virtual	int fssynch() = 0;
	virtual	int newFile(std::string file) = 0;
	virtual	int rmFile(std::string file) = 0;
	virtual	int getFirstBlock(std::string file) = 0;
	virtual	int addBlock(std::string file, std::string block) = 0;
	virtual	int delBlock(std::string file, int blockNumber) = 0;
	virtual	int readBlock(std::string file, int blockNumber, std::string &buffer) = 0;
	virtual	int writeBlock(std::string file, int blockNumber, std::string &buffer) = 0;
	virtual	int nextBlock(std::string file, int blockNumber) = 0;

	virtual std::vector<std::string> getRoot() = 0;

	virtual int getBlockSize() = 0;
	virtual int getNumBlocks() = 0;
private:
};

#endif //ABSTRACTFILESYSTEM_HPP
