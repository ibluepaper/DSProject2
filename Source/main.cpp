#include "hash_table_class.h"
#include <string>

int stringToInt(string str);
void addDisease(HashTable *disease_hash, string symptom, string disease, string medication);
Disease *searchDisease(HashTable *disease_hash, string symptom);
void removeDisease(HashTable *disease_hash, string symptom);
void printMainMenu();

int main(){
  int hash_size, b_tree_degree;
  cout << "Enter hash table size: ";
  cin >> hash_size;
  cout << "Now enter b-tree minimum degree: ";
  cin >> b_tree_degree;


}


int stringToInt(string str){
    int len = str.size();
    int sum = 0;
    for (int i = 0; i < len; i++)
      sum += int(str[i]);
    return sum;
}

void addDisease(HashTable *disease_hash, string symptom, string disease, string medication){
  Disease *disease_node = new Disease(stringToInt(symptom), disease, medication);
  disease_hash->addData(disease_node);
}

Disease *searchDisease(HashTable *disease_hash, string symptom){
  return disease_hash->search(stringToInt(symptom));
}


void removeDisease(HashTable *disease_hash, string symptom){
  return disease_hash->removeData(stringToInt(symptom));
}

void printMainMenu(){
  cout << endl << "|:==== Doctors Unemployment ====:|" << endl << endl
      << "1. Add Disease" << endl
      << "2. Remove Disease" << endl
      << "3. Search Disease" << endl
      << endl;

  cout << "Please enter the command number (1 - 3): ";
}
