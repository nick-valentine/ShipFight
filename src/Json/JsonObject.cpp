#include "../../inc/Json/JsonObject.hpp"

JsonObject::JsonObject()
{
  this->objects = std::vector<childJson>();
  this->properties = std::vector<property>();
}

JsonObject::~JsonObject()
{

}

int JsonObject::length()
{
  return this->objects.size() + this->properties.size();
}

std::string JsonObject::get_key(uint i)
{
  if( i > 0 ) {
    if( i < this->objects.size() ) {
      return this->objects[i].first;
    } else if( i < this->objects.size() + this->properties.size() ) {
      i -= this->objects.size();
      return this->properties[i].first;
    }
  }
  return "Invalid key provided";
}

bool JsonObject::is_direct_child(uint i)
{
  if( i > this->objects.size() ) {
    i-=this->objects.size();
    if( i < this->properties.size() ) {
      return true;
    }
  }
  return false;
}

bool JsonObject::is_json(uint i)
{
  if( i > 0 && i < this->objects.size() ) {
    return true;
  } else {
    return false;
  }
}

JsonObject::property &JsonObject::get_direct_child(uint i)
{
  if( this->is_direct_child(i) ) {
    return this->properties[i];
  }
}

JsonObject::childJson &JsonObject::get_json(uint i)
{
  if( this->is_json(i) ) {
    return this->objects[i];
  }
}

void JsonObject::add_property(property p)
{
  this->properties.push_back(p);
}

void JsonObject::add_json(childJson j)
{
  this->objects.push_back(j);
}
