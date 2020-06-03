#if ! defined ( ALGORITHM_H )
#define ALGORITHM_H

#include "Capteur.h"
#include "Mesure.h"
#include "measurementsReader.h"
#include "UtilisateurPrive.h"
#include <math.h>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

class Algorithm
{
 public:
    static void capteursSimilaires(Capteur & capt);
    static vector<vector<double>> statistiques(measurementsReader* mesReader, map<int,UtilisateurPrive*>& sensorToUser); //renvoie -1 si aucune mesure n'a pu etre prise en compte, la valeur moyenne sinon
    static void identifierFausseDonnee(Mesure& mesureAExaminer,  map<int,UtilisateurPrive*>& sensorToUser);
    static void impactAirCleaner();
    static void recompenserUtilisateur(UtilisateurPrive* utilisateur, int recompense);


private:
    Algorithm();
    ~Algorithm();
};

 #endif
