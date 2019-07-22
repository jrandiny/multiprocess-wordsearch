cmake_minimum_required (VERSION 3.10)
project (wordsearch)

include_directories(include)

file(GLOB_RECURSE wordsearch_src CONFIGURE_DEPENDS "src/*.cpp")

find_package(OpenMP)

add_executable(wordsearch ${wordsearch_src})
target_link_libraries(wordsearch PUBLIC OpenMP::OpenMP_CXX)