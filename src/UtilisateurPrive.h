#include <iostream>
#include <string>
#include "Mesure.h"
#include "Utilisateur.h"

using namespace std;

class UtilisateurPrive : public Utilisateur {
    public :
        UtilisateurPrive(int ID, string nom, int pts);
        UtilisateurPrive(UtilisateurPrive & unUtilisateurPrive);
        ~UtilisateurPrive();
        int consultationPoints();
        void ajoutMesure(Mesure & m);
        void historiqueMesure();
        void recompenser(pointsAttribues);
        void identifierFausseDonnee();

    private :
        string name;
        int points;
        Mesure * mesuresFournies;
};