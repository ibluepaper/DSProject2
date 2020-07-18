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
  //If tree is Empty add new Node and add "a" to it
  if (!root){
    root = new BTreeNode(t, true);
    root->setKeys(0, a);
    root->setN(1);
    return;
  }
  //If root root is full split it to two nodes and create new_root that points to these nodes
  if(root->getN() == 2 * t - 1){

    //Create new node as the new_root that points to the splited nodes from root
    BTreeNode *new_root = new BTreeNode(t, false);
    //Set root as one of new_root childs (child_1)
    new_root->setChilds(0, root);
    //Split root to child_1 and child_2 and make new_root their parents
    split(new_root, 0, root);

    //Find out where we should add "a"
    int i = 0;
    if (new_root->getKeys(0) < a)
      i++;

    //Add "a" to its correct place
    int i = new_root->getN();

    //Set new_root as root
    root = new_root;
  }
  //If root is not full add a to the root in right place
  else

}

void BTree::split(BTreeNode *new_root, int i, BTreeNode *child_1){

  //Create a new child node called child_2 and set its values to right of child_1 values
  BTreeNode *child_2 = new BTreeNode(t, child_1->getLeaf());
  child_2->setN(t - 1);
  for (int j = 0; j < t - 1; j++)
    child_2->setKeys(j, child_1->getKeys(j + t));
  if (!child_1->getLeaf())
    for (int j = 0; j < t; j++)
      child_2->setChilds(j, child_1->getChilds(j + t));

  //Remove child_2 elements from child_1
  child_1->setN(t - 1);

  //Find the right place for the child_2 in new_root
  for (int j = new_root->getN(), j >= i + 1; j--)
    new_root->setChilds(j + 1, new_root->getChilds(j));

  //Add child_2 in new_root
  new_root->setChilds(i + 1, child_2);

  //Find the right place in new_root for the data from child that is gonna add to the new_root
  for (int j = new_root->getN() - 1; j >= i; j--)
    new_root->setKeys(j + 1, new_root->getKeys(j));

  //Move the data from child_1 to the new_root
  new_root->setKeys(i, child_1->getKeys(t - 1));

  //Increase new_root full places one number
  new_root->setN(new_root->getN() + 1);
}
