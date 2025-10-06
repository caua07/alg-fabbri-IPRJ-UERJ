#include "../tree.h"
#include "../graph.h"

int
main()
{
  GraphNode* node1 = new GraphNode{"node1", false, nullptr, nullptr, nullptr, nullptr};
  GraphNode* node2 = new GraphNode{"node2", false, nullptr, nullptr, nullptr, nullptr};
  GraphNode* node3 = new GraphNode{"node3", false, nullptr, nullptr, nullptr, nullptr};
  GraphNode* node4 = new GraphNode{"node4", false, nullptr, nullptr, nullptr, nullptr};
  GraphNode* node5 = new GraphNode{"node5", false, nullptr, nullptr, nullptr, nullptr};
  GraphNode* node6 = new GraphNode{"node6", false, nullptr, nullptr, nullptr, nullptr};
  std::vector<GraphNode*> paths;

  node1->right = node2;
  node2->top = node3;
  node2->bottom = node4;
  node3->bottom = node4;
  node2->right = node5;
  node3->right = node5;
  node5->right = node6;

  GraphNode* res1 = DFS(node1, "node6");
  BFSclean(node1);
  GraphNode* res2 = BFS(paths, node1, "node6");

  std::cout << "\n\n dfs node: " << res1->data << "\n";
  std::cout << "\n\n bfs data: " << res2->data << "\n\n";

  for(const auto& el: paths){
    std::cout << el->data << "\n";
  }

  std::cout << "end of code";
  return 0;
}
