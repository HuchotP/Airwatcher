#include <iostream>
#include <string>
#include "Capteur.h"

using namespace std;

Capteur::Capteur(int ID, double lat, double lon, int userID) {
    #ifdef MAP 
        cout << "Appel au constructeur de Capteur." << endl;
    #endif
    this->sensorID = ID;
    this->latitude = lat;
    this->longitude = lon;
    this->userID = userID;
}

Capteur::Capteur() {
    #ifdef MAP 
        cout << "Appel au constructeur vide de Capteur." << endl;
    #endif
    
}
/*
Capteur::Capteur(Capteur & unCapteur) {
    #ifdef MAP
        cout << "Appel au constructeur par copie de Capteur." << endl;
    #endif
    this->sensorID = unCapteur.sensorID;
    this->latitude = unCapteur.latitude;
    this->longitude = unCapteur.longitude;
}
*/


Capteur::~Capteur() {
    #ifdef MAP 
        cout << "Appel au destructeur de Capteur." << endl;
    #endif
}

int Capteur::getSensorId() const{
    return sensorID;
}