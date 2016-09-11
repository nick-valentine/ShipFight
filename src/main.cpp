#include <iostream>
#include <string>
#include <vector>

#include "Computer/SmallComputer.hpp"
#include "Computer/ScreenIO/LinuxIO.hpp"

int main()
{
  AbstractIO *io = new LinuxIO();
  SmallComputer comp(256,10000,io);
  comp.Run();

  delete io;

  return 0;
}
