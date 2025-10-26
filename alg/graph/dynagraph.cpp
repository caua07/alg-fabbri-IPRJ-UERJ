#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <new>

#define GRAPH_BUFFER 100

class no;
struct lista;

struct lista {
  no* no;
  int peso;
  lista* next;
};

class no {
  private:
    char* name;
    lista* connectionHead;
    uint64_t size;
  
  public:
    no(const char* nameArg = nullptr) : connectionHead(nullptr) {
      if (nameArg != nullptr) {
        name = (char*)malloc(sizeof(char) * (std::strlen(nameArg) + 1));
        if (!name) {
          std::cerr << "Error: name malloc failled.\n";
          throw std::bad_alloc();
        }
        std::strcpy(name, nameArg);
      } else {
        name = nullptr;
      }
    }

    ~no() {
      lista* current = connectionHead;
      while ( current != nullptr ) {
        lista* next = current->next;
        free(current);
        current = next;
      }
      connectionHead = nullptr;
    }

    void
    print_connections() {
      lista* current = connectionHead;
      if ( current == nullptr ) {
        std::cout << "no conections here.\n";
      }
      while ( current != nullptr ) {
        std::cout << current->no->name;
        current = current->next;
      } 
    }

    void
    connect(no* no, int peso) {
      if (connectionHead == nullptr){
        lista* newNode = (lista*)malloc(sizeof(lista));
        newNode->no = no;
        newNode->peso = peso;
        newNode->next = nullptr;
        connectionHead = newNode;
      } else {
        lista* newNode = (lista*)malloc(sizeof(lista));
        newNode->no = no;
        newNode->peso = peso;
        newNode->next = connectionHead;
        connectionHead = newNode;
      }
      ++size;
    }

    void
    connect_two_way(no* no, int peso) {
      this->connect(no, peso);
      no->connect(this, peso);
    }

    void
    remove(no* no){
      if (connectionHead == nullptr) {
        std::cout << "List is empty\n";
        return;
      }

      lista* current = connectionHead;

      if (current->no == no) {
        connectionHead = connectionHead->next;
        free(current);
        --size;
        return;
      }

      while (current != nullptr) {

        if ((current->next != nullptr) && (current->next->no == no)) {
          --size;
          if (current->next->next != nullptr) {
            lista* to_delete = current->next;  
            current->next = current->next->next;
            free(to_delete);
            return;
          } else {
            current = current->next;
            free(current);
            return;
          }

        }
      }
      std::cout << "no nao foi achado na lista de conections.\n";
      return;
    }
};

class graph {
  private: 
    no** nodes;
    uint64_t size;

  public:
    graph() {
      nodes = (no**)malloc(sizeof(no*) * GRAPH_BUFFER);
      size = 0;
    } 

    ~graph() {
    }

    no*
    insert(const char* name) {
      no* newNode = new no(name);
      nodes[size] = newNode;
      ++size;
      return newNode;
    }
};



int 
main()
{
  graph graph;
  auto node1 = graph.insert("brenicio");
  auto node2 = graph.insert("caua");

  node1->connect_two_way(node2, 50);

  
  node1->print_connections();
  node2->print_connections();
  return 1;
}