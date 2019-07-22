cmake_minimum_required (VERSION 3.10)
project (wordsearch)

include_directories(include)

file(GLOB_RECURSE wordsearch_src CONFIGURE_DEPENDS "src/*.cpp")

add_executable(wordsearch ${wordsearch_src})