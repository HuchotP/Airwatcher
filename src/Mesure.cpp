#include <time.h>
#include <iostream>
#include "Mesure.h"
#include "measurementsReader.h"
using namespace std;

Mesure::Mesure(time_t time, int sID, string aID, float val, bool status)
    : timeStamp(time), sensorID(sID), attributeID(aID), value(val), status(status)
{
    #ifdef MAP
    cout << "Appel au constructeur de <Mesure>" << endl;
    #endif


}

Mesure::Mesure(const Mesure& mes) : timeStamp(mes.timeStamp), sensorID(mes.sensorID), attributeID(mes.attributeID), value(mes.value), status(mes.status) {
}

Mesure::Mesure() {
  timeStamp=0;
  sensorID=-1;
  attributeID=-1;
  value=-1;
  status=false;
}

Mesure::~Mesure()
{
    #ifdef MAP
    cout << "Appel au destructeur de <Mesure>" << endl;
    #endif

}

void Mesure::AfficherMesure()
{
    cout << "date " << timeStamp << " | sensorID " << sensorID << "| attributeID " << attributeID << "| value " << value << "| status " << status << endl;
}
