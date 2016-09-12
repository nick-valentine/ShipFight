#ifndef SMALLVIRTUALMACHINE_HPP
#define SMALLVIRTUALMACHINE_HPP

#include <vector>
#include <map>
#include <iostream>

#include "Computer/VirtualMachine/AbstractVirtualMachine.hpp"
#include "Computer/ScreenIO/AbstractIO.hpp"
#include "lib/Helper.hpp"

class SmallVirtualMachine : public AbstractVirtualMachine
{
 public:
	SmallVirtualMachine();
	SmallVirtualMachine(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io);


	/**
	 * Loads a program into memory
	 * @param[in] base starting address of program loaded
	 * @param[out] end ending address of program loaded
	 * @param[in] program program to load
	 * @return error code
	 */
	int Load(unsigned int base, unsigned int &offset, std::vector<unsigned int> program);

	enum LoadErrorCode {
		NONE = 0,
		INVALIDBASE,
		OUTOFRANGE
	};

	/**
	 * Run the program until a blocking operation 
	 * or error occurs
	 * such as an input request
	 */
	int Run();

	struct sr_field
	{
		unsigned int carry      : 1;
		unsigned int greater    : 1;
		unsigned int equal      : 1;
		unsigned int less       : 1;
		unsigned int overflow   : 1;
		unsigned int vm_stat    : 3;
		unsigned int io_reg     : 2;
		unsigned int page_fault : 1;
		unsigned int            : 21;
	};

	union status_register
	{
		int i;
		sr_field sr;
	};

	struct instr_format_1
	{
		unsigned int    : 6;
		unsigned int RS : 2;
		unsigned int I  : 1;
		unsigned int RD : 2;
		unsigned int OP : 5;
		unsigned int    : 16;
	};

	struct instr_format_2
	{
		unsigned int ADDR : 8;
		unsigned int I    : 1;
		unsigned int RD   : 2;
		unsigned int OP   : 5;
		unsigned int      : 16;
	};

	struct instr_format_3
	{
		int CONST       : 8;
		unsigned int I  : 1;
		unsigned int RD : 2;
		unsigned int OP : 5;
		unsigned int    : 16;
	};

	union instruction
	{
		int i;
		instr_format_1 f1;
		instr_format_2 f2;
		instr_format_3 f3;
	};

 private:
	void init(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io);
	
	typedef int(*FP) (SmallVirtualMachine *vm, instruction INSTR);
	
	struct int_halves
	 {
		int low   :16;
		int hight: 16;
	 };

	 union int16 {
		int i;
		int_halves i16;
	 };

	 unsigned int mem_size;
	 unsigned int clock_speed;
	 static const unsigned int REG_FILE_SIZE = 4;

	 static int load(SmallVirtualMachine *vm, instruction INSTR);
	 static int loadi(SmallVirtualMachine *vm, instruction INSTR);
	 static int store(SmallVirtualMachine *vm, instruction INSTR);
	 static int add(SmallVirtualMachine *vm, instruction INSTR);
	 static int addi(SmallVirtualMachine *vm, instruction INSTR);
	 static int addc(SmallVirtualMachine *vm, instruction INSTR);
	 static int addci(SmallVirtualMachine *vm, instruction INSTR);
	 static int sub(SmallVirtualMachine *vm, instruction INSTR);
	 static int subi(SmallVirtualMachine *vm, instruction INSTR);
	 static int subc(SmallVirtualMachine *vm, instruction INSTR);
	 static int subci(SmallVirtualMachine *vm, instruction INSTR);
	 static int AND(SmallVirtualMachine *vm, instruction INSTR);
	 static int ANDI(SmallVirtualMachine *vm, instruction INSTR);
	 static int XOR(SmallVirtualMachine *vm, instruction INSTR);
	 static int XORI(SmallVirtualMachine *vm, instruction INSTR);
	 static int COMPL(SmallVirtualMachine *vm, instruction INSTR);
	 static int shl(SmallVirtualMachine *vm, instruction INSTR);
	 static int shla(SmallVirtualMachine *vm, instruction INSTR);
	 static int shr(SmallVirtualMachine *vm, instruction INSTR);
	 static int shra(SmallVirtualMachine *vm, instruction INSTR);
	 static int compr(SmallVirtualMachine *vm, instruction INSTR);
	 static int compri(SmallVirtualMachine *vm, instruction INSTR);
	 static int getstat(SmallVirtualMachine *vm, instruction INSTR);
	 static int putstat(SmallVirtualMachine *vm, instruction INSTR);
	 static int jump(SmallVirtualMachine *vm, instruction INSTR);
	 static int jumpl(SmallVirtualMachine *vm, instruction INSTR);
	 static int jumpg(SmallVirtualMachine *vm, instruction INSTR);
	 static int jumpe(SmallVirtualMachine *vm, instruction INSTR);
	 static int call(SmallVirtualMachine *vm, instruction INSTR);
	 static int RETURN(SmallVirtualMachine *vm, instruction INSTR);
	 static int read(SmallVirtualMachine *vm, instruction INSTR);
	 static int write(SmallVirtualMachine *vm, instruction INSTR);
	 static int halt(SmallVirtualMachine *vm, instruction INSTR);
	 static int noop(SmallVirtualMachine *vm, instruction INSTR);
	 static int trap(SmallVirtualMachine *vm, instruction INSTR);

	 int r[REG_FILE_SIZE];		//general purpose registers
	 std::vector<unsigned int> mem;		//Memory
	 int pc;					//program counter
	 instruction ir;			//instruction register
	 status_register sr;		//status register
	 int sp;					//stack pointer
	 int clock;					//clock
	 int base;					//base of current program
	 int limit;					//limit of current program

	 AbstractIO *io;

	 //map of opcodes to function pointers,
	 //concatenating OP and I such that
	 //OP = bits 6:1 and I = bit 0, creates 
	 //a unique key to the map
	 std::map<int, FP> opcodes;
};

#endif //SMALLVIRTUALMACHINE_HPP
