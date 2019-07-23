#include <cudaProcessor.h>
#include <processor.h>
#include <chrono>
#include <cmath>
#include <iostream>

void cudaProcessor::process() {
  std::vector<std::vector<char>> data = (this->data).getData();
  int row = data.size();
  int col = data.size();

  std::chrono::time_point<std::chrono::high_resolution_clock> startTime =
      std::chrono::high_resolution_clock::now();

  std::vector<std::pair<int, int>> move = {{0, 1}, {1, 0}, {1, 1}, {-1, -1}};

  std::chrono::duration<double> timeElapsed =
      std::chrono::high_resolution_clock::now() - startTime;

  std::cout << "Time " << timeElapsed.count() << " seconds" << std::endl;
}