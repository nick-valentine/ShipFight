#include "../../inc/Assembler/AbstractAssembler.hpp"

AbstractAssembler::AbstractAssembler()
{

}

std::vector<int> AbstractAssembler::translate_program(std::vector<std::string> assembly_program)
{
  std::vector<int> return_val;

  for(uint i = 0; i < assembly_program.size(); ++i) {
    return_val.push_back(this->translate_statement());
  }

  return return_val;
}
