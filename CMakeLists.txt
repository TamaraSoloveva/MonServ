cmake_minimum_required(VERSION 3.5)

project(MonServ VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets  REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS SerialPort REQUIRED)

set(PROJECT_SOURCES
        main.cpp mainwindow.cpp mainwindow.h ui_MonServ.h outTimerClass.cpp outTimerClass.h parseData.cpp parseData.h
        script.cpp script.h common.h ui_portWrRd.h ui_memWrRd.h memloadfile.cpp memloadfile.h Pack.h monOperations.cpp
        monOperations.h extLineEdit.cpp extLineEdit.h Messages.h Messages.cpp MAIN_INCLUDES.h WorkingStrings.h textDocument.cpp textDocument.h
        report.cpp report.h hexspinbox.cpp hexspinbox.h outThread.cpp outThread.h Work_variables.h baseCommandClass.cpp baseCommandClass.h wrInfoClass.cpp
        wrInfoClass.h outputConsole.cpp outputConsole.h )


qt5_add_resources(RSS_SOURCES resources.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MonServ
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MonServ APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MonServ SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MonServ
            ${PROJECT_SOURCES}
            ${RSS_SOURCES}
        )
    endif()
endif()

target_link_libraries(MonServ PRIVATE
       Qt${QT_VERSION_MAJOR}::Widgets
       Qt${QT_VERSION_MAJOR}::SerialPort )


set_target_properties(MonServ PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


#enable_testing(true)

#add_subdirectory(Q_tst)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MonServ)
endif()

