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
    int size;
    int sum;
    std::vector<std::pair<int, Node*>> indexes;
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
    int getSum();
    void print();

    //insert
    void insert(int pos, const char*);

    //remove
    void remove(int pos);
};
