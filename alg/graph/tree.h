#pragma once

extern unsigned int acc;

struct Node {
  char* data;
  Node* left;
  Node* right;
};

extern Node* root;

void print(Node* root);
Node* createNode(const char* text);
bool insertNode(Node*& root, const char* text);
bool findNode(Node* root, const char* text);
void printBT(const char* prefix, const Node* root, bool isLeft);
unsigned int sumRec(Node* root, unsigned int acc);
void destroyTree(Node* node);
