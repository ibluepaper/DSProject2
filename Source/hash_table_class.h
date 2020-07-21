#include "b_tree_class.h"

class HashTable{
private:
  int size;
  BTree **hash_nodes;

public:
  HashTable(int size, int t){
    this->size = size;
    hash_nodes = new BTree*[size];
    for(int i = 0; i < size; i++)
      hash_nodes[i] = new BTree(t);
  }

  int hashFunction(int a){
    return a % size;
  }

  void addData(Disease *disease){
    int hash_index = hashFunction(disease->getSymptom());
    hash_nodes[hash_index]->insert(disease);
  }

  void removeData(int symptom){
    hash_nodes[hashFunction(symptom)]->remove(symptom);
  }

  Disease *search(int symptom){
    BTreeNode *disease_node = nullptr;
    if (hash_nodes[hashFunction(symptom)]->getRoot())
      disease_node = hash_nodes[hashFunction(symptom)]->search(symptom, hash_nodes[hashFunction(symptom)]->getRoot());
    if (disease_node)
      return disease_node->search(symptom);
    return nullptr;
  }
};
