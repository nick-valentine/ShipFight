#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <vector>
#include <string>

#include "Parameters.hpp"

class JsonObject
{
public:

  struct property
  {
    std::string label;
    std::string value;

    property() : label(""), value("")
    {
    }
    property(std::string l, std::string v) : label(l), value(v)
    {
    }
  };

  struct childJson
  {
    std::string label;
    JsonObject *value;

    childJson() : label(""), value(0)
    {
    }
    childJson(std::string l, JsonObject *v) : label(l), value(v)
    {
    }
  };

  property  invalid_property;
  childJson invalid_childJson;

  JsonObject();
  ~JsonObject();

  uint length();
  std::string get_key(uint i);
  bool is_direct_child(uint i);
  bool is_json(uint i);

  property &get_direct_child(uint i);
  childJson &get_json(uint i);

  void add_property(property p);
  void add_json(childJson j);

private:
  std::vector<childJson> objects;
  std::vector<property> properties;
};

#endif //JSONOBJECT_HPP
