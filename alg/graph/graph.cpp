#include "graph.h"
#include <cstring>
#include <queue>
#include <set>

GraphNode*
DFS(GraphNode* begin, const char* target)
{
  if (!begin || begin->visited)
    return nullptr;

  if (strcmp((begin->data), target) == 0){
    return begin;
  }

  begin->visited = true;

  GraphNode* result = nullptr;
  result = DFS(begin->left, target);
  if (result) return result;
  result = DFS(begin->right, target);
  if (result) return result;
  result = DFS(begin->bottom, target);
  if (result) return result;
  result = DFS(begin->top, target);
  if (result) return result;

  return nullptr;
}

GraphNode*
BFS(std::vector<GraphNode*>& paths, GraphNode* begin, const char* target){
  if(!begin)
    return nullptr;

  std::queue<std::pair<GraphNode*, int>> q;
  std::unordered_map<GraphNode*, GraphNode*> parent;
  parent[begin] = nullptr;
  begin->visited = true;
  q.push({begin, 0});


  while (!q.empty()){
    GraphNode* cur = q.front().first;
    int distance = q.front().second;
    q.pop();


    if (strcmp(cur->data, target) == 0){
      std::cout << "shortest path: " << distance << '\n';
      
      paths.resize(distance + 1);
      GraphNode* node = cur;
      while(node != nullptr){
        paths[distance] = node; 
        node = parent[node];
        --distance;
      }

      return cur;
    }

    
    if (cur->left != nullptr && !cur->left->visited) {
        parent[cur->left] = cur;
        cur->left->visited = true;
        q.push({cur->left, distance + 1});
    }

    if (cur->right != nullptr && !cur->right->visited) {
        parent[cur->right] = cur;
        cur->right->visited = true;
        q.push({cur->right, distance + 1});
    }

    if (cur->top != nullptr && !cur->top->visited) {
        parent[cur->top] = cur;
        cur->top->visited = true;
        q.push({cur->top, distance + 1});
    }
    
    if (cur->bottom != nullptr && !cur->bottom->visited) {
        parent[cur->bottom] = cur;
        cur->bottom->visited = true;
        q.push({cur->bottom, distance + 1});
    }
  }

  return nullptr;
}

void
BFSclean(GraphNode* begin)
{
  if (!begin)
    return;
  begin->visited = false;
  
  BFSclean(begin->top);
  BFSclean(begin->left);
  BFSclean(begin->right);
  BFSclean(begin->bottom);
}
