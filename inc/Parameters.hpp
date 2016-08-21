#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#define uint unsigned int

struct uint16 {
  unsigned char f;
  unsigned char b;

  uint16(int x)
  {
    f = x & 0xFF00;
    b = x & 0x00FF;
  }
};

#endif //PARAMETERS_HPP
