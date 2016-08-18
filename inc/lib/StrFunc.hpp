#ifndef STRFUNC_HPP
#define STRFUNC_HPP

#include <string>
#include <vector>

#include "lib/VecFunc.hpp"

namespace string
{
  std::string implode(std::vector<std::string> arr, char delim);
  std::vector<std::string> explode(std::string str, char delim, bool ignore_quotes = true);
  std::vector<std::string> explode(std::string str, std::string delims, bool ignore_quotes = true);

  std::string no_whitespace(std::string str);
}

#endif //STRFUNC_HPP
