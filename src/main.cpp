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

  return 0;
}