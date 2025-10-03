#include "bigString.h"
#include <algorithm>

char
bigString::operator[](size_t index)
{
  if (index >= sum)
    return '\0';

  auto it = std::upper_bound(indexes.begin(), indexes.end(), index,
    [](size_t val, const std::pair<size_t, Node*>& pair) {
      return val < pair.first;
  });

  auto target_it = std::prev(it);
  size_t local_index = index - target_it->first;
  return target_it->second->data[local_index];
}

void
LinkedList::index()
{
  indexes.clear();
  Node* cur = head;
  while(cur != nullptr){
    indexes.emplace_back(std::make_pair(sum, cur));
    cur = cur->next;
  }
}

void
LinkedList::printData()
{
  for(size_t i = 0; i<indexes.size(); ++i){
    std::cout << "{" << indexes[i].first << ", " << indexes[i].second << "} "; 
  }
}

void 
LinkedList::print()
{
  Node* cur = head;
  while(cur != nullptr){
    std::cout << cur->data << " -> ";
    cur = cur->next;
  }
  std::cout << "NULL";
  return;
}

Node* 
LinkedList::create(const char* txt)
{
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->next = nullptr;
  newNode->data = (char*)malloc((std::strlen(txt) + 1) * sizeof(char));
  std::strcpy(newNode->data, txt);
  return newNode;
}

size_t
LinkedList::getSum()
{
  return sum;
}

void 
LinkedList::insert(size_t pos, const char* txt)
{
  if (pos > size){
    std::cout << "list out of index :(\\n";
    return;
  }

  Node* newNode = create(txt);
  size_t len = std::strlen(txt);

  if(pos == 0){
    newNode->next = head;
    head = newNode;
  } else {
    Node* cur = head;
    for(size_t i = 1; i < pos; ++i){
      cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
  }

  size++;
  sum += len;
  index();
  printData();
}

void 
LinkedList::remove(size_t pos)
{
  if (pos >= size) {
    std::cout << "list out of index :(\\n";
    return;
  }

  Node* to_delete;
  if(pos == 0){
    to_delete = head;
    head = head->next;
  } else {
    Node* cur = head;
    for(size_t i = 1; i < pos; ++i){
      cur = cur->next;
    }
    to_delete = cur->next;
    cur->next = to_delete->next;
  }

  sum -= std::strlen(to_delete->data);
  free(to_delete->data);
  free(to_delete);
  size--;
  index();
}


LinkedList::~LinkedList() {
    Node* current = head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
};
