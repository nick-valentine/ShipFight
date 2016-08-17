#include <iostream>
#include <string>

#include "../inc/Parameters.hpp"
#include "../inc/lib/VecFunc.hpp"
#include "../inc/lib/StrFunc.hpp"
#include "../inc/Assembler/AbstractAssembler.hpp"
#include "../inc/Assembler/AssemblerFromFile.hpp"
#include "../inc/Json/JsonParser.hpp"
#include "../inc/Json/JsonObject.hpp"

int main()
{
  std::string a = "hello, how. are, you";

  std::vector<std::string> b = string::explode(a," .,");

  for(uint i = 0; i < b.size(); ++i) {
    std::cout<<b[i]<<"\n";
  }
  std::cout<<std::endl;

  std::cout<<string::implode(b,'|')<<std::endl;

  std::cout<<vector::in(b,std::string(" how"))<<std::endl;

  return 0;
}
