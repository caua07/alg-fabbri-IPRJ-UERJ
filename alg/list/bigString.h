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

};
