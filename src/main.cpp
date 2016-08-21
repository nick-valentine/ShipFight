#include <iostream>
#include <string>
#include <vector>

#include "Parameters.hpp"
#include "Helper.hpp"
#include "lib/VecFunc.hpp"
#include "lib/StrFunc.hpp"
#include "Assembler/AbstractAssembler.hpp"
#include "Assembler/SmallAssembler.hpp"

void print_binary(int x)
{
  for(int i = 31; i >= 0; --i){
    std::cout<<((x & (1<<i))?1:0);
    if(i == 11 || i == 16) {
      std::cout<<" ";
    }
  }
}

int main()
{
  SmallAssembler my_asm;
  std::vector<std::string> p;
  p.push_back("load 1 69");
  p.push_back("loadi 1 10");
  p.push_back("addi 1 5");
  p.push_back("store 1 4");
  p.push_back("halt");
  p.push_back("noop");

  std::vector<int> o_file = my_asm.translate_program(p);

  for (size_t i = 0; i < o_file.size(); i++) {
    print_binary(o_file[i]);
    std::cout<<" "<<o_file[i]<<std::endl;
  }

  return 0;
}
