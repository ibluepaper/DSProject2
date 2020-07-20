#include "disease_class.h"

class BTreeNode{
private:
  int n;
  Disease **keys;
  BTreeNode **childs;
  bool leaf;

public:
  BTreeNode(int t, bool leaf){
    n = 0;
    keys = new Disease *[2 * t - 1];
    childs = new BTreeNode *[2 * t];
    this->leaf = leaf;
  }

  void setN(int n){
    this->n = n;
  }

  void setKeys(int index, Disease *key){
    keys[index] = key;
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

  Disease *getKeys(int index){
    return keys[index];
  }

  BTreeNode *getChilds(int index){
    return childs[index];
  }

  bool getLeaf(){
    return leaf;
  }

  Disease *search(int symptom){
    for (int i = 0; i < n; i++)
      if (keys[i]->getSymptom() == symptom)
        return keys[i];
    return nullptr;
  }
};
