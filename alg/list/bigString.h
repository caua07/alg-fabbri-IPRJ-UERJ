#pragma once
#include "linked_list_string.h"

class bigString : public LinkedList {
  public:
    
    char
    operator[] (unsigned int index)
    {
      if(head == nullptr){
        std::cout << "index out of list buffer";
        return -1;
      }
      
      Node* current = head;

      while (true){
        if(std::strlen(current->data) <= index){ 
          if(current->next == nullptr){
            std::cout << "index out of list buffer\n";
            return 'z';
          }
          index -= std::strlen(current->data);
          current = current->next;
        } else {
          std::cout << "found node to print\n";
          std::cout << current->data[index];
          return current->data[index];
        }
      }

      

      return -1;
    }

    size_t
    binarySearch(const char* txt,auto arr, int left, int right)
    {
      if(left < right) {
        int mid = left+(right-left)/2;

        if(txt[mid] > 
      }
    }
};
