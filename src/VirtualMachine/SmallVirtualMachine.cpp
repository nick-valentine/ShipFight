#include "VirtualMachine/SmallVirtualMachine.hpp"

SmallVirtualMachine::SmallVirtualMachine()
{
	this->init(256, 10000,0);
}

SmallVirtualMachine::SmallVirtualMachine(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io)
{
	this->init(mem_size, clock_speed, io);
}

void SmallVirtualMachine::init(unsigned int mem_size, unsigned int clock_speed, AbstractIO *io)
{
	this->mem_size = mem_size;
	this->clock_speed = clock_speed;
	this->mem = std::vector<unsigned int>(mem_size,0);

	this->io = io;

	//init pcb
	for(unsigned int i = 0; i < REG_FILE_SIZE; ++i) {
		r[i] = 0;
	}
	pc = 0;
	ir.i = 0;
	sr.i = 0;
	sp = 0;
	clock = 0;
	base = 0;
	limit = 0;

	opcodes[0] = &load;		//00000 0
	opcodes[1] = &loadi;	//00000 1
	opcodes[2] = &store;	//00001 0	
	opcodes[4] = &add;		//00010 0
	opcodes[5] = &addi;		//00010 1
	opcodes[6] = &addc;		//00011 0
	opcodes[7] = &addci;	//00011 1
	opcodes[8] = &sub;		//00100 0
	opcodes[9] = &subi;		//00100 1
	opcodes[10] = &subc;	//00101 0
	opcodes[11] = &subci;	//00101 1
	opcodes[12] = &AND;		//00110 0
	opcodes[13] = &ANDI;	//00110 1
	opcodes[14] = &XOR;		//00111 0
	opcodes[15] = &XORI;	//00111 1
	opcodes[16] = &COMPL;	//01000 0
	opcodes[18] = &shl;		//01001 0
	opcodes[20] = &shla;	//01010 0
	opcodes[22] = &shr;		//01011 0
	opcodes[24] = &shra;	//01100 0
	opcodes[26] = &compr;	//01101 0
	opcodes[27] = &compri;	//01101 1
	opcodes[28] = &getstat; //01110 0
	opcodes[30] = &putstat; //01111 0
	opcodes[32] = &jump;	//10000 0
	opcodes[34] = &jumpl;	//10001 0
	opcodes[36] = &jumpe;	//10010 0
	opcodes[38] = &jumpg;	//10011 0
	opcodes[40] = &call;	//10100 0
	opcodes[42] = &RETURN;	//10101 0
	opcodes[44] = &read;	//10110 0
	opcodes[46] = &write;	//10111 0
	opcodes[48] = &halt;	//11000 0
	opcodes[50] = &noop;	//11001 0
	opcodes[52] = &trap;	//11010 0
	
}

int SmallVirtualMachine::Load(unsigned int base, unsigned int &offset, std::vector<unsigned int> program)
{
	if( base >= 0 && base < this->mem_size) {
		for(unsigned int i = 0; i < program.size(); ++i) {
			if (i+base < mem_size) {
				this->mem[i+base] = program[i];
			} else {
				return OUTOFRANGE;
			}
		}
		offset = base + program.size();
		this->base = base;
		this->limit = offset;
		this->pc = base;

		return NONE;
	} else {
		return INVALIDBASE;
	}
}

int SmallVirtualMachine::Run()
{
	while(true) {
		this->ir.i = this->mem[this->pc];
		this->pc++;
		int lookup = (this->ir.f1.OP << 1) + (this->ir.f1.I);

		if(this->opcodes.find(lookup) == this->opcodes.end()) {
			//opcode not found
			std::cout<<"Opcode not found"<<std::endl;
			return 1;
		}
		int ErrorNo = this->opcodes[lookup](this,ir);

		if(ErrorNo == 0) {
			return 0;
		} else if(ErrorNo == -1) {
			return 0;
		}
	}
}

int SmallVirtualMachine::load(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_2 f = INSTR.f2;
	if(f.ADDR >= vm->base && f.ADDR <= vm->base + vm->limit) {
		vm->r[f.RD] = vm->mem[f.ADDR];
		vm->clock += 4;
		return 1;
	}
	//error: address out of range
	return 0;
}

