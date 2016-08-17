#include "../../inc/lib/StrFunc.hpp"

namespace string
{
  std::string implode(std::vector<std::string> arr, char delim)
  {
    std::string return_val;

    if( arr.size() > 0 ) {
      return_val = arr[0];
      for(int i = 1; i < arr.size(); ++i) {
        return_val = return_val + delim + arr[i];
      }
    }

    return return_val;
  }

  std::vector<std::string> explode(std::string str, char delim)
  {
    std::vector<std::string> return_val;

    int position = str.find(delim);
    while(position != std::string::npos) {
      return_val.push_back(str.substr(0, position));
      str = str.substr(position+1);
      position = str.find(delim);
    }
    return_val.push_back(str);

    return return_val;
  }

  std::vector<std::string> explode(std::string str, std::string delims)
  {
    std::vector<char> d;
    for(int i = 0; i < delims.size(); ++i) {
      d.push_back(delims[i]);
    }

    std::vector<std::string> return_val;

    int last_cut = 0;
    for(int i = 0; i < str.size(); ++i) {
      if(vector::in(d, str[i])) {
        return_val.push_back(str.substr(last_cut,i - last_cut));
        last_cut = i+1;
      }
    }
    return_val.push_back(str.substr(last_cut));

    return return_val;
  }
}
