#pragma once

extern unsigned int acc;

struct TreeNode {
  char* data;
  TreeNode* left;
  TreeNode* right;
};

extern TreeNode* root;

void print(TreeNode* root);
TreeNode* createNode(const char* text);
bool insertNode(TreeNode*& root, const char* text);
bool findNode(TreeNode* root, const char* text);
void printBT(const char* prefix, const TreeNode* root, bool isLeft);
unsigned int sumRec(TreeNode* root);
void destroyTree(TreeNode* node);
