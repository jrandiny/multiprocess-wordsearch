#include <table.h>
#include <fstream>
#include <iostream>
#include <string>

table::table(std::string filename) {
  std::ifstream wordfile;

  wordfile.open(filename, std::ios::in);

  if (!wordfile.is_open()) {
    throw std::runtime_error("Error opening file");
  }

  std::string tempLine;

  while (wordfile >> tempLine) {
    std::vector<char> tempVector;
    for (int i = 0; i < tempLine.length(); i++) {
      tempVector.push_back(tempLine[i]);
    }
    data.push_back(tempVector);
  }

  wordfile.close();
}

std::vector<std::vector<char>> table::getData() const { return data; }

void table::print() const {
  if (data.size() < 100) {
    for (int i = 0; i < data.size(); i++) {
      for (int j = 0; j < data.size(); j++) {
        std::cout << data[i][j];
      }
      std::cout << std::endl;
    }
  } else {
    std::cout << "[" << data.size() << "X" << data.size() << "]" << std::endl;
  }
}