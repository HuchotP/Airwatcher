#if ! defined ( UTILISATEURPRIVE_H )
#define UTILISATEURPRIVE_H

#include <iostream>
#include <string>
#include "Mesure.h"
#include "Utilisateur.h"

using namespace std;

class UtilisateurPrive : public Utilisateur {
    public :
        UtilisateurPrive(int ID, string nom, int pts, int idCapteur, int noteFiabilité=5);
        UtilisateurPrive(UtilisateurPrive & unUtilisateurPrive);
        ~UtilisateurPrive();
        int consultationPoints();
        int getIdCapteur();
        void ajoutMesure(Mesure & m);
        void historiqueMesure();
        void recompenser(int pointsAttribues);
        void identifierFausseDonnee();

    private :
        string name;
        int points;
        int idCapteur;
        int fiabilité;
        Mesure * mesuresFournies;
};
 #endif