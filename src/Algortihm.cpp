#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm(vector<UtilisateurPrive> &utilisateurs) {
    vector<UtilisateurPrive> utilisateurs = utilisateurs ; 
}

void Algorithm::capteursSimilaires(Capteur & capt) {

}

float Algorithm::moyenne(measurementsReader reader) {    
    float moyenne=0;
    int recompense = 20;
    unsigned int n = 0;

    vector<string> current;
    current = reader.next();
    while (!current.empty()) {
        current = reader.next();
        Mesure mesure = util::stringVectorToMesure(current);

        moyenne += mesure.value;
        if(mesure.sensorID.userID != -1){
            int userID = mesure.sensorID.userID;
            Algorithm::recompenserUtilisateur(userID, recompense);
        }
        ++n;
    }
    moyenne /= n;
    return moyenne;

}

void Algorithm::identifierFausseDonnee(measurementsReader reader, mesureAExaminer) {
    float facteurIncertitude = 1;
    float moyenneDesMesures=Algorithm::moyenne(reader);
    int n = reader.acceptedMesures.size();
    float sum = 0;
    for(unsigned int i = 0; i < reader.acceptedMesures.size(); ++i)
    {
        sum += (reader.acceptedMesures[i].value - moyenneDesMesures);
    }
    float ecartType=sqrt((1.0/n)*pow(sum,2));
    float borneInf = moyenneDesMesures - ecartType*facteurIncertitude/sqrt(n);
    float borneSup = moyenneDesMesures + ecartType*facteurIncertitude/sqrt(n);

//les mesures examinées font partie de celles qui contribuent à la moyenne/ecart type ?

    if(mesureAExaminer.value<borneInf ||mesureAExaminer.value>borneSup){
         mesureAExaminer.status=true;
         int userID = mesureAExaminer.sensorID.userID;
        utilisateurs[userID].fiabilité -- ;
    }    
}

void Algorithm::impactAirCleaner() {

}

void Algorithm::recompenserUtilisateur(int userID, int recompense){
    utilisateurs[userID]+=recompense;
}