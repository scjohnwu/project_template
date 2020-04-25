set(VCPKG_SUPORT VERSION 1.0)
set(VCPKG_REPO "https://github.com/microsoft/vcpkg.git")

# must be called before the project() function!
function(vcpkg_init_toolchain)
  set(VCPKG_PATH "${CMAKE_SOURCE_DIR}/vcpkg")
  set(VCPKG_PATH ${VCPKG_PATH} PARENT_SCOPE)
  set(CMAKE_TOOLCHAIN_FILE 
      "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake"
      PARENT_SCOPE)

  # git is necessary dependency
  find_package(Git)
  if(NOT Git_FOUND)
    message(FATAL_ERROR "Git has not been found")
  endif()
 
  # clone the official repo
  if(NOT EXISTS ${VCPKG_PATH})
    execute_process(COMMAND ${GIT_EXECUTABLE} "clone" ${VCPKG_REPO} ${VCPKG_PATH}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})  

    # failed to clone
    if(NOT EXISTS ${VCPKG_PATH})
      message(FATAL_ERROR "Could not clone vcpkg from ${VCPKG_REPO}")
    endif()
  endif()
 
  set(VCPKG_TOOLCHAIN_ENABLED TRUE PARENT_SCOPE)
endfunction()

# must be called after project() function
function(vcpkg_init)
  if(NOT DEFINED VCPKG_TOOLCHAIN_ENABLED)
    message(FATAL_ERROR "Toolchain must be initialized first!")
  endif()

  # early return if already enabled
  if(DEFINED VCPKG_SUPPORT_ENABLED)
    return()
  endif()

  if(MSVC)
    set(VCPKG_BIN "${VCPKG_PATH}/vcpkg.exe")
  else()
    set(VCPKG_BIN "${VCPKG_PATH}/vcpkg")
  endif()

  # build vcpkg binary
  if(NOT EXISTS ${VCPKG_BIN})
    if(MSVC)
      execute_process(COMMAND "cmd" "/c" "${VCPKG_PATH}/bootstrap-vcpkg.bat")
    else()
      execute_process(COMMAND "sh" "-c" "${VCPKG_PATH}/bootstrap-vcpkg.sh")
    endif()

    # failed to build
    if(NOT EXISTS ${VCPKG_BIN})
      message(FATAL_ERROR "Could not build vcpkg")
    endif()
  endif()

  # set external binary path
  set(VCPKG_BIN ${VCPKG_BIN} PARENT_SCOPE)

  # set prefix triplet which defines target architecture
  if(MSVC)
    set(VCPKG_TRIPLET "x64-windows" PARENT_SCOPE)
  elseif(APPLE)
    set(VCPKG_TRIPLET "x64-osx" PARENT_SCOPE)
  else()
    set(VCPKG_TRIPLET "x64-linux" PARENT_SCOPE)
  endif()
  
  # set support flag to avoid repeated initialization
  set(VCPKG_SUPPORT_ENABLED TRUE PARENT_SCOPE)
endfunction()

function(vcpkg_add_packages)
  # should call vcpkg_init() first
  if(NOT DEFINED VCPKG_SUPPORT_ENABLED)
    message(FATAL_ERROR "vcpkg_add_packages requires VCPKG_SUPPORT_ENABLED")
  endif()

  # install each package, in case if package is already installed appropriate
  # message is reported by vcpkg itself
  foreach(package IN LISTS ARGN)
    message(" -- Adding package ${package}...")
    execute_process(COMMAND ${VCPKG_BIN} "install" ${package}:${VCPKG_TRIPLET}
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
                    OUTPUT_QUIET)  
  endforeach()
endfunction()
