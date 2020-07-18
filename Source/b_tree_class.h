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
  void split(BTreeNode *new_root, int i, BTreeNode *child_1);
};

void BTree::insert(int a){
  if (!root){
    root = new BTreeNode(t, true);
    root->setKeys(0, a);
    root->setN(1);
    return;
  }

  if(root->getN() == 2 * t - 1){
    BTreeNode *new_root = new BTreeNode(t, false);
    new_root->setChilds(0, root);
    new_root = split(new_root, 0, root);

  }
  else{

  }
}

BTreeNode *BTree::split(BTreeNode *new_root, int i, BTreeNode *child_1){

  BTreeNode *child_2 = new BTreeNode(t, child_1->getLeaf());
  child_2->setN(t - 1);
  for (int j = 0; j < t - 1; j++)
    child_2->setKeys(j, child_1->getKeys(j + t));
  if (!child_1->getLeaf())
    for (int j = 0; j < t; j++)
      child_2->setChilds(j, child_1->getChilds(j + t));

  child_1->setN(t - 1);

  for (int j = new_root->getN(), j > i; j--)
    new_root->setChilds(j + 1, new_root->getChilds(j));

  new_root->setChilds(i + 1, child_2);

  for (int j = new_root->getN() - 1; j >= i; j--)
    new_root->setKeys(j + 1, new_root->getKeys(j));

  new_root->setKeys(i, child_1->getKeys(t - 1));

  new_root->setN(new_root->getN() + 1);
  return new_root;
}
