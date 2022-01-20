# photochemistry

```
conda create -n test -c conda-forge python numpy pybind11 xtensor xtensor-python cmake yaml-cpp
conda activate test

mkdir build
cd build
cmake ..
cmake --build . && cmake --install .

cd ../test
python test.py
```
