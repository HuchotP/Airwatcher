#if ! defined ( ENTREPRISE_H )
#define ENTREPRISE_H

#include <iostream>
#include <string>
#include <vector>
#include "Cleaner.h"
#include "Utilisateur.h"

 using namespace std;

 class Entreprise : public Utilisateur {
     public :
        Entreprise(int ID, string nom);
        Entreprise(Entreprise & uneEntreprise);
        ~Entreprise();
        void ajoutAirCleaner(Cleaner & c);
        float mesuresProchesAirCleaner(Cleaner & c);
        float moyenneAirCleaner (Cleaner & c);
        float etendueZoneTraitee(Cleaner & c);
        float niveauAmelioration(Cleaner & c);

     private :
        string name;
        vector<Cleaner> tabCleaner;
        int userID;
 };
  #endif