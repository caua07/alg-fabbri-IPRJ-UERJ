#include "gtest/gtest.h"
#include "sort_char.h"
#include <string.h>

TEST(SortCharTest, SimpleSort) {
    char arr[] = "badcfe";
    sort_char_array(arr, 6);
    ASSERT_STREQ(arr, "abcdef");
}

TEST(SortCharTest, EmptySort) {
    char arr[] = "";
    sort_char_array(arr, 0);
    ASSERT_STREQ(arr, "");
}

TEST(SortCharTest, SortedSort) {
    char arr[] = "abcdef";
    sort_char_array(arr, 6);
    ASSERT_STREQ(arr, "abcdef");
}
