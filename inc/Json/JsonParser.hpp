#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <string>
#include <vector>

#include "../lib/StrFunc.hpp"
#include "JsonObject.hpp"

class JsonParser
{
private:

public:
  JsonParser();

  JsonObject parse(std::string json);
};

#endif //JSONPARSER_HPP
