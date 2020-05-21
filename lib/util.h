

//---------- Interface de la classe <util> (fichier util.h) ----------------
#if ! defined ( UTIL_H )
#define UTIL_H
using namespace std;

#include <string>
#include <vector>
#include <cmath>
#include <fstream>

//--------------------------------------------------- Interfaces utilisées


//------------------------------------------------------------------------
// Rôle de la classe <util>
// Permet de stocker la synthèse du fichier log et d'effectuer des opérations sur celle-ci
//
//------------------------------------------------------------------------

class util
{
public:


    ifstream fichier;
    util (string nomFichier, char subdelim);

    //----------------------------------------------------- Méthodes publiques statiques
    
    static bool estDansRayon(double lat_o, double long_o, double r, double lat_d, double long_d) {
        double PI = 3.14159265;
        return (acos(sin(lat_o*2*PI/360) * sin(lat_d*2*PI/360) + cos(lat_o*2*PI/360) * cos(lat_d*2*PI/360) * cos((long_d-long_o)*2*PI/360) ) *6378.137 < r);
    }

};


#endif // LOGREADER_H
