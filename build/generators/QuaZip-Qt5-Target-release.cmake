# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(quazip_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(quazip_FRAMEWORKS_FOUND_RELEASE "${quazip_FRAMEWORKS_RELEASE}" "${quazip_FRAMEWORK_DIRS_RELEASE}")

set(quazip_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET quazip_DEPS_TARGET)
    add_library(quazip_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET quazip_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${quazip_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${quazip_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:qt::qt;ZLIB::ZLIB;BZip2::BZip2>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### quazip_DEPS_TARGET to all of them
conan_package_library_targets("${quazip_LIBS_RELEASE}"    # libraries
                              "${quazip_LIB_DIRS_RELEASE}" # package_libdir
                              "${quazip_BIN_DIRS_RELEASE}" # package_bindir
                              "${quazip_LIBRARY_TYPE_RELEASE}"
                              "${quazip_IS_HOST_WINDOWS_RELEASE}"
                              quazip_DEPS_TARGET
                              quazip_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "quazip"    # package_name
                              "${quazip_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${quazip_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET QuaZip::QuaZip
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${quazip_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${quazip_LIBRARIES_TARGETS}>
                 )

    if("${quazip_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET QuaZip::QuaZip
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     quazip_DEPS_TARGET)
    endif()

    set_property(TARGET QuaZip::QuaZip
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${quazip_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET QuaZip::QuaZip
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${quazip_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET QuaZip::QuaZip
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${quazip_LIB_DIRS_RELEASE}>)
    set_property(TARGET QuaZip::QuaZip
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${quazip_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET QuaZip::QuaZip
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${quazip_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(quazip_LIBRARIES_RELEASE QuaZip::QuaZip)
