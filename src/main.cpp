#include <iostream>
#include <string>
#include <vector>

#include "Parameters.hpp"
#include "lib/Helper.hpp"
#include "lib/VecFunc.hpp"
#include "lib/StrFunc.hpp"
#include "Assembler/AbstractAssembler.hpp"
#include "Assembler/SmallAssembler.hpp"
#include "VirtualMachine/SmallVirtualMachine.hpp"

int main()
{
  SmallAssembler my_asm;
  std::vector<std::string> p;
  p.push_back("loadi 1 22");
  p.push_back("loadi 1 10");
  p.push_back("addi 1 5");
  p.push_back("store 1 6");
  p.push_back("write 1");
  p.push_back("halt");
  p.push_back("noop");

  std::vector<unsigned int> o_file = my_asm.translate_program(p);

  for (size_t i = 0; i < o_file.size(); i++) {
    print_binary(o_file[i]);
    std::cout<<" "<<o_file[i]<<std::endl;
  }

  std::cout<<"\n\n\n";

  SmallVirtualMachine my_vm;
  unsigned int base = 0,offset = 0;
  my_vm.Load(base,offset,o_file);
  my_vm.Run();

  return 0;
}
