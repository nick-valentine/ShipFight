#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <vector>
#include <utility> //std::pair
#include <string>

#include "../Parameters.hpp"

class JsonObject
{
public:
  typedef std::pair<std::string,std::string> property;
  typedef std::pair<std::string,JsonObject> childJson;
private:
  std::vector<childJson> objects;
  std::vector<property> properties;
public:
  JsonObject();
  ~JsonObject();

  int length();
  std::string get_key(uint i);
  bool is_direct_child(uint i);
  bool is_json(uint i);

  property &get_direct_child(uint i);
  childJson &get_json(uint i);

  void add_property(property p);
  void add_json(childJson j);
};

#endif //JSONOBJECT_HPP
