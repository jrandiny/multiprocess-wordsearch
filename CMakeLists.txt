cmake_minimum_required (VERSION 3.10)
project (wordsearch)

include_directories(include)

option(BUILD_OPENMP "Build openmp processor" ON)
option(BUILD_OPENMPI "Build openmpi processor" OFF)
option(BUILD_CUDA "Build cuda processor" OFF)

configure_file("config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/include/config.h")

set(wordsearch_src
  "src/main.cpp"
  "src/bruteProcessor.cpp"
  "src/processor.cpp"
  "src/table.cpp"
)

if(BUILD_OPENMP)
  find_package(OpenMP REQUIRED)
  add_definitions(-DUSE_OPENMP)
  LIST(APPEND wordsearch_src "src/openmpProcessor.cpp")
endif()

if(BUILD_OPENMPI)
  find_package(MPI REQUIRED)
  LIST(APPEND wordsearch_src "src/openmpiProcessor.cpp")
  add_definitions(-DUSE_OPENMPI)
  add_executable(openmpiWorker
    "src/openmpiWorker.cpp"
  )

  target_link_libraries(openmpiWorker PUBLIC MPI::MPI_CXX)

endif()

add_executable(wordsearch ${wordsearch_src})

if(BUILD_OPENMP)
  target_link_libraries(wordsearch PUBLIC OpenMP::OpenMP_CXX)
endif()

if(BUILD_OPENMPI)
  target_link_libraries(wordsearch PUBLIC MPI::MPI_CXX)
endif()