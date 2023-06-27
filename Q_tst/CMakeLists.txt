
add_executable(MonSrc_tst testInter.cpp test_GUI.cpp testInter.h ${COMMON_SRCS})

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Test)

target_include_directories(MonSrc_tst PUBLIC ${CMAKE_SOURCE_DIR})

#find_package(Qt5 COMPONENTS TESTS REQUIRED)

target_link_libraries(MonSrc_tst PRIVATE  Qt${QT_VERSION_MAJOR}::Test)


