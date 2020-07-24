#include "hash_table_class.h"
#include <string>

int stringToInt(string str);
void addDisease(HashTable *disease_hash);
void searchDisease(HashTable *disease_hash);
void removeDisease(HashTable *disease_hash);
void printMainMenu();
void continueFunction();

int main(){
  //get hash size and b-tree degree from user
  int hash_size, b_tree_degree;
  cout << "Enter hash table size: ";
  cin >> hash_size;
  cout << "Now enter b-tree minimum degree: ";
  cin >> b_tree_degree;

  //create a hash table object to store diseases
  HashTable *disease_hash = new HashTable(hash_size, b_tree_degree);

  //command number that get it from user
  char command_number;

  //a loop to get command number and do what user input it
  do {
    printMainMenu();
    cin >> command_number;
    switch (command_number) {
      //add disease case
      case '1':
        addDisease(disease_hash);
        continueFunction();
      break;

      //remove disease case
      case '2':
        removeDisease(disease_hash);
        continueFunction();
      break;

      //search disease case that first of all call evenOddSort function
      //when user enter this case there is no way to add or remove disease anymore
      case '3':
        disease_hash->evenOddSort();
        searchDisease(disease_hash);
        continueFunction();
        while (1){
          cout << "\n1. Search Disease" << endl
              << "2. Exit" << endl << endl;
          cout << "Please enter the command number (1 - 2): ";
          cin >> command_number;
          switch (command_number) {
            case '1':
              searchDisease(disease_hash);
              continueFunction();
            break;

            case '2':
              return 0;

            default:
              cout << "\nWrong input; Try again..." << endl << endl;
            break;
          }
        }
      break;

      //quit program case
      case '4':
        return 0;
      break;

      //default case when user enter a wrong command number
      default:
        cout << "\nWrong input; Try again..." << endl << endl;
      break;
    }
  } while(1);
}

//this function get a string and sum each of this string characters ASCII number
int stringToInt(string str){
    int len = str.size();
    int sum = 0;
    for (int i = 0; i < len; i++)
      sum += int(str[i]);
    return sum;
}

//add disease function
void addDisease(HashTable *disease_hash){
  string symptom, disease, medication;

  //get a symptom and check if its available in the database or not
  cout << "- Enter Symptom: ";
  string getline_problem;
  getline(cin, getline_problem);
  getline(cin, symptom);
  if (disease_hash->search(stringToInt(symptom))){
    cout << "\n* Symptom is available in database; To change, try remove it and add it again." << endl;
    return;
  }

  //if symptom is not available in the database user should enter disease and medication
  //and disease will add to database
  cout << "- Enter Disease: ";
  getline(cin, disease);
  cout << "- Enter Medication: ";
  getline(cin, medication);

  //disease object to store symptom disease and medication and add it to correct b-tree in hash table
  Disease *disease_node = new Disease(stringToInt(symptom), disease, medication);
  disease_hash->addData(disease_node);

  cout << "\n* Disease added successfully." << endl;
}

//search disease function
void searchDisease(HashTable *disease_hash){
  string symptom;

  cout << "- Enter Symptom: ";
  string getline_problem;
  getline(cin, getline_problem);
  getline(cin, symptom);

  //disease object to store search result
  Disease *disease = disease_hash->search(stringToInt(symptom));

  //if disease is nullptr symptom not found
  if (!disease){
    cout << "\n* Disease not found :/" << endl;
    return;
  }

  //else print disease and medication
  cout << "\n* Disease with this symptom is \" " << disease->getDisease() << " \" "
      << "and medication for this disease is \" " << disease->getMedication() << " \"."
      << endl << endl << endl;
}

//remove disease function
void removeDisease(HashTable *disease_hash){
  string symptom;

  //get symptom and call remove data in hash table
  cout << "- Enter Symptom to remove: ";
  string getline_problem;
  getline(cin, getline_problem);
  getline(cin, symptom);

  disease_hash->removeData(stringToInt(symptom));
}

//print main menu function
void printMainMenu(){
  cout << endl << "|:==== Doctors Unemployment ====:|" << endl << endl
      << "1. Add Disease" << endl
      << "2. Remove Disease" << endl
      << "3. Search Disease" << endl
      << "4. Exit" << endl
      << endl;

  cout << "Please enter the command number (1 - 4): ";
}

//continue function that user should enter 1 after each case to back to main menu
void continueFunction(){
  cout << endl << "Enter 1 to continue: ";
  string str;
  cin >> str;
  while (str != "1"){
    cout << "Wrong input; Try again: ";
    cin >> str;
  }
}
