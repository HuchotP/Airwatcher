//---------------------------------------------------------------- INCLUDE
using namespace std;
//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <time.h>
#include <ctime>
#include <algorithm>
#include "../lib/util.h"



//------------------------------------------------------ Include personnel
#include "measurementsReader.h"
#include "Capteur.h"
#include "Mesure.h"



//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur
measurementsReader::measurementsReader(string nomFichier, char subdelim, vector<double> localisation, double r_value, vector<int>& t_value, bool flag_d, bool flag_t, vector<tm> d_value) :
	logReader(nomFichier, subdelim), localisation_value(localisation), rayon_value(r_value), flag_temporel(flag_t), temporal_values(t_value), flag_date(flag_d), date_value(d_value)
	// Algorithme :
	//
{
#ifdef MAP
	cout << "Appel au constructeur de <measurementsReader>" << endl;
#endif

	if (rayon_value != (-1)) {
		logReader reader("./data/sensors.csv", ';');
		vector<string> current;

		current = reader.next();

		while (!current.empty()) {
			string lat_c = current[1];
			string long_c = current[2];
			if (util::estDansRayon(localisation_value[0], localisation_value[1], rayon_value, stod(lat_c), stod(long_c))) {
				Capteur c(stoi(current[0].substr(6)), current[1], current[2],true);
				acceptedSensors.push_back(c);
			}
			current = reader.next();
		}
	}



} //----- Fin de measurementsMap

//----------------------------------------------------- Méthodes publiques

measurementsReader::~measurementsReader()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <measurementsReader>" << endl;
#endif
} //----- Fin de ~measurementsMap

Mesure* measurementsReader::next() {
	vector<string> result = logReader::next();
	while (!result.empty()) {
		int sensorId = stoi(result[1].substr(6));
		if (rayon_value != (-1)) {
			if (find_if(acceptedSensors.begin(), acceptedSensors.end(),[&sensorId](const Capteur& obj) {return obj.getSensorId() == sensorId;}) == acceptedSensors.end()) {
				result = logReader::next();
				continue;
			}
		}

		if (flag_date) { //if we want to filter measurements between two dates
			tm time;

			strptime(result[0].c_str(), "%Y-%m-%d %H", &time);
			time.tm_sec = 0;
			time.tm_min = 0;
			if (time.tm_year >= date_value[0].tm_year && time.tm_year <= date_value[1].tm_year &&
				time.tm_mon >= date_value[0].tm_mon && time.tm_mon <= date_value[1].tm_mon &&
				time.tm_mday >= date_value[0].tm_mday && time.tm_mday <= date_value[1].tm_mday) {
				Mesure* resultat = new Mesure(util::stringVectorToMesure(result));
				return resultat;
			}

		}
		else if (flag_temporel) { //we want to filter according to a temporal frame
			tm time_sensor;
			strptime(result[0].c_str(), "%Y-%m-%d %H", &time_sensor);
			time_sensor.tm_sec = 0;
			time_sensor.tm_min = 0;

		//	cout << "strptime : année : "<< time_sensor.tm_year << " mois : " <<  time_sensor.tm_mon << " jour : " << time_sensor.tm_mday <<  endl;
	
			time_t now_t = time(0);
			tm * now = localtime(&now_t);
	//		cout << "strptime now : année : " << now->tm_year << " mois : " << now->tm_mon << " jour : " << now->tm_mday << endl;

			tm min_time = { 0 };
			min_time.tm_year = now->tm_year - temporal_values[0];
			min_time.tm_mon = now->tm_mon - temporal_values[1];
			min_time.tm_mday = now->tm_mday - temporal_values[2];
			min_time.tm_hour = now->tm_hour - temporal_values[3];
			min_time.tm_sec = 0;
			min_time.tm_min = 0;
		//	cout << "strptime min_time : année : " << min_time.tm_year << " mois : " << min_time.tm_mon << " jour : " << min_time.tm_mday << endl;

		//	cout << "mktime sensor :" << mktime(&time_sensor) << " mktime min : " << mktime(&min_time) << endl;

		//	cout << "difftime: " <<difftime(mktime(&time_sensor), mktime(&min_time)) << endl;
			if (difftime(mktime(&time_sensor), mktime(&min_time)) >= 0){
				Mesure* resultat = new Mesure(util::stringVectorToMesure(result));
				return resultat;
			}
			
		}
		else{
			tm time;

			strptime(result[0].c_str(), "%Y-%m-%d %H", &time);
			time.tm_sec = 0;
			time.tm_min = 0;
			Mesure* resultat = new Mesure(util::stringVectorToMesure(result));
			return resultat;
		}
		result = logReader::next();
	}

	return NULL;
}
