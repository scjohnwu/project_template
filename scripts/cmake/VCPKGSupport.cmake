set(VCPKG_SUPORT VERSION 1.0)
set(VCPKG_REPO "https://github.com/microsoft/vcpkg.git")

function(vcpkg_init)
  # early return if already enabled
  if(DEFINED VCKPG_SUPPORT_ENABLED)
    return()
  endif()

  set(VCPKG_PATH "${CMAKE_SOURCE_DIR}/vcpkg")
  set(VCPKG_PATH ${VCKPG_PATH} PARENT_SCOPE)

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

  if(MSVC)
    set(VCPKG_BIN "${VCPKG_PATH}/vcpkg.exe")
  else()
    set(VCPKG_BIN "${VCPKG_PATH}/vcpkg")
  endif()

  # build vcpkg binary
  if(NOT EXISTS ${VCPKG_BIN})
    if(MSVC)
      execute_process(COMMAND "cmd" "/c" "${VCPKG_PATH}/bootstrap-vcpkg.bat" 
                      WORKING_DIRECTORY ${VCPKG_REPO})
    else()
      execute_process(COMMAND "sh" "-c" "${VCPKG_PATH}/bootstrap-vcpkg.sh"
                      WORKING_DIRECTORY ${VCPKG_REPO})
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
  set(VCPKG_SUPPORT_ENABELD TRUE PARENT_SCOPE)
endfunction()

function(vcpkg_add_libs)

endfunction()