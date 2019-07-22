#pragma once
#include <processor.h>

class bruteProcessor : public processor {
 public:
  bruteProcessor(table data, std::string query, int numThread)
      : processor(data, query, numThread) {}
  void process();
};
