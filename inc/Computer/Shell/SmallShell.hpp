#ifndef SMALLSHELL_HPP
#define SMALLSHELL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Computer/ScreenIO/AbstractIO.hpp"
#include "Computer/FileSystem/AbstractFileSystem.hpp"
#include "lib/StrFunc.hpp"

class SmallShell
{
public:
	SmallShell();
	SmallShell(AbstractIO *io, AbstractFileSystem *fs);

	int Run();

private:
	int mkFile(std::string fileName, std::string buffer);
	int catFile(std::string fileName);
	int cpFile(std::string fileName, std::string newFileName);
	int rmFile(std::string fileName);
	int ls();

	bool initialized;
	AbstractIO *io;
	AbstractFileSystem *fs;
};

#endif //SMALLSHELL_HPP
