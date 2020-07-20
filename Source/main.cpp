#include "hash_table_class.h"
#include <string>

int stringToInt(string str);
void addDisease(HashTable *disease_hash);
void searchDisease(HashTable *disease_hash);
void removeDisease(HashTable *disease_hash);
void printMainMenu();

int main(){
  int hash_size, b_tree_degree;
  cout << "Enter hash table size: ";
  cin >> hash_size;
  cout << "Now enter b-tree minimum degree: ";
  cin >> b_tree_degree;

  HashTable *disease_hash = new HashTable(hash_size, b_tree_degree);

  int command_number;

  do {
    printMainMenu();
    cin >> command_number;
    switch (command_number) {
      case 1:
        addDisease(disease_hash);
      break;
      case 2:
        removeDisease(disease_hash);
      break;
      case 3:
        searchDisease(disease_hash);
      break;
      case 4:
        return 0;
      break;
      default:
        cout << "Wrong input; Try again..." << endl << endl;
      break;
    }
  } while(1);
}


int stringToInt(string str){
    int len = str.size();
    int sum = 0;
    for (int i = 0; i < len; i++)
      sum += int(str[i]);
    return sum;
}

void addDisease(HashTable *disease_hash){
  string symptom, disease, medication;

  cout << "- Enter Symptom: ";
  cin >> symptom;
  cout << "- Enter Disease: ";
  cin >> disease;
  cout << "- Enter Medication: ";
  cin >> medication;

  Disease *disease_node = new Disease(stringToInt(symptom), disease, medication);
  disease_hash->addData(disease_node);

  cout << "* Disease added successfully." << endl;
}

void searchDisease(HashTable *disease_hash){
  string symptom;

  cout << "- Enter Symptom: ";
  cin >> symptom;

  Disease *disease = disease_hash->search(stringToInt(symptom));

  cout << "* Disease with this symptom is \" " << disease->getDisease() << " \" "
      << "and medication for this disease is \" " << disease->getMedication() << " \"."
      << endl << endl << endl;
}


void removeDisease(HashTable *disease_hash){
  string symptom;

  cout << "- Enter Symptom to remove: ";
  cin >> symptom;

  //disease_hash->removeData(stringToInt(symptom));

  cout << "* Disease removed successfully." << endl;
}

void printMainMenu(){
  cout << endl << "|:==== Doctors Unemployment ====:|" << endl << endl
      << "1. Add Disease" << endl
      << "2. Remove Disease" << endl
      << "3. Search Disease" << endl
      << "4. Exit" << endl
      << endl;

  cout << "Please enter the command number (1 - 3): ";
}
