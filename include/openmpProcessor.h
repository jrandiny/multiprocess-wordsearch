#pragma once
#include <processor.h>

class openmpProcessor : public processor {
 public:
  openmpProcessor(table data, std::string query, int numThread)
      : processor(data, query, numThread) {}
  void process();
};
