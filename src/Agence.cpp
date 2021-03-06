#include <iostream>
#include <ctime>
#include "Agence.h"
#include "Algorithm.h"
#include "usersReader.h"
#include "../lib/util.h"
#include <vector>

using namespace std;

Agence::Agence(int ID) : Utilisateur(ID) {
  #ifdef MAP
      cout << "Appel au constructeur de Agence." << endl;
  #endif
}

Agence::~Agence()
{
    #ifdef MAP
    cout << "Appel au destructeur de <Agence>" << endl;
    #endif

}

void Agence::accederDonnees(measurementsReader& dataReader)
{
    #ifdef MAP
        cout<<"Appel a la methode accederDonnees() de Agence" << endl;
    #endif

    Mesure* data = dataReader.next();

    cout << "Timestamp | SensorId | Lat/Long | AttributeId | Value" << endl;

    while(data!=NULL){

        tm * mesure_time = localtime(&(data->timeStamp));

        cout << mesure_time->tm_mday << "/" << (mesure_time->tm_mon+1) << "/" << (mesure_time->tm_year+1900) << ":";
        cout << mesure_time->tm_hour << ":" << mesure_time->tm_min << ":" << mesure_time->tm_sec;

        cout << " | " << data->sensorID;
        cout << " | " << data->sensor.latitude << ", " << data->sensor.longitude;
        cout << " | " << data->attributeID;
        cout << " | " << data->value << endl;


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

void Agence::statistiques(measurementsReader& dataReader)
{
    #ifdef MAP
        cout<<"Appel a la methode moyenne() de Agence" << endl;
    #endif


    usersReader utilisateurs("./data/users.csv", ';');

    vector<vector<double>> statistiques = Algorithm::statistiques(&dataReader, utilisateurs.sensorToUser);

    cout << "Indices de la qualité de l'air par polluant : " << endl;
    util::printStats("03", statistiques[0]);
    util::printStats("SO2", statistiques[1]);
    util::printStats("NO2", statistiques[2]);
    util::printStats("PM10", statistiques[3]);
}
