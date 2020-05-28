#if ! defined ( UTILISATEUR_H )
#define UTILISATEUR_H

#include <iostream>
#include <string>

class Utilisateur {
    public :
        Utilisateur(int id);
        Utilisateur(Utilisateur & unUtilisateur);
        ~Utilisateur();
        int getUserID();
        void creerCompte();
        void connexion();
        void deconnexion();
    private :
        int userid;
};
 #endif