#include <iostream>
#include "Agence.h"

using namespace std;

Agence::Agence(int id) : Utilisateur(id)
{
    #ifdef MAP 
        cout << "Appel au constructeur de Agence." << endl;
    #endif
    
}

Agence::~Agence()
{
    #ifdef MAP
    cout << "Appel au destructeur de <Agence>" << endl;
    #endif

}

Mesure * Agence::accederDonnees()
{
    #ifdef MAP
        cout<<"Appel a la methode accederDonnees() de Agence" << endl;
    #endif 

}

float Agence::evaluerCapteur(Capteur & capt)
{
    #ifdef MAP
        cout<<"Appel a la methode evaluerCapteur() de Agence" << endl;
    #endif 

}

float Agence::moyenne()
{
    #ifdef MAP
        cout<<"Appel a la methode moyenne() de Agence" << endl;
    #endif 

}

float Agence::comportementSimilaire(Capteur & capt)
{
    #ifdef MAP
        cout<<"Appel a la methode comportementSimilaire() de Agence" << endl;
    #endif 

}