cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

project(zetty)

file(GLOB_RECURSE zetty_SOURCES "src/*.cpp")
file(GLOB_RECURSE zetty_HEADERS "include/*.hpp")

file(COPY resources DESTINATION .)

include_directories(include)
add_executable(zetty ${zetty_SOURCES})
target_link_libraries(zetty z)
