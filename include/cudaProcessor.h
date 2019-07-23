#pragma once
#include <processor.h>

class cudaProcessor : public processor {
 public:
  cudaProcessor(table data, std::string query, int numThread)
      : processor(data, query, numThread) {}
  void process();
};
