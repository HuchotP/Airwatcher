#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

#include <iostream>
#include <string>

using namespace std;

class Capteur{
    public :
        Capteur(int id, double lat, double lon, int userID);
        // Capteur(Capteur & unCapteur)
        Capteur();
        ~Capteur();
        int getSensorId() const;
        double longitude;
        double latitude;
        int sensorID;
        int userID;
};

 #endif