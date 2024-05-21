########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(quazip_COMPONENT_NAMES "")
if(DEFINED quazip_FIND_DEPENDENCY_NAMES)
  list(APPEND quazip_FIND_DEPENDENCY_NAMES Qt5 ZLIB BZip2)
  list(REMOVE_DUPLICATES quazip_FIND_DEPENDENCY_NAMES)
else()
  set(quazip_FIND_DEPENDENCY_NAMES Qt5 ZLIB BZip2)
endif()
set(Qt5_FIND_MODE "NO_MODULE")
set(ZLIB_FIND_MODE "NO_MODULE")
set(BZip2_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(quazip_PACKAGE_FOLDER_RELEASE "C:/Users/quan2/.conan2/p/b/quazib051f4879b682/p")
set(quazip_BUILD_MODULES_PATHS_RELEASE )


set(quazip_INCLUDE_DIRS_RELEASE "${quazip_PACKAGE_FOLDER_RELEASE}/include/QuaZip-Qt5-1.4")
set(quazip_RES_DIRS_RELEASE )
set(quazip_DEFINITIONS_RELEASE "-DQUAZIP_STATIC")
set(quazip_SHARED_LINK_FLAGS_RELEASE )
set(quazip_EXE_LINK_FLAGS_RELEASE )
set(quazip_OBJECTS_RELEASE )
set(quazip_COMPILE_DEFINITIONS_RELEASE "QUAZIP_STATIC")
set(quazip_COMPILE_OPTIONS_C_RELEASE )
set(quazip_COMPILE_OPTIONS_CXX_RELEASE )
set(quazip_LIB_DIRS_RELEASE "${quazip_PACKAGE_FOLDER_RELEASE}/lib")
set(quazip_BIN_DIRS_RELEASE )
set(quazip_LIBRARY_TYPE_RELEASE STATIC)
set(quazip_IS_HOST_WINDOWS_RELEASE 1)
set(quazip_LIBS_RELEASE quazip1-qt5)
set(quazip_SYSTEM_LIBS_RELEASE )
set(quazip_FRAMEWORK_DIRS_RELEASE )
set(quazip_FRAMEWORKS_RELEASE )
set(quazip_BUILD_DIRS_RELEASE )
set(quazip_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(quazip_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${quazip_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${quazip_COMPILE_OPTIONS_C_RELEASE}>")
set(quazip_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${quazip_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${quazip_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${quazip_EXE_LINK_FLAGS_RELEASE}>")


set(quazip_COMPONENTS_RELEASE )