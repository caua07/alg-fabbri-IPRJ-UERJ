add_library(homework homework.cpp)

add_executable(home-exe homework_main.cpp)
target_link_libraries(home-exe PRIVATE homework)

if(alg_BUILD_TESTS)
  add_subdirectory(tests)
endif()
# if(alg_BUILD_BENCHMARKS)
#     add_subdirectory(benchmark)
# endif()
