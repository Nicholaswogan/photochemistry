#include "example.h"
#include "yaml-cpp/yaml.h"


double MyClass::sum_arr()
{  
  return xt::sum(arr)();  
}

namespace Photochem {
  

void check_for_keys(YAML::Node n, std::string place, std::vector<std::string> &keys)
{
  for (int j = 0; j < keys.size(); j++){
    if (!n[keys[j]]){
      throw PhotoException(place+" does not contain key \""+keys[j]+"\"");
    }
  }
}

void check_for_key(YAML::Node n, std::string place, std::string key)
{
  if (!n[key]){
    throw PhotoException(place+" does not contain key \""+key+"\"");
  }
}
  
  

void read_stuff()
{
  PhotoData d;
  
  YAML::Node file;
  std::string filename = "../photochemistry/data/reaction_mechanisms/zahnle_earth.yaml";
  try{
    file = YAML::LoadFile(filename);
  }
  catch (YAML::BadFile& e) {
    throw PhotoException(filename+" does not exist.");
  }
  
  // Read all data
  try{
  
  
  { // atoms
  
  check_for_key(file, filename+"/", "atoms");
  YAML::Node a = file["atoms"];
  
  std::vector<std::string> keys = {"name", "mass", "redox"};
  d.natoms = a.size();
  d.atoms.resize(d.natoms);
  for (int i = 0; i < a.size(); i++){
    check_for_keys(a[i], filename+"/atoms["+std::to_string(i)+"]", keys);
    
    d.atoms[i].name = a[i]["name"].as<std::string>();
    d.atoms[i].mass = a[i]["mass"].as<real>();
    d.atoms[i].redox = a[i]["redox"].as<real>();
  } 
  
  } // end atoms
  
  { // species
  
  check_for_key(file, filename+"/", "species");
  YAML::Node s = file["species"];
  
  std::vector<std::string> keys = {"name", "composition", "thermo"};
  d.species.resize(s.size());
  for (int i = 0; i < s.size(); i++){
    check_for_keys(s[i], filename+"/species["+std::to_string(i)+"]", keys);
    
    // determine type of species
    
    std::unique_ptr<LongLivedGas_t> g = std::make_unique<LongLivedGas_t>();
    
    // common components of all species
    std::string sp = s[i]["name"].as<std::string>();
    g->name = sp;
    g->composition.resize(d.natoms);
    g->mass = 0.0;
    g->redox = 0.0;
    for (int j = 0; j < d.natoms; j++){
      if (s[i]["composition"][d.atoms[j].name]){
        g->composition[j] = s[i]["composition"][d.atoms[j].name].as<int>();
        g->mass += g->composition[j]*d.atoms[j].mass;
        g->redox += g->composition[j]*d.atoms[j].redox;
      } else {
        g->composition[j] = 0;
      }
    }
    
    // Components specific to each species type
    
    
    d.species[i] = std::move(g);
    
  } 
    
  } // end species

    
    
  std::cout << d.species.size() << std::endl;
    
    
    
    
    
  
  
  // s.reserve(2);
  // std::unique_ptr<Particle_t> p = std::make_unique<Particle_t>();
  // std::unique_ptr<LongLivedGas_t> g = std::make_unique<LongLivedGas_t>();
  // p->name = "hi";
  // p->type = Particle;
  // p->b = 100;
  // g->name = "hiiiii";
  // g->type = LongLivedGas;
  // g->a = 101;
  // s.push_back(std::move(p));
  // s.push_back(std::move(g));
  // 
  // std::cout << s[0]->type << std::endl;
  // std::cout << static_cast<Particle_t&>(*s[0]).name << std::endl;
  // 
  // s[0]->net_production();
  // s[1]->net_production();
  
  // SpeciesVector s;
  
  // for (YAML::const_iterator it=file.begin(); it != file.end(); ++it){
  //   std::string key = it->first.as<std::string>();
  //   std::cout << key << std::endl;
  // }
  
  
  }
  catch (YAML::BadConversion& e) {
    throw PhotoException(e.what());
  }
  
}

void read_stuff_wrapper()
{
  try{
    read_stuff();
  }
  catch (YAML::BadConversion& e) {
    throw PhotoException(e.what());
  }
}


} // namespace