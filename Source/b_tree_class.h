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

  void insert(Disease *key);

  void insert_non_full(BTreeNode *child, Disease *key);

  void split(BTreeNode *new_root, int i, BTreeNode *child_1);

  BTreeNode *search(int key, BTreeNode *node);

  BTreeNode *getRoot(){
    return root;
  }

  void remove(int symptom);
};

void BTree::insert(Disease *key){
  //If tree is Empty add new Node and add "key" to it
  if (!root){
    root = new BTreeNode(t, true);
    root->setKeys(0, key);
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

    //Find out which child of new_root should add "key"
    int i = 0;
    if (new_root->getKeys(0)->getSymptom() < key->getSymptom())
      i++;

    //Add "key" to the child
    insert_non_full(new_root->getChilds(i), key);

    //Set new_root as root
    root = new_root;
  }
  //If root is not full add key to the root in right place
  else
    insert_non_full(root, key);
}

void BTree::insert_non_full(BTreeNode *child, Disease *key){
  //Set last element place as "i"
  int i = child->getN() - 1;

  //If the child is leaf add "key" to the correct place in child
  if (child->getLeaf()){
    //Shift keys to right of array till "key" is in right place
    for (; i >= 0 && child->getKeys(i)->getSymptom() > key->getSymptom(); i--)
      child->setKeys(i + 1, child->getKeys(i));
    //Add "key"
    child->setKeys(i + 1, key);
    //Increase "n" one number
    child->setN(child->getN() + 1);
  }
  //If the child is not leaf
  else{
    //Find the child to add "key" in it
    for (; i >= 0 && child->getKeys(i)->getSymptom() > key->getSymptom(); i--);

    //If the found child is full split it
    if (child->getChilds(i + 1)->getN() == 2 * t - 1){
      split(child, i+1, child->getChilds(i + 1));
      if(child->getKeys(i + 1)->getSymptom() > key->getSymptom())
        i++;
    }
    insert_non_full(child->getChilds(i + 1), key);
  }
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
  for (int j = new_root->getN(); j >= i + 1; j--)
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

BTreeNode *BTree::search(int key, BTreeNode *node){
  //Find the place of "key" in this node
  int i = 0;
  for(; i < node->getN() && key > node->getKeys(i)->getSymptom(); i++);

  //Return this node if "key" is here
  if (node->getKeys(i)->getSymptom() == key)
    return node;

  //Return nullptr if "key" is not here and this node is leaf
  if (node->getLeaf())
    return nullptr;

  //Return recursive function for this node's correct child
  return search(key, node->getChilds(i));
}

void BTree::remove(int symptom){
  if (!root){
    cout << "\n* This symptom not found in the database." << endl;
    return;
  }

  if (root->removeKey(symptom))
    cout << "\n* Disease removed successfully." << endl;

  //if root node has no keys there will 2 state:
  //1. set its first child as root
  //2. set it nullptr if it has no child
  if (root->getN() == 0){
    BTreeNode *tmp = root;
    if (root->getLeaf())
      root = nullptr;
    else
      root = root->getChilds(0);
    delete tmp;
  }
}
