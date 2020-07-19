#include <iostream>

using namespace std;

struct DiseaseNode{
  int symptom;
  string disease;
  string medication;
};

class BTreeNode{
private:
  int n;
  DiseaseNode *keys;
  BTreeNode **childs;
  bool leaf;

public:
  BTreeNode(int t, bool leaf){
    n = 0;
    keys = new DiseaseNode[2 * t - 1];
    childs = new BTreeNode *[2 * t];
    this->leaf = leaf;
  }

  void setN(int n){
    this->n = n;
  }
  void setKeys(int index, int symptom, string disease, string medication){
    keys[index].symptom = symptom;
    keys[index].disease = disease;
    keys[index].medication = medication;
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
  //-------------->
  int getKeys(int index){
    return keys[index];
  }
  //-------------->
  BTreeNode *getChilds(int index){
    return childs[index];
  }
  bool getLeaf(){
    return leaf;
  }
};
