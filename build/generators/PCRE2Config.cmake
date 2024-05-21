########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(PCRE2_FIND_QUIETLY)
    set(PCRE2_MESSAGE_MODE VERBOSE)
else()
    set(PCRE2_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/PCRE2Targets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${pcre2_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(PCRE2_VERSION_STRING "10.42")
set(PCRE2_INCLUDE_DIRS ${pcre2_INCLUDE_DIRS_RELEASE} )
set(PCRE2_INCLUDE_DIR ${pcre2_INCLUDE_DIRS_RELEASE} )
set(PCRE2_LIBRARIES ${pcre2_LIBRARIES_RELEASE} )
set(PCRE2_DEFINITIONS ${pcre2_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${pcre2_BUILD_MODULES_PATHS_RELEASE} )
    message(${PCRE2_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


