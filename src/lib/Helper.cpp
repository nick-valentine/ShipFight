#include "lib/Helper.hpp"

int int16mask(int x)
{
  return x & 0xFFFF;
}

void print_binary(int x)
{
  for(int i = 31; i >= 0; --i){
    std::cout<<((x & (1<<i))?1:0);
    if(i == 11 || i == 16) {
      std::cout<<" ";
    }
  }
}

