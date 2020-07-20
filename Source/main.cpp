#include "hash_table_class.h"
#include <string>

int stringToInt(string str);
void addDisease(HashTable *disease_hash, string symptom, string disease, string medication);
Disease *searchDisease(HashTable *disease_hash, string symptom);

int main(){
  /*HashTable *disease_hash = new HashTable(5, 3);
  addDisease(disease_hash, "Headache", "Synozit", "Morphin");
  addDisease(disease_hash, "Backache", "Disk", "Rest");
  cout << searchDisease(disease_hash, "Headache")->getMedication() << endl;*/
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
