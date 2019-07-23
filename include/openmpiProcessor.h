#pragma once
#include <processor.h>

class openmpiProcessor : public processor {
 public:
  openmpiProcessor(table data, std::string query, int numThread)
      : processor(data, query, numThread) {}
  void process();
};
