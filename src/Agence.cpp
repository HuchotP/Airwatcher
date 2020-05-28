#include <iostream>
#include <ctime>
#include "Agence.h"

using namespace std;

Agence::Agence(int id, measurementsReader reader) : Utilisateur(id)
{
    #ifdef MAP 
        cout << "Appel au constructeur de Agence." << endl;
    #endif
    
    this->dataReader = reader;

}

Agence::~Agence()
{
    #ifdef MAP
    cout << "Appel au destructeur de <Agence>" << endl;
    #endif

}

void Agence::accederDonnees()
{
    #ifdef MAP
        cout<<"Appel a la methode accederDonnees() de Agence" << endl;
    #endif 

    vector<string> data;

    data = dataReader.next();

    cout << "Timestamp | SensorId | Lat/Long | AttributeId | Value" << endl;
    
    while(!data.empty()){

        Mesure current = util::stringVectorToMesure(data);


        tm * mesure_time = localtime(&current.timeStamp);

        cout << mesure_time->tm_mday << "/" << mesure_time->tm_mon << "/" << mesure_time->tm_year << ":";
        cout << mesure_time->tm_hour << ":" << mesure_time->tm_min << ":" << mesure_time->tm_sec;

        cout << " | " << current.sensorID;
        //cout << " | " << current.lat/long;
        cout << " | " << current.attributeID;
        cout << " | " << current.value << endl;


        data = dataReader.next();

    }

}

float Agence::evaluerCapteur(Capteur & capt)
{
    #ifdef MAP
        cout<<"Appel a la methode evaluerCapteur() de Agence" << endl;
    #endif 

    return 0.0;

}

double Agence::moyenne()
{
    #ifdef MAP
        cout<<"Appel a la methode moyenne() de Agence" << endl;
    #endif 

    return 0.0;

}

float Agence::comportementSimilaire(Capteur & capt)
{
    #ifdef MAP
        cout<<"Appel a la methode comportementSimilaire() de Agence" << endl;
    #endif 

    return 0.0;

}