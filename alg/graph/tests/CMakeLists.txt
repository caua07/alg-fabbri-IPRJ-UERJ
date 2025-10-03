find_package(GTest REQUIRED)

add_executable(test-graph test.cpp)

target_link_libraries(
  test-graph
  bst_lib
  GTest::GTest
  GTest::Main
)

add_test(
  NAME test-graph
  COMMAND test-graph
)