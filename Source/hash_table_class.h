#include "b_tree_class.h"

class HashTable{
private:
  int t; //for b-tree class
  int size;
  BTree *hash_nodes;

public:
  HashTable(int size, int t){
    this->size = size;
    this->t = t;
    hash_nodes = new BTree[size];
    for(int i = 0; i < size; i++)
      hash_nodes[i].setT(t);
  }
  int hashFunction(int a){
    return a % size;
  }
  void addData(int a){
    int hash_index = hashFunction(a);
    BTree[hash_index].insert(a);
  }


};
