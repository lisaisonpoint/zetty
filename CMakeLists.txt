cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)

project(zetty)

file(GLOB_RECURSE zetty_SOURCES "src/*.cpp")
file(GLOB_RECURSE zetty_HEADERS "include/*.hpp")

include_directories(include)
add_library(zetty ${zetty_SOURCES})
