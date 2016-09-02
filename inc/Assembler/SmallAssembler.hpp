#ifndef SMALLASSEMBLER_HPP
#define SMALLASSEMBLER_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <stdlib.h>

#include "Parameters.hpp"
#include "lib/Helper.hpp"
#include "Assembler/AbstractAssembler.hpp"

class SmallAssembler : public AbstractAssembler
{
public:
  SmallAssembler();

  virtual int translate_statement(std::string line);
private:

  enum FormatIdentifier {
    NONE = 0,
    REGISTER = 1,
    ADDRESS = 2,
    CONSTANT = 3,
    UNARY = 4
  };

  struct TranslationInformation {
    int opcode;
    FormatIdentifier format;
    bool immediate;

    TranslationInformation()
    {
      opcode = 0;
      format = NONE;
      immediate = 0;
    }
    TranslationInformation(int o, FormatIdentifier f, bool i) : opcode(o), format(f), immediate(i)
    {
    }
  };

  struct Register {
    unsigned int UNUSED : 6;
    unsigned int RS : 2;
    unsigned int I : 1;
    unsigned int RD : 2;
    unsigned int OP : 5;
    unsigned int : 16;
  };

  struct Address {
    unsigned int ADDR : 8;
    unsigned int I : 1;
    unsigned int RD : 2;
    unsigned int OP : 5;
    unsigned int : 16;
  };

  struct Constant {
    unsigned int CONST : 8;
    unsigned int I : 1;
    unsigned int RD : 2;
    unsigned int OP : 5;
    unsigned int : 16;
  };

  struct Unary {
    unsigned int UNUSED : 9;
    unsigned int RD : 2;
    unsigned int OP : 5;
    unsigned int : 16;
  };

  struct None {
    unsigned int UNUSED : 11;
    unsigned int OP : 5;
    unsigned int : 16;
  };

  union operation {
    unsigned int i;
    Register r;
    Address a;
    Constant c;
    Unary u;
    None n;
  };

  int current_statement;
  std::map<std::string, TranslationInformation> opcode_map;
  std::stringstream ss;

  int translate_register(TranslationInformation op);
  int translate_address(TranslationInformation op);
  int translate_constant(TranslationInformation op);
  int translate_unary(TranslationInformation op);
  int translate_none(TranslationInformation op);
};

#endif //SMALLASSEMBLER_HPP
