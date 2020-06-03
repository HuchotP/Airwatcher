#include <iostream>
#include <cstdlib>
#include "Utilisateur.h"

using namespace std;

Utilisateur::Utilisateur(int id){
    #ifdef MAP
        cout<<"Appel au constructeur de Utilisateur" << endl;
    #endif
    this->userid=id;
}

Utilisateur::Utilisateur(Utilisateur & unUser) {
    #ifdef MAP
        cout<<"Appel au constructeur de copie de Utilisateur" << endl;
    #endif
    this->userid=unUser.userid;
}

Utilisateur::~Utilisateur() {
    #ifdef MAP
        cout<<"Appel au destructeur de Utilisateur" << endl;
    #endif
}

int Utilisateur::getUserID() {
    #ifdef MAP
        cout<<"Appel a la methode getUserID() de Utilisateur" << endl;
    #endif 
    return this->userid;
}

void Utilisateur::creerCompte() {
     #ifdef MAP
        cout<<"Appel a la methode creerCompte() de Utilisateur" << endl;
    #endif 
    int numeroID = rand()%100+1;
    this->userid=numeroID;
    cout << "Votre compte a été créé et votre numéro d'utilisateur est le " << numeroID << "." << endl;
}

void Utilisateur::connexion() {
    #ifdef MAP
        cout<<"Appel a la methode Connexion() de Utilisateur" << endl;
    #endif
    cout << "Vous etes connecte a AirWatcher." << endl;
}

void Utilisateur::deconnexion() {
    #ifdef MAP
        cout<<"Appel a la methode Deconnexion de Utilisateur" << endl;
    #endif
    cout << "Vous etes deconnecte de AirWatcher." << endl;
}