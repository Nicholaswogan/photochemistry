#pragma once

#include <iostream>
#include <exception>
#include <xtensor/xarray.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xio.hpp>

class MyClass
{
public:
  xt::xarray<double> arr {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double sum_arr();  
};

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


void read_stuff();