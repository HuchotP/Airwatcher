#include <time.h> 
#include <iostream>
#include "Mesure.h"
#include "measurementsReader.h"
using namespace std;

Mesure::Mesure(time_t time, int sID, string aID, float val, bool status=null)
    : timeStamp(time), sensorID(sID), attributeID(aID), value(val), status(status)
{ 
    #ifdef MAP
    cout << "Appel au constructeur de <Mesure>" << endl;
    #endif
    iterator it = find_if(measurementsReader::acceptedSensors.begin(), measurementsReader::acceptedSensors.end(),[&sensorId](const Capteur& obj) {return obj.getSensorId() == sensorId;});
    if(it != measurementsReader::acceptedSensors.end()) {
        sensor = measurementsReader::acceptedSensors[it];
    }

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
