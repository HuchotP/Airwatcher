//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <time.h>
#include <ctime>
#include <algorithm>
#include "../lib/util.h"

using namespace std;

//------------------------------------------------------ Include personnel
#include "measurementsReader.h"
#include "Capteur.h"



//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur
measurementsReader::measurementsReader (string nomFichier, char subdelim, vector<double> localisation, double r_value, vector<int> & t_value, bool flag_d, vector<tm> d_value) : 
 logReader(nomFichier, subdelim), localisation_value(localisation), rayon_value(r_value), temporal_values(t_value), flag_date(flag_d), date_value(d_value)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <measurementsReader>" << endl;
#endif

    logReader reader("./data/sensors.csv", ';');
    vector<string> current;
    current = reader.next();
    while(!current.empty()) {
        string lat_c = current[1];
        string long_c = current[2];
        if(util::estDansRayon(localisation[0], localisation[1], rayon_value, stod(lat_c), stod(long_c))) {
            Capteur c(stoi(current[0].substr(6)), current[1], current[2]);
            acceptedSensors.push_back(c);
        }
        current = reader.next();

    }

    
} //----- Fin de measurementsMap

//----------------------------------------------------- Méthodes publiques

measurementsReader::~measurementsReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <measurementsReader>" << endl;
#endif
} //----- Fin de ~measurementsMap

vector<string> measurementsReader::next() {
        vector<string> result = logReader::next();
               
        int sensorId = stoi(result[2].substr(6));

        if(find(acceptedSensors.begin(), acceptedSensors.end(), sensorId) != acceptedSensors.end()){ //if sensor is in vector of accepted sensors

            if(flag_date){ //if we want to filter measuremnts between two dates
                
                tm time;
                strptime(result[0], "%Y-%m-%d", &time);

                if(time.tm_year >= date_value[0].tm_year && time.tm_year <= date_value[1].tm_year &&
                    time.tm_mon >= date_value[0].tm_mon && time.tm_mon <= date_value[1].tm_mon && 
                    time.tm_mday >= date_value[0].tm_mday && time.tm_mday <= date_value[1].tm_mday){
                        
                        return result;

                    }
                
            }else if(flag_temporel){ //we want to filter according to a temporal frame

                tm * now = localtime();
                tm min_time = {0};
                min_time.tm_year = now->tm_year - temporal_values[0];
                min_time.tm_mon = now->tm_mon - temporal_values[1];
                min_time.tm_mday = now->tm_mday - temporal_values[2];
                min_time.tm_hour = now->tm_hour - temporal_values[3];
                min_time.tm_sec = 0;
                min_time.tm_min = 0;


            }

        }
        string line;
        getline(fichier, line);
        stringstream ges(line);
        string subtoken;
        while (getline(ges, subtoken, delim)) {
            result.push_back(subtoken);
        }
        return result;
}
