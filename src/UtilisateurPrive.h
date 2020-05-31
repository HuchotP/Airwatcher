#if ! defined ( UTILISATEURPRIVE_H )
#define UTILISATEURPRIVE_H

#include <iostream>
#include <string>
#include <vector>
#include "Mesure.h"
#include "Utilisateur.h"

using namespace std;

class UtilisateurPrive : public Utilisateur {
    public :
        UtilisateurPrive(int ID, string nom, int pts, int idCapteur, int noteFiabilite);
        UtilisateurPrive(UtilisateurPrive & unUtilisateurPrive);
        ~UtilisateurPrive();
        int consultationPoints();
        int getIdCapteur();
        void ajoutMesure(Mesure & m);
        void historiqueMesure();
        void recompenser(int pointsAttribues);

    private :
        string name;
        int points;
        int idCapteur;
        int fiabilite;
        vector<Mesure> mesuresFournies;
};
 #endif
