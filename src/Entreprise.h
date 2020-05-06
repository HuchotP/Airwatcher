#include <iostream>
#include <string>
#include "lib/Cleaner.h"

 using namespace std;

 class Entreprise : Utilisateur {
     public :
        Entreprise(string nom);
        Entreprise(Entreprise & uneEntreprise);
        ~Entreprise();
        void ajoutAirCleaner(Cleaner & c);
        float mesuresProchesAirCleaner(Cleaner & c);
        float moyenneAirCleaner (Cleaner & c);
        float etendueZoneTraitee(Cleaner & c);
        float niveauAmelioration(Cleaner & c);

     private :
        string name;
        Cleaner * tabCleaner;
 };