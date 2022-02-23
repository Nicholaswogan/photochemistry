#include "example.h"
#define FORCE_IMPORT_ARRAY

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <xtensor-python/pyarray.hpp>

namespace py = pybind11;

PYBIND11_MODULE(_example, m) {
  xt::import_numpy();
}