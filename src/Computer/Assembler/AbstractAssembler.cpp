#include "Assembler/AbstractAssembler.hpp"

AbstractAssembler::AbstractAssembler()
{

}

AbstractAssembler::~AbstractAssembler()
{

}

std::vector<unsigned int> AbstractAssembler::translate_program(std::vector<std::string> assembly_program)
{
  std::vector<unsigned int> return_val;

  for(uint i = 0; i < assembly_program.size(); ++i) {
    int operation = this->translate_statement(assembly_program[i]);
    if( operation != -1 ) {
      return_val.push_back(operation);
    } else {
      return std::vector<unsigned int>();
    }
  }

  return return_val;
}
