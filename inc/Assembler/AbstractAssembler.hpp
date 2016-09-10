#ifndef ABSTRACTASSEMBLER_HPP
#define ABSTRACTASSEMBLER_HPP

#include <vector>
#include <string>

#include "Parameters.hpp"
#include "lib/Helper.hpp"

class AbstractAssembler
{
public:
  AbstractAssembler();
  virtual ~AbstractAssembler();

  //this function must self iterate
  virtual int translate_statement(std::string line) = 0;

  std::vector<unsigned int> translate_program(std::vector<std::string> assembly_program);
};

#endif //ABSTRACTASSEMBLER_HPP
