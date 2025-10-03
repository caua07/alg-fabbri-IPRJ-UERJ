#pragma once
#include <iostream>

struct GraphNode {
  char* data;
  bool visited{false};
  GraphNode* left;
  GraphNode* bottom;
  GraphNode* right;
  GraphNode* top;
};

GraphNode* DFS(GraphNode* begin, const char* target, int acc);
GraphNode* BFS(GraphNode* begin, const char* target);
