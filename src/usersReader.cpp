//---------------------------------------------------------------- INCLUDE
using namespace std;
//-------------------------------------------------------- Include système


//------------------------------------------------------ Include personnel
#include "usersReader.h"
#include "../lib/util.h"


//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur
usersReader::usersReader(string nomFichier, char subdelim) :
	logReader(nomFichier, subdelim)
	// Algorithme :
	//
{
#ifdef MAP
	cout << "Appel au constructeur de <usersReader>" << endl;
#endif

    vector<string> current = logReader::next();

		while (!current.empty()) {
            string userId = current[0].substr(4);
            string sensorId = current[1].substr(6);
            //cout<< userId<<"   |   "<< sensorId<<endl;
            UtilisateurPrive* user =new UtilisateurPrive(stoi(userId), stoi(sensorId));
             //UtilisateurPrive user (stoi(userId), stoi(sensorId));
            sensorToUser.insert(pair<int,UtilisateurPrive*>(stoi(sensorId),user));
            current = logReader::next();
        }
}

usersReader::~usersReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <logReader>" << endl;
#endif
} //----- Fin de ~logMap



//----------------------------------------------------- Méthodes publiques
