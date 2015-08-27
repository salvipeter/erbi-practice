cmake_minimum_required(VERSION 2.8)
project(Erbi)

find_package(SDL)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++1y")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories(${SDL_INCLUDE_DIR})

add_executable(erbi erbi.cc testtype.cc)
target_link_libraries(erbi ${SDL_LIBRARY})
