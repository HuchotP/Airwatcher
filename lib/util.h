

//---------- Interface de la classe <util> (fichier util.h) ----------------
#if !defined(UTIL_H)
#define UTIL_H
using namespace std;

#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <fstream>
#include <ctime>
#include "../src/Mesure.h"
#include "../src/logReader.h"
#include "../src/usersReader.h"
#include "../src/UtilisateurPrive.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------------------
// Rôle de la classe <util>
// Permet de stocker la synthèse du fichier log et d'effectuer des opérations sur celle-ci
//
//------------------------------------------------------------------------

class util
{
public:
    //----------------------------------------------------- Méthodes publiques statiques

    static bool estDansRayon(double lat_o, double long_o, double r, double lat_d, double long_d)
    {
        double PI = 3.14159265;
        return (acos(sin(lat_o * 2 * PI / 360) * sin(lat_d * 2 * PI / 360) + cos(lat_o * 2 * PI / 360) * cos(lat_d * 2 * PI / 360) * cos((long_d - long_o) * 2 * PI / 360)) * 6378.137 < r);
    }

    static double distance(double lat_o, double long_o, double lat_d, double long_d)
    {
        double PI = 3.14159265;
        return (acos(sin(lat_o * 2 * PI / 360) * sin(lat_d * 2 * PI / 360) + cos(lat_o * 2 * PI / 360) * cos(lat_d * 2 * PI / 360) * cos((long_d - long_o) * 2 * PI / 360)) * 6378.137);
    }

    static vector<Capteur> listerCapteurs()
    {

        logReader logReaderCapteur("./data/sensors.csv", ';');
        usersReader utilisateurs("./data/users.csv", ';');

        vector<Capteur> liste;

        vector<string> capteurData;
        while (!(capteurData = logReaderCapteur.next()).empty())
        {

            map<int, UtilisateurPrive *>::iterator it = utilisateurs.sensorToUser.begin();
            while (it != utilisateurs.sensorToUser.end())
            {

                if (it->second->getUserID() == stoi(capteurData[0].substr(6)))
                {

                    break;
                }

                ++it;
            }

            if (it != utilisateurs.sensorToUser.end())
            {
                liste.push_back(Capteur(stoi(capteurData[0].substr(6)), stod(capteurData[1]), stod(capteurData[2]), it->second->getUserID()));
            }else{

                liste.push_back(Capteur(stoi(capteurData[0].substr(6)), stod(capteurData[1]), stod(capteurData[2]), -1));
            }
        
        }
    }

    static Mesure stringVectorToMesure(vector<string> vector_mesures)
    {

        static vector<Capteur> mesCapteurs = listerCapteurs(); // c'est pour pas relire le fichier à chaque fois qu'on veut convertir une mesure
        logReader logReaderCapteur("./data/sensors.csv", ';');
        tm temps;
        strptime(vector_mesures[0].c_str(), "%Y-%m-%d %H", &temps);
        temps.tm_hour = 0;
        temps.tm_min = 0;
        temps.tm_sec = 0;
        Mesure m(mktime(&temps), stoi(vector_mesures[1].substr(6)), vector_mesures[2], stod(vector_mesures[3]), true);
        vector<string> currentLine = logReaderCapteur.next();
        while (currentLine[0] != vector_mesures[1])
        {
            currentLine = logReaderCapteur.next();
        }
        if (currentLine.empty())
        {
        }
        m.sensor = Capteur(stoi(vector_mesures[1].substr(6)), stod(currentLine[1]), stod(currentLine[2]), 0);
        return m;
    }

    static void printStats(string name, vector<double> stats){

        cout << "\t " << name << endl;
        cout << "Moyenne | Maximum | Minimum | Variance " << endl;
        cout << stats[0] << " | " << stats[1] << " | " << stats[2] << " | " << stats[3] << endl; 

    }
};

#endif // LOGREADER_H
