# Parallel Wordsearch

Simple wordsearch program to demonstrate parallel programming

## Supported Runtime
- OpenMP
- OpenMPI
- CUDA

## Compilation

This program uses CMake with the following default option

```
BUILD_OPENMP=ON
BUILD_OPENMPI=OFF
BUILD_CUDA=OFF
```

**Example command**
```
mkdir build
cd build
cmake .. -DBUILD_OPENMPI=ON //Build with OpenMP and OpenMPI
make
```

## Usage

This program accepts text file containing square grid of letter

**input.txt**

```
abc
def
ghj
```

```bash
./wordsearch input.txt
```
