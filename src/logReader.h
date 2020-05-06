

//---------- Interface de la classe <logReader> (fichier logReader.h) ----------------
#if ! defined ( LOGREADER_H )
#define LOGREADER_H
using namespace std;

#include <string>
#include <vector>

#include <fstream>

//--------------------------------------------------- Interfaces utilisées


//------------------------------------------------------------------------
// Rôle de la classe <logReader>
// Permet de stocker la synthèse du fichier log et d'effectuer des opérations sur celle-ci
//
//------------------------------------------------------------------------

class logReader
{
public:
    //Constructeurs de logMap
	string nomfichier;
    char delim;


    ifstream fichier;
   logReader (string nomFichier, char subdelim);

    //----------------------------------------------------- Méthodes publiques
    ~logReader ();
    vector<string> next();
};


#endif // LOGREADER_H
