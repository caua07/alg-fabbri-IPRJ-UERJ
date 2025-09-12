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
    insert(size_t pos, const char* text)
    {
      if(pos > count){
        std::cout << "pos does not exit in list" << '\n';
        return;
      }

      Node* newNode = (Node*)malloc(sizeof(Node));
      newNode->next = nullptr;
      newNode->value = (char*)malloc(std::strlen(text) + 1);

      strcpy(newNode->value, text);
      
      Node* current = head;
      for(size_t i = 0; i < pos-1; ++i){
        current = current->next;
      }

      newNode->next = current->next;
      current->next = newNode;
    }

    void
    remove(size_t pos)
    {
      if(pos > count){
        std::cout << "pos does not exit in list" << '\n';
        return;
      }

      Node* prev = nullptr;
      Node* current = head;
      for(size_t i = 0; i < pos; ++i){
        prev = current;
        current = current->next;
      }
      
      if(current->next != nullptr){
        prev->next = nullptr;
      } else {
        prev->next = current->next;
      }

        free(current->value);
        free(current);
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
};
