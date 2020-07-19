#include <iostream>

using namespace std;

class DiseaseNode{
private:
  int symptom;
  string disease;
  string medication;

public:
  DiseaseNode(int symptom, string disease, string medication){
    this->symptom = symptom;
    this->disease = disease;
    this->medication = medication;
  }

  int getSymptom(){
    return symptom;
  }

  string getDisease(){
    return disease;
  }

  string getMedication(){
    return medication;
  }
};
