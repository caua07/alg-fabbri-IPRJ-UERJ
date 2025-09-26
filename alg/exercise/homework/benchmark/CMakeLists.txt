add_executable(bm-homework bm_homework.cpp)
target_link_libraries(bm-homework PRIVATE homework benchmark::benchmark)
set_property(GLOBAL APPEND PROPERTY BENCHMARK_TARGETS bm-homework)
