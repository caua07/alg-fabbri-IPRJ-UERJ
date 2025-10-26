cmake_minimum_required(VERSION 3.16)

# Find dependencies
find_package(Threads REQUIRED)

# Gather test sources (adjust pattern to your layout if needed)
file(GLOB_RECURSE HOMEWORK_TEST_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
)

add_executable(run-tests-homework ${HOMEWORK_TEST_SOURCES})

# Link against the imported targets found above.
# Use benchmark::benchmark and GTest::gtest_main which are standard imported targets.
target_link_libraries(run-tests-homework
  PRIVATE
    GTest::gtest_main
    benchmark::benchmark
    Threads::Threads
)

enable_testing()
add_test(NAME run-tests-homework COMMAND run-tests-homework)
