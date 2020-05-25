//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>

using namespace std;

//------------------------------------------------------ Include personnel
#include "logReader.h"


//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur
logReader::logReader (string nomFichier, char subdelim) : fichier(nomFichier.c_str())
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <logReader>" << endl;
#endif
    nomfichier = nomFichier;
    delim = subdelim;
	if(fichier.is_open()){
		cout << "fichier ouvert" << endl;
	}else{
		cout << "erreur dans l'ouverture du fichier"<<endl;
	}

} //----- Fin de logMap

//----------------------------------------------------- Méthodes publiques

logReader::~logReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <logReader>" << endl;
#endif
} //----- Fin de ~logMap

vector<string> logReader::next(){
          vector<string> result = NULL;
    if(fichier.eof()) {
        return result;
    }
          string line;

          getline(fichier,line);
          stringstream ges(line);
          string subtoken;
          while (getline(ges, subtoken, delim)) {
              result.push_back(subtoken);
          }
          return result;
}
