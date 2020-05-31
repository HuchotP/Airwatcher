<<<<<<< HEAD
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <time.h>
#include <ctime>
#include <limits>
#include "../lib/optionparser.h"
#include "logReader.h"
#include "./measurementsReader.h"
#include "../lib/util.h"



enum optionIndex
{
	UNKNOWN,
	LOCALISATION,
	ETENDUE_T,
	ETENDUE_D,
	RAYON,
	HELP,
	QUALITE,
	SIMILAIRE,
	IMPACT,
	FALSIFIE
};
enum optionType
{
	MODE,
	PARAMETRE,
	OTHER
};

option::ArgStatus IsCleanerId(const option::Option& option, bool msg)
{
	if (!option.arg)
	{
		cerr << "Le mode -i doit être suivi d'un id de cleaner de la forme \"Cleaner\" + un entier " << endl;
		cerr << option.arg << endl;
		return option::ARG_ILLEGAL;
	}
	string arg(option.arg);
	if (arg.substr(0, 7) == "Cleaner")
	{
		return option::ARG_OK;
	}
	else
	{
		cerr << "Le mode -i doit être suivi d'un id de cleaner de la forme \"Cleaner\" + un entier " << endl;
		cerr << option.arg << endl;
		return option::ARG_ILLEGAL;
	}
}

option::ArgStatus IsLocalisation(const option::Option& option, bool msg)
{

	if (!option.arg[0])
	{
		cerr << "La localisation doit être suivie de \"latitude,longitude\"." << endl;
		return option::ARG_ILLEGAL;
	}

	string arg(option.arg);
	size_t pos = arg.find(",");
	if (pos == string::npos)
	{
		cerr << "La localisation doit être en format \"nombre réel,nombre réel\"" << endl;
		return option::ARG_ILLEGAL;
	}

	string lat = arg.substr(0, pos);
	string longitude = arg.substr(pos + 1);

	if (lat.empty() || longitude.empty())
	{
		cerr << "La localisation doit être en format \"nombre réel,nombre réel\"" << endl;
		return option::ARG_ILLEGAL;
	}

	try
	{
		double lat_d = stod(lat);
		double long_d = stod(longitude);

		if (lat_d > 90 || lat_d < -90 || long_d > 180 || long_d < -180)
		{
			cerr << "La latitude doit être comprise entre -90° et 90°. La longitude doit être comprise entre -180° et 180° " << endl;
			return option::ARG_ILLEGAL;
		}
		return option::ARG_OK;
	}
	catch (exception e)
	{
		cerr << "La localisation doit être en format \"nombre réel,nombre réel\"" << endl;
		return option::ARG_ILLEGAL;
	}
}

option::ArgStatus IsEtendueT(const option::Option& option, bool msg)
{
	if (!option.arg)
	{
		cerr << "Etendue temporelle invalide. Le format demandé est : \"...a...m...j...h\"" << endl;
		exit(0);
		return option::ARG_ILLEGAL;
	}
	string arg(option.arg);
	size_t pos = arg.find(" ");
	if (pos != string::npos)
	{
		cerr << "L'étendue temporelle ne doit pas contenir d'espace" << endl;
		exit(0);
		return option::ARG_ILLEGAL;
	}
	bool a, m, j, h;
	a = m = j = h = false; // si un caractère est rencontré on met à jour son booléen
	string buffer("");
	for (string::iterator it = arg.begin(); it != arg.end(); ++it)
	{
		if (isdigit(*it))
		{
			continue;
		}
		else if (*it == 'a' && !a && !(m || j || h))
		{
			a = true;
			continue;
		}
		else if (*it == 'm' && !m && !(j || h))
		{
			m = true;
			continue;
		}
		else if (*it == 'j' && !j && !h)
		{
			j = true;
			continue;
		}
		else if (*it == 'h' && !h && it == arg.end() - 1)
		{
			h = true;
			break;
		}
		else
		{
			break;
		}
	}
	if (!(a || m || j || h))
	{
		cerr << "Etendue temporelle invalide. Le format demandé est : \"...a...m...j...h\"" << endl;
		exit(0);
		return option::ARG_ILLEGAL;
	}
	else
	{
		return option::ARG_OK;
	}
}

