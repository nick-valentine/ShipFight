#ifndef VECFUNC_HPP
#define VECFUNC_HPP

#include <vector>

#include "Parameters.hpp"

namespace vector
{
  template<typename T>
  bool in(std::vector<T> vec, T val)
  {
    for(uint i = 0; i < vec.size(); ++i) {
      if(vec[i] == val) {
        return true;
      }
    }
    return false;
  }
}

#endif //VECFUNC_HPP
