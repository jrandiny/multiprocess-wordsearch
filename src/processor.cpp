#include <processor.h>
#include <table.h>

processor::processor(table data, std::string query, int threadCount) {
  this->data = data;
  this->threadCount = threadCount;
  this->query = query;
  this->found = false;
}

void processor::process() {
  found = true;
  foundCol = 1;
  foundRow = 2;
  foundDir = vertical;
}

bool processor::isFound() const { return found; }

int processor::getFoundRow() const { return foundRow; }

int processor::getFoundCol() const { return foundCol; }

std::string processor::getFoundDirection() const {
  switch (foundDir) {
    case horizontal:
      return "horizontal";
      break;
    case vertical:
      return "vertical";
      break;
    case diagonal:
      return "diagonal topleft->bottomright";
      break;
    case reverseDiagonal:
      return "diagonal topright->bottomleft";
      break;
  }
}