#include <gtest/gtest.h>
#include "graph.h"
#include <cstring>

// Helper function to create a GraphNode
GraphNode* createNode(const char* data) {
  GraphNode* node = new GraphNode();
  node->data = new char[strlen(data) + 1];
  strcpy(node->data, data);
  node->visited = false;
  node->left = nullptr;
  node->bottom = nullptr;
  node->right = nullptr;
  node->top = nullptr;
  return node;
}

// Helper function to reset visited flags
void resetVisited(GraphNode* node) {
  if (!node || node->visited == false) return;
  node->visited = false;
  resetVisited(node->left);
  resetVisited(node->right);
  resetVisited(node->bottom);
  resetVisited(node->top);
}

// Helper function to delete graph
void deleteGraph(GraphNode* node) {
  if (!node) return;
  // Mark as visited to avoid cycles
  if (node->visited) return;
  node->visited = true;
  
  deleteGraph(node->left);
  deleteGraph(node->right);
  deleteGraph(node->bottom);
  deleteGraph(node->top);
  
  delete[] node->data;
  delete node;
}

class DFSTest : public ::testing::Test {
protected:
  GraphNode* root;
  
  void SetUp() override {
    root = nullptr;
  }
  
  void TearDown() override {
    if (root) {
      deleteGraph(root);
    }
  }
};

TEST_F(DFSTest, NullBeginReturnsNull) {
  GraphNode* result = DFS(nullptr, "target", 0);
  EXPECT_EQ(result, nullptr);
}

TEST_F(DFSTest, FindNodeAtRoot) {
  root = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  std::string output = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(result, root);
  EXPECT_TRUE(output.find("path lenght: 1") != std::string::npos);
}

TEST_F(DFSTest, FindNodeInLeftChild) {
  root = createNode("root");
  root->left = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  std::string output = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(result, root->left);
  EXPECT_TRUE(output.find("path lenght: 2") != std::string::npos);
}

TEST_F(DFSTest, FindNodeInRightChild) {
  root = createNode("root");
  root->right = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  std::string output = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(result, root->right);
  EXPECT_TRUE(output.find("path lenght: 2") != std::string::npos);
}

TEST_F(DFSTest, FindNodeInBottomChild) {
  root = createNode("root");
  root->bottom = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  std::string output = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(result, root->bottom);
  EXPECT_TRUE(output.find("path lenght: 2") != std::string::npos);
}

TEST_F(DFSTest, FindNodeInTopChild) {
  root = createNode("root");
  root->top = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  std::string output = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(result, root->top);
  EXPECT_TRUE(output.find("path lenght: 2") != std::string::npos);
}

TEST_F(DFSTest, TargetNotFound) {
  root = createNode("root");
  root->left = createNode("left");
  root->right = createNode("right");
  
  GraphNode* result = DFS(root, "notfound", 0);
  
  EXPECT_EQ(result, nullptr);
}

TEST_F(DFSTest, FindNodeInDeeperTree) {
  root = createNode("root");
  root->left = createNode("A");
  root->left->left = createNode("B");
  root->left->left->bottom = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  std::string output = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(result, root->left->left->bottom);
  EXPECT_TRUE(output.find("path lenght: 4") != std::string::npos);
}

TEST_F(DFSTest, HandlesVisitedNodes) {
  root = createNode("root");
  root->left = createNode("target");
  root->left->visited = true;
  
  GraphNode* result = DFS(root, "target", 0);
  
  EXPECT_EQ(result, nullptr);
}

TEST_F(DFSTest, SearchOrderLeftRightBottomTop) {
  root = createNode("root");
  root->left = createNode("A");
  root->right = createNode("target");
  root->bottom = createNode("target");
  root->top = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  testing::internal::GetCapturedStdout();
  
  // Should find right child first due to DFS order
  EXPECT_EQ(result, root->right);
}

TEST_F(DFSTest, ComplexGraphStructure) {
  root = createNode("root");
  root->left = createNode("L1");
  root->right = createNode("R1");
  root->bottom = createNode("B1");
  root->top = createNode("T1");
  
  root->left->right = createNode("L1R");
  root->right->bottom = createNode("target");
  
  testing::internal::CaptureStdout();
  GraphNode* result = DFS(root, "target", 0);
  std::string output = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(result, root->right->bottom);
  EXPECT_TRUE(output.find("path lenght: 3") != std::string::npos);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

