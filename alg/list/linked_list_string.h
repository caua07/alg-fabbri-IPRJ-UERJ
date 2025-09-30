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
    int* arrS;
    size_t sum;
    Node** arrP;
    int capacityS, size, capacityP;

  private:
    void
    incrementData(size_t len, Node* node){
      sum += len;
      arrS[size] = sum;
      arrP[size] = node;
      ++size;
    }

  public:

    LinkedList(){
      head = nullptr;
      sum = 0;
      capacityS = 124;
      capacityP = 1024;
      arrS = (int*)malloc(sizeof(int)*capacityS);
      arrP =(Node**)malloc(sizeof(Node*)*capacityP);
      size = 0;
    }

    ~LinkedList(){
      Node* temp = head;
      free(arrS);
      free(arrP);
    }

    size_t
    getSum()
    {
      return sum;
    }

    void
    printData()
    {
      std::cout << '\n';
      std::cout << '\n';
      std::cout << "sizes\n";
      for(int i = 0; i < size; ++i){
        std::cout << arrS[i] << " ";
      }
      std::cout << '\n';
      std::cout << "pointers\n";
      for(int i = 0; i < size; ++i){
        std::cout << arrP[i] << " ";
      }
      std::cout << '\n';
      std::cout << '\n';
    }

    void
    insert(size_t pos, const char* text)
    {
      Node* newNode = (Node*)malloc(sizeof(Node));
      size_t len = std::strlen(text);
      if(!newNode) return;
      newNode->data = (char*)malloc(len + 1);
      if(!newNode->data){
        free(newNode);
        return;
      }
      std::strcpy(newNode->data, text);
      newNode->next = nullptr;
      incrementData(len, newNode);
      printData();


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
      sum -= std::strlen(current->next->data);

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
