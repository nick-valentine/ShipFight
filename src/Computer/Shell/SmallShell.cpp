#include "Computer/Shell/SmallShell.hpp"

SmallShell::SmallShell()
{
	this->initialized = false;
}

SmallShell::SmallShell(AbstractIO *io, AbstractFileSystem *fs)
{
	this->io = io;
	this->fs = fs;

	this->initialized = true;
}

int SmallShell::Run()
{
	std::string input;

	this->io->putstr("/ =>");
	input = this->io->getstr();
	this->io->putstr(input);
	this->io->putch('\n');
	while(input != "exit") {
		if(input == "touch") {
			std::string fileName = this->io->getstr();
			this->mkFile(fileName,"");
		} else if(input == "echo") {
			std::string line;
			char x;
			x = this->io->getch();
			while(x != '\n') {
				line.push_back(x);
				x = this->io->getch();
			}
			std::vector<std::string> cmdParts = string::explode(line,'>');
			if(cmdParts.size() < 2) {
				this->io->putstr(line);
			} else {
				this->mkFile(cmdParts[1],cmdParts[0]);
			}
		} else if(input == "cat") {
			std::string fileName = this->io->getstr();
			this->catFile(fileName);
		} else if(input == "cp") {
			std::string fileName, newFile;
			fileName = this->io->getstr();
			newFile = this->io->getstr();
			this->cpFile(fileName,newFile);
		} else if(input == "rm") {
			std::string fileName = this->io->getstr();
			this->rmFile(fileName);
		} else if(input == "ls") {
			this->ls();	
		} else {
			this->io->putstr("unknown command: ");
			this->io->putstr(input);
		}
		this->io->putstr("\n/ =>");
		input = this->io->getstr();	
		this->io->putstr(input);
		this->io->putch('\n');
	}

	return 0;
}

int SmallShell::mkFile(std::string fileName, std::string buffer)
{
	int error = fs->newFile(fileName);
	if(error == 0) {
		this->io->putstr("Could not create file\n");
		return 0;
	}

	if(buffer != "") {
		std::vector<std::string> blocks = string::block(buffer, fs->getBlockSize());

		for(unsigned int i = 0; i < blocks.size(); ++i) {
			error = fs->addBlock(fileName, blocks[i]);
			if(error == 0) {
				this->io->putstr("Error writing to disk");
				return 0;
			}
		}
	}

	return 1;
}

int SmallShell::catFile(std::string fileName)
{
	int block = fs->getFirstBlock(fileName);
	if(block == 1) {
		return 0;
	}

	while(block != 0) {
		std::string buffer;
		this->fs->readBlock(fileName, block, buffer);
		this->io->putstr(buffer);
		block = this->fs->nextBlock(fileName, block);
	}

	return 1;
}

int SmallShell::cpFile(std::string fileName, std::string newFileName)
{
	int block = this->fs->getFirstBlock(fileName);
	this->fs->newFile(newFileName);
	if(block == 1) {
		return 0;
	}

	while(block != 0) {
		std::string buffer;
		this->fs->readBlock(fileName, block, buffer);
		this->fs->addBlock(newFileName, buffer);
		block = this->fs->nextBlock(fileName, block);
	}

	return 1;
}

int SmallShell::rmFile(std::string fileName)
{
	int block = this->fs->getFirstBlock(fileName);
	if(block == 1) {
		this->io->putstr("Could not remove file\n");
		return 0;
	}

	while(block != 0) {
		this->fs->delBlock(fileName, block);
		block = this->fs->getFirstBlock(fileName);
	}

	fs->rmFile(fileName);
	return 1;
}

int SmallShell::ls()
{
	std::vector<std::string> root = this->fs->getRoot();
	for(unsigned int i = 0; i < root.size(); ++i) {
		this->io->putstr(root[i]);
		this->io->putch(' ');
	}
	return 1;
}
