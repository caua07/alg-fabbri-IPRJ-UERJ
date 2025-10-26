add_library(
  bst_lib
  tree.cpp
  graph.cpp
  dynagraph.c
  dynagraph.cpp
)

target_include_directories(bst_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(dynagraph-cmd dynagraph.c)
add_executable(dynagraphcpp-cmd dynagraph.cpp)

add_subdirectory(cmd)
add_subdirectory(tests)
