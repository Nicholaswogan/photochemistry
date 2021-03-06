#pragma once

#include <iostream>
#include <memory>
#include <cmath>

#include <xtensor/xarray.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xio.hpp>

#include "exception.hpp"

#define real REAL_KIND

namespace Photochem{

/////////////////////////
// Boundary conditions //
/////////////////////////
enum {DepositionVelocity, FixedMixingRatio, FixedFlux, VdepDistributedFlux};

struct BoundaryCondition_t
{
  size_t type;
  float vdep;
  float fixedmr;
  float flux;
  float disth;
};

//////////////
// Settings //
//////////////

struct Settings
{
  std::string filename;
  
  // atmosphere-grid
  real bottom;
  real top;
  size_t number_of_layers;
  
  // photolysis-grid
  real lower_wavelength;
  real upper_wavelength;
  size_t number_of_bins;
  
  // planet
  bool use_background_gas;
  std::string background_gas;
  real surface_pressure;
  real planet_mass;
  real planet_radius;
  real surface_albedo;
  real diurnal_averaging_factor;
  real solar_zenith_angle;
  bool diff_lim_hydrogen_escape;
  bool gas_rainout;
  real rainfall_rate;
  real tropopause_altitude;
    
  // particle condensation rates
  
  // boundary conditions and species types
  std::vector<std::string> species_names;
  std::vector<size_t> species_types;
  std::vector<BoundaryCondition_t> lower_bc;
  std::vector<BoundaryCondition_t> upper_bc;
  
};

///////////
// Atoms //
///////////
struct Atom_t
{
  std::string name;
  real mass;
  real redox;
};

/////////////
// Species //
/////////////
enum {Particle, LongLivedGas, ShortLivedGas, BackgroundGas};

// 
struct SpeciesBase_t
{
  size_t type;
  std::string name;
  std::vector<size_t> iprod;
  std::vector<size_t> iloss;
  
  std::vector<int> composition;
  real mass;
  real redox;
  
  // Production/Loss mechanisms
  //   1. reactions
  //   2. rainout
  //   3. condensation/evaporations
  
  // virtual void net_production();
};

struct Particle_t: public SpeciesBase_t
{
  
};

struct LongLivedGas_t: public SpeciesBase_t
{
  
};

struct ShortLivedGas_t: public SpeciesBase_t
{
  
};

struct BackgroundGas_t: public SpeciesBase_t
{
  
};

///////////////
// Reactions //
///////////////

struct Efficiencies_t
{
  size_t n_eff;
  size_t def_eff;
  std::vector<real> efficiencies;
  std::vector<size_t> eff_sp_inds;
};

enum {PhotolysisReaction, ElementaryReaction, ThreeBodyReaction, FalloffReaction, ReverseReaction};

struct ReactionBase_t
{
  size_t type;
  std::string equation;
  size_t nreact;
  size_t nprod;
  std::vector<size_t> react_sp_inds;
  std::vector<size_t> prod_sp_inds;
  bool is_a_reverse;
  size_t reverse_info; 
  
  // computes rate for all heights in atmosphere. Pass NULL to forward_rates
  // if reaction is a forward.
  virtual void reaction_rate(const xt::xarray<real> &temp, 
                             const xt::xarray<real> &gibbsE, 
                             const xt::xarray<real> &density,
                             const xt::xarray<real> &densities,
                             const xt::xarray<real> *forward_rates,
                             xt::xarray<real> &rx_rates);

};

struct PhotolysisReaction_t: public ReactionBase_t
{
};

struct ElementaryReaction_t: public ReactionBase_t
{
  real A;
  real b;
  real Ea;
  
  void reaction_rate(const xt::xarray<real> &temp, 
                     const xt::xarray<real> &gibbsE, 
                     const xt::xarray<real> &density,
                     const xt::xarray<real> &densities,
                     const xt::xarray<real> *forward_rates,
                     xt::xarray<real> &rx_rates);
};

struct ThreeBodyReaction_t: public ReactionBase_t
{
  real A;
  real b;
  real Ea;
  Efficiencies_t eff; // efficiencies
};

struct FalloffRate_t: public ReactionBase_t
{
  real A0;
  real b0;
  real Ea0;
  real Ainf;
  real binf;
  real Eainf;
  
  size_t falloff_type;
  real A_T;
  real T1;
  real T2;
  real T3;
  
  Efficiencies_t eff; // efficiencies
};

struct ReverseReaction_t: public ReactionBase_t
{
};

///////////////
// PhotoData //
///////////////

struct PhotoData
{
  // atoms
  size_t natoms;
  std::vector<Atom_t> atoms; // [natoms]
  
  // species
  // Organization is as follows
  // [       nsp       ]
  // [   nq   + nsl + 1]
  // [np + ng + nsl + 1]
  // |_______|
  //     |
  // Only np + ng = nq evolve through time. nsl are assumed to be in equilibrium. +1 is background gas.
  size_t np;   // number of particles that evolve through time
  size_t ng;   // number of gas-phase species that evolve through time
  size_t ng_1; // index of first gas
  size_t nq;   // number of speices that evolve through time
  size_t nsl;  // number of short-lived gas moleules.
  size_t nsp;  // total number of species
  std::vector<std::string> species_names; // copy of species names
  std::vector<std::unique_ptr<SpeciesBase_t>> species; // [nsp]
  
  // reactions
  bool reverse; // True if there are reverse reactions
  size_t nrF; // number of forward reactions
  size_t nrR; // number of reverse reactions
  size_t nrT; // number of total reactions
  std::vector<std::string> reaction_equations; // copy of reaction names
  std::vector<std::unique_ptr<ReactionBase_t>> reactions; // [nrT]
  
};

struct PhotoVars
{
  // PhotoVars can change change between integrations
  // but not during a single integration.
  
  // boundary conditions
  std::vector<BoundaryCondition_t> lower_bc; // [nq]
  std::vector<BoundaryCondition_t> upper_bc; // [nq]

};

struct PhotoWrk
{
  // work arrays used during the course of integration
};

class Clima
{
  // climate model
};


struct AtmosphereBase
{
public:
  PhotoData dat;
  PhotoVars var;
  PhotoWrk  wrk;
  
  // methods
  
};

struct MixingRatioAtmosphere : public AtmosphereBase
{  
};

struct MixingRatioClimaAtmosphere : public AtmosphereBase
{  
  Clima c;
};

struct DensityClimaAtmosphere : public AtmosphereBase
{  
  Clima c;
};

void read_stuff();





} // Photochem namespace






