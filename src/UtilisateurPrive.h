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
        UtilisateurPrive(int ID, int idCapteur, int pts=0, int noteFiabilite=5);
        UtilisateurPrive(UtilisateurPrive & unUtilisateurPrive);
        ~UtilisateurPrive();
        int getPoints() const;
        void setPoints(int nouveauxPoints);
        int getIdCapteur() const;
        int getFiabilite() const;
        void setFiabilite(int nouvelleFiabilite);
        void ajoutMesure(Mesure & m);
        void historiqueMesure();
        void recompenser(int pointsAttribues);

    private :
        int points;
        int idCapteur;
        int fiabilite;
        vector<Mesure> mesuresFournies;
};
 #endif
