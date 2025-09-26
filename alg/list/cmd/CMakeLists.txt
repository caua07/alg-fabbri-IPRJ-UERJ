add_executable(linked_list_string-cmd main.cpp)

target_link_libraries(linked_list_string-cmd linked_lib benchmark::benchmark)

set_property(GLOBAL APPEND PROPERTY BENCHMARK_TARGETS linked_list_string-cmd)
