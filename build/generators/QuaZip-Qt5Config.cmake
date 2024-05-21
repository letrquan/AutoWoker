########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(QuaZip-Qt5_FIND_QUIETLY)
    set(QuaZip-Qt5_MESSAGE_MODE VERBOSE)
else()
    set(QuaZip-Qt5_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/QuaZip-Qt5Targets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${quazip_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(QuaZip-Qt5_VERSION_STRING "1.4")
set(QuaZip-Qt5_INCLUDE_DIRS ${quazip_INCLUDE_DIRS_RELEASE} )
set(QuaZip-Qt5_INCLUDE_DIR ${quazip_INCLUDE_DIRS_RELEASE} )
set(QuaZip-Qt5_LIBRARIES ${quazip_LIBRARIES_RELEASE} )
set(QuaZip-Qt5_DEFINITIONS ${quazip_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${quazip_BUILD_MODULES_PATHS_RELEASE} )
    message(${QuaZip-Qt5_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


