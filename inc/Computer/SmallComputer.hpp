#ifndef SMALLCOMPUTER_HPP
#define SMALLCOMPUTER_HPP

#include "Computer/VirtualMachine/SmallVirtualMachine.hpp"
#include "Computer/Assembler/SmallAssembler.hpp"
#include "Computer/ScreenIO/AbstractIO.hpp"
#include "Computer/ScreenIO/LinuxIO.hpp"
#include "Computer/FileSystem/VDisk.hpp"
#include "Computer/FileSystem/Fat32.hpp"
#include "Computer/Shell/SmallShell.hpp"

//@todo: Operating System, File system
//@notes: io system must be injected and managed/deleted by caller
class SmallComputer
{
public:
	SmallComputer();
	~SmallComputer();
	SmallComputer(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io);

	void Run();
private:
	void init(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io);

	unsigned int mem_size;
	unsigned int clock_speed;

	SmallVirtualMachine vm;
	SmallAssembler assembler;
	AbstractIO *io;
	VDisk disk;
	Fat32 fsys;
	SmallShell shell;
};

#endif //SMALLCOMPUTER_HPP
