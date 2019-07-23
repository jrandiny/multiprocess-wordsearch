#include <mpi/mpi.h>
#include <processor.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

int main(int argc, char* argv[]) {
  std::vector<std::pair<int, int>> move = {{0, 1}, {1, 0}, {1, 1}, {-1, -1}};

  int tid, threadCount;
  std::string query = argv[1];

  std::vector<char> data;
  int row;
  int col;

  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &tid);
  MPI_Comm_size(MPI_COMM_WORLD, &threadCount);

  MPI_Comm parentComm;
  MPI_Comm_get_parent(&parentComm);

  MPI_Bcast(&row, 1, MPI_INT, 0, parentComm);
  col = row;

  data.reserve(col * row);

  MPI_Bcast(&data[0], row * col, MPI_CHAR, 0, parentComm);

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
          while (!found && k < query.size()) {
            int tempRow = i + move[currDir].first * k;
            int tempCol = j + move[currDir].second * k;

            if (tempRow >= row || tempCol >= col || tempRow < 0 ||
                tempCol < 0) {
              break;
            }

            if (data[tempRow * row + tempCol] != query[k]) {
              break;
            }

            if (k == query.size() - 1) {
              found = true;
              int payload[] = {true, i + 1, j + 1, currDir};
              MPI_Send(payload, 4, MPI_INT, 0, 0, parentComm);
            }
            k++;
          }
        }
      }
      j++;
    }
    i++;
  }

  if (!found) {
    int payload[] = {false, 0, 0, 0};
    MPI_Send(payload, 4, MPI_INT, 0, 0, parentComm);
  }

  MPI_Finalize();
  return 0;
}