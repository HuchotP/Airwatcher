#include <iostream>
#include "CleanerSession.h"
#include <time.h> 
using namespace std;

CleanerSession::CleanerSession(float latitude, float longitude, time_t start, time_t stop)
    : latitude(latitude), longitude(longitude), start(start), stop(stop)
{ 
    #ifdef MAP
    cout << "Appel au constructeur de <CleanerSession>" << endl;
    #endif
}

CleanerSession::~CleanerSession()
{
    #ifdef MAP
    cout << "Appel au destructeur de <CleanerSession>" << endl;
    #endif

}

int CleanerSession::getCleanerID()
{
    #ifdef MAP
        cout<<"Appel a la methode getLatitude() de CleanerSession" << endl;
    #endif 
    return cleanerID;
}

float CleanerSession::getLatitude()
{
    #ifdef MAP
        cout<<"Appel a la methode getLatitude() de CleanerSession" << endl;
    #endif 
    return latitude;
}

float CleanerSession::getLongitude()
{
    #ifdef MAP
        cout<<"Appel a la methode getLongitude() de CleanerSession" << endl;
    #endif 
    return longitude;
}

time_t CleanerSession::getStart()
{
    #ifdef MAP
        cout<<"Appel a la methode getStart() de CleanerSession" << endl;
    #endif 
    return start;
}

time_t CleanerSession::getStop()
{
    #ifdef MAP
        cout<<"Appel a la methode getStop() de CleanerSession" << endl;
    #endif 
    return stop;
}

