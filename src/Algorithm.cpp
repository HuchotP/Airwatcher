#include "Algorithm.h"

using namespace std;



void Algorithm::capteursSimilaires(Capteur & capt) {

}

vector<float> Algorithm::moyenne(measurementsReader* mesReader, vector<UtilisateurPrive*> &utilisateurs) {
    float moyenneO3=0;
    float moyenneSO2=0;
    float moyenneNO2=0;
    float moyennePM10=0;
    int recompense = 20;
    unsigned int nbO3 = 0, nbSO2 = 0, nbNO2 = 0, nbPM10 = 0;
    vector<float> moyennes;

    Mesure* mes;
		while ((mes=mesReader->next())!=nullptr) {

      string attribute = mes->attributeID;

      if(attribute.compare("O3")==0){
        moyenneO3 += mes->value;
        ++nbO3;
      }else if(attribute.compare("SO2")==0){
        moyenneSO2 += mes->value;
        ++nbSO2;
      }else if(attribute.compare("NO2")==0){
        moyenneNO2 += mes->value;
        ++nbNO2;
      }else{
        moyennePM10 += mes->value;
        ++nbPM10;
      }

      vector<UtilisateurPrive*>::iterator it;
      int sensorId = mes->sensorID;
      it = find_if(utilisateurs.begin(), utilisateurs.end(), [&sensorId](const UtilisateurPrive* user) {return user->getIdCapteur() == sensorId;});
      if(it!=utilisateurs.end()){

        int userID = (*it)->getUserID();
        if(userID != -1){
            Algorithm::recompenserUtilisateur(utilisateurs, userID, recompense);
        }
      }
		}

    //remettre le curseur au debut du fichier
    mesReader->fichier.clear();
    mesReader->fichier.seekg(0, ios::beg);

    if(nbO3!=0){
      moyennes.push_back(moyenneO3/nbO3);
    }else{
      moyennes.push_back(-1.0);
    }
    if(nbSO2!=0){
      moyennes.push_back(moyenneSO2/nbSO2);
    }else{
      moyennes.push_back(-1.0);
    }
    if(nbNO2!=0){
      moyennes.push_back(moyenneNO2/nbNO2);
    }else{
      moyennes.push_back(-1.0);
    }
    if(nbPM10!=0){
      moyennes.push_back(moyennePM10/nbPM10);
    }else{
      moyennes.push_back(-1.0);
    }

    return moyennes;
}

void Algorithm::identifierFausseDonnee(measurementsReader* mesReader, Mesure& mesureAExaminer, vector<UtilisateurPrive*> &utilisateurs) {
    float facteurIncertitude = 1; //pour 68%
//trouver les mesures proches en tempes et en geographie
    // vector<double> localisationVector;
    // double rayon = 60;
    // vector<int> t_value;
  	// vector<tm> d_value;
    // bool flag_d=false, flag_t=true; //recherches des mesures proches le meme jour
    //
    // localisationVector.push_back(mesureAExaminer.sensor.latitude);
    // localisationVector.push_back(mesureAExaminer.sensor.longitude);
    // t_value.push_back(0);
    // t_value.push_back(0);
    // t_value.push_back(1);
    // t_value.push_back(0);
    //
    // measurementsReader* mesProchesReader = new measurementsReader(string("./data/measurementsTest.csv"), ';', localisationVector, rayon, t_value, flag_d, flag_t, d_value);


    //vector<float> moyenneDesMesures=Algorithm::moyenne(mesProchesReader,utilisateurs);
    vector<float> moyenneDesMesures=Algorithm::moyenne(mesReader,utilisateurs);
    float moy;
    if(mesureAExaminer.attributeID.compare("O3")==0){
      moy = moyenneDesMesures[0];
    }else if(mesureAExaminer.attributeID.compare("SO2")==0){
      moy = moyenneDesMesures[1];
    }else if(mesureAExaminer.attributeID.compare("NO2")==0){
      moy = moyenneDesMesures[2];
    }else{
      moy = moyenneDesMesures[3];
    }

    int n = 0;
    float sum = 0;
    Mesure* mes;

    //while ((mes=mesProchesReader->next())!=nullptr) {
    while ((mes=mesReader->next())!=nullptr) {
        if(mes->attributeID.compare(mesureAExaminer.attributeID)==0){
          sum += pow((mes->value - moy),2);
          ++n;
        }
    }

    float ecartType=sqrt(sum/n);
    float borneInf = moy - ecartType*facteurIncertitude/sqrt(n);
    float borneSup = moy + ecartType*facteurIncertitude/sqrt(n);
    cout << "borneInf : "<<borneInf<<"   |   borneSup : "<<borneSup<<endl;
    if(mesureAExaminer.value<borneInf ||mesureAExaminer.value>borneSup){
        mesureAExaminer.status=false;
        vector<UtilisateurPrive*>::iterator it;
        int sensorId = mesureAExaminer.sensorID;
        it = find_if(utilisateurs.begin(), utilisateurs.end(), [&sensorId](const UtilisateurPrive* user) {return user->getIdCapteur() == sensorId;});
        int userID = (*it)->getUserID();
        utilisateurs[userID]->setFiabilite (utilisateurs[userID]->getFiabilite() - 1) ;
        cout << "Mesure fausse : ";
        mesureAExaminer.AfficherMesure();
    }
}

void Algorithm::impactAirCleaner() {

}

void Algorithm::recompenserUtilisateur(vector<UtilisateurPrive*> &utilisateurs, int userID, int recompense){
    utilisateurs[userID]->setPoints(utilisateurs[userID]->getPoints() + recompense);
}
