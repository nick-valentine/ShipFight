#ifndef SMALLVIRTUALMACHINE_HPP
#define SMALLVIRTUALMACHINE_HPP

#include <vector>
#include <map>

class SmallVirtualMachine
{
 public:
	 //@todo: add Computer class to allow for reading and writing interface
	SmallVirtualMachine();
	SmallVirtualMachine(unsigned int mem_size, unsigned int clock_speed);


	/**
	 * Loads a program into memory
	 * @param[out] base starting address of program loaded
	 * @param[out] end ending address of program loaded
	 * @param[in] program program to load
	 * @return error code
	 */
	int Load(int &base, std::vector<int> program);

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

	struct insr_format_1
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
	typedef int(*FP) (VirtualMachine *vm, instruction INSTR);
	
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

	 static int load(VirtualMachine *vm, instruction INSTR);
	 static int loadi(VirtualMachine *vm, instruction INSTR);
	 static int store(VirtualMachine *vm, instruction INSTR);
	 static int add(VirtualMachine *vm, instruction INSTR);
	 static int addi(VirtualMachine *vm, instruction INSTR);
	 static int addc(VirtualMachine *vm, instruction INSTR);
	 static int addci(VirtualMachine *vm, instruction INSTR);
	 static int sub(VirtualMachine *vm, instruction INSTR);
	 static int subi(VirtualMachine *vm, instruction INSTR);
	 static int subc(VirtualMachine *vm, instruction INSTR);
	 static int subci(VirtualMachine *vm, instruction INSTR);
	 static int AND(VirtualMachine *vm, instruction INSTR);
	 static int ANDI(VirtualMachine *vm, instruction INSTR);
	 static int XOR(VirtualMachine *vm, instruction INSTR);
	 static int XORI(VirtualMachine *vm, instruction INSTR);
	 static int COMPL(VirtualMachine *vm, instruction INSTR);
	 static int shl(VirtualMachine *vm, instruction INSTR);
	 static int shla(VirtualMachine *vm, instruction INSTR);
	 static int shr(VirtualMachine *vm, instruction INSTR);
	 static int shra(VirtualMachine *vm, instruction INSTR);
	 static int compr(VirtualMachine *vm, instruction INSTR);
	 static int compri(VirtualMachine *vm, instruction INSTR);
	 static int getstat(VirtualMachine *vm, instruction INSTR);
	 static int putstat(VirtualMachine *vm, instruction INSTR);
	 static int jump(VirtualMachine *vm, instruction INSTR);
	 static int jumpl(VirtualMachine *vm, instruction INSTR);
	 static int jumpg(VirtualMachine *vm, instruction INSTR);
	 static int jumpe(VirtualMachine *vm, instruction INSTR);
	 static int call(VirtualMachine *vm, instruction INSTR);
	 static int RETURN(VirtualMachine *vm, instruction INSTR);
	 static int read(VirtualMachine *vm, instruction INSTR);
	 static int write(VirtualMachine *vm, instruction INSTR);
	 static int halt(VirtualMachine *vm, instruction INSTR);
	 static int noop(VirtualMachine *vm, instruction INSTR);
	 static int trap(VirtualMachine *vm, instruction INSTR);

	 int r[REG_FILE_SIZE];		//general purpose registers
	 std::vector<int> mem;		//Memory
	 int pc;					//program counter
	 instruction ir;			//instruction register
	 status_register sr;		//status register
	 int sp;					//stack pointer
	 int clock;					//clock
	 int base;					//base of current program
	 int limit;					//limit of current program

	 //map of opcodes to function pointers,
	 //concatenating OP and I such that
	 //OP = bits 6:1 and I = bit 0, creates 
	 //a unique key to the map
	 std::map<int, FP> opcodes;
};

#endif //SMALLVIRTUALMACHINE_HPP
