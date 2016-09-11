#include "Computer/SmallComputer.hpp"

SmallComputer::SmallComputer()
{
	this->init(256,10000,0);
}

SmallComputer::~SmallComputer()
{
}

SmallComputer::SmallComputer(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io)
{
	this->init(mem_size, clock_speed, io);
}

void SmallComputer::Run()
{
	this->io->putstr("Hello World!\n");
	
	std::vector<std::string> p;
	p.push_back("loadi 1 60");
	p.push_back("addi 1 5");
	p.push_back("store 1 6");
	p.push_back("write 1"); //write 65: A
	p.push_back("halt");
	p.push_back("noop");

	std::vector<unsigned int> o_file = assembler.translate_program(p);

  unsigned int base = 0,offset = 0;
  vm.Load(base,offset,o_file);
  vm.Run();
}

void SmallComputer::init(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io)
{
	this->mem_size = mem_size;
	this->clock_speed = clock_speed;

	this->vm = SmallVirtualMachine(mem_size, clock_speed,io);

	this->io = io;
}


