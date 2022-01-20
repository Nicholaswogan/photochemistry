#pragma once

#include <iostream>
#include <xtensor/xmath.hpp> 
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

class MyClass
{
public:
  xt::xarray<double> arr {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double sum_arr();  
};
