#include "gtest/gtest.h"
#include "../homework.h"

TEST(SinglyLinkedListTest, InsertAndRemove) {
    SinglyLinked list;
    list.insert(0, "hello");
    list.insert(1, "world");
    list.remove(0);
    list.remove(0);
    // The test will pass if it doesn't crash, which is a basic check
    // for memory management issues in insert/remove.
    SUCCEED();
}

TEST(DoublyLinkedListTest, InsertAndRemove) {
    DoublyLinked list;
    list.insert(0, "hello");
    list.insert(1, "world");
    list.remove(0);
    list.remove(0);
    SUCCEED();
}

TEST(CircularBufferTest, PushAndPop) {
    CircularBuffer<char*> buffer(5);
    char* str1 = (char*)malloc(6);
    strcpy(str1, "hello");
    buffer.push(str1);

    char* str2 = (char*)malloc(6);
    strcpy(str2, "world");
    buffer.push(str2);

    char* popped1 = buffer.pop();
    ASSERT_STREQ("hello", popped1);
    free(popped1);

    char* popped2 = buffer.pop();
    ASSERT_STREQ("world", popped2);
    free(popped2);

    ASSERT_TRUE(buffer.empty());
}