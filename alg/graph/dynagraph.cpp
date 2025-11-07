#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <new>
#include <vector>
#include <iomanip>

#define GRAPH_BUFFER 100

class no;
struct lista;

struct lista {
  no* node;
  int peso;
  lista* next;
};

class no {
  private:
    char* name;
    lista* connectionHead;
    uint64_t size;
  
  public:
    no(const char* nameArg = nullptr)
      : name(nullptr), connectionHead(nullptr), size(0) {
      if (nameArg != nullptr) {
        name = (char*)malloc(sizeof(char) * (std::strlen(nameArg) + 1));
        if (!name) {
          std::cerr << "Error: name malloc failled.\n";
          throw std::bad_alloc();
        }
        std::strcpy(name, nameArg);
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
      free(name);
      name = nullptr;
    }

    void
    print_connections() {
      lista* current = connectionHead;
      if ( current == nullptr ) {
        std::cout << "no conections here.\n";
      }
      while ( current != nullptr ) {
        std::cout << current->node->name;
        current = current->next;
      } 
    }

    void
    connect(no* target, int peso) {
      if (connectionHead == nullptr){
        lista* newNode = (lista*)malloc(sizeof(lista));
        newNode->node = target;
        newNode->peso = peso;
        newNode->next = nullptr;
        connectionHead = newNode;
      } else {
        lista* newNode = (lista*)malloc(sizeof(lista));
        newNode->node = target;
        newNode->peso = peso;
        newNode->next = connectionHead;
        connectionHead = newNode;
      }
      ++size;
    }

    void
    connect_two_way(no* target, int peso) {
      this->connect(target, peso);
      target->connect(this, peso);
    }

    void
    remove(no* target){
      if (connectionHead == nullptr) {
        std::cout << "List is empty\n";
        return;
      }

      lista* current = connectionHead;

      if (current->node == target) {
        connectionHead = connectionHead->next;
        free(current);
        --size;
        return;
      }

      while (current != nullptr) {

        if ((current->next != nullptr) && (current->next->node == target)) {
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
        current = current->next;
      }
      std::cout << "no nao foi achado na lista de conections.\n";
      return;
    }

    lista*
    get_connection_head() const {
      return connectionHead;
    }

    const char*
    get_name() const {
      return name ? name : "";
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
      for (uint64_t i = 0; i < size; ++i) {
        delete nodes[i];
      }
      free(nodes);
      nodes = nullptr;
    }

    no*
    insert(const char* name) {
      no* newNode = new no(name);
      nodes[size] = newNode;
      ++size;
      return newNode;
    }

    int
    find_node_index(const no* target) const {
      for (uint64_t i = 0; i < size; ++i) {
        if (nodes[i] == target) {
          return static_cast<int>(i);
        }
      }
      return -1;
    }

    std::vector<std::vector<int>>
    build_adjacency_matrix() const {
      std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));

      for (uint64_t i = 0; i < size; ++i) {
        lista* current = nodes[i]->get_connection_head();
        while (current != nullptr) {
          int column = find_node_index(current->node);
          if (column >= 0) {
            matrix[i][static_cast<size_t>(column)] = current->peso;
          }
          current = current->next;
        }
      }

      return matrix;
    }

    void
    print_adjacency_matrix() const {
      auto matrix = build_adjacency_matrix();

      if (size == 0) {
        std::cout << "Graph is empty.\n";
        return;
      }

      std::cout << "Adjacency matrix:\n";

      std::cout << std::setw(8) << "";
      for (uint64_t j = 0; j < size; ++j) {
        std::cout << std::setw(8) << nodes[j]->get_name();
      }
      std::cout << '\n';

      for (uint64_t i = 0; i < size; ++i) {
        std::cout << std::setw(8) << nodes[i]->get_name();
        for (uint64_t j = 0; j < size; ++j) {
          std::cout << std::setw(8) << matrix[i][static_cast<size_t>(j)];
        }
        std::cout << '\n';
      }
    }
};



int 
main()
{
  graph graph;
  auto node1 = graph.insert("brenicio");
  auto node2 = graph.insert("caua");

  node1->connect_two_way(node2, 50);

  graph.print_adjacency_matrix();

  node1->print_connections();
  node2->print_connections();
  return 1;
}