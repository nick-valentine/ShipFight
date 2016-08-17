#ifndef STRFUNC_HPP
#define STRFUNC_HPP

#include <string>
#include <vector>

#include "VecFunc.hpp"

namespace string
{
  std::string implode(std::vector<std::string> arr, char delim);
  std::vector<std::string> explode(std::string str, char delim);
  std::vector<std::string> explode(std::string str, std::string delims);
}

#endif //STRFUNC_HPP
