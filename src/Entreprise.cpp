#include <iostream>
#include <string>
#include "Entreprise.h"

using namespace std;

Entreprise::Entreprise(int ID, string nom) {
    #ifdef MAP 
        cout << "Appel au constructeur de Entreprise." << endl;
    #endif
    this->userID = ID;
    this->name = nom;
    this->tabCleaner = Cleaner[100];
    for (int i=0; i<100; ++i) {
        tabCleaner[i]=null;
    }
}

Entreprise::Entreprise(Entreprise & uneEmtreprise) {
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

Entreprise::ajoutAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode ajoutAirCleaner() de Entreprise." << endl;
    #endif
    for (int i=0; i<100; ++i) {
        
 (tabCleaner[i]==null) {
            tabCleaner[i]=c;
            break;
        }    }
}

Entreprise::mesuresProchesAirClfeaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode mesuresProchesAirCleaner() de Entreprise." << endl;
    #endif
}
 
Entreprise::moyenneAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode moyenneAirCleaner() de Entreprise." << endl;
    #endif
}

Entreprise::etendueZoneTraitee(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode etendueZoneTraitee de Entreprise." << endl;
    #endif
}

Entreprise::niveauAmelioration(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode niveauAmelioration() de Entreprise." << endl;
    #endif
}