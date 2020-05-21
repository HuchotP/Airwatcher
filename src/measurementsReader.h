//---------- Interface de la classe <measurementsReader> (fichier measurementsReader.h) ----------------
#if ! defined ( MEASUREMENTSREADER_H )
#define MEASUREMENTSREADER_H
using namespace std;

#include <string>
#include <vector>

#include <fstream>
#include <time.h>
#include "logReader.h"

//--------------------------------------------------- Interfaces utilisées


//------------------------------------------------------------------------
// Rôle de la classe <measurementsReader>
// Permet de stocker la synthèse du fichier measurements et d'effectuer des opérations sur celle-ci
//
//------------------------------------------------------------------------

class measurementsReader : public logReader
{
public:
    //Constructeurs de measurementsMap

   measurementsReader (string nomFichier, char subdelim, vector<double> localisation, double r_value, vector<int> & t_value, bool flag_d, vector<tm> d_value);

    //----------------------------------------------------- Méthodes publiques
    ~measurementsReader ();

    vector<string> next();

protected:

    vector<Capteur> acceptedSensors;

    vector<double> localisation_value;
    bool flag_rayon;
    double rayon_value;

    bool flag_temporel;
    vector<int>  temporal_values;
    bool flag_date;
    vector<tm> date_value;

    const unsigned int secondsInHour = 3600;
    const unsigned int hoursInDay = 24;
    const unsigned int dayInMonth = 
};


#endif // MEASUREMENTSREADER_H
