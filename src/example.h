#pragma once

#include <iostream>
#include <exception>
#include <memory>

#include <xtensor/xarray.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xio.hpp>

class MyClass
{
public:
  xt::xarray<double> arr {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double sum_arr();  
};

namespace Photochem{
  
class PhotoException : public std::exception
{
  std::string _msg;
public:
  PhotoException(const std::string& msg) : _msg(msg){}

  virtual const char* what() const noexcept override
  {
    return _msg.c_str();
  }
}; 

struct Atom
{
  std::string name;
  double mass;
  double redox;
};

enum {Particle, LongLivedGas, ShortLivedGas, BackgroundGas};

struct SpeciesBase 
{
  size_t type;
  std::string name;
  std::vector<size_t> iprod;
  std::vector<size_t> iloss;
  
  std::vector<size_t> composition;
  double mass;
  double redox;
  size_t thermo;
  size_t henry;
  
  // Production/Loss mechanisms
  //   1. reactions
  //   2. rainout
  //   3. condensation/evaporations
  
  virtual void net_production();

};

struct LongLivedGas_t: public SpeciesBase
{
  int a;
  void net_production();
};

struct Particle_t: public SpeciesBase
{
  int b;
  void net_production();
};





void read_stuff();


}