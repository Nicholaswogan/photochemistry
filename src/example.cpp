#include "example.h"

double MyClass::sum_arr()
{
  return xt::sum(arr)();
}