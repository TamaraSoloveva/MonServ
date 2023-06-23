
add_executable(MonSrc_tst testInter.cpp testInter.h ${COMMON_SRCS})

target_include_directories(MonSrc_tst PUBLIC ${CMAKE_SOURCE_DIR})

#find_package(Qt5 COMPONENTS TESTS REQUIRED)

#target_link_libraries(MonSrc_tst PRIVATE  Qt${QT_VERSION_MAJOR}::Test)


