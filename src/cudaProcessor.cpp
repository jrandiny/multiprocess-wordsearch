#include <cudaProcessor.h>
#include <cudaWorker.h>
#include <processor.h>
#include <chrono>
#include <cmath>
#include <iostream>

void cudaProcessor::process() {
  std::vector<std::vector<char>> data = (this->data).getData();
  std::vector<char> serialData;
  std::vector<int> result = {0, 0, 0, 0};

  result.reserve(4);

  int row = data.size();
  int col = data.size();

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      serialData.push_back(data[i][j]);
    }
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> startTime =
      std::chrono::high_resolution_clock::now();

  std::vector<std::pair<int, int>> move = {{0, 1}, {1, 0}, {1, 1}, {-1, -1}};

  docuda(&serialData[0], row, query, threadCount, &result[0]);

  found = result[0];
  foundRow = result[1];
  foundCol = result[2];
  foundDir = static_cast<direction>(result[3]);

  std::chrono::duration<double> timeElapsed =
      std::chrono::high_resolution_clock::now() - startTime;

  std::cout << "Time " << timeElapsed.count() << " seconds" << std::endl;
}