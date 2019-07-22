#pragma once
#include <table.h>
#include <string>

enum direction { horizontal, vertical, diagonal, reverseDiagonal };

class processor {
 private:
  table data;
  int threadCount;
  std::string query;

  bool found;
  int foundCol;
  int foundRow;
  direction foundDir;

 public:
  processor(table, std::string, int);
  virtual void process();
  bool isFound() const;
  int getFoundRow() const;
  int getFoundCol() const;
  std::string getFoundDirection() const;
};
