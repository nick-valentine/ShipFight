#include "Json/JsonParser.hpp"

JsonParser::JsonParser()
{

}


JsonObject *JsonParser::parse(std::string json)
{
  JsonObject *return_val = 0;

  json = string::no_whitespace(json);
  std::vector<std::string> objects = string::explode(json,"{}[]",false);

  if( objects.size() == 0 ) {
    return return_val;
  }

  return_val = this->recursive_parse(objects);

  for (uint i = 0; i < return_val->length(); i++) {
    if(return_val->is_direct_child(i)) {
      std::cout<<return_val->get_direct_child(i).label<<": "<<return_val->get_direct_child(i).value<<std::endl;
    }
  }



  return new JsonObject();
}

JsonObject *JsonParser::recursive_parse(std::vector<std::string> json)
{
  JsonObject *return_val = new JsonObject;

  std::vector<std::string> subJSONLabels;
  std::vector<std::string> subJSON;
  std::vector<std::string> property;

  //separate subJSONs from parameters
  //sub JSONs will not start with commas
  //and never start on line one

  size_t iterator = 0;
  for(; iterator < json.size(); iterator++) {
    if(json[iterator].size() > 1) {
      property.push_back(json[iterator++]);
      break;
    }
  }

  for (; iterator < json.size(); iterator++) {
    if(json[iterator].size() > 1) {
      if(json[iterator][0] != ',') {
        std::vector<std::string> properties = this->separate_properties(json[iterator-1]);
        std::string label = string::explode(properties[properties.size()-1],':',false)[0];
        subJSONLabels.push_back(label);
        subJSON.push_back(json[iterator]);
      } else {
        property.push_back(json[iterator]);
      }
    }
  }

  for (size_t i = 0; i < subJSON.size(); i++) {
    std::cout<<subJSONLabels[i]<<" "<<subJSON[i]<<std::endl;
  }
  std::cout<<std::endl;
  for (size_t i = 0; i < property.size(); i++) {
    std::cout<<property[i]<<std::endl;
  }
  exit(1);

  //parse subJSONs
  for (size_t i = 0; i < subJSON.size(); i++) {
    std::vector<std::string> push_value;
    push_value.push_back(subJSON[i]);
    return_val->add_json(
      JsonObject::childJson(
        subJSONLabels[i],
        this->recursive_parse(
          push_value
        )
      )
    );
  }

  //separate and parse direct children parameters
  for (size_t i = 0; i < property.size(); i++) {
    std::vector<std::string> properties = this->separate_properties(property[i]);
    for (size_t i = 0; i < properties.size(); i++) {
      Pair<std::string,std::string> property = this->str_to_property(properties[i]);
      return_val->add_property(
        JsonObject::property(
          property.get_first(),
          property.get_second()
        )
      );
    }
  }

  return return_val;
}

std::vector<std::string> JsonParser::separate_properties(std::string str)
{
  return string::explode(str, ',',false);
}

Pair<std::string,std::string> JsonParser::str_to_property(std::string str)
{
  std::vector<std::string> arr = string::explode(str,':',false);
  if( arr.size() == 2 ) {
    return Pair<std::string,std::string>(arr[0],arr[1]);
  } else {
    return Pair<std::string,std::string>("","");
  }
}
