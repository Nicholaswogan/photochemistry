
#include "input.hpp"

namespace Photochem {
  

Settings read_settings(const std::string &filename){
  Settings s;
  
  s.filename = filename;
  
  YAML::Node file;
  try{
    file = YAML::LoadFile(filename);
  }
  catch (YAML::BadFile& e) {
    throw PhotoException(filename+" does not exist.");
  }
  catch (YAML::ParserException& e) {
    throw PhotoException(filename+", "+e.what());
  }
  
  // Read all settings
  try{
  
  // check all keys at root level
  const std::vector<std::string> root_keys = 
      {"atmosphere-grid", "photolysis-grid", "planet", "particles", "boundary-conditions"};
  check_for_keys(file, filename+"/", root_keys);
  
  // atmosphere-grid
  YAML::Node atmgrid = file["atmosphere-grid"];
  const std::vector<std::string> atmgrid_keys = 
      {"bottom", "top", "number-of-layers"};
  check_for_keys(atmgrid, filename+"/atmosphere-grid/", atmgrid_keys);
  s.bottom = atmgrid["bottom"].as<real>();
  s.top = atmgrid["top"].as<real>();
  s.number_of_layers = atmgrid["number-of-layers"].as<size_t>();
  
  // photolysis-grid
  YAML::Node photogrid = file["photolysis-grid"];
  const std::vector<std::string> photogrid_keys = 
      {"lower-wavelength", "upper-wavelength", "number-of-bins"};
  check_for_keys(photogrid, filename+"/photolysis-grid/", photogrid_keys);
  s.lower_wavelength = photogrid["lower-wavelength"].as<real>();
  s.upper_wavelength = photogrid["upper-wavelength"].as<real>();
  s.number_of_bins = photogrid["number-of-bins"].as<size_t>();
  
  // planet
  YAML::Node planet = file["planet"];
  const std::vector<std::string> planet_keys = 
      {"use-background-gas", "background-gas", "surface-pressure", "planet-mass", 
       "planet-radius", "surface-albedo", "diurnal-averaging-factor", 
       "solar-zenith-angle", "diff-lim-hydrogen-escape", "gas-rainout"};
  check_for_keys(planet, filename+"/planet/", planet_keys);
  s.use_background_gas = planet["use-background-gas"].as<bool>();
  s.background_gas = planet["background-gas"].as<std::string>();
  s.surface_pressure = planet["surface-pressure"].as<real>();
  s.planet_mass = planet["planet-mass"].as<real>();
  s.planet_radius = planet["planet-radius"].as<real>();
  s.surface_albedo = planet["surface-albedo"].as<real>();
  s.diurnal_averaging_factor = planet["diurnal-averaging-factor"].as<real>();
  s.solar_zenith_angle= planet["solar-zenith-angle"].as<real>();
  s.diff_lim_hydrogen_escape = planet["diff-lim-hydrogen-escape"].as<bool>();
  s.gas_rainout = planet["gas-rainout"].as<bool>();
  if (s.gas_rainout){
    check_for_keys(planet, filename+"/planet/", "rainfall-rate");
    check_for_keys(planet, filename+"/planet/", "tropopause-altitude");
    s.rainfall_rate = planet["rainfall-rate"].as<real>();
    s.tropopause_altitude = planet["tropopause-altitude"].as<real>();
  }
  
  // particle condensation rates
  
  
  // boundary conditions
  YAML::Node bcs = file["boundary-conditions"];
  if (!bcs.IsSequence()){
    throw PhotoException(filename+"/boundary-conditions must be a sequence.");
  }
  s.species_names.resize(bcs.size());
  s.species_types.resize(bcs.size());
  s.lower_bc.resize(bcs.size());
  s.upper_bc.resize(bcs.size());
  // default values
  for (int i = 0; i < bcs.size(); i++){
    s.species_types[i] = LongLivedGas;
    s.lower_bc[i].type = DepositionVelocity;
    s.lower_bc[i].vdep = 0.0;
    s.upper_bc[i].type = DepositionVelocity;
    s.upper_bc[i].vdep = 0.0;
  }
  
  for (int i = 0; i < bcs.size(); i++){
    check_for_keys(bcs[i], filename+"/boundary-conditions["+std::to_string(i)+"]", "name");
    s.species_names[i] = bcs[i]["name"].as<std::string>();
    
    if (bcs[i]["type"]){
      std::string sptype = bcs[i]["type"].as<std::string>();
    }
  }
  
  }
  catch (YAML::BadConversion& e) {
    throw PhotoException(e.what());
  }
  
  
  return s;
}
  

} // namespace Photochem


