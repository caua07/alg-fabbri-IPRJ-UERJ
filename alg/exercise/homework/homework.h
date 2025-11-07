#pragma once
#include <cstring>
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <memory>

int run_homework_cli();

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
    insert(size_t pos, const char* text)
    {
      if(pos > count){
        std::cout << "pos does not exist in list" << '\n';
        return;
      }

      Node* newNode = (Node*)malloc(sizeof(Node));
      if (!newNode) return;
      newNode->value = (char*)malloc(std::strlen(text) + 1);
      if (!newNode->value) {
          free(newNode);
          return;
      }
      strcpy(newNode->value, text);
      
      if (pos == 0) {
        newNode->next = head;
        head = newNode;
      } else {
        Node* current = head;
        for(size_t i = 0; i < pos - 1; ++i){
          current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
      }
      count++;
    }

    void
    remove(size_t pos)
    {
      if(pos >= count){
        std::cout << "pos does not exist in list" << '\n';
        return;
      }

      Node* toDelete = head;
      if (pos == 0) {
        head = head->next;
      } else {
        Node* prev = head;
        for (size_t i = 0; i < pos - 1; ++i) {
          prev = prev->next;
        }
        toDelete = prev->next;
        prev->next = toDelete->next;
      }

      free(toDelete->value);
      free(toDelete);
      count--;
    }

    void
    print()
    {
      Node* current = head;
      while(current != nullptr){
        std::cout << current->value << " -> ";
        current = current->next;
      }
      std::cout << "nullptr" << '\n';
    }
};

class DoublyLinked {
private:
    struct Node {
        char* value;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;
    size_t count;

public:
    DoublyLinked() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~DoublyLinked() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            free(current->value);
            free(current);
            current = next;
        }
    }

    void insert(size_t pos, const char* text) {
        if (pos > count) {
            std::cout << "pos does not exist in list" << '\n';
            return;
        }

        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) return;
        newNode->value = (char*)malloc(std::strlen(text) + 1);
        if(!newNode->value) {
            free(newNode);
            return;
        }
        std::strcpy(newNode->value, text);
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (count == 0) {
            head = newNode;
            tail = newNode;
        } else if (pos == 0) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else if (pos == count) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            Node* current = head;
            for (size_t i = 0; i < pos; ++i) {
                current = current->next;
            }
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
        count++;
    }

    void remove(size_t pos) {
        if (pos >= count || head == nullptr) {
            std::cout << "pos does not exist in list" << '\n';
            return;
        }

        Node* toDelete = nullptr;

        if (count == 1) {
            toDelete = head;
            head = nullptr;
            tail = nullptr;
        } else if (pos == 0) {
            toDelete = head;
            head = head->next;
            head->prev = nullptr;
        } else if (pos == count - 1) {
            toDelete = tail;
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            toDelete = head;
            for (size_t i = 0; i < pos; ++i) {
                toDelete = toDelete->next;
            }
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }

        free(toDelete->value);
        free(toDelete);
        count--;
    }

    void print() const {
        Node* current = head;
        std::cout << "nullptr <=> ";
        while (current != nullptr) {
            std::cout << current->value << " <=> ";
            current = current->next;
        }
        std::cout << "nullptr" << '\n';
    }
};

template <typename T>
class CircularBuffer {
private:
    std::unique_ptr<T[]> buffer;
    size_t head;
    size_t tail;
    size_t current_size;
    size_t max_size;
    bool is_full_flag;

public:
    explicit CircularBuffer(size_t capacity)
        : buffer(std::make_unique<T[]>(capacity)),
          head(0),
          tail(0),
          current_size(0),
          max_size(capacity),
          is_full_flag(false) {}

    ~CircularBuffer() {
        while(current_size > 0) {
            T item = buffer[head];
            free(item);
            head = (head + 1) % max_size;
            current_size--;
        }
    }

    void push(T item) {
        if (full()) {
            free(buffer[head]);
            head = (head + 1) % max_size;
            current_size--;
        }
        
        buffer[tail] = item;
        tail = (tail + 1) % max_size;
        current_size++;
        if (current_size == max_size) {
            is_full_flag = true;
        }
    }

    T pop() {
        if (empty()) {
            throw std::runtime_error("Buffer is empty");
        }
        T item = buffer[head];
        head = (head + 1) % max_size;
        current_size--;
        is_full_flag = false;
        return item;
    }

    bool empty() const {
        return current_size == 0;
    }

    bool full() const {
        return current_size == max_size;
    }

    size_t size() const {
        return current_size;
    }

    size_t capacity() const {
        return max_size;
    }

    void print() const {
        if (empty()) {
            std::cout << "Buffer is empty" << '\n';
            return;
        }
        std::cout << "Buffer contents (head to tail):" << '\n';
        for (size_t i = 0; i < current_size; ++i) {
            std::cout << "  " << buffer[(head + i) % max_size] << '\n';
        }
    }
};
