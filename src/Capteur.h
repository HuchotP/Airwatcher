#include <iostream>
#include <string>

using namespace std;

class Capteur{
    public :
        Capteur (int id, string lon, string lat);
        Capteur (Capteur & unCapteur);
        ~Capteur();
        string longitude;
        string latitude;
        int sensorID;
};