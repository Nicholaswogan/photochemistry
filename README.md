# CXX template

This is a template for projects that use xtensor python with pybind11.

Test with

```
conda create -n test python numpy pybind11 xtensor xtensor-python cmake
conda activate test

mkdir build
cd build
cmake ..
cmake --build . && cmake --install .

cd ../test
python test.py
```
