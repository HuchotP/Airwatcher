#if ! defined ( ALGORITHM_H )
#define ALGORITHM_H

#include "Capteur.h"
#include "Mesure.h"
#include "measurementsReader.h"
#include "UtilisateurPrive.h"
#include <math.h> 


using namespace std;

class Algorithm
{
 public:
    Algorithm(vector<UtilisateurPrive> &utilisateurs) {}
    static void capteursSimilaires(Capteur & capt);
    static float moyenne(measurementsReader reader);
    static void identifierFausseDonnee(measurementsReader reader, Mesure& mesureAExaminer);
    static void impactAirCleaner();
    static void recompenserUtilisateur(int userID, int recompense);
    vector<UtilisateurPrive> utilisateurs;
    

 private:
  
};

 #endif