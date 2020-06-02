//---------- Interface de la classe <usersReader> (fichier usersReader.h) ----------------
#if ! defined ( USERSREADER_H )
#define USERSREADER_H
using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include "logReader.h"
#include "Mesure.h"
#include "UtilisateurPrive.h"
#include "UtilisateurPrive.h"
#include <algorithm>

//--------------------------------------------------- Interfaces utilisées


//------------------------------------------------------------------------
// Rôle de la classe <usersReader>
// Permet de stocker les utilisateurs
//
//------------------------------------------------------------------------

class usersReader : public logReader
{

public:
    //Constructeurs de measurementsMap

   usersReader (string nomFichier, char subdelim);
    ~usersReader ();

    map<int,UtilisateurPrive*> sensorToUser;



};


#endif // USERSREADER_H
