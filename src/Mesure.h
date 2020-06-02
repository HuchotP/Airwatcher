#if ! defined ( MESURE_H )
#define MESURE_H

#include <iostream>
#include <string>
#include <time.h>
#include "Capteur.h"

using namespace std;

class Mesure
{
public :
    Mesure(time_t time, int sID, string aID, double val, bool status);
    Mesure();
    Mesure(const Mesure& mes);
    ~Mesure();
    void AfficherMesure();

    time_t timeStamp ;
    int sensorID ;
    string attributeID ;
    double value ;
    bool status ;
    Capteur sensor;

};

#endif
