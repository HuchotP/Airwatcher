#include <iostream>
#include <string>
#include "UtilisateurPrive.h"
#include "Mesure.h"

using namespace std;

UtilisateurPrive::UtilisateurPrive(int ID, string nom, int  pts, int idCapteur, int noteFiabilite=5) : Utilisateur(ID) {
    #ifdef MAP
        cout << "Appel au constructeur de UtilisateurPrive." << endl;
    #endif
    this->name = nom;
    this->points = pts;
    this->idCapteur=idCapteur;
    this->fiabilite = noteFiabilite;
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

int UtilisateurPrive::getIdCapteur(){
    #ifdef MAP
        cout << "Appel a la methode getIdCapteur() de UtilisateurPrive." << endl;
    #endif
    return idCapteur;
}

int UtilisateurPrive::consultationPoints() {
    #ifdef MAP
        cout << "Appel a la methode consultationPoints() de UtilisateurPrive." << endl;
    #endif
    return points;
}

void UtilisateurPrive::ajoutMesure(Mesure & m) {
    #ifdef MAP
        cout << "Appel a la methode ajoutMesure() de UtilisateurPrive." << endl;
    #endif
    mesuresFournies.push_back(m);
}

void UtilisateurPrive::historiqueMesure() {
    #ifdef MAP
        cout << "Appel a la methode historiqueMesure() de UtilisateurPrive." << endl;
    #endif
    for(unsigned int i = 0; i < mesuresFournies.size(); i++) // D’ailleurs, i++ ou ++i ?
    {
      mesuresFournies[i].AfficherMesure();
    }
}

void UtilisateurPrive::recompenser(int pointsAttribues) {
    #ifdef MAP
        cout << "Appel a la methode recompenser() de UtilisateurPrive." << endl;
    #endif
    this->points+=pointsAttribues;
}
