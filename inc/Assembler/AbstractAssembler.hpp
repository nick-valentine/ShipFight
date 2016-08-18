#ifndef ABSTRACTASSEMBLER_HPP
#define ABSTRACTASSEMBLER_HPP

#include <vector>
#include <map>
#include <string>

#include "Parameters.hpp"

class AbstractAssembler
{
protected:
  std::map<std::string /* instruction */, int /* opcode */> opcode_map;
public:
  AbstractAssembler();

  //this function must self iterate
  virtual int translate_statement() = 0;

  std::vector<int> translate_program(std::vector<std::string> assembly_program);
};

#endif //ABSTRACTASSEMBLER_HPP
