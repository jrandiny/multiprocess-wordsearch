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

  double timeElapsed = omp_get_wtime() - startTime;

  std::cout << "Time " << timeElapsed << " seconds" << std::endl;

  found = true;
  foundCol = 3;
  foundRow = 4;
  foundDir = horizontal;
}