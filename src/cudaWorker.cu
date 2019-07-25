#include <cudaWorker.h>
#include <math.h>
#include <processor.h>
#include <iostream>
#include <string>
#include <vector>

__global__ void calculate(int row, char* data, int queryLength, char* query,
                          int* result) {
  int move[8] = {0, 1, 1, 0, 1, 1, -1, -1};

  int col = row;
  int threadCount = blockDim.x * gridDim.x;

  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  int segment = row / threadCount;

  int i = segment * tid;
  int j = 0;

  int iMax = segment * (tid + 1);
  if (tid == (threadCount - 1)) {
    iMax = row;
  }

  bool found = false;

  while (!found && i < iMax) {
    j = 0;
    while (!found && j < col) {
      // If first letter matched
      if (query[0] == data[i * row + j]) {
        // For all direction
        for (int dir = 0; dir < 4; dir++) {
          direction currDir = static_cast<direction>(dir);
          int k = 0;
          while (!found && k < queryLength) {
            int tempRow = i + move[currDir * 2] * k;
            int tempCol = j + move[currDir * 2 + 1] * k;

            if (tempRow >= row || tempCol >= col || tempRow < 0 ||
                tempCol < 0) {
              break;
            }

            if (data[tempRow * row + tempCol] != query[k]) {
              break;
            }

            if (k == queryLength - 1) {
              found = true;
              result[0] = true;
              result[1] = i + 1;
              result[2] = j + 1;
              result[3] = currDir;
            }
            k++;
          }
        }
      }
      j++;
    }
    i++;
  }
}

void docuda(char* cpuData, int row, std::string cpuQuery, int threadCount,
            int* cpuResult) {
  char* serialData;
  char* query;
  int* result;

  cudaMallocManaged(&serialData, row * row * sizeof(char));
  cudaMallocManaged(&result, 4 * sizeof(int));
  cudaMallocManaged(&query, cpuQuery.size() * sizeof(char));

  for (int i = 0; i < cpuQuery.size(); i++) {
    query[i] = cpuQuery[i];
  }

  for (int i = 0; i < row * row; i++) {
    serialData[i] = cpuData[i];
  }

  cudaDeviceProp props;
  cudaGetDeviceProperties(&props, 0);
  std::cout << "Device info" << std::endl;
  std::cout << props.name << ": " << props.major << "." << props.minor
            << std::endl;
  std::cout << "  Warp size            : " << props.warpSize << std::endl;
  std::cout << "  Threads per block    : " << props.maxThreadsPerBlock
            << std::endl;
  std::cout << "  SM (Processor) count : " << props.multiProcessorCount
            << std::endl;

  int threadPerBlock = 128;
  std::cout << "Thread per block (recommended 128/256): ";
  std::cin >> threadPerBlock;

  int blockCount = threadCount / threadPerBlock;

  std::cout << "Using " << blockCount << " blocks" << std::endl;

  calculate<<<blockCount, threadPerBlock>>>(row, serialData, cpuQuery.size(),
                                            query, result);

  cudaDeviceSynchronize();

  for (int i = 0; i < 4; i++) {
    // std::cout << result[i] << std::endl;
    cpuResult[i] = result[i];
  }

  cudaFree(serialData);
  cudaFree(query);
  cudaFree(result);
}