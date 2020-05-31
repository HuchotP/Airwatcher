#if ! defined ( AGENCE_H )
#define AGENCE_H

#include <iostream>
#include <string>
#include "Capteur.h"
#include "Utilisateur.h"
#include "Mesure.h"
#include "measurementsReader.h"

using namespace std;

class Agence : public Utilisateur {
     public :
        Agence(int id, measurementsReader reader);
        Agence(Agence & uneAgence);
        void accederDonnees();
        float evaluerCapteur (Capteur & capt);
        double moyenne();
        void comportementSimilaire(Capteur & capt);

        measurementsReader dataReader;
 };

 #endif
