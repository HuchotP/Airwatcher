#include <iostream>
#include "Cleaner.h"
#include <time.h>
using namespace std;

Cleaner::Cleaner(int ID, float latitude, float longitude, time_t start, time_t stop)
    : cleanerID(ID), latitude(latitude), longitude(longitude), start(start), stop(stop)
{
    #ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
    #endif
}

Cleaner::~Cleaner()
{
    #ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
    #endif

}

int Cleaner::getID()
{
    #ifdef MAP
        cout<<"Appel a la methode getLatitude() de Cleaner" << endl;
    #endif
    return cleanerID;
}

float Cleaner::getLatitude()
{
    #ifdef MAP
        cout<<"Appel a la methode getLatitude() de Cleaner" << endl;
    #endif
    return latitude;
}

float Cleaner::getLongitude()
{
    #ifdef MAP
        cout<<"Appel a la methode getLongitude() de Cleaner" << endl;
    #endif
    return longitude;
}

time_t Cleaner::getStart()
{
    #ifdef MAP
        cout<<"Appel a la methode getStart() de Cleaner" << endl;
    #endif
    return start;
}

time_t Cleaner::getStop()
{
    #ifdef MAP
        cout<<"Appel a la methode getStop() de Cleaner" << endl;
    #endif
    return stop;
}
