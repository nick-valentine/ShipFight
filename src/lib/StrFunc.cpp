#include "lib/StrFunc.hpp"

namespace string
{
  /**
   * implode a string around a delimiter
   * @param  arr   vector of strings to be imploded
   * @param  delim delimiter to place between elements in vector
   * @return       imploded string
   */
  std::string implode(std::vector<std::string> arr, char delim)
  {
    std::string return_val;

    if( arr.size() > 0 ) {
      return_val = arr[0];
      for(uint i = 1; i < arr.size(); ++i) {
        return_val = return_val + delim + arr[i];
      }
    }

    return return_val;
  }

  std::vector<std::string> explode(std::string str, char delim, bool ignore_quotes)
  {
    std::vector<std::string> return_val;

    bool in_quotes = false;

    int start_cut = 0;
    int last_cut = 0;

    bool delim_at_end = false;

    for (size_t i = 0; i < str.size(); ++i) {

      if(str[i] == '\"' || str[i] == '\'') {
        in_quotes = !in_quotes;
      }

      if( !in_quotes || ignore_quotes ) {
        if(str[i] == delim) {
          start_cut = i;
          while( str[i+1] == delim && i < str.size() ) {
            ++i;
            delim_at_end = true;
          }
          return_val.push_back(str.substr(last_cut, start_cut - last_cut));
          last_cut = i+1;
        }
      }
    }
    if(!delim_at_end) {
      return_val.push_back(str.substr(last_cut));
    }

    return return_val;
  }

  std::vector<std::string> explode(std::string str, std::string delims, bool ignore_quotes)
  {
    std::vector<char> d;
    for(uint i = 0; i < delims.size(); ++i) {
      d.push_back(delims[i]);
    }

    std::vector<std::string> return_val;

    bool in_quotes = false;

    int start_cut = 0;
    int last_cut = 0;
    bool delim_at_end = false;

    for(size_t i = 0; i < str.size(); ++i) {

      if(str[i] == '\"' || str[i] == '\'') {
        in_quotes = !in_quotes;
      }

      if( !in_quotes || ignore_quotes ) {
        if(vector::in(d, str[i])) {
          start_cut = i;
          while(vector::in(d,str[i+1]) && i < str.size()) {
            ++i;
            delim_at_end = true;
          }
          return_val.push_back(str.substr(last_cut,start_cut - last_cut));
          last_cut = i+1;
        }
      }
    }
    if(!delim_at_end) {
      return_val.push_back(str.substr(last_cut));
    }

    return return_val;
  }

  /**
   * [no_whitespace: remove whitespace that is not in parenthesis]
   * @param  str string to be cleaned
   * @return     string without whitespace
   */
  std::string no_whitespace(std::string str)
  {
    std::string return_val;

    bool in_quotes = false;

    for (size_t i = 0; i < str.size(); i++) {
      if( !in_quotes ) {
        if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
          //do nothing
        } else {
          return_val.push_back(str[i]);
        }
      } else {
        //if in parens, still append white space
        return_val.push_back(str[i]);
      }
      if(str[i] == '\"' || str[i] == '\'') {
        in_quotes = !in_quotes;
      }
    }

    return return_val;
  }
}
