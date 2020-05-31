#include <iostream>
#include <string>
#include "Entreprise.h"
#include "Cleaner.h"

using namespace std;

Entreprise::Entreprise(int ID, string nom) : Utilisateur(ID) {
    #ifdef MAP 
        cout << "Appel au constructeur de Entreprise." << endl;
    #endif
    this->userID = ID;
    this->name = nom;
}

Entreprise::Entreprise(Entreprise & uneEntreprise) : Utilisateur(uneEntreprise) {
    #ifdef MAP 
        cout << "Appel au constructeur par copie de Entreprise." << endl;
    #endif
    this->name = uneEntreprise.name;
    this->tabCleaner = uneEntreprise.tabCleaner;
    this->userID = uneEntreprise.userID;
}

Entreprise::~Entreprise() {
    #ifdef MAP 
        cout << "Appel au destructeur de Entreprise." << endl;
    #endif
}

void Entreprise::ajoutAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode ajoutAirCleaner() de Entreprise." << endl;
    #endif
    tabCleaner.push_back(c);
}

float Entreprise::mesuresProchesAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode mesuresProchesAirCleaner() de Entreprise." << endl;
    #endif
}
 
float Entreprise::moyenneAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode moyenneAirCleaner() de Entreprise." << endl;
    #endif
}

float Entreprise::etendueZoneTraitee(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode etendueZoneTraitee de Entreprise." << endl;
    #endif
}

float Entreprise::niveauAmelioration(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode niveauAmelioration() de Entreprise." << endl;
    #endif
}