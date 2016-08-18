#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "lib/StrFunc.hpp"
#include "lib/Pair.hpp"
#include "Json/JsonObject.hpp"

class JsonParser
{
public:
  JsonParser();

  JsonObject *parse(std::string json);
private:
  JsonObject *recursive_parse(std::vector<std::string> json);
  std::vector<std::string> separate_properties(std::string str);
  Pair<std::string,std::string> str_to_property(std::string str);
};

#endif //JSONPARSER_HPP
