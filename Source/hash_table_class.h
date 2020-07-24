#include "b_tree_class.h"

//hash table class
class HashTable{
private:
  int size;
  BTree **hash_nodes;

public:
  //hash table constructor that get hash table size and b-tree minimum degree
  //and make a array of b-tree class with size of "size"
  //and each b-tree classes create with minimum degree t
  HashTable(int size, int t){
    this->size = size;
    hash_nodes = new BTree*[size];
    for(int i = 0; i < size; i++)
      hash_nodes[i] = new BTree(t);
  }

  //get a number and return hash index of that number
  int hashFunction(int a){
    return a % size;
  }

  //get a disease object and add it to correct b-tree in the hash table
  void addData(Disease *disease){
    int hash_index = hashFunction(disease->getSymptom());
    hash_nodes[hash_index]->insert(disease);
  }

  //get a symtpom and remove it from its b-tree
  void removeData(int symptom){
    hash_nodes[hashFunction(symptom)]->remove(symptom);
  }

  //get a symptom and return disease object that contain Symptom
  //return nullptr if object not found
  Disease *search(int symptom){
    BTreeNode *disease_node = nullptr;
    if (hash_nodes[hashFunction(symptom)]->getRoot())
      disease_node = hash_nodes[hashFunction(symptom)]->search(symptom, hash_nodes[hashFunction(symptom)]->getRoot());
    if (disease_node)
      return disease_node->search(symptom);
    return nullptr;
  }

  //sort each b-trees in even odd sort
  void evenOddSort(){
    for (int i = 0; i < size; i++)
      hash_nodes[i]->bTreeEvenOddSort();
  }
};
