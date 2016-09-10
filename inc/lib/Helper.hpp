#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>

typedef unsigned int uint; 

struct uint16 {
  unsigned char f;
  unsigned char b;

  uint16(int x)
  {
    f = (x & 0xFF00) >> 8;
    b = x & 0x00FF;
  }
};

int int16mask(int x);

void print_binary(int x);

#endif //HELPER_HPP
