#if ! defined ( CLEANER_H )
#define CLEANER_H

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Cleaner
{
    public :
    Cleaner(int ID, float latitude, float longitude, time_t start, time_t stop);
    ~Cleaner();
    float getLatitude();
    float getLongitude();
    time_t getStart();
    time_t getStop();
    int getID();

    private:
    int cleanerID;
    float latitude ;
    float longitude ;
    time_t start ;
    time_t stop ;
};

#endif
