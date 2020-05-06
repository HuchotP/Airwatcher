#include <iostream>
#include "Capteur.h"

using namespace std;

Capteur::Capteur(int ID, string lat, string lon) {
    #ifdef MAP 
        cout << "Appel au constructeur de Capteur." << endl;
    #endif
    this->sensorID = ID;
    this->latitude = lat;
    this->longitude = lon;
}

Capteur::Capteur(Capteur & unCapteur) {
    #ifdef MAP 
        cout << "Appel au constructeur par copie de Capteur." << endl;
    #endif
    this->sensorID = unCapteur.sensorID;
    this->latitude = unCapteur.latitude;
    this->longitude = unCapteur.longitude;
}

Capteur::~Capteur() {
    #ifdef MAP 
        cout << "Appel au destructeur de Capteur." << endl;
    #endif
}