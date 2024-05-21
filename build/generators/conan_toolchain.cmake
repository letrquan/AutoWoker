

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()




########## generic_system block #############
# Definition of system, platform and toolset
#############################################


set(CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "" FORCE)

message(STATUS "Conan toolchain: CMAKE_GENERATOR_TOOLSET=v143")
set(CMAKE_GENERATOR_TOOLSET "v143" CACHE STRING "" FORCE)






# Definition of VS runtime, defined from build_type, compiler.runtime, compiler.runtime_type
cmake_policy(GET CMP0091 POLICY_CMP0091)
if(NOT "${POLICY_CMP0091}" STREQUAL NEW)
    message(FATAL_ERROR "The CMake policy CMP0091 must be NEW, but is '${POLICY_CMP0091}'")
endif()
set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Release>:MultiThreadedDLL>")

# Definition of CMAKE_VS_DEBUGGER_ENVIRONMENT
set(CMAKE_VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:Release>:C:/Users/quan2/.conan2/p/b/quazib051f4879b682/p/bin;C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin;C:/Users/quan2/.conan2/p/opensdb2426aea165e/p/bin;C:/Users/quan2/.conan2/p/pcre2e09694aa47719/p/bin;C:/Users/quan2/.conan2/p/doubl7f4178a78728c/p/bin;C:/Users/quan2/.conan2/p/freet32e1b30696343/p/bin;C:/Users/quan2/.conan2/p/brotl79757a5cae055/p/bin;C:/Users/quan2/.conan2/p/libjp0a77fd78bf747/p/bin;C:/Users/quan2/.conan2/p/libpndb3c6d0c34302/p/bin;C:/Users/quan2/.conan2/p/sqlitb5ab857f87dc0/p/bin;C:/Users/quan2/.conan2/p/libpqd244a5d06e603/p/bin;C:/Users/quan2/.conan2/p/opena005d0fd6b1bf8/p/bin;C:/Users/quan2/.conan2/p/zstd47f7663753ed0/p/bin;C:/Users/quan2/.conan2/p/md4cf1f8b7cdadac5/p/bin;C:/Users/quan2/.conan2/p/zlib6f797a4dd16fb/p/bin;C:/Users/quan2/.conan2/p/bzip2e06444d88ab4f/p/bin>;%PATH%")


message(STATUS "Conan toolchain: C++ Standard 14 with extensions OFF")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(APPEND CONAN_CXX_FLAGS " /MP12")
string(APPEND CONAN_C_FLAGS " /MP12")

# Conan conf flags start: Release
# Conan conf flags end

foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
list(PREPEND CMAKE_MODULE_PATH "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5LinguistTools" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Qml" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Widgets" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Gui" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/bin" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Core" "C:/Users/quan2/.conan2/p/opensdb2426aea165e/p/lib/cmake")
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The explicitly defined "builddirs" of "host" context dependencies must be in PREFIX_PATH
list(PREPEND CMAKE_PREFIX_PATH "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5LinguistTools" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Qml" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Widgets" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Gui" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/bin" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib/cmake/Qt5Core" "C:/Users/quan2/.conan2/p/opensdb2426aea165e/p/lib/cmake")
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/quan2/.conan2/p/b/quazib051f4879b682/p/lib" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/plugins/audio" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/plugins/mediaservice" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/plugins/playlistformats" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/lib" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/plugins/sqldrivers" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/plugins/styles" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/plugins/platforms" "C:/Users/quan2/.conan2/p/opensdb2426aea165e/p/lib" "C:/Users/quan2/.conan2/p/pcre2e09694aa47719/p/lib" "C:/Users/quan2/.conan2/p/doubl7f4178a78728c/p/lib" "C:/Users/quan2/.conan2/p/freet32e1b30696343/p/lib" "C:/Users/quan2/.conan2/p/brotl79757a5cae055/p/lib" "C:/Users/quan2/.conan2/p/libjp0a77fd78bf747/p/lib" "C:/Users/quan2/.conan2/p/libpndb3c6d0c34302/p/lib" "C:/Users/quan2/.conan2/p/sqlitb5ab857f87dc0/p/lib" "C:/Users/quan2/.conan2/p/libpqd244a5d06e603/p/lib" "C:/Users/quan2/.conan2/p/opena005d0fd6b1bf8/p/lib" "C:/Users/quan2/.conan2/p/zstd47f7663753ed0/p/lib" "C:/Users/quan2/.conan2/p/md4cf1f8b7cdadac5/p/lib" "C:/Users/quan2/.conan2/p/zlib6f797a4dd16fb/p/lib" "C:/Users/quan2/.conan2/p/bzip2e06444d88ab4f/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/quan2/.conan2/p/b/quazib051f4879b682/p/include/QuaZip-Qt5-1.4" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtMultimediaQuick" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtMultimediaWidgets" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtMultimedia" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQuickTemplates2" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQuickControls2" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtHelp" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtDesigner" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtUiTools" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtUiPlugin" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQuickTest" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQmlWorkerScript" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQuickShapes" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQuickWidgets" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQuick" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQmlModels" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtQml" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtXml" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtConcurrent" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtOpenGLExtensions" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtOpenGL" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtTest" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtSql" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtNetwork" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtWindowsUIAutomationSupport" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtPrintSupport" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtWidgets" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtAccessibilitySupport" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtThemeSupport" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtFontDatabaseSupport" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtEventDispatcherSupport" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtGui" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/include/QtCore" "C:/Users/quan2/.conan2/p/b/qt8d3a85f9cf233/p/bin/archdatadir/mkspecs/win32-msvc" "C:/Users/quan2/.conan2/p/opensdb2426aea165e/p/include" "C:/Users/quan2/.conan2/p/pcre2e09694aa47719/p/include" "C:/Users/quan2/.conan2/p/doubl7f4178a78728c/p/include" "C:/Users/quan2/.conan2/p/freet32e1b30696343/p/include" "C:/Users/quan2/.conan2/p/freet32e1b30696343/p/include/freetype2" "C:/Users/quan2/.conan2/p/brotl79757a5cae055/p/include" "C:/Users/quan2/.conan2/p/brotl79757a5cae055/p/include/brotli" "C:/Users/quan2/.conan2/p/libjp0a77fd78bf747/p/include" "C:/Users/quan2/.conan2/p/libpndb3c6d0c34302/p/include" "C:/Users/quan2/.conan2/p/sqlitb5ab857f87dc0/p/include" "C:/Users/quan2/.conan2/p/libpqd244a5d06e603/p/include" "C:/Users/quan2/.conan2/p/opena005d0fd6b1bf8/p/include" "C:/Users/quan2/.conan2/p/opena005d0fd6b1bf8/p/include/AL" "C:/Users/quan2/.conan2/p/zstd47f7663753ed0/p/include" "C:/Users/quan2/.conan2/p/md4cf1f8b7cdadac5/p/include" "C:/Users/quan2/.conan2/p/zlib6f797a4dd16fb/p/include" "C:/Users/quan2/.conan2/p/bzip2e06444d88ab4f/p/include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration


if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()