int SmallVirtualMachine::loadi(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	vm->r[f.RD] = f.CONST;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::store(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_2 f = INSTR.f2;
	if(f.ADDR >= vm->base && f.ADDR <= vm->base + vm->limit) {
		vm->mem[f.ADDR] = vm->r[f.RD];
		vm->clock += 4;
		return 1;
	} else {
		//error: address out of range
		return 0;
	}
}

int SmallVirtualMachine::add(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] + vm->r[f.RS];
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::addi(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	int result = vm->r[f.RD] + f.CONST;
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::addc(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] + vm->r[f.RS] + vm->sr.sr.carry;
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::addci(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	int result = vm->r[f.RD] + f.CONST + vm->sr.sr.carry;
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::sub(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] - vm->r[f.RS];
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::subi(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	int result = vm->r[f.RD] - f.CONST;
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::subc(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] - vm->r[f.RS] - vm->sr.sr.carry;
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::subci(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	int result = vm->r[f.RD] - f.CONST - vm->sr.sr.carry;
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::AND(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	vm->r[f.RD] = vm->r[f.RD] & vm->r[f.RS];
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::ANDI(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	vm->r[f.RD] = vm->r[f.RD] & f.CONST;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::XOR(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	vm->r[f.RD] = vm->r[f.RD] ^ vm->r[f.RS];
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::XORI(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	vm->r[f.RD] = vm->r[f.RD] ^ f.CONST;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::COMPL(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	vm->r[f.RD] = ~vm->r[f.RD];
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::shl(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] << 1;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::shla(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] << 1;
	result = (vm->r[f.RD] & 0x0080) > 0 ? result | 0x0080 : result & ~0x0080;
	vm->r[f.RD] = result;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::shr(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] >> 1;
	vm->sr.sr.carry = (vm->r[f.RD] & 1) > 0;
	vm->r[f.RD] = result;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::shra(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	int result = vm->r[f.RD] >> 1;
	result = (vm->r[f.RD] & 0x0080) > 0 ? result & ~0x0080 : result | 0x0080;
	vm->r[f.RD] = result;
	vm->sr.sr.carry = (result & 0x0100) > 0;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::compr(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	vm->sr.sr.equal = 0;
	vm->sr.sr.greater = 0;
	vm->sr.sr.less = 0;
	if(vm->r[f.RD] > vm->r[f.RS]) vm->sr.sr.greater = 1;
	else if(vm->r[f.RD] < vm->r[f.RS]) vm->sr.sr.less = 1;
	else vm->sr.sr.equal = 1;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::compri(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_3 f = INSTR.f3;
	vm->sr.sr.equal = 0;
	vm->sr.sr.greater = 0;
	vm->sr.sr.less = 0;
	if(vm->r[f.RD] > f.CONST) vm->sr.sr.greater = 1;
	else if(vm->r[f.RD] < f.CONST) vm->sr.sr.less = 1;
	else vm->sr.sr.equal = 1;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::getstat(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	vm->r[f.RD] = vm->sr.i;
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::putstat(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_1 f = INSTR.f1;
	vm->sr.i = vm->r[f.RD];
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::jump(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_2 f = INSTR.f2;
	if(f.ADDR >= vm->base && f.ADDR < vm->base + vm->limit) {
		vm->pc = f.ADDR;
		vm->clock += 1;
		return 1;
	} else {
		//error: address out of range
		return 0;
	}
}

int SmallVirtualMachine::jumpl(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_2 f = INSTR.f2;
	if(f.ADDR >= vm->base && f.ADDR < vm->base + vm->limit) {
		if(vm->sr.sr.less) vm->pc = f.ADDR;
		vm->clock += 1;
		return 1;
	} else {
		//error: address out of range
		return 0;
	}
}

int SmallVirtualMachine::jumpe(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_2 f = INSTR.f2;
	if(f.ADDR >= vm->base && f.ADDR < vm->base + vm->limit) {
		if(vm->sr.sr.equal) vm->pc = f.ADDR;
		vm->clock += 1;
		return 1;
	} else {
		//error: address out of range
		return 0;
	}
}

int SmallVirtualMachine::jumpg(SmallVirtualMachine *vm, instruction INSTR)
{
	instr_format_2 f = INSTR.f2;
	if(f.ADDR >= vm->base && f.ADDR < vm->base + vm->limit) {
		if(vm->sr.sr.greater) vm->pc = f.ADDR;
		vm->clock += 1;
		return 1;
	} else {
		//error: address out of range
		return 0;
	}
}

int SmallVirtualMachine::call(SmallVirtualMachine *vm, instruction INSTR)
{
	if(vm->sp < vm->limit + vm->REG_FILE_SIZE + 2) {
		//stack overflow
		return 0;
	}

	instr_format_2 f = INSTR.f2;
	if(f.ADDR >= vm->base && f.ADDR <= vm->base + vm->limit) {
		//save state
		vm->mem[--vm->sp] = vm->pc;
		vm->mem[--vm->sp] = vm->sr.i;
		for( int i = vm->REG_FILE_SIZE - 1; i >= 0; --i ) {
			vm->mem[--vm->sp] = vm->r[i];
		}

		vm->pc = f.ADDR;
		vm->clock += 4;
		return 1;
	} else {
		//error: address out of range
		return 0;
	}
}

int SmallVirtualMachine::RETURN(SmallVirtualMachine *vm, instruction INSTR)
{
	if(vm->sp >= vm->mem_size) {
		//stack underflow
		return 0;
	}

	for(int i = 0; i < vm->REG_FILE_SIZE; ++i) {
		vm->r[i] = vm->mem[vm->sp++];
	}
	vm->sr.i = vm->mem[vm->sp++];
	vm->pc = vm->mem[vm->sp++];

	vm->clock += 4;
	return 1;
}

int SmallVirtualMachine::read(SmallVirtualMachine *vm, instruction INSTR)
{
	std::cout<<"Reading";
	if( vm->io != 0 ) {
		instr_format_1 f = INSTR.f1;
		char x;
		x = vm->io->getch();
		//std::cin>>x;
		int16 readValue;
		readValue.i = x;
		vm->r[f.RD] = readValue.i16.low;

		vm->clock += 28;
		return 1;
	} else {
		//error: no io interface present
		return 0;
	}
}

int SmallVirtualMachine::write(SmallVirtualMachine *vm, instruction INSTR)
{
	if( vm->io != 0 ) {
		instr_format_1 f = INSTR.f1;
		int16 writeValue;
		writeValue.i = vm->r[f.RD];
		//std::cout<<writeValue.i16.low;
		vm->io->putch((char)writeValue.i16.low);

		vm->clock += 28;
		return 1;
	} else {
		//error: no io interface present
		return 0;
	}
}

int SmallVirtualMachine::halt(SmallVirtualMachine *vm, instruction INSTR)
{
	vm->clock += 1;
	return 0;
}

int SmallVirtualMachine::noop(SmallVirtualMachine *vm, instruction INSTR)
{
	vm->clock += 1;
	return 1;
}

int SmallVirtualMachine::trap(SmallVirtualMachine *vm, instruction INSTR)
{
	//@todo: implement trap interface
	return 1;
}
