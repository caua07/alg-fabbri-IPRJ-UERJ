#include "tree.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio> // For snprintf

unsigned int acc = 0;
TreeNode* root = nullptr;

TreeNode* createNode(const char* text){
  TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
  newNode->left = nullptr;
  newNode->right = nullptr;
  newNode->data = (char*)malloc(std::strlen(text) + 1);

  std::strcpy(newNode->data, text);

  return newNode;
}

void printBT(const char* prefix, const TreeNode* root, bool isLeft) {
    if (root != nullptr) {
        std::cout << prefix << (isLeft ? "├──" : "└──") << root->data << '\n';
        char new_prefix[1024];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, isLeft ? "│   " : "    ");
        // Print right child first (appears on top)
        printBT(new_prefix, root->right, true);
        // Print left child second (appears on bottom)  
        printBT(new_prefix, root->left, false);
    }
}

bool findNode(TreeNode* root, const char* text){
  if(root == nullptr){
    return false;
  }
  if(strcmp(text, root->data) == 0){
    return true;
  }

  if(strcmp(text, root->data) < 0){
    return findNode(root->left, text);
  } else {
    return findNode(root->right, text);
  }
}

bool insertNode(TreeNode*& root, const char* text){

  if(root == nullptr){
    root = createNode(text);
    return true;
  }

  if(strcmp(text, root->data) == 0){
    std::cerr  << "value already exists in tree\n";
    return false;
  }

  if(std::strcmp(text,root->data) < 0 ){
    return insertNode(root->left, text);
  } else {
    return insertNode(root->right, text);
  }
}

unsigned int sumRec(TreeNode* root) {
  if (root == nullptr) {
    return 0;
  }
  return std::strlen(root->data) + sumRec(root->left) + sumRec(root->right);
}

void destroyTree(TreeNode* root) {
  if (root != nullptr) {
    destroyTree(root->left);
    destroyTree(root->right);
    free(root->data);
    free(root);
  }
}
