cmake_minimum_required(VERSION 3.5)

project(AutoWorker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Sql Concurrent)  # Add Sql here
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Sql Concurrent)  # And here
set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AutoWorker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        MCommon/json_settings.h MCommon/json_settings.cpp

        maxcare/SettingsTool.h
        Form/loginwindow.h Form/loginwindow.cpp Form/loginwindow.ui
        MCommon/AwApi.h

        MCommon/RequestParams.h
        MCommon/requesthandle.h MCommon/requesthandle.cpp
        Utils/Utils.h

        Form/mainwindow.h Form/mainwindow.cpp Form/mainwindow.ui
        MCommon/Common.h
        maxcare/Language.h
        maxcare/Base.h
        maxcare/FileHelper.h
        Form/downloaddialog.h Form/downloaddialog.cpp Form/downloaddialog.ui
        maxcare/Enum/StatusChromeAccount.h
        maxcare/Enum/GetContentStatusChrome.h
        maxcare/emailhelper.h maxcare/emailhelper.cpp
        maxcare/SettingsTool.cpp
        maxcare/setupfolder.h maxcare/setupfolder.cpp
        MCommon/connector.h MCommon/connector.cpp
        maxcare/Language.cpp
        maxcare/Base.cpp
        MCommon/Common.cpp
        MCommon/AwApi.cpp
        MCommon/commonsql.h MCommon/commonsql.cpp
        MCommon/chrome.h MCommon/chrome.cpp

        maxcare/interactsql.h maxcare/interactsql.cpp
        maxcare/updatestatus.h maxcare/updatestatus.cpp
        CloneDatabase/clonedatabase.h CloneDatabase/clonedatabase.cpp
        CloneDatabase/connectsqlite.h CloneDatabase/connectsqlite.cpp

        maxcare/collectionhelper.h maxcare/collectionhelper.cpp
        maxcare/datagridviewhelper.h maxcare/datagridviewhelper.cpp
        Form/fcauhinhhienthi.h Form/fcauhinhhienthi.cpp Form/fcauhinhhienthi.ui
        Form/fimportaccount.h Form/fimportaccount.cpp Form/fimportaccount.ui
        maxcare/MessageBoxHelper.h
        Form/faddfile.h Form/faddfile.cpp Form/faddfile.ui
        Form/fimportaccountformatinput.h Form/fimportaccountformatinput.cpp Form/fimportaccountformatinput.ui
        maxcare/StringHelper.h
        Form/fchonthumuc.h Form/fchonthumuc.cpp Form/fchonthumuc.ui
        MCommon/CommonRequest.h
        MCommon/CommonChrome.h
        resource.qrc
        maxcare/ImapHelper.h
        maxcare/ImapHelper.cpp
        Table/customtablemodel.h Table/customtablemodel.cpp
        Form/fcauhinhtuongtac.h Form/fcauhinhtuongtac.cpp Form/fcauhinhtuongtac.ui
        Form/fdanhsachkichban_old.h Form/fdanhsachkichban_old.cpp Form/fdanhsachkichban_old.ui
        maxcare/KichBan/interactconnector.h maxcare/KichBan/interactconnector.cpp
        Form/fcauhinhchung.h Form/fcauhinhchung.cpp Form/fcauhinhchung.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AutoWorker APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AutoWorker SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AutoWorker
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AutoWorker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Concurrent)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AutoWorker)
endif()
set_target_properties(AutoWorker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AutoWorker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AutoWorker)
endif()
