#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>

struct Node {
  char* data;
  Node* next;
};

class LinkedList {
  protected:
    Node* head;
    size_t size;
    size_t sum;
    std::vector<std::pair<size_t, Node*>> indexes;
    void index();

  public:
    //constructor
    LinkedList() : head(nullptr), size(0), sum(0) {}
    Node* create(const char* txt);

    //destructor
    ~LinkedList();

    //tests
    void printData();

    //display data
    size_t getSum();
    void print();

    //insert
    void insert(size_t pos, const char*);

    //remove
    void remove(size_t pos);
};
