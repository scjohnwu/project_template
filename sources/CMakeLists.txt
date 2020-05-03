cmake_minimum_required(VERSION 3.10)

project(sample_lib)

include_directories(${CMAKE_SOURCE_DIR}/sources ${CMAKE_SOURCE_DIR}/includes)

vcpkg_add_packages( sqlite3 fmt )

find_package(sqlite3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_library(sample_writer sample_writer.cpp sqlite3_wrapper.cpp)
add_library(sample_reader sample_reader.cpp sqlite3_wrapper.cpp)

target_link_libraries(sample_writer PRIVATE sqlite3)
target_link_libraries(sample_reader PRIVATE sqlite3)
target_link_libraries(sample_writer PRIVATE fmt::fmt fmt::fmt-header-only)
