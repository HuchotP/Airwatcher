#include <iostream>
#include <string>
#include "UtilisateurPrive.h"
#include "Mesure.h"

using namespace std;

UtilisateurPrive::UtilisateurPrive(int ID, int idCapteur, int  pts, int noteFiabilite) : Utilisateur(ID) {
    #ifdef MAP
        cout << "Appel au constructeur de UtilisateurPrive." << endl;
    #endif
    this->points = pts;
    this->idCapteur=idCapteur;
    this->fiabilite = noteFiabilite;
}

UtilisateurPrive::UtilisateurPrive(UtilisateurPrive & unUtilisateurPrive) : Utilisateur(unUtilisateurPrive) {
    #ifdef MAP
        cout << "Appel au constructeur par copie de UtilisateurPrive." << endl;
    #endif
    this->points = unUtilisateurPrive.points;
    this->mesuresFournies = unUtilisateurPrive.mesuresFournies;
}

UtilisateurPrive::~UtilisateurPrive() {
    #ifdef MAP
        cout << "Appel au desstructeur de UtilisateurPrive." << endl;
    #endif
}

int UtilisateurPrive::getIdCapteur() const{
    #ifdef MAP
        cout << "Appel a la methode getIdCapteur() de UtilisateurPrive." << endl;
    #endif
    return idCapteur;
}

int UtilisateurPrive::getPoints() const{
    #ifdef MAP
        cout << "Appel a la methode getPoints() de UtilisateurPrive." << endl;
    #endif
    return points;
}

void UtilisateurPrive::setPoints(int nouveauxPoints) {
    #ifdef MAP
        cout << "Appel a la methode setPoints() de UtilisateurPrive." << endl;
    #endif
    points = nouveauxPoints;
}

int UtilisateurPrive::getFiabilite() const{
    #ifdef MAP
        cout << "Appel a la methode getFiabilite() de UtilisateurPrive." << endl;
    #endif
    return fiabilite;
}

void UtilisateurPrive::setFiabilite(int nouvelleFiabilite) {
    #ifdef MAP
        cout << "Appel a la methode setFiabilite() de UtilisateurPrive." << endl;
    #endif
    fiabilite = nouvelleFiabilite;
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
