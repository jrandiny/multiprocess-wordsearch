#include <bruteProcessor.h>
#include <omp.h>
#include <iostream>
#include <utility>
#include <vector>

void bruteProcessor::process() {
  std::vector<std::vector<char>> data = (this->data).getData();
  int row = data.size();
  int col = data.size();

  double startTime = omp_get_wtime();

  int i = 0;
  int j = 0;

  std::vector<std::pair<int, int>> move = {{0, 1}, {1, 0}, {1, 1}, {-1, -1}};

  while (!found && i < row) {
    j = 0;
    while (!found && j < col) {
      if (query[0] == data[i][j]) {
        for (int dir = 0; dir < 4; dir++) {
          int k = 0;
          while (!found && k < query.size()) {
            direction currDir = static_cast<direction>(dir);
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

  double timeElapsed = omp_get_wtime() - startTime;

  std::cout << "Time " << timeElapsed << " seconds" << std::endl;
}