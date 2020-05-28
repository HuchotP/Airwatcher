

//---------- Interface de la classe <util> (fichier util.h) ----------------
#if ! defined ( UTIL_H )
#define UTIL_H
using namespace std;

#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>
#include "../src/Mesure.h"


//--------------------------------------------------- Interfaces utilisées


//------------------------------------------------------------------------
// Rôle de la classe <util>
// Permet de stocker la synthèse du fichier log et d'effectuer des opérations sur celle-ci
//
//------------------------------------------------------------------------

class util
{
public:

    //----------------------------------------------------- Méthodes publiques statiques
    
    static bool estDansRayon(double lat_o, double long_o, double r, double lat_d, double long_d) {
        double PI = 3.14159265;
        return (acos(sin(lat_o*2*PI/360) * sin(lat_d*2*PI/360) + cos(lat_o*2*PI/360) * cos(lat_d*2*PI/360) * cos((long_d-long_o)*2*PI/360) ) *6378.137 < r);
    }

    static Mesure stringVectorToMesure(vector<string> vector_mesures) {
        tm temps;
        strptime(vector_mesures[0].c_str(), "%Y-%m-%d %H", &temps);
        temps.tm_hour = 0;
        temps.tm_min = 0;
        temps.tm_sec = 0;
        Mesure m(mktime(&temps), stoi(vector_mesures[1].substr(6)), vector_mesures[2], stof(vector_mesures[3]), true);
        return m;
    } 

};


#endif // LOGREADER_H