option::ArgStatus IsEtendueD(const option::Option& option, bool msg)
{
	string arg(option.arg);
	size_t pos = arg.find("-");
	if (pos == string::npos)
	{
		cerr << "L'étendue datée doit être de la forme \"JJ/MM/AAAA-JJ/MM/AAAA\"" << endl;
		return option::ARG_ILLEGAL;
	}

	string first_date = arg.substr(0, pos);
	string second_date = arg.substr(pos + 1, string::npos);
	tm time_one;
	tm time_two;
	strptime(first_date.c_str(), "%d/%m/%Y", &time_one);
	strptime(second_date.c_str(), "%d/%m/%Y", &time_two);

	if (time_one.tm_year == NULL ||
		time_one.tm_mon == NULL ||
		time_one.tm_mday == NULL ||
		time_two.tm_year == NULL ||
		time_two.tm_mon == NULL ||
		time_two.tm_mday == NULL)
	{

		cerr << "L'étendue datée doit être de la forme \"JJ/MM/AAAA-JJ/MM/AAAA\"" << endl;
		return option::ARG_ILLEGAL;
	}

	return option::ARG_OK;


}

option::ArgStatus IsRayon(const option::Option& option, bool msg) {
	string arg(option.arg);
	char* end = nullptr;
	double val = strtod(arg.c_str(), &end);
	 if (end != arg.c_str() && *end == '\0' && val != HUGE_VAL) {
		 return option::ARG_OK;
	 }
	 else {
		 exit(0);
		 return option::ARG_ILLEGAL;
	 }
}

const option::Descriptor usage[] =
{
	{UNKNOWN, OTHER, "", "", option::Arg::None, "USAGE: Airwatcher [mode] [options]\n\n"
												"Les données doivent se trouver dans le dossier ./data"},
	{LOCALISATION, PARAMETRE, "l", "localisation", IsLocalisation, "  --localisation, -l \tChoix de la localisation pour l'analyse"},
	{ETENDUE_T, PARAMETRE, "t", "etendue_t", IsEtendueT, "  --etendue_t, -t \tChoix de l'étendue temporelle"},
	{ETENDUE_D, PARAMETRE, "d", "date", IsEtendueD, "  --date, -d \tChoix de l'étendue datée. Format : JJ/MM/AAAA-JJ/MM/AAAA"},
	{RAYON, PARAMETRE, "r", "rayon", IsRayon, "  --rayon, -r \tPermet de préciser le rayon dans lequel les données doivent êtres examinées. Doit être suivie de l'option -l."},
	{HELP, OTHER, "h", "help", option::Arg::None, "  --help, -h  \tAfficher l'aide."},
	{QUALITE, MODE, "q", "qualite", option::Arg::None, "  --qualite, -q  \tAffiche un indice de la qualité de l'air. Doit être suivie de l'option -l."},
	{SIMILAIRE, MODE, "s", "similaire", option::Arg::None, "  --similaire, -s \tMode de recherche des comportements similaires. Doit être suivie de l'option -l."},
	{IMPACT, MODE, "i", "impact", IsCleanerId, "  --impact, -i \tMode d'étude d'impact d'un AirCleaner (suivi de l'id du cleaner)"},
	{FALSIFIE, MODE, "f", "falsifie", option::Arg::None, "  --falsifie, -f \tRecherche de données abberantes parmi les données utilisateur."},
	{0, 0, 0, 0, 0, 0} };

