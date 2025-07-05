cmake_minimum_required(VERSION 3.10)

add_subdirectory(third-party/big-uint)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file (GLOB_RECURSE SOURCES "source/*.cpp")
add_library(big_float STATIC ${SOURCES})

target_include_directories(big_float PUBLIC include)
target_link_libraries(big_float PUBLIC big_unsigned_int)
