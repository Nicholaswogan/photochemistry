cmake_minimum_required(VERSION 3.18)

project(photochemistry VERSION "0.1" LANGUAGES CXX)

# options
option(SKBUILD "Should be ON of being build by skbuild, 
and OFF of being build by regular cmake" OFF)

option(BUILD_PYTHON "ON if building python interface" OFF)

set(PHOTOCHEM_PRECISION "double" CACHE STRING "Precision")

if (${PHOTOCHEM_PRECISION} STREQUAL "double")
  add_definitions(-DREAL_KIND=double)
endif()

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# dependencies
find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(yaml-cpp REQUIRED)

add_subdirectory(src)

add_executable(main test/main.cpp)
target_link_libraries(main example)
target_include_directories(main PUBLIC src/)

if (BUILD_PYTHON)
  
  if (NOT SKBUILD)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
  endif()

  find_package(NumPy REQUIRED)
  find_package(pybind11 REQUIRED)
  find_package(xtensor-python REQUIRED)

  pybind11_add_module(_example MODULE photochemistry/wrapper.cpp)
  target_link_libraries(_example PUBLIC xtensor-python pybind11::module example)
  target_include_directories(_example PUBLIC ${NumPy_INCLUDE_DIRS} src)

  if (SKBUILD)
    install(TARGETS _example DESTINATION photochemistry)
  else()
    install(TARGETS _example DESTINATION ${CMAKE_SOURCE_DIR}/photochemistry)
  endif()
  
endif()

