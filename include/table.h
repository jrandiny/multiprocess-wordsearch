#include <string>
#include <vector>

class table {
 private:
  // std::vector<std::string> horizontal;
  // std::vector<std::string> vertical;
  // std::vector<std::string> diagonal;
  // std::vector<std::string> reverseDiagonal;
  std::vector<std::vector<char>> data;

 public:
  table(std::string filename);

  void print() const;
  std::vector<std::vector<char>> getData() const;

  // std::string getHorizontal(int index) const;
  // std::string getVertical(int index) const;
  // std::string getDiagonal(int index) const;
  // std::string getReverseDiagonal(int index) const;
};