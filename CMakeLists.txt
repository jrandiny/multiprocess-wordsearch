cmake_minimum_required (VERSION 3.10)
project (wordsearch)

include_directories(include)

option(BUILD_OPENMP "Build openmp processor" ON)
option(BUILD_OPENMPI "Build openmpi processor" OFF)
option(BUILD_CUDA "Build cuda processor" OFF)

configure_file("config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h")

set(wordsearch_src
  "src/main.cpp"
  "src/bruteProcessor.cpp"
  "src/processor.cpp"
  "src/table.cpp"
)

if(BUILD_OPENMP)
  find_package(OpenMP)
  LIST(APPEND wordsearch_src "src/openmpProcessor.cpp")
endif()

add_executable(wordsearch ${wordsearch_src})

if(BUILD_OPENMP)
  target_link_libraries(wordsearch PUBLIC OpenMP::OpenMP_CXX)
endif()