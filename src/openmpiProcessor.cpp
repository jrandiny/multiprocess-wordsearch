#include <mpi/mpi.h>
#include <openmpiProcessor.h>
#include <processor.h>
#include <chrono>
#include <iostream>

void openmpiProcessor::process() {
  std::vector<std::vector<char>> data = (this->data).getData();
  std::vector<char> serialData;

  int row = data.size();
  int col = data.size();

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      serialData.push_back(data[i][j]);
    }
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> startTime =
      std::chrono::high_resolution_clock::now();

  MPI_Init(NULL, NULL);

  MPI_Comm childComm;
  int spawnError[threadCount];

  char* argv[] = {(char*)query.c_str(), NULL};

  MPI_Comm_spawn("./openmpiWorker", argv, threadCount, MPI_INFO_NULL, 0,
                 MPI_COMM_WORLD, &childComm, spawnError);

  MPI_Bcast(&row, 1, MPI_INT, MPI_ROOT, childComm);
  MPI_Bcast(&serialData[0], row * col, MPI_CHAR, MPI_ROOT, childComm);

  int threadFinish = 0;

  while (!found && threadFinish < threadCount) {
    int payload[4];
    MPI_Recv(&payload, 4, MPI_INT, MPI_ANY_SOURCE, 0, childComm,
             MPI_STATUS_IGNORE);
    threadFinish++;
    found = payload[0];
    foundRow = payload[1];
    foundCol = payload[2];
    foundDir = static_cast<direction>(payload[3]);
  }

  MPI_Finalize();

  std::chrono::duration<double> timeElapsed =
      std::chrono::high_resolution_clock::now() - startTime;

  std::cout << "Time " << timeElapsed.count() << " seconds" << std::endl;
}