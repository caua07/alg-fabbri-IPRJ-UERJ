# Find the GTest package
find_package(GTest REQUIRED)

# Create the test executable
add_executable(sort_char_test test.cpp)

# Link the test executable against the gtest and gmock libraries
target_link_libraries(sort_char_test PRIVATE sort_char_lib GTest::gtest GTest::gmock)

# Add the test to CTest
add_test(NAME sort_char_test COMMAND sort_char_test)
