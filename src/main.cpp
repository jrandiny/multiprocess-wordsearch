#include <bruteProcessor.h>
#include <config.h>
#include <openmpProcessor.h>
#include <openmpiProcessor.h>
#include <processor.h>
#include <table.h>
#include <iostream>
#include <memory>
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
  int processorOption;

  std::cout << "Search query : ";
  std::cin >> searchQuery;

  std::cout << "Thread count : ";
  std::cin >> threadCount;

  std::cout << "Avaiable processor:" << std::endl;
  std::cout << "1. No processor (not parallel)" << std::endl;
#ifdef BUILD_OPENMP
  std::cout << "2. OpenMP" << std::endl;
#endif
#ifdef BUILD_OPENMPI
  std::cout << "3. OpenMPI" << std::endl;
#endif
  std::cout << "Processor : ";
  std::cin >> processorOption;

  std::unique_ptr<processor> searchProcessor;

  switch (processorOption) {
    case 1:
      searchProcessor = std::unique_ptr<processor>(
          new bruteProcessor(wordTable, searchQuery, threadCount));
      break;
#ifdef BUILD_OPENMP
    case 2:
      searchProcessor = std::unique_ptr<processor>(
          new openmpProcessor(wordTable, searchQuery, threadCount));
      break;
#endif
#ifdef BUILD_OPENMPI
    case 3:
      searchProcessor = std::unique_ptr<processor>(
          new openmpiProcessor(wordTable, searchQuery, threadCount));
      break;
#endif
    default:
      throw std::runtime_error("Invalid processor option");
      break;
  }

  searchProcessor->process();

  if (searchProcessor->isFound()) {
    std::cout << "Word found at row " << searchProcessor->getFoundRow()
              << " col " << searchProcessor->getFoundCol() << " on the "
              << searchProcessor->getFoundDirection() << " direction "
              << std::endl;
  } else {
    std::cout << "Word not found" << std::endl;
  }

  return 0;
}