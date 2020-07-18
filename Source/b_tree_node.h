#include <iostream>

using namespace std;

class BTreeNode{
private:
  int n;
  int *keys;
  BTreeNode **childs;
  bool leaf;

public:
  BTreeNode(int t, bool leaf){
    n = 0;
    keys = new int[2 * t - 1];
    childs = new BTreeNode *[2 * t];
    this->leaf = leaf;
  }

  void setN(int n){
    this->n = n;
  }
  void setKeys(int index, int a){
    keys[index] = a;
  }
  void setChilds(int index, BTreeNode *child){
    childs[index] = child;
  }
  void setLeaf(bool leaf){
    this->leaf = leaf;
  }

  int getN(){
    return n;
  }
  int getKeys(int index){
    return keys[index];
  }
  BTreeNode *getChilds(int index){
    return childs[index];
  }
  bool getLeaf(){
    return leaf;
  }
};
