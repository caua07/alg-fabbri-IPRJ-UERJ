if(alg_BUILD_TESTS)
  include(GoogleTest)

  add_executable(run-tests-homework test_homework.cpp)
  target_link_libraries(run-tests-homework PRIVATE GTest::gtest_main GTest::gtest)

  gtest_discover_tests(run-tests-homework)
endif()
