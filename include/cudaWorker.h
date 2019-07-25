#pragma once
#include <string>

void docuda(char* cpuData, int row, std::string cpuQuery, int threadCount,
            int* cpuResult);