cmake_minimum_required(VERSION 3.10)

include(scripts/cmake/VCPKGSupport.cmake)
vcpkg_init_toolchain()

project(project_template)

set(CMAKE_CXX_STANDARD 17)

vcpkg_init()

# hack to spread warning settings
add_library(project_warnings INTERFACE)

include(scripts/cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(scripts/cmake/DoxygenSupport.cmake)
doxygen_init()

include(scripts/cmake/Targets.cmake)
set_target_naming()

# Every project is a library, static or shared
add_libs()

# Add apps based on project library
add_apps()

include(scripts/cmake/UnitTests.cmake)
add_unit_tests()



