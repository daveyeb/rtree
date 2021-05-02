cmake_minimum_required(VERSION 3.10)

project(rm)

add_executable(rm ${CMAKE_CURRENT_SOURCE_DIR}/src/cli.cc)
target_include_directories(rm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/specs/javascript)
target_include_directories(rm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/utils)
target_include_directories(rm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/tinydir)
