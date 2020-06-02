#include <iostream>
#include <string>
#include "Entreprise.h"
#include "Cleaner.h"
#include "logReader.h"
#include "measurementsReader.h"
#include "../lib/util.h"

using namespace std;

Entreprise::Entreprise(int ID, string nom) : Utilisateur(ID) {
    #ifdef MAP 
        cout << "Appel au constructeur de Entreprise." << endl;
    #endif
    this->userID = ID;
    this->name = nom;
}

Entreprise::Entreprise(Entreprise & uneEntreprise) : Utilisateur(uneEntreprise) {
    #ifdef MAP 
        cout << "Appel au constructeur par copie de Entreprise." << endl;
    #endif
    this->name = uneEntreprise.name;
    this->tabCleaner = uneEntreprise.tabCleaner;
    this->userID = uneEntreprise.userID;
}

Entreprise::~Entreprise() {
    #ifdef MAP 
        cout << "Appel au destructeur de Entreprise." << endl;
    #endif
}

void Entreprise::ajoutAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode ajoutAirCleaner() de Entreprise." << endl;
    #endif
    tabCleaner.push_back(c);
}

float Entreprise::mesuresProchesAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode mesuresProchesAirCleaner() de Entreprise." << endl;
    #endif
}
 
float Entreprise::moyenneAirCleaner(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode moyenneAirCleaner() de Entreprise." << endl;
    #endif
}

