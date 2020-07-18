#include <iostream>

using namespace std;

class BTreeNode{
private:
  int t;
  int n;
  int *keys;
  BTreeNode **childs;
  bool leaf;

public:
  BTreeNode(int t, bool leaf){
    this->t = t;
    n = 0;
    keys = new int[2 * t - 1];
    childs = new BTreeNode *[2 * t];
    this->leaf = leaf
  }

  void setN(int n){
    this->n = n;
  }
  void setKeys(int *keys){
    this->keys = keys;
  }
  void setChilds(BTreeNode **childs){
    this->childs = childs;
  }
  void setLeaf(bool leaf){
    this->leaf = leaf;
  }

  int getN(){
    return n;
  }
  int *getKeys(){
    return keys;
  }
  BTreeNode **getChilds(){
    return childs;
  }
  bool getLeaf(){
    return leaf;
  }
};
