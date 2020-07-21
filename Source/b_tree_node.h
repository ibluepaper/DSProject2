#include "disease_class.h"

class BTreeNode{
private:
  int t;
  int n;
  Disease **keys;
  BTreeNode **childs;
  bool leaf;

public:
  BTreeNode(int t, bool leaf){
    this->t = t;
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

  //return the index of first key that is equal or greater than enterance symptom
  int findKey(int symptom){
    int index;
    for (index = 0; index < n && keys[index]->getSymptom() < symptom; index++);
    //return index; it will return "n" if the symptom not found in this node
    return index;
  }

  //remove function to remove a disease key in this node
  void removeKey(int symptom){
    int index = findKey(symptom);

    //if symptom key is available in this node; there is two state {1. this node is leaf 2. this node isn't leaf}
    if (index < n && keys[index]->getSymptom() == symptom){
      if (leaf)
        removeFromLeaf(index);
      else
        removeFromNonLeaf(index);
    }

    //if symptom key is not available is this node; there is two state
    //1. this node is leaf ->>> so it means key is not available in this tree
    //2. the key is in the sub-tree rooted from this node
    else {
      if (leaf){
        cout << "This symptom not found in the database." << endl;
        return;
      }

      //this boolian store if the symptom is in the last child node of this node or not
      bool flag = false;
      if (index == n) flag = true;

      //if the sub-tree node has less than t keys it should be fill
      if (childs[index]->getN() < t)
        fill(index);

      //if fill, merged the last child n will be n - 1 and symptom is in index - 1 child Now
      //else remove should call on child[index]
      if (flag && index > n)
        childs[index - 1]->removeKey(symptom);
      else
        childs[index]->removeKey(symptom);
    }
  }

  //a function that remove index-th keys in this node - that is leaf
  void removeFromLeaf(int index){
    for (int i = index + 1; i < n; i++)
      keys[i - 1] = keys[i];
    n--;
  }

  //a function that remove index-th keys in this node - that is not leaf
  //there is 3 states:
  //1. left child has t or more than t keys --> call getL()
  //2. right child has t or more than t keys --> call getR()
  //3. both have less than t childs --> call merge()
  void removeFromNonLeaf(int index){
    int symptom = keys[index]->getSymptom();

    if (childs[index]->getN() >= t){
      Disease *l = getL(index);
      keys[index] = l;
      childs[index]->removeKey(keys[index]->getSymptom());
    }

    else if (childs[index + 1]->getN() >= t){
      Disease *r = getR(index);
      keys[index] = r;
      childs[index + 1]->removeKey(keys[index]->getSymptom());
    }

    else {
      merge(index);
      childs[index]->removeKey(symptom);
    }
  }

  //a function that return the right most node key that is in the left child of a key
  Disease *getL(int index){
    BTreeNode *current = childs[index];
    while (!current->getLeaf())
      current = current->getChilds(current->getN());
    return current->getKeys(current->getN() - 1);
  }

  //a function that return the left most node key that is in the right child of a key
  Disease *getR(int index){
    BTreeNode *current = childs[index];
    while (!current->getLeaf())
      current = current->getChilds(0);
    return current->getKeys(0);
  }

  int merge(int index){

  }

  void fill(int index){

  }
};
