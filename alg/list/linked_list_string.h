#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstring>
#include <iostream> 
#include <cstdlib>

struct Node {
  char* data;
  Node* next;
};

class LinkedList {
  protected:
    Node* head;

  public:

    LinkedList(){
      head = nullptr;
    }

    void
    insert(size_t pos, const char* text)
    {
      Node* newNode = (Node*)malloc(sizeof(Node));
      if(!newNode) return;
      newNode->data = (char*)malloc(std::strlen(text) + 1);
      if(!newNode->data){
        free(newNode);
        return;
      }
      std::strcpy(newNode->data, text);
      newNode->next = nullptr;

      if(pos == 0){
        newNode->next = head;
        head = newNode;
        return;
      }
      
      Node* current = head;
      for(size_t i = 0; i < pos - 1; ++i){
        if(current == nullptr){
          std::cout << "position out of list index :(";
          free(newNode->data);
          free(newNode);
          return;
        }
        current = current->next;
      }

      if(current == nullptr){
        std::cout << "position out of list index :(";
        free(newNode->data);
        free(newNode);
        return;
      }

      newNode->next = current->next;
      current->next = newNode;
    }

    void
    remove(size_t pos)
    {
      if (head == nullptr) {
        std::cout << "position out of list index :(" << '\n';
        return;
      }

      if (pos == 0) {
        Node* to_delete = head;
        head = head->next;
        free(to_delete->data);
        free(to_delete);
        return;
      }

      Node* current = head;
      for (size_t i = 0; i < pos - 1; ++i) {
        if (current->next == nullptr) {
          std::cout << "position out of list index :(" << '\n';
          return;
        }
        current = current->next;
      }

      if (current->next == nullptr) {
        std::cout << "position out of list index :(" << '\n';
        return;
      }

      Node* to_delete = current->next;
      current->next = to_delete->next;
      free(to_delete->data);
      free(to_delete);
    }

    void
    print()
    {
      Node* temp = head;
      while(temp != nullptr){
        std::cout << temp->data << "->";
        temp = temp->next;
      }
      std::cout << "NULL" << '\n';
    }
};

#endif // LINKEDLIST_H
