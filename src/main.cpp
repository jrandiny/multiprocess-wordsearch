#include <processor.h>
#include <table.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  std::cout << "Welcome to wordsearch" << std::endl;

  std::string filePath;

  if (argc == 2) {
    filePath = argv[1];
  } else {
    std::cout << "File name : ";
    std::cin >> filePath;
  }

  std::cout << "Opening " << filePath << std::endl;

  table wordTable(filePath);
  std::cout << "Table : " << std::endl;
  wordTable.print();

  std::string searchQuery;
  int threadCount;

  std::cout << "Search query : ";
  std::cin >> searchQuery;

  std::cout << "Thread count : ";
  std::cin >> threadCount;

  processor searchProcessor(wordTable, searchQuery, threadCount);

  searchProcessor.process();

  if (searchProcessor.isFound()) {
    std::cout << "Word found at row " << searchProcessor.getFoundRow()
              << " col " << searchProcessor.getFoundCol() << " on the "
              << searchProcessor.getFoundDirection() << " direction "
              << std::endl;
  }else{
    std::cout<<"Word not found"<<std::endl;
  }

  return 0;
}