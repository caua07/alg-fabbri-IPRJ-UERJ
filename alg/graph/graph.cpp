#include "graph.h"
#include <cstring>
#include <queue>
#include <set>

GraphNode*
DFS(GraphNode* begin, const char* target, int acc)
{
  if (!begin || begin->visited)
    return nullptr;

  if (strcmp((begin->data), target) == 0){
    ++acc;
    std::cout << "path lenght: " << acc << '\n';
    return begin;
  }

  begin->visited = true;

  GraphNode* result = nullptr;
  result = DFS(begin->left, target, acc+1);
  if (result) return result;
  result = DFS(begin->right, target, acc+1);
  if (result) return result;
  result = DFS(begin->bottom, target, acc+1);
  if (result) return result;
  result = DFS(begin->top, target, acc+1);
  if (result) return result;

  return nullptr;
}

GraphNode*
BFS(GraphNode* begin, const char* target){
  if(!begin)
    return nullptr;

  std::queue<std::pair<GraphNode*, int>> q;
  begin->visited = true;
  q.push({begin, 0});


  while (!q.empty()){
    GraphNode* cur = q.front().first;
    int distance = q.front().second;
    std::cout << "{ " << q.front().first << ", " << q.front().second << "} \n";
    q.pop();

    std::cout << "before statements";

    if (strcmp(cur->data, target) == 0){
      std::cout << "shortest path: " << distance;
      return cur;
    }
    std::cout << "after first if";
    if (cur->left != nullptr && !cur->left->visited) {
        std::cout << "went on left";
        cur->left->visited = true;
        q.push({cur->left, distance + 1});
    }

    if (cur->right != nullptr && !cur->right->visited) {
        std::cout << "went on right";
        cur->right->visited = true;
        q.push({cur->right, distance + 1});
    }

    if (cur->top != nullptr && !cur->top->visited) {
        std::cout << "went on top";
        cur->top->visited = true;
        q.push({cur->top, distance + 1});
    }
    
    if (cur->bottom != nullptr && !cur->bottom->visited) {
        std::cout << "went on bottom";
        cur->bottom->visited = true;
        q.push({cur->bottom, distance + 1});
    }
    std::cout << "got here";
  }

  return nullptr;
}