double Entreprise::etendueZoneTraitee(string cleanerId, measurementsReader & mesReader) {
    #ifdef MAP 
        cout << "Appel a la methode etendueZoneTraitee de Entreprise." << endl;
    #endif
    Mesure * mes;
    cout << "impact" << endl;
    int outliers = 0;
    logReader logReaderCleaner("./data/cleaners.csv", ';');
    vector<string> currentLine;
    currentLine = logReaderCleaner.next();
    while(currentLine[0] != cleanerId) {
        currentLine = logReaderCleaner.next();
        if(currentLine.empty()) {
            cerr << "Cleaner introuvable" << endl;
            return -1;
        }
    }
    double cleanerLatitude = stod(currentLine[1]);
    double cleanerLongitude = stod(currentLine[2]);
    double maxImpact = 0;
    double distanceToSensor;
    tm debutCleaner;
    tm finCleaner;
    strptime(currentLine[4].c_str(),"%d/%m/%Y %H:%M", &debutCleaner);
    strptime(currentLine[5].c_str(),"%d/%m/%Y %H:%M", &finCleaner);

    int count_SO2, count_NO3, count_O3, count_PM;
    double sum_SO2, sum_NO3, sum_O3, sum_PM;

    sum_SO2 = sum_NO3 = sum_O3 = sum_PM = 0;
    count_SO2 = count_NO3 = count_O3 = count_PM = 0;

    double moyenne_SO2_avant, moyenne_NO3_avant, moyenne_O3_avant, moyenne_PM_avant;
    double moyenne_SO2_pendant, moyenne_NO3_pendant, moyenne_O3_pendant, moyenne_PM_pendant;

    while ((mes=mesReader.next())!=nullptr) {
        tm * timeMesure = localtime(&(mes->timeStamp));
        
        if(timeMesure->tm_yday > finCleaner.tm_yday) continue;


        while(timeMesure->tm_yday < debutCleaner.tm_yday) {
            if(mes->attributeID == "SO2") {
                sum_SO2 += mes->value;
                count_SO2++;
            }
            if(mes->attributeID == "NO2") {
                sum_NO3 += mes->value;
                count_NO3++;
            }
            if(mes->attributeID == "O3") {
                sum_O3 += mes->value;
                count_O3++;
            }
            if(mes->attributeID == "PM10") {
                sum_PM += mes->value;
                count_PM++;
            }
            if((mes=mesReader.next())==nullptr) break;
            tm * timeMesure = localtime(&(mes->timeStamp));
        }
        moyenne_SO2_avant = sum_SO2/count_SO2;
        moyenne_NO3_avant = sum_NO3/count_NO3;
        moyenne_O3_avant = sum_O3/count_O3;
        moyenne_PM_avant = sum_PM/count_PM;

        /* cout << "sommes : " << sum_SO2<< " " << sum_NO3<< " " << sum_O3<< " " << sum_PM<< " " << endl;
        cout << "comptes : " << count_SO2<< " " << count_NO3<< " " << count_O3<< " " << count_PM<< " " << endl;
*/
        sum_SO2 = sum_NO3 = sum_O3 = sum_PM = 0;
        count_SO2 = count_NO3 = count_O3 = count_PM = 0;

        while(timeMesure->tm_yday < finCleaner.tm_yday) {
            if(mes->attributeID == "SO2") {
                sum_SO2 += mes->value;
                count_SO2++;
            }
            if(mes->attributeID == "NO2") {
                sum_NO3 += mes->value;
                count_NO3++;
            }
            if(mes->attributeID == "O3") {
                sum_O3 += mes->value;
                count_O3++;
            }
            if(mes->attributeID == "PM10") {
                sum_PM += mes->value;
                count_PM++;
            }
            if((mes=mesReader.next())==nullptr) break;
            tm * timeMesure = localtime(&(mes->timeStamp));
        }

        moyenne_SO2_pendant = sum_SO2/count_SO2;
        moyenne_NO3_pendant = sum_NO3/count_NO3;
        moyenne_O3_pendant = sum_O3/count_O3;
        moyenne_PM_pendant = sum_PM/count_PM;

        /* cout << "sommes : " << sum_SO2<< " " << sum_NO3<< " " << sum_O3<< " " << sum_PM<< " " << endl;
        cout << "comptes : " << count_SO2<< " " << count_NO3<< " " << count_O3<< " " << count_PM<< " " << endl;
*/
        sum_SO2 = sum_NO3 = sum_O3 = sum_PM = 0;
        count_SO2 = count_NO3 = count_O3 = count_PM = 0;

        bool impactCleaner = moyenne_NO3_pendant/moyenne_NO3_avant < 0.34 || moyenne_SO2_pendant/moyenne_SO2_avant < 0.34 || moyenne_O3_pendant/moyenne_O3_avant < 0.34 || moyenne_PM_pendant/moyenne_PM_avant < 0.34;
        distanceToSensor = util::distance(cleanerLatitude, cleanerLongitude, mes->sensor.latitude, mes->sensor.longitude);

        if(impactCleaner) {
            
            cout << distanceToSensor << " " << mes->sensorID << endl;
            cout << moyenne_NO3_pendant/moyenne_NO3_avant << " " << moyenne_SO2_pendant/moyenne_SO2_avant << " " << moyenne_O3_pendant/moyenne_O3_avant << " " << moyenne_PM_pendant/moyenne_PM_avant << " " << endl;
            
            if(maxImpact < distanceToSensor) {
                maxImpact = distanceToSensor;
                cout << "seuil augmenté" << endl;
            }

        } else {
            if(maxImpact > distanceToSensor) {
                maxImpact = 0;
                outliers++;
                cout << "Conflit d'impacts " << distanceToSensor << " " << mes->sensorID << endl;
                
                cout << moyenne_NO3_pendant/moyenne_NO3_avant << " " << moyenne_SO2_pendant/moyenne_SO2_avant << " " << moyenne_O3_pendant/moyenne_O3_avant << " " << moyenne_PM_pendant/moyenne_PM_avant << " " << endl;
                break;
            }
        }
        // boucle pour passer au capteur suivant 
        int currentSensor = mes->sensorID;
        while(mes->sensorID == currentSensor) {
            if((mes=mesReader.next())==nullptr) break;
        }

    }

    if(maxImpact != 0) {
        cout << "Votre cleaner a un rayon d'impact estimé à : " << maxImpact << " kilomètres." << endl;
    } else {
        cout << "Nous n'avons pas pu démontrer l'efficacité de votre cleaner." << endl;
    }
    return maxImpact;
}

float Entreprise::niveauAmelioration(Cleaner & c) {
    #ifdef MAP 
        cout << "Appel a la methode niveauAmelioration() de Entreprise." << endl;
    #endif
}