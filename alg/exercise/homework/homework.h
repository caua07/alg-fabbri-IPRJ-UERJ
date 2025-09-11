#pragma once
#include <cstring>
#include <iostream>

class SinglyLinked {
  private:
    struct Node {
      char* value;
      Node* next;
      Node() : value(nullptr), next(nullptr) {}
    };
    Node* head;
    size_t count;

  public:
    SinglyLinked() : head(nullptr), count(0) {}
    ~SinglyLinked(){
      Node* current = head;
        while( current != nullptr ) {
          Node* next = current->next;
          free(current->value);
          free(current);
          current = next;
        }
      head = nullptr;
    }

    void
    insert_front(const char* text)
    {
      Node* newNode = (Node*)malloc(sizeof(Node));
      newNode->value = (char*)malloc(std::strlen(text) + 1);
      strcpy(newNode->value, text);
      newNode->next = head;
      head = newNode;
      ++count;
    }

    void
    insert_back(const char* text)
    {
      Node* newNode = (Node*)malloc(sizeof(Node));
      newNode->value = (char*)malloc(std::strlen(text) + 1);
      strcpy(newNode->value, text);
      newNode->next = nullptr;

      if (head == nullptr) {
        head = newNode;
      } else {
        Node* current = head;
        while (current->next != nullptr) {
          current = current->next;
        }
        current->next = newNode;
      }
      ++count;
    }

    void
    remove_front()
    {
      if (head == nullptr) {
        return;
      }
      Node* to_delete = head;
      head = head->next;
      free(to_delete->value);
      free(to_delete);
      --count;
    }

    void
    remove_back()
    {
      if (head == nullptr) {
        return;
      }

      if (head->next == nullptr) {
        free(head->value);
        free(head);
        head = nullptr;
        --count;
        return;
      }

      Node* current = head;
      while (current->next->next != nullptr) {
        current = current->next;
      }

      Node* to_delete = current->next;
      current->next = nullptr;
      free(to_delete->value);
      free(to_delete);
      --count;
    }

    void
    print()
    {
      Node* current = head;
      while(current != nullptr){
        std::cout << current->value << '\n';
        current = current->next;
      }
    }
};

class DoublyLinked{
  private:
    struct Node {
      char* value;
      Node* next;
      Node* prev;
      Node() : value(nullptr), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t count;

  public:
    DoublyLinked() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinked(){
      Node* current = head;
        while( current != nullptr ) {
          Node* next = current->next;
          free(current->value);
          free(current);
          current = next;
        }
      head = nullptr;
      tail = nullptr;
    }

    void
    insert_front(const char* text)
    {
      Node* newNode = (Node*)malloc(sizeof(Node));
      newNode->value = (char*)malloc(std::strlen(text) + 1);
      strcpy(newNode->value, text);
      newNode->prev = nullptr;
      newNode->next = head;

      if (head != nullptr) {
        head->prev = newNode;
      }
      head = newNode;
      if (tail == nullptr) {
        tail = newNode;
      }
      ++count;
    }

    void
    insert_back(const char* text)
    {
      Node* newNode = (Node*)malloc(sizeof(Node));
      newNode->value = (char*)malloc(std::strlen(text) + 1);
      strcpy(newNode->value, text);
      newNode->next = nullptr;
      newNode->prev = tail;

      if (tail != nullptr) {
        tail->next = newNode;
      }
      tail = newNode;
      if (head == nullptr) {
        head = newNode;
      }
      ++count;
    }

    void
    remove_front()
    {
      if (head == nullptr) {
        return;
      }
      Node* to_delete = head;
      head = head->next;
      if (head != nullptr) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
      free(to_delete->value);
      free(to_delete);
      --count;
    }

    void
    remove_back()
    {
      if (tail == nullptr) {
        return;
      }
      Node* to_delete = tail;
      tail = tail->prev;
      if (tail != nullptr) {
        tail->next = nullptr;
      } else {
        head = nullptr;
      }
      free(to_delete->value);
      free(to_delete);
      --count;
    }

    void
    print()
    {
      Node* current = head;
      while(current != nullptr){
        std::cout << current->value << '\n';
        current = current->next;
      }
    }
};

class CircularBuffer {
private:
    char** buffer;
    size_t head;
    size_t tail;
    size_t max_size;
    bool full;

public:
    CircularBuffer(size_t size) : max_size(size), head(0), tail(0), full(false) {
        buffer = (char**)calloc(max_size, sizeof(char*));
    }

    ~CircularBuffer() {
        for (size_t i = 0; i < max_size; ++i) {
            free(buffer[i]);
        }
        free(buffer);
    }

    bool is_full() const {
        return full;
    }

    bool is_empty() const {
        return (!full && (head == tail));
    }

    void push(const char* text) {
        buffer[head] = (char*)realloc(buffer[head], strlen(text) + 1);
        strcpy(buffer[head], text);

        if (full) {
            tail = (tail + 1) % max_size;
        }

        head = (head + 1) % max_size;
        full = (head == tail);
    }

    char* pop() {
        if (is_empty()) {
            return nullptr;
        }

        char* item = buffer[tail];
        buffer[tail] = nullptr;
        full = false;
        tail = (tail + 1) % max_size;

        return item;
    }

    void print() const {
        if (is_empty()) {
            std::cout << "Buffer is empty\n";
            return;
        }
        size_t i = tail;
        if (full) {
            do {
                std::cout << buffer[i] << '\n';
                i = (i + 1) % max_size;
            } while (i != tail);
        } else {
            while (i != head) {
                std::cout << buffer[i] << '\n';
                i = (i + 1) % max_size;
            }
        }
    }
};