#include "Algorithm.h"
#include <limits>
using namespace std;



void Algorithm::capteursSimilaires(Capteur & capt) {

}

// ordre : return[0] = statsO3, return[1] = statsSO2, return[2] = statsNO2, return[3] = statsPM10
// ordre : stats[0] =moyenne, stats[1] = max, stats[2] = min, stats[3]=variance
vector<vector<double>> Algorithm::statistiques(measurementsReader* mesReader, map<int,UtilisateurPrive*>& sensorToUser) {

    double maxO3=0;
    double maxSO2=0;
    double maxNO2=0;
    double maxPM10=0;

    double sumO3=0;
    double sumSO2=0;
    double sumNO2=0;
    double sumPM10=0;

    double sumCarreO3=0;
    double sumCarreSO2=0;
    double sumCarreNO2=0;
    double sumCarrePM10=0;

    double ecartTypeO3=0;
    double ecartTypeSO2=0;
    double ecartTypeNO2=0;
    double ecartTypePM10=0;

    double minO3=numeric_limits<double>::max();
    double minSO2=numeric_limits<double>::max();
    double minNO2=numeric_limits<double>::max();
    double minPM10=numeric_limits<double>::max();
    int recompense = 20;
    unsigned int nbO3 = 0, nbSO2 = 0, nbNO2 = 0, nbPM10 = 0;
    vector<double> statsO3;
    vector<double> statsSO2;
    vector<double> statsNO2;
    vector<double> statsPM10;

    vector<vector<double>> stats;

    Mesure* mes;
		while ((mes=mesReader->next())!=nullptr) {

      string attribute = mes->attributeID;

      if(attribute.compare("O3")==0){
        sumO3 += mes->value;
        sumCarreO3 += (mes->value * mes->value);
        if(mes->value > maxO3) {
          maxO3 = mes->value;
        }
        if (mes-> value < minO3) {
          minO3 = mes->value;
        }
        ++nbO3;
      }else if(attribute.compare("SO2")==0){
        sumSO2 += mes->value;
        sumCarreSO2 += (mes->value * mes->value);
        if(mes->value > maxSO2) {
          maxSO2 = mes->value;
        }
        if (mes-> value < minSO2) {
          minSO2 = mes->value;
        }
        
        ++nbSO2;
      }else if(attribute.compare("NO2")==0){
        sumNO2 += mes->value;
        sumCarreNO2 += (mes->value * mes->value);
        if(mes->value > maxNO2) {
          maxNO2 = mes->value;
        }
        if (mes-> value < minNO2) {
          minNO2 = mes->value;
        }
        ++nbNO2;
      }else{
        sumPM10 += mes->value;
        sumCarrePM10 += (mes->value * mes->value);
        if(mes->value > maxPM10) {
          maxPM10 = mes->value;
        }
        if (mes-> value < minPM10) {
          minPM10 = mes->value;
        }
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
      statsO3.push_back(sumO3/nbO3);
      statsO3.push_back(maxO3);
      statsO3.push_back(minO3);
      statsO3.push_back(sumCarreO3/nbO3 - (sumO3/nbO3)*(sumO3/nbO3));
    }else{
      statsO3.push_back(-1.0);
      statsO3.push_back(-1.0);
      statsO3.push_back(-1.0);
      statsO3.push_back(-1.0);
    }
    if(nbSO2!=0){
      statsSO2.push_back(sumSO2/nbSO2);
      statsSO2.push_back(maxSO2);
      statsSO2.push_back(minSO2);
      statsSO2.push_back(sumCarreSO2/nbSO2 - (sumSO2/nbSO2)*(sumSO2/nbSO2));
    }else{
      statsSO2.push_back(-1.0);
      statsSO2.push_back(-1.0);
      statsSO2.push_back(-1.0);
      statsSO2.push_back(-1.0);
    }
    if(nbNO2!=0){
      statsNO2.push_back(sumNO2/nbNO2);
      statsNO2.push_back(maxNO2);
      statsNO2.push_back(minNO2);
      statsNO2.push_back(sumCarreNO2/nbNO2 - (sumNO2/nbNO2)*(sumNO2/nbNO2));
    }else{
      statsNO2.push_back(-1.0);
      statsNO2.push_back(-1.0);
      statsNO2.push_back(-1.0);
      statsNO2.push_back(-1.0);
    }
    if(nbPM10!=0){
      statsPM10.push_back(sumPM10/nbPM10);
      statsPM10.push_back(maxPM10);
      statsPM10.push_back(minPM10);
      statsPM10.push_back(sumCarrePM10/nbPM10 - (sumPM10/nbPM10)*(sumPM10/nbPM10));
    }else{
      statsPM10.push_back(-1.0);
      statsPM10.push_back(-1.0);
      statsPM10.push_back(-1.0);
      statsPM10.push_back(-1.0);
    }

    stats.push_back(statsO3);
    stats.push_back(statsSO2);
    stats.push_back(statsNO2);
    stats.push_back(statsPM10);
    return stats;
}

void Algorithm::identifierFausseDonnee(Mesure& mesureAExaminer, map<int,UtilisateurPrive*>& sensorToUser) {
    float facteurIncertitude = 2; //pour 95%
    unsigned int nMin = 4; //nombre de valeurs minimal à considérer que l'estimation soit correcte
//trouver les mesures proches en tempes et en geographie
    vector<double> localisationVector;
    double rayon = 80; // ~entre 2 capteurs en diagonale
    vector<int> t_value;
  	vector<tm> d_value;
    bool flag_d=true, flag_t=false;

    localisationVector.push_back(mesureAExaminer.sensor.latitude);
    localisationVector.push_back(mesureAExaminer.sensor.longitude);

    //recherches des mesures proches le meme jour
    tm* time;
    time=localtime(&(mesureAExaminer.timeStamp));
		d_value.push_back(*time);
		d_value.push_back(*time);

    measurementsReader* mesProchesReader = new measurementsReader(string("./data/measurements.csv"), ';', localisationVector, rayon, t_value, flag_d, flag_t, d_value);

    vector<vector<double>> stats = Algorithm::statistiques(mesProchesReader,sensorToUser);
    vector<double> moyenneDesMesures;
    
    float moy;
    if(mesureAExaminer.attributeID.compare("O3")==0){
      moy = stats[0][0];
    }else if(mesureAExaminer.attributeID.compare("SO2")==0){
      moy = stats[1][0];
    }else if(mesureAExaminer.attributeID.compare("NO2")==0){
      moy = stats[2][0];
    }else{
      moy = stats[3][0];
    }

    int n = 0;
    float sum = 0;
    Mesure* mes;

    while ((mes=mesProchesReader->next())!=nullptr) {
        if((mes->attributeID.compare(mesureAExaminer.attributeID)==0)&&(mes->sensorID!=mesureAExaminer.sensorID)){
          sum += pow((mes->value - moy),2);
          ++n;
          //mes->AfficherMesure();
        }
    }

    if(n>nMin){
      float ecartType=sqrt(sum/n);
      float borneInf = moy - ecartType*facteurIncertitude/sqrt(n);
      float borneSup = moy + ecartType*facteurIncertitude/sqrt(n);
      if(mesureAExaminer.value<borneInf ||mesureAExaminer.value>borneSup){
        cout << "borneInf : "<<borneInf<<"   |   borneSup : "<<borneSup<<endl;
        mesureAExaminer.status=false;
        int sensorId = mesureAExaminer.sensorID;

        map<int,UtilisateurPrive*>::iterator it;
		    it = sensorToUser.find(sensorId);
		    if(it!=sensorToUser.end()){
		  	  it->second->setFiabilite(it->second->getFiabilite() - 1);
          cout<<"Note de fiabilite de l'utilisateur "<<it->second->getUserID()<<" diminuee"<<endl;
		    }
        cout << "Mesure potentiellement fausse : ";
        mesureAExaminer.AfficherMesure();
      }
      //cout<<endl;
    }else{
      //cout<<"Mesures insuffisantes pour déterminer si la mesure est fausse"<<endl;
    }
    delete mesProchesReader;

}

void Algorithm::impactAirCleaner() {

}

void Algorithm::recompenserUtilisateur(UtilisateurPrive* utilisateur, int recompense){
    utilisateur->setPoints(utilisateur->getPoints() + recompense);
}
