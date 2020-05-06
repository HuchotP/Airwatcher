#include <iostream>
#include <string>
#include "UtilisateurPrive.h"

using namespace std;

UtilisateurPrive::UtilisateurPrive(int ID, string nom, int  pts) : Utilisateur(ID) {
    #ifdef MAP
        cout << "Appel au constructeur de UtilisateurPrive." << endl;
    #endif
    this->name = nom;
    this->points = pts;
    this->mesuresFournies = Mesure[100];
    for (int i=0; i<100; ++i) {
        this.mesuresFournies[i]=null;
    }
}

UtilisateurPrive::UtilisateurPrive(UtilisateurPrive & unUtilisateurPrive) : Utilisateur(unUtilisateurPrive) {
    #ifdef MAP
        cout << "Appel au constructeur par copie de UtilisateurPrive." << endl;
    #endif
    this->name = unUtilisateurPrive.name;
    this->points = unUtilisateurPrive.points;
    this->mesuresFournies = unUtilisateurPrive.mesuresFournies;
}

UtilisateurPrive::~UtilisateurPrive() {
    #ifdef MAP
        cout << "Appel au desstructeur de UtilisateurPrive." << endl;
    #endif
}

int UtilisateurPrive::consultationPoints() {
    #ifdef MAP
        cout << "Appel a la methode consultationPoints() de UtilisateurPrive." << endl;
    #endif
    return this->points;
}

void UtilisateurPrive::ajoutMesure(Mesure & m) {
    #ifdef MAP
        cout << "Appel a la methode ajoutMesure() de UtilisateurPrive." << endl;
    #endif
    for (int i=0; i<100; ++i) {
        if (mesuresFournies[i]==null) {
            mesuresFournies[i]=m;
            break;
        }
    }
}

void UtilisateurPrive::historiqueMesure() {
    #ifdef MAP
        cout << "Appel a la methode historiqueMesure() de UtilisateurPrive." << endl;
    #endif
    for (int i=0; i<100; ++i) {
        if (mesuresFournies[i]!=null) {
            afficher(mesuresFournies[i]);
        }
    }
}

void UtilisateurPrive::recompenser(int pointsAttribues) {
    #ifdef MAP
        cout << "Appel a la methode recompenser() de UtilisateurPrive." << endl;
    #endif
    this->points+=pointsAttribues;
}

Mesure * UtilisateurPrive::identifierFausseDonnee(){
    #ifdef MAP
        cout << "Appel a la methode identifierFausseMesure() de UtilisateurPrive." << endl;
    #endif
}