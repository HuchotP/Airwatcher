#if ! defined ( MESURE_H )
#define MESURE_H

#include <iostream>
#include <string>
#include <time.h> 

using namespace std;

class Mesure
{
    public :
    Mesure(time_t time, string sID, string aID, float val, bool status);    
    ~Mesure();
    void AfficherMesure();

    time_t timeStamp ;
    string sensorID ;
    string attributeID ;
    float value ;
    bool status ;
};

#endif