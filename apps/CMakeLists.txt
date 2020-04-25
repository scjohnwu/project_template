cmake_minimum_required(VERSION 3.10)

project(sample_app)

vcpkg_add_packages(fmt)

find_package(fmt CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/sources ${CMAKE_SOURCE_DIR}/includes)

add_executable(sample sample/main.cpp)

target_link_libraries(sample PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(sample PRIVATE sample_reader)