#include <iostream>
#include "Mesure.h"
#include <time.h> 
using namespace std;

Mesure::Mesure(time_t time, string sID, string aID, float val, bool status)
    : timeStamp(time), sensorID(sID), attributeID(aID), value(val), status(status)
{ 
    #ifdef MAP
    cout << "Appel au constructeur de <Mesure>" << endl;
    #endif
}

Mesure::~Mesure()
{
    #ifdef MAP
    cout << "Appel au destructeur de <Mesure>" << endl;
    #endif

}

void Mesure::AfficherMesure()
{
    cout<< "date" << timeStamp << " | sensorID " << sensorID << "| attributeID " << attributeID << "| value " << value << "| status" << status ;
}
