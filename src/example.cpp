#include "example.h"
#include "yaml-cpp/yaml.h"


double MyClass::sum_arr()
{  
  return xt::sum(arr)();  
}


void check_key(const YAML::Node &n, const std::string &key){
  if (!n[key])
  {
    // throw PhotoException(filename+" is missing key atmos");
  }
}

void read_stuff()
{
  YAML::Node file;
  std::string filename = "../photochemistry/data/reaction_mechanisms/zahnle_earth.yaml";
  file = YAML::LoadFile(filename);
  
  
  if (!file["atoms"]){throw PhotoException(filename+" is missing key atmos");}
  // YAML::Node atmos = 
  
  // for (YAML::const_iterator it=file.begin(); it != file.end(); ++it){
  //   std::string key = it->first.as<std::string>();
  //   std::cout << key << std::endl;
  // }
  
}