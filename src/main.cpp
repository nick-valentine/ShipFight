#include <iostream>
#include <string>

#include "Parameters.hpp"
#include "lib/VecFunc.hpp"
#include "lib/StrFunc.hpp"
#include "Assembler/AbstractAssembler.hpp"
#include "Assembler/AssemblerFromFile.hpp"
#include "Json/JsonParser.hpp"
#include "Json/JsonObject.hpp"

int main()
{
  std::string a = "hello, \"how, are\". you";

  std::vector<std::string> b = string::explode(a," ,.", false);

  for(uint i = 0; i < b.size(); ++i) {
    std::cout<<b[i]<<"\n";
  }
  std::cout<<std::endl;

  std::cout<<string::implode(b,'|')<<std::endl;

  std::cout<<vector::in(b,std::string("hello"))<<std::endl;

  JsonParser jparse;
  JsonObject *json = jparse.parse("{a:hello,b:{c:\"goodbye:{apples:cheese} there\",d:{e:apples},l:{a:v}}}");

  return 0;
}
