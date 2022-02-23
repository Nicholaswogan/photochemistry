#include "yaml_tools.hpp"

void check_for_keys(const YAML::Node n, const std::string place, const std::vector<std::string> &keys)
{
  for (int j = 0; j < keys.size(); j++){
    if (!n[keys[j]]){
      throw Photochem::PhotoException(place+" does not contain key \""+keys[j]+"\"");
    }
  }
}

void check_for_keys(const YAML::Node n, const std::string place, const std::string key)
{
  if (!n[key]){
    throw Photochem::PhotoException(place+" does not contain key \""+key+"\"");
  }
}