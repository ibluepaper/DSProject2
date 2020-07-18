#include "b_tree_node.h"

class BTree{
private:
  int t;
  BTreeNode *root;

public:
  BTree(int t){
    this->t = t;
    root = nullptr;
  }

  void insert(int a);
};

void BTree::insert(int a){
  if (!root){
    root = new BTreeNode(t, true);
    root->setKeys(0, a);
    root->setN(1);
  }
}
