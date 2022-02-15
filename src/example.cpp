#include "example.h"
#include "yaml-cpp/yaml.h"


double MyClass::sum_arr()
{  
  return xt::sum(arr)();  
}

namespace Photochem {
  
void SpeciesBase::net_production()
{
  
}

void LongLivedGas_t::net_production()
{
  std::cout << "LongLivedGas" << std::endl;
}

void Particle_t::net_production()
{
  std::cout << "Particle" << std::endl;
}
  
  
}




namespace Photochem {

void read_stuff()
{
  YAML::Node file;
  std::string filename = "../photochemistry/data/reaction_mechanisms/zahnle_earth.yaml";
  file = YAML::LoadFile(filename);
  
  
  if (!file["atoms"]){throw PhotoException(filename+" is missing key atoms");}
  YAML::Node atoms = file["atoms"];
  std::vector<Atom> a(atoms.size());
  for (int i = 0; i < atoms.size(); i++){
    a[i].name = atoms[i]["name"].as<std::string>();
    a[i].mass = atoms[i]["mass"].as<double>();
    a[i].redox = atoms[i]["redox"].as<double>();
  }
  
  if (!file["species"]){throw PhotoException(filename+" is missing key species");}
  YAML::Node species = file["species"];
  
  
  std::vector<std::unique_ptr<SpeciesBase>> s;
  s.reserve(2);
  std::unique_ptr<Particle_t> p = std::make_unique<Particle_t>();
  std::unique_ptr<LongLivedGas_t> g = std::make_unique<LongLivedGas_t>();
  p->name = "hi";
  p->type = Particle;
  p->b = 100;
  g->name = "hiiiii";
  g->type = LongLivedGas;
  g->a = 101;
  s.push_back(std::move(p));
  s.push_back(std::move(g));
  
  std::cout << s[0]->type << std::endl;
  std::cout << static_cast<Particle_t&>(*s[0]).name << std::endl;
  
  s[0]->net_production();
  s[1]->net_production();
  
  // SpeciesVector s;
  
  // for (YAML::const_iterator it=file.begin(); it != file.end(); ++it){
  //   std::string key = it->first.as<std::string>();
  //   std::cout << key << std::endl;
  // }
  
}


} // namespace