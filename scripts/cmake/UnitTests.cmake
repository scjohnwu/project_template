# Catch2 - CTest integration requires direct injection in root CMakeLists.txt
macro(add_unit_tests)
  aux_source_directory(tests/unit TestSources)
  include_directories(${CMAKE_SOURCE_DIR}/sources ${CMAKE_SOURCE_DIR}/includes)

  vcpkg_add_packages(Catch2)
  find_package(Catch2 REQUIRED)

  add_executable(tests ${TestSources})

  # test framework and project libraries
  target_link_libraries(tests Catch2::Catch2 ${PROJECT_LIBS})

  include(CTest)
  include(Catch)

  catch_discover_tests(tests)
endmacro()