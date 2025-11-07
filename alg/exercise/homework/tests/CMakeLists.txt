cmake_minimum_required(VERSION 3.16)

find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB HOMEWORK_TEST_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
)

add_executable(run-tests-homework ${HOMEWORK_TEST_SOURCES})

target_link_libraries(run-tests-homework
  PRIVATE
    homework
    GTest::gtest_main
    GTest::gtest
)

gtest_discover_tests(run-tests-homework)
