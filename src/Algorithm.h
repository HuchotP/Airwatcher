#if ! defined ( ALGORITHM_H )
#define ALGORITHM_H

#include "Capteur.h"
#include "Mesure.h"
#include "measurementsReader.h"
#include "UtilisateurPrive.h"
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

class Algorithm
{
 public:
    static void capteursSimilaires(Capteur & capt);
    static vector<float> moyenne(measurementsReader* mesReader, vector<UtilisateurPrive*> &utilisateurs); //renvoie -1 si aucune mesure n'a pu etre prise en compte, la valeur moyenne sinon
    static void identifierFausseDonnee(Mesure& mesureAExaminer,  vector<UtilisateurPrive*> &utilisateurs);
    static void impactAirCleaner();
    static void recompenserUtilisateur(vector<UtilisateurPrive*> &utilisateurs, int userID, int recompense);


private:
    Algorithm();
    ~Algorithm();
};

 #endif
