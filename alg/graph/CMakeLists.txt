add_library(
  bst_lib
  tree.cpp
  graph.cpp
)

target_include_directories(bst_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cmd)
add_subdirectory(tests)
