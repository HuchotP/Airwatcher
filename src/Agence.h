#if ! defined ( AGENCE_H )
#define AGENCE_H

#include <iostream>
#include <string>
#include "Capteur.h"
#include "Utilisateur.h"
#include "Mesure.h"

 using namespace std;

 class Agence : public Utilisateur {
     public :
        Agence();
        Agence(Agence & uneAgence);
        ~Agence();
        Mesure * accederDonnees();
        float evaluerCapteur (Capteur & capt);
        float moyenne();
        float comportementSimilaire(Capteur & capt);
 };

 #endif