int main(int argc, char* argv[])
{
	measurementsReader* mesReader;
	argc -= (argc > 0);
	argv += (argc > 0); // skip program name argv[0] if present
	option::Stats stats(usage, argc, argv);
	vector<option::Option> options(stats.options_max);
	vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

	double rayonEffectif = -1;
	string rayon, etendueT, etendueD;
	bool flag_l = false, flag_t = false, flag_d = false;
	vector<double> localisationVector;
	vector<int> t_value;
	vector<tm> d_value;

	// Première possibilité : données brutes
	if (options[LOCALISATION]) {
		string localisation = options[LOCALISATION].arg;
		size_t pos = localisation.find(",");
		string lat = localisation.substr(0, pos);
		string longitude = localisation.substr(pos + 1);

		char* end;
		double latitudeDouble = strtod(lat.c_str(), &end);
		localisationVector.push_back(latitudeDouble);
		char* end2;
		double longitudeDouble = strtod(longitude.c_str(), &end);
		localisationVector.push_back(longitudeDouble);

		rayonEffectif = 190;
		if (options[RAYON]) {
			rayon = options[RAYON].arg;
			char* end3;
			double rayonEffectif = strtod(rayon.c_str(),&end3);
			cout << rayonEffectif << endl;
			flag_l = true;
		}

	}
	if (options[ETENDUE_T]) {
		cout << "etendue temporelle " << endl;
		etendueT = options[ETENDUE_T].arg;
		flag_t = true;
		int lastDigit;
		t_value.push_back(0);
		t_value.push_back(0);
		t_value.push_back(0);
		t_value.push_back(0);
		bool a, m, j, h;
		a = m = j = h = false;
		int lastNumber = 0;
		for (string::iterator it = etendueT.begin(); it != etendueT.end(); ++it)
		{
			lastDigit = *it;
			
			if (isdigit(lastDigit))
			{
				lastNumber = lastDigit-48;
				continue;
			}
			else if (*it == 'a' && !a && !(m || j || h))
			{
				t_value[0]= lastNumber;
				cout << "annee : " << t_value[0] << endl;
				a = true;
				continue;
			}
			else if (*it == 'm' && !m && !(j || h))
			{
				t_value[1] = lastNumber;
				cout << "mois : " << t_value[1] << endl;
				m = true;
				continue;
			}
			else if (*it == 'j' && !j && !h)
			{
				t_value[2] = lastNumber;
				cout << "jour : " << t_value[2] << endl;
				j = true;
				continue;
			}
			else if (*it == 'h' && !h && it == etendueT.end() - 1)
			{
				t_value[3] = lastNumber;
				cout << "heure : " << t_value[3] << endl;
				h = true;
				break;
			}
			else
			{
				break;
			}
		}

		//init measurementsReader avec recherche tempo
	}else if (options[ETENDUE_D]) {

		etendueD = options[ETENDUE_D].arg;
		flag_d = true;
		size_t pos = etendueD.find("-");
		string first_date = etendueD.substr(0, pos);
		string second_date = etendueD.substr(pos + 1, string::npos);
		tm time_one;
		tm time_two;
		strptime(first_date.c_str(), "%d/%m/%Y", &time_one);
		strptime(second_date.c_str(), "%d/%m/%Y", &time_two);
		d_value.push_back(time_one);
		d_value.push_back(time_two);

		//init measurementsReader avec recherche date
	}

	mesReader = new measurementsReader(string("./data/measurements.csv"), ';', localisationVector, rayonEffectif, t_value, flag_d, flag_t, d_value);
	Mesure* mes;

	// si l'utilisateur cherche à obtenir des informations sur l'impact d'un AirCleaner
	if(options[IMPACT]) {
		cout << "impact" << endl;
		rayonEffectif = numeric_limits<double>::max(); // on met le rayon d'analyse au maximum pour obtenir toutes les données
		logReader logReaderCleaner("./data/cleaners.csv", ';');
		vector<string> currentLine;
		currentLine = logReaderCleaner.next();
		while(currentLine[0] != options[IMPACT].arg) {
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

		while ((mes=mesReader->next())!=nullptr) {
			tm * timeMesure = localtime(&(mes->timeStamp));
			
			if(timeMesure->tm_yday > finCleaner.tm_yday) continue;


			int count_SO2, count_NO3, count_O3, count_PM;
			double sum_SO2, sum_NO3, sum_O3, sum_PM;
			double moyenne_SO2_avant, moyenne_NO3_avant, moyenne_O3_avant, moyenne_PM_avant;
			while(timeMesure->tm_yday < debutCleaner.tm_yday) {
				if(mes->attributeID == "SO2") {
					sum_SO2 += mes->value;
					count_SO2++;
				}
				if(mes->attributeID == "NO3") {
					sum_NO3 += mes->value;
					count_NO3++;
				}
				if(mes->attributeID == "O3") {
					sum_O3 += mes->value;
					count_O3++;
				}
				if(mes->attributeID == "PM") {
					sum_PM += mes->value;
					count_PM++;
				}
				if((mes=mesReader->next())==nullptr) break;
				tm * timeMesure = localtime(&(mes->timeStamp));
			}
			moyenne_SO2_avant = sum_SO2/count_SO2;
			moyenne_NO3_avant = sum_NO3/count_NO3;
			moyenne_O3_avant = sum_O3/count_O3;
			moyenne_PM_avant = sum_PM/count_PM;

			sum_SO2 = sum_NO3 = sum_O3 = sum_PM = 0;
			count_SO2 = count_NO3 = count_O3 = count_PM = 0;
			double moyenne_SO2_pendant, moyenne_NO3_pendant, moyenne_O3_pendant, moyenne_PM_pendant;

			while(timeMesure->tm_yday < finCleaner.tm_yday) {
				if(mes->attributeID == "SO2") {
					sum_SO2 += mes->value;
					count_SO2++;
				}
				if(mes->attributeID == "NO3") {
					sum_NO3 += mes->value;
					count_NO3++;
				}
				if(mes->attributeID == "O3") {
					sum_O3 += mes->value;
					count_O3++;
				}
				if(mes->attributeID == "PM") {
					sum_PM += mes->value;
					count_PM++;
				}
				if((mes=mesReader->next())==nullptr) break;
				tm * timeMesure = localtime(&(mes->timeStamp));
			}

			moyenne_SO2_pendant = sum_SO2/count_SO2;
			moyenne_NO3_pendant = sum_NO3/count_NO3;
			moyenne_O3_pendant = sum_O3/count_O3;
			moyenne_PM_pendant = sum_PM/count_PM;

			bool impactCleaner = moyenne_NO3_pendant/moyenne_NO3_avant < 0.15 || moyenne_SO2_pendant/moyenne_SO2_avant < 0.15 || moyenne_O3_pendant/moyenne_O3_avant < 0.15 || moyenne_PM_pendant/moyenne_PM_avant < 0.15;
			distanceToSensor = util::distance(cleanerLatitude, cleanerLongitude, mes->sensor.latitude, mes->sensor.longitude);

			if(impactCleaner) {
				
				if(maxImpact < distanceToSensor) {
					maxImpact = util::distance(cleanerLatitude, cleanerLongitude, mes->sensor.latitude, mes->sensor.longitude);
					cout << maxImpact << " " << mes->sensorID << endl;
				}

			} else {
				if(maxImpact > distanceToSensor) {
					maxImpact = 0;
					cout << "Conflit d'impacts " << distanceToSensor << " " << mes->sensorID << endl;
					//return 0;
				}
			}
		}

	}

	while ((mes=mesReader->next())!=nullptr) {
		mes->AfficherMesure();
	}
}
=======
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <time.h>
#include <ctime>
#include "../lib/optionparser.h"
#include "logReader.h"
#include "./measurementsReader.h"
#include "../lib/util.h"
#include "usersReader.h"



enum optionIndex
{
	UNKNOWN,
	LOCALISATION,
	ETENDUE_T,
	ETENDUE_D,
	RAYON,
	HELP,
	QUALITE,
	SIMILAIRE,
	IMPACT,
	FALSIFIE
};
enum optionType
{
	MODE,
	PARAMETRE,
	OTHER
};

option::ArgStatus IsCleanerId(const option::Option& option, bool msg)
{
	if (!option.arg)
	{
		cerr << "Le mode -i doit être suivi d'un id de cleaner de la forme \"Cleaner\" + un entier " << endl;
		cerr << option.arg << endl;
		return option::ARG_ILLEGAL;
	}
	string arg(option.arg);
	if (arg.substr(0, 7) == "Cleaner")
	{
		return option::ARG_OK;
	}
	else
	{
		cerr << "Le mode -i doit être suivi d'un id de cleaner de la forme \"Cleaner\" + un entier " << endl;
		cerr << option.arg << endl;
		return option::ARG_ILLEGAL;
	}
}

option::ArgStatus IsLocalisation(const option::Option& option, bool msg)
{

	if (!option.arg[0])
	{
		cerr << "La localisation doit être suivie de \"latitude,longitude\"." << endl;
		return option::ARG_ILLEGAL;
	}

	string arg(option.arg);
	size_t pos = arg.find(",");
	if (pos == string::npos)
	{
		cerr << "La localisation doit être en format \"nombre réel,nombre réel\"" << endl;
		return option::ARG_ILLEGAL;
	}

	string lat = arg.substr(0, pos);
	string longitude = arg.substr(pos + 1);

	if (lat.empty() || longitude.empty())
	{
		cerr << "La localisation doit être en format \"nombre réel,nombre réel\"" << endl;
		return option::ARG_ILLEGAL;
	}

	try
	{
		double lat_d = stod(lat);
		double long_d = stod(longitude);

		if (lat_d > 90 || lat_d < -90 || long_d > 180 || long_d < -180)
		{
			cerr << "La latitude doit être comprise entre -90° et 90°. La longitude doit être comprise entre -180° et 180° " << endl;
			return option::ARG_ILLEGAL;
		}
		return option::ARG_OK;
	}
	catch (exception e)
	{
		cerr << "La localisation doit être en format \"nombre réel,nombre réel\"" << endl;
		return option::ARG_ILLEGAL;
	}
}

option::ArgStatus IsEtendueT(const option::Option& option, bool msg)
{
	if (!option.arg)
	{
		cerr << "Etendue temporelle invalide. Le format demandé est : \"...a...m...j...h\"" << endl;
		exit(0);
		return option::ARG_ILLEGAL;
	}
	string arg(option.arg);
	size_t pos = arg.find(" ");
	if (pos != string::npos)
	{
		cerr << "L'étendue temporelle ne doit pas contenir d'espace" << endl;
		exit(0);
		return option::ARG_ILLEGAL;
	}
	bool a, m, j, h;
	a = m = j = h = false; // si un caractère est rencontré on met à jour son booléen
	string buffer("");
	for (string::iterator it = arg.begin(); it != arg.end(); ++it)
	{
		if (isdigit(*it))
		{
			continue;
		}
		else if (*it == 'a' && !a && !(m || j || h))
		{
			a = true;
			continue;
		}
		else if (*it == 'm' && !m && !(j || h))
		{
			m = true;
			continue;
		}
		else if (*it == 'j' && !j && !h)
		{
			j = true;
			continue;
		}
		else if (*it == 'h' && !h && it == arg.end() - 1)
		{
			h = true;
			break;
		}
		else
		{
			break;
		}
	}
	if (!(a || m || j || h))
	{
		cerr << "Etendue temporelle invalide. Le format demandé est : \"...a...m...j...h\"" << endl;
		exit(0);
		return option::ARG_ILLEGAL;
	}
	else
	{
		return option::ARG_OK;
	}
}

option::ArgStatus IsEtendueD(const option::Option& option, bool msg)
{
	string arg(option.arg);
	size_t pos = arg.find("-");
	if (pos == string::npos)
	{
		cerr << "L'étendue datée doit être de la forme \"JJ/MM/AAAA-JJ/MM/AAAA\"" << endl;
		return option::ARG_ILLEGAL;
	}

	string first_date = arg.substr(0, pos);
	string second_date = arg.substr(pos + 1, string::npos);
	tm time_one;
	tm time_two;
	strptime(first_date.c_str(), "%d/%m/%Y", &time_one);
	strptime(second_date.c_str(), "%d/%m/%Y", &time_two);

	if (time_one.tm_year == NULL ||
		time_one.tm_mon == NULL ||
		time_one.tm_mday == NULL ||
		time_two.tm_year == NULL ||
		time_two.tm_mon == NULL ||
		time_two.tm_mday == NULL)
	{

		cerr << "L'étendue datée doit être de la forme \"JJ/MM/AAAA-JJ/MM/AAAA\"" << endl;
		return option::ARG_ILLEGAL;
	}

	return option::ARG_OK;


}

option::ArgStatus IsRayon(const option::Option& option, bool msg) {
	string arg(option.arg);
	char* end = nullptr;
	double val = strtod(arg.c_str(), &end);
	 if (end != arg.c_str() && *end == '\0' && val != HUGE_VAL) {
		 return option::ARG_OK;
	 }
	 else {
		 exit(0);
		 return option::ARG_ILLEGAL;
	 }
}

const option::Descriptor usage[] =
{
	{UNKNOWN, OTHER, "", "", option::Arg::None, "USAGE: Airwatcher [mode] [options]\n\n"
												"Les données doivent se trouver dans le dossier ./data"},
	{LOCALISATION, PARAMETRE, "l", "localisation", IsLocalisation, "  --localisation, -l \tChoix de la localisation pour l'analyse"},
	{ETENDUE_T, PARAMETRE, "t", "etendue_t", IsEtendueT, "  --etendue_t, -t \tChoix de l'étendue temporelle"},
	{ETENDUE_D, PARAMETRE, "d", "date", IsEtendueD, "  --date, -d \tChoix de l'étendue datée. Format : JJ/MM/AAAA-JJ/MM/AAAA"},
	{RAYON, PARAMETRE, "r", "rayon", IsRayon, "  --rayon, -r \tPermet de préciser le rayon dans lequel les données doivent êtres examinées. Doit être suivie de l'option -l."},
	{HELP, OTHER, "h", "help", option::Arg::None, "  --help, -h  \tAfficher l'aide."},
	{QUALITE, MODE, "q", "qualite", option::Arg::None, "  --qualite, -q  \tAffiche un indice de la qualité de l'air. Doit être suivie de l'option -l."},
	{SIMILAIRE, MODE, "s", "similaire", option::Arg::None, "  --similaire, -s \tMode de recherche des comportements similaires. Doit être suivie de l'option -l."},
	{IMPACT, MODE, "i", "impact", IsCleanerId, "  --impact, -i \tMode d'étude d'impact d'un AirCleaner (suivi de l'id du cleaner)"},
	{FALSIFIE, MODE, "f", "falsifie", option::Arg::None, "  --falsifie, -f \tRecherche de données abberantes parmi les données utilisateur."},
	{0, 0, 0, 0, 0, 0} };

int main(int argc, char* argv[])
{
	measurementsReader* mesReader;
	argc -= (argc > 0);
	argv += (argc > 0); // skip program name argv[0] if present
	option::Stats stats(usage, argc, argv);
	vector<option::Option> options(stats.options_max);
	vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

	double rayonEffectif = -1;
	string rayon, etendueT, etendueD;
	bool flag_l = false, flag_t = false, flag_d = false;
	vector<double> localisationVector;
	vector<int> t_value;
	vector<tm> d_value;

	// Première possibilité : données brutes
	if (options[LOCALISATION]) {
		string localisation = options[LOCALISATION].arg;
		size_t pos = localisation.find(",");
		string lat = localisation.substr(0, pos);
		string longitude = localisation.substr(pos + 1);

		char* end;
		double latitudeDouble = strtod(lat.c_str(), &end);
		localisationVector.push_back(latitudeDouble);
		char* end2;
		double longitudeDouble = strtod(longitude.c_str(), &end);
		localisationVector.push_back(longitudeDouble);

		rayonEffectif = 60;
		if (options[RAYON]) {
			rayon = options[RAYON].arg;
			char* end3;
			double rayonEffectif = strtod(rayon.c_str(),&end3);
			cout << rayonEffectif << endl;
			flag_l = true;
		}

	}
	if (options[ETENDUE_T]) {
		cout << "etendue temporelle " << endl;
		etendueT = options[ETENDUE_T].arg;
		flag_t = true;
		int lastDigit;
		t_value.push_back(0);
		t_value.push_back(0);
		t_value.push_back(0);
		t_value.push_back(0);
		bool a, m, j, h;
		a = m = j = h = false;
		int lastNumber = 0;
		for (string::iterator it = etendueT.begin(); it != etendueT.end(); ++it)
		{
			lastDigit = *it;

			if (isdigit(lastDigit))
			{
				lastNumber = lastDigit-48;
				continue;
			}
			else if (*it == 'a' && !a && !(m || j || h))
			{
				t_value[0]= lastNumber;
				cout << "annee : " << t_value[0] << endl;
				a = true;
				continue;
			}
			else if (*it == 'm' && !m && !(j || h))
			{
				t_value[1] = lastNumber;
				cout << "mois : " << t_value[1] << endl;
				m = true;
				continue;
			}
			else if (*it == 'j' && !j && !h)
			{
				t_value[2] = lastNumber;
				cout << "jour : " << t_value[2] << endl;
				j = true;
				continue;
			}
			else if (*it == 'h' && !h && it == etendueT.end() - 1)
			{
				t_value[3] = lastNumber;
				cout << "heure : " << t_value[3] << endl;
				h = true;
				break;
			}
			else
			{
				break;
			}
		}

		//init measurementsReader avec recherche tempo
	}else if (options[ETENDUE_D]) {

		etendueD = options[ETENDUE_D].arg;
		flag_d = true;
		size_t pos = etendueD.find("-");
		string first_date = etendueD.substr(0, pos);
		string second_date = etendueD.substr(pos + 1, string::npos);
		tm time_one;
		tm time_two;
		strptime(first_date.c_str(), "%d/%m/%Y", &time_one);
		strptime(second_date.c_str(), "%d/%m/%Y", &time_two);
		d_value.push_back(time_one);
		d_value.push_back(time_two);

		//init measurementsReader avec recherche date
	}

		mesReader = new measurementsReader(string("./data/measurements.csv"), ';', localisationVector, rayonEffectif, t_value, flag_d, flag_t, d_value);
		Mesure* mes;
		while ((mes=mesReader->next())!=nullptr) {
			mes->AfficherMesure();
		}

		//usersReader uReader = new usersReader(string("./data/users.csv"), ';');

}
>>>>>>> origin/1st-side-branch
