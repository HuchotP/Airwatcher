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
    Mesure(time_t time, int sID, string aID, float val, bool status=NULL);    
    ~Mesure();
    void AfficherMesure();

    time_t timeStamp ;
    int sensorID ;
    Capteur sensor;
    string attributeID ;
    float value ;
    bool status ;

};

#endif