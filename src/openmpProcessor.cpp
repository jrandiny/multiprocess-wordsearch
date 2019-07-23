#include <omp.h>
#include <openmpProcessor.h>
#include <processor.h>
#include <cmath>
#include <iostream>

void openmpProcessor::process() {
  std::vector<std::vector<char>> data = (this->data).getData();
  int row = data.size();
  int col = data.size();

  double startTime = omp_get_wtime();

  std::vector<std::pair<int, int>> move = {{0, 1}, {1, 0}, {1, 1}, {-1, -1}};

#pragma omp parallel num_threads(threadCount)
  {
    // Calculate partition range
    int tid = omp_get_thread_num();
    int segment = row / threadCount;

    int i = segment * tid;
    int j = 0;

    int iMax = segment * (tid + 1);
    if (tid == (threadCount - 1)) {
      iMax = row;
    }

    while (!found && i < iMax) {
      j = 0;
      while (!found && j < col) {
        // If first letter matched
        if (query[0] == data[i][j]) {
          // For all direction
          for (int dir = 0; dir < 4; dir++) {
            direction currDir = static_cast<direction>(dir);
            int k = 0;
            while (!found && k < query.size()) {
              int tempRow = i + move[currDir].first * k;
              int tempCol = j + move[currDir].second * k;

              if (tempRow >= row || tempCol >= col || tempRow < 0 ||
                  tempCol < 0) {
                break;
              }

              if (data[tempRow][tempCol] != query[k]) {
                break;
              }

              if (k == query.size() - 1) {
                found = true;
                foundRow = i + 1;
                foundCol = j + 1;
                foundDir = currDir;
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

  double timeElapsed = omp_get_wtime() - startTime;

  std::cout << "Time " << timeElapsed << " seconds" << std::endl;
}