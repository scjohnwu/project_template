macro(set_target_naming)
  set(CMAKE_DEBUG_POSTFIX "debug")
  if( ${CMAKE_SIZEOF_VOID_P} EQUAL 8 )
    set(GENERATOR_ARCH "x64")
  else()
    set(GENERATOR_ARCH "x86")
  endif()

  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
endmacro()

macro(add_apps)
  add_subdirectory(apps)
  get_directory_property(targets DIRECTORY sources BUILDSYSTEM_TARGETS)
  foreach(target IN LISTS targets)
    get_target_property(target_type ${target} TYPE)
    if(${target_type} STREQUAL "EXECUTABLE")
      # set target postfixes
      set_target_properties(${target} 
                            PROPERTIES 
                            DEBUG_POSTFIX 
                            _${GENERATOR_ARCH}_${CMAKE_DEBUG_POSTFIX}
                            )
      list(APPEND PROJECT_APPS ${target})
    endif()
  endforeach()
endmacro()

macro(add_libs)
  add_subdirectory(sources)
  get_directory_property(targets DIRECTORY sources BUILDSYSTEM_TARGETS)
  foreach(target IN LISTS targets)
    get_target_property(target_type ${target} TYPE)
    if(${target_type} STREQUAL "STATIC_LIBRARY")
      # set target postfixes
      set_target_properties(${target} 
                            PROPERTIES 
                            DEBUG_POSTFIX 
                            _${GENERATOR_ARCH}_${CMAKE_DEBUG_POSTFIX}
                            )
      list(APPEND PROJECT_LIBS ${target})
    endif()
  endforeach()
endmacro()