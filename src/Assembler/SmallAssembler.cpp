#include "Assembler/SmallAssembler.hpp"

SmallAssembler::SmallAssembler() : AbstractAssembler()
{
  this->current_statement = 0;

  this->opcode_map["load"] = TranslationInformation(0,ADDRESS,0);
  this->opcode_map["loadi"] = TranslationInformation(0,CONSTANT,1);
  this->opcode_map["store"] = TranslationInformation(1,ADDRESS,0);
  this->opcode_map["add"] = TranslationInformation(2,REGISTER,0);
  this->opcode_map["addi"] = TranslationInformation(2,CONSTANT,1);
  this->opcode_map["addc"] = TranslationInformation(3,REGISTER,0);
  this->opcode_map["addci"] = TranslationInformation(3,CONSTANT,1);
  this->opcode_map["sub"] = TranslationInformation(4,REGISTER,0);
  this->opcode_map["subi"] = TranslationInformation(4,CONSTANT,1);
  this->opcode_map["subc"] = TranslationInformation(5,REGISTER,0);
  this->opcode_map["subci"] = TranslationInformation(5,CONSTANT,1);
  this->opcode_map["and"] = TranslationInformation(6,REGISTER,0);
  this->opcode_map["andi"] = TranslationInformation(6,CONSTANT,1);
  this->opcode_map["xor"] = TranslationInformation(7,REGISTER,0);
  this->opcode_map["xori"] = TranslationInformation(7,CONSTANT,1);
  this->opcode_map["compl"] = TranslationInformation(8,UNARY,0);
  this->opcode_map["shl"] = TranslationInformation(9,UNARY,0);
  this->opcode_map["shla"] = TranslationInformation(10,UNARY,0);
  this->opcode_map["shr"] = TranslationInformation(11,UNARY,0);
  this->opcode_map["shra"] = TranslationInformation(12,UNARY,0);
  this->opcode_map["compr"] = TranslationInformation(13,REGISTER,0);
  this->opcode_map["compri"] = TranslationInformation(13,CONSTANT,1);
  this->opcode_map["getstat"] = TranslationInformation(14,UNARY,0);
  this->opcode_map["putstat"] = TranslationInformation(15,UNARY,0);
  this->opcode_map["jump"] = TranslationInformation(16,ADDRESS,0);
  this->opcode_map["jumpl"] = TranslationInformation(17,ADDRESS,0);
  this->opcode_map["jumpe"] = TranslationInformation(18,ADDRESS,0);
  this->opcode_map["jumpg"] = TranslationInformation(19,ADDRESS,0);
  this->opcode_map["call"] = TranslationInformation(20,ADDRESS,0);
  this->opcode_map["return"] = TranslationInformation(21,NONE,0);
  this->opcode_map["read"] = TranslationInformation(22,UNARY,0);
  this->opcode_map["write"] = TranslationInformation(23,UNARY,0);
  this->opcode_map["halt"] = TranslationInformation(24,NONE,0);
  this->opcode_map["trap"] = TranslationInformation(25,CONSTANT,0);
  this->opcode_map["noop"] = TranslationInformation(26,NONE,0);
}

int SmallAssembler::translate_statement(std::string line)
{
  int return_val = 0;
  this->ss.clear();
  this->ss.str(line);
  std::string opcode;
  if( this->ss>>opcode ) {
    if(this->opcode_map.find(opcode) != this->opcode_map.end() ) {}
      switch(this->opcode_map[opcode].format) {
        case NONE:
          return_val = this->translate_none(this->opcode_map[opcode]);
          break;
        case REGISTER:
          return_val = this->translate_register(this->opcode_map[opcode]);
          break;
        case ADDRESS:
          return_val = this->translate_address(this->opcode_map[opcode]);
          break;
        case CONSTANT:
          return_val = this->translate_constant(this->opcode_map[opcode]);
          break;
        case UNARY:
          return_val = this->translate_unary(this->opcode_map[opcode]);
          break;
        default:
          std::cout<<"Opcode not found for: "<<opcode<<std::endl;
          return -1;
          break;
    };
    return int16mask(return_val);
  } else {
    std::cout<<"STRINSTREAM FAILED"<<std::endl;
    return -1;
  }
}

int SmallAssembler::translate_register(TranslationInformation op)
{
  int rd, rs;
  this->ss>>rd>>rs;
  operation x;
  x.i = 0;
  x.r.OP = op.opcode;
  x.r.RD = rd;
  x.r.I = op.immediate;
  x.r.RS = rs;

  return x.i;
}

int SmallAssembler::translate_address(TranslationInformation op)
{
  int rd, address;
  this->ss>>rd>>address;
  operation x;
  x.i = 0;
  x.a.OP = op.opcode;
  x.a.RD = rd;
  x.a.I = op.immediate;
  x.a.ADDR = address;

  return x.i;
}

int SmallAssembler::translate_constant(TranslationInformation op)
{
  int rd, constant;
  this->ss>>rd>>constant;
  operation x;
  x.i = 0;
  x.c.OP = op.opcode;
  x.c.RD = rd;
  x.c.I = op.immediate;
  x.c.CONST = constant;

  return x.i;
}

int SmallAssembler::translate_unary(TranslationInformation op)
{
  int rd;
  this->ss>>rd;
  operation x;
  x.i = 0;
  x.u.OP = op.opcode;
  x.u.RD = rd;

  return x.i;
}

int SmallAssembler::translate_none(TranslationInformation op)
{
  operation x;
  x.i = 0;
  x.n.OP = op.opcode;

  return x.i;
}
