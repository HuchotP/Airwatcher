#include "Algorithm.h"

#include "UtilisateurPrive.h"
using namespace std;



void Algorithm::capteursSimilaires(Capteur & capt) {

}

vector<float> Algorithm::moyenne(measurementsReader* mesReader, map<int,UtilisateurPrive*> sensorToUser) {
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

      
      int sensorId = mes->sensorID;
	  

      map<int,UtilisateurPrive*>::iterator it;
		it = sensorToUser.find(sensorId);
		if(it!=sensorToUser.end()){

        Algorithm::recompenserUtilisateur(it->second, recompense);
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
        

void Algorithm::identifierFausseDonnee(Mesure& mesureAExaminer, map<int,UtilisateurPrive*> sensorToUser) {
    float facteurIncertitude = 2; //pour 95%
    unsigned int nMin = 30; //nombre de valeurs minimal à considérer que l'estimation soit correcte
//trouver les mesures proches en tempes et en geographie
    vector<double> localisationVector;
    double rayon = 60;
    vector<int> t_value;
  	vector<tm> d_value;
    bool flag_d=true, flag_t=false;
    
    localisationVector.push_back(mesureAExaminer.sensor.latitude);
    localisationVector.push_back(mesureAExaminer.sensor.longitude);

    //recherches des mesures proches le meme jour
    tm* time;
    time=localtime(&(mesureAExaminer.timeStamp));
		d_value.push_back(*time);
    time->tm_mday++;
		d_value.push_back(*time);

    measurementsReader* mesProchesReader = new measurementsReader(string("./data/measurementsTest.csv"), ';', localisationVector, rayon, t_value, flag_d, flag_t, d_value);

    vector<float> moyenneDesMesures=Algorithm::moyenne(mesProchesReader,sensorToUser);
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

    while ((mes=mesProchesReader->next())!=nullptr) {
        if(mes->attributeID.compare(mesureAExaminer.attributeID)==0){
          sum += pow((mes->value - moy),2);
          ++n;
        }
    }

    if(n>nMin){
      float ecartType=sqrt(sum/n);
      float borneInf = moy - ecartType*facteurIncertitude/sqrt(n);
      float borneSup = moy + ecartType*facteurIncertitude/sqrt(n);
      //cout << "borneInf : "<<borneInf<<"   |   borneSup : "<<borneSup<<endl;
      if(mesureAExaminer.value<borneInf ||mesureAExaminer.value>borneSup){
        mesureAExaminer.status=false;
 
        int sensorId = mesureAExaminer.sensorID;

        map<int,UtilisateurPrive*>::iterator it;
		it = sensorToUser.find(sensorId);
		if(it!=sensorToUser.end()){
			it->second->setFiabilite(it->second->getFiabilite() - 1);
		}
		

        cout << "Mesure fausse : ";
        mesureAExaminer.AfficherMesure();
      }
    }else{
      cout<<"Mesures insuffisantes pour déterminer si la mesure est fausse"<<endl;
    }

}

void Algorithm::impactAirCleaner() {

}

void Algorithm::recompenserUtilisateur(UtilisateurPrive* utilisateur, int recompense){

    utilisateur->setPoints(utilisateur->getPoints() + recompense);
}
