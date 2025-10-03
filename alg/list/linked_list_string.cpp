#include "bigString.h"
#include <algorithm>

int 
binarySearch(const std::vector<std::pair<int, Node*>>& vector, int target)
{
  int low = 0;
  int high = vector.size() - 1;

  while(low<=high){
    int mid = low + (high-low)/2;

    if (mid == vector.size() - 1) {
      return (target >= vector[mid].first) ? mid : -1;
    }

    if (vector[mid].first == target || (target > vector[mid].first && target < vector[mid+1].first)){
      return mid;
    } else if (vector[mid].first < target){
      low = mid+1;
    } else {
      high = mid-1;
    }
  } 

  return -1;
}


char
bigString::operator[](int index)
{
  if (index >= sum)
    return '\0';

  int res = binarySearch(indexes, index);
  if(res == -1){
    std::cout << "access out of array index\n";  
  }
  std::cout << "indexes target: {" << indexes[res].first << ", " << indexes[res].second << "} \n"; 

  int offset = index - indexes[res].first;
  return indexes[res].second->data[offset];
}

void
LinkedList::index()
{
  indexes.clear();
  Node* cur = head;
  int running_sum = 0;
  while(cur){
    indexes.emplace_back(std::make_pair(running_sum, cur));
    running_sum += std::strlen(cur->data);
    cur = cur->next;
  }
}

void
LinkedList::printData()
{
  for(int i = 0; i<indexes.size(); ++i){
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

int
LinkedList::getSum()
{
  return sum;
}

void 
LinkedList::insert(int pos, const char* txt)
{
  if (pos > size){
    std::cout << "list out of index :(\\n";
    return;
  }

  Node* newNode = create(txt);
  int len = std::strlen(txt);

  if(pos == 0){
    newNode->next = head;
    head = newNode;
  } else {
    Node* cur = head;
    for(int i = 1; i < pos; ++i){
      cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
  }

  size++;
  sum += len;
  index();
}


void 
LinkedList::remove(int pos)
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
    for(int i = 1; i < pos; ++i){
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
