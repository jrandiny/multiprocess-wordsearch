#pragma once
#include <table.h>
#include <string>

enum direction {
  horizontal = 0,
  vertical = 1,
  diagonal = 2,
  reverseDiagonal = 3
};

class processor {
 protected:
  table data;
  int threadCount;
  std::string query;

  bool found;
  int foundCol;
  int foundRow;
  direction foundDir;

 public:
  processor(table, std::string, int);
  virtual void process() = 0;
  bool isFound() const;
  int getFoundRow() const;
  int getFoundCol() const;
  std::string getFoundDirection() const;
};
