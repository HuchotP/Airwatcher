#if ! defined ( CLEANERSESSION_H )
#define CLEANERSESSION_H

#include <iostream>
#include <string>
#include <time.h> 

using namespace std;

class CleanerSession
{
    public :
    CleanerSession(float latitude, float longitude, time_t start, time_t stop);    
    ~CleanerSession();    
    float getLatitude();
    float getLongitude();
    time_t getStart();
    time_t getStop();
    int getCleanerID();   

    private:
    int cleanerID;
    float latitude ;
    float longitude ;
    time_t start ;
    time_t stop ;
};

#endif