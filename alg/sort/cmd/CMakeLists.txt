# Create the executable for the command-line tool
add_executable(sort-char-cmd main.cpp)

# Link the executable against the library that we defined in the parent directory
target_link_libraries(sort-char-cmd PRIVATE sort_char_lib)
