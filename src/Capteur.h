#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

#include <iostream>
#include <string>

using namespace std;

class Capteur{
    public :
        Capteur(int id, string lon, string lat, int userID);
        // Capteur(Capteur & unCapteur)
        ~Capteur();
        int getSensorId() const;
        float longitude;
        float latitude;
        int sensorID;
        int userID;
};

 #endif