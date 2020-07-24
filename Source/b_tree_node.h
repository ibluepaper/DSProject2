#include "disease_class.h"

class BTreeNode{
private:
  int t; //b-tree degree
  int n; //number of keys that stored in this node
  Disease **keys;
  BTreeNode **childs;
  bool leaf; //true if this node is leaf

public:
  //get b-tree degree and create keys and childs arrays and set leaf
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

  int getN(){
    return n;
  }

  //get index and disease object as key
  void setKeys(int index, Disease *key){
    keys[index] = key;
  }

  Disease *getKeys(int index){
    return keys[index];
  }

  //get index and b-tree node object as child
  void setChilds(int index, BTreeNode *child){
    childs[index] = child;
  }

  BTreeNode *getChilds(int index){
    return childs[index];
  }

  void setLeaf(bool leaf){
    this->leaf = leaf;
  }

  bool getLeaf(){
    return leaf;
  }

  //search symptom in the keys array and return disease object
  //return nullptr if it's not found
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
  bool removeKey(int symptom){
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
        cout << "\n* This symptom not found in the database." << endl;
        return false;
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
    return true;
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

  //a function to fill a child that has less than t keys
  //this function has 3 states
  void fill(int index){
    //if previous child has more than t keys borrow one from that
    if (index != 0 && childs[index - 1]->getN() >= t)
      borrowFromPrev(index);

    //if next child has more than t keys borrow one from that
    if (index != n && childs[index + 1]->getN() >= t)
      borrowFromNext(index);

    //else merge it with the next child and if its last child in this node merge it with previous child
    else {
      if (index != n)
        merge(index);
      else
        merge(index - 1);
    }
  }

  //a function that borrow a key from childs[index - 1] and add it to child[index]
  void borrowFromPrev(int index){
    BTreeNode *child = childs[index];
    BTreeNode *prev_child = childs[index - 1];

    //the last key of prev_child replace with the index key
    //and index key will add at start of child

    //shift all child's key one right to add key at start of it
    for (int i = child->getN() - 1; i >= 0; i--)
      child->setKeys(i + 1, child->getKeys(i));

    //if child isn't leaf shifting all its childs one right
    if (!child->getLeaf()){
      for (int i = child->getN(); i >= 0; i--)
        child->setChilds(i + 1, child->getChilds(i));
    }

    //set child's first key to this current node key
    child->setKeys(0, keys[index - 1]);

    //last prev_child's child moving to first child's child if child isn't leaf
    if (!child->getLeaf())
      child->setChilds(0, prev_child->getChilds(prev_child->getN()));

    //set current node key to last prev_child's key
    keys[index - 1] = prev_child->getKeys(prev_child->getN() - 1);

    child->setN(child->getN() + 1);
    prev_child->setN(child->getN() - 1);
  }

  //a function that borrow a key from childs[index + 1] and add it to child[index]
  void borrowFromNext(int index){
    BTreeNode *child = childs[index];
    BTreeNode *next_child = childs[index + 1];

    //the first key of next_child replace with the index key
    //and index key will add at last of child

    //set child's last key to this current node key
    child->setKeys(child->getN(), keys[index]);

    //set current node key to first next_child's key
    keys[index] = next_child->getKeys(0);

    //shift all next_child's keys one left
    for (int i = 1; i < next_child->getN(); i++)
      next_child->setKeys(i - 1, next_child->getKeys(i));

    //if next_child isn't leaf shifting all its childs one left
    if (!next_child->getLeaf()){
      for (int i = 1; i <= next_child->getN(); i++)
        next_child->setChilds(i - 1, next_child->getChilds(i));
    }

    child->setN(child->getN() + 1);
    next_child->setN(child->getN() - 1);
  }

  //a function to merge childs[index] with childs[index + 1] and free up childs[index + 1]
  void merge(int index){
    BTreeNode *child = childs[index];
    BTreeNode *next_child = childs[index + 1];

    //add the key that is between child and next_child to end of child
    child->setKeys(t - 1, keys[index]);

    //copy keys from next_child to end of child
    for (int i = 0; i < next_child->getN(); i++)
      child->setKeys(i + t, next_child->getKeys(i));

    //copy childs from next_child to end of child if child isn't leaf
    if (!child->getLeaf()){
      for (int i = 0; i <= next_child->getN(); i++)
        child->setChilds(i + t, next_child->getChilds(i));
    }

    //shift all keys and childs after index one left to fill the empty place
    for (int i = index + 1; i < n; i++)
      keys[i - 1] = keys[i];
    for (int i = index + 1; i <= n; i++)
      childs[i - 1] = childs[i];

    child->setN(child->getN() + next_child->getN() + 1);
    n--;

    delete next_child;
  }

  //revese keys and childs arrays
  //it is used for odd and even sort
  void reverseKeysAndChilds(){
    for (int start = 0, end = n - 1; start < end; start++, end--){
      Disease *tmp = keys[start];
      keys[start] = keys[end];
      keys[end] = tmp;
    }

    if (!leaf)
      for (int start = 0, end = n; start < end; start++, end--){
        BTreeNode *tmp = childs[start];
        childs[start] = childs[end];
        childs[end] = tmp;
      }
  }
};
