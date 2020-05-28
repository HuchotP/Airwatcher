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
		return option::ARG_ILLEGAL;
	}
	string arg(option.arg);
	size_t pos = arg.find(" ");
	if (pos != string::npos)
	{
		cerr << "L'étendue temporelle ne doit pas contenir d'espace" << endl;
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

const option::Descriptor usage[] =
{
	{UNKNOWN, OTHER, "", "", option::Arg::None, "USAGE: Airwatcher [mode] [options]\n\n"
												"Les données doivent se trouver dans le dossier ./data"},
	{LOCALISATION, PARAMETRE, "l", "localisation", IsLocalisation, "  --localisation, -l \tChoix de la localisation pour l'analyse"},
	{ETENDUE_T, PARAMETRE, "t", "etendue_t", IsEtendueT, "  --etendue_t, -t \tChoix de l'étendue temporelle"},
	{ETENDUE_D, PARAMETRE, "d", "date", IsEtendueD, "  --date, -d \tChoix de l'étendue datée. Format : JJ/MM/AAAA-JJ/MM/AAAA"},
	{RAYON, PARAMETRE, "r", "rayon", option::Arg::None, "  --rayon, -r \tPermet de préciser le rayon dans lequel les données doivent êtres examinées. Doit être suivie de l'option -l."},
	{HELP, OTHER, "h", "help", option::Arg::None, "  --help, -h  \tAfficher l'aide."},
	{QUALITE, MODE, "q", "qualite", option::Arg::None, "  --qualite, -q  \tAffiche un indice de la qualité de l'air. Doit être suivie de l'option -l."},
	{SIMILAIRE, MODE, "s", "similaire", option::Arg::None, "  --similaire, -s \tMode de recherche des comportements similaires. Doit être suivie de l'option -l."},
	{IMPACT, MODE, "i", "impact", IsCleanerId, "  --impact, -i \tMode d'étude d'impact d'un AirCleaner (suivi de l'id du cleaner)"},
	{FALSIFIE, MODE, "f", "falsifie", option::Arg::None, "  --falsifie, -f \tRecherche de données abberantes parmi les données utilisateur."},
	{0, 0, 0, 0, 0, 0} };

int main(int argc, char* argv[])
{

	argc -= (argc > 0);
	argv += (argc > 0); // skip program name argv[0] if present
	option::Stats stats(usage, argc, argv);
	vector<option::Option> options(stats.options_max);
	vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);
	double rayonEffectif;
	string rayon, etendueT, etendueD;
	bool flag_r = false, flag_t = false, flag_d = false;
	vector<double> localisation;
	vector<int> t_value;
	vector<tm> d_value;

	// Première possibilité : données brutes
	if (options[LOCALISATION]) {
		string localisation = options[LOCALISATION].arg;
		cout << localisation << endl;

		if (options[RAYON]) {
			cout << "afficher r" << endl;
			rayon = options[RAYON].arg;
			double rayonEffectif = stoi(rayon);
			flag_r = true;
		}

	}
	if (options[ETENDUE_T]) {
		etendueT = options[ETENDUE_T].arg;
		flag_t = true;
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
		//init measurementsReader avec recherche date
	}
	measurementsReader mesReader;
	if (!(flag_d)&&(!flag_r)&&(!flag_t)){
		//init sans rien
		mesReader(string("./data/measurements.csv"),';',localisation,rayonEffectif,t_value,flag_d,flat_t,d_value);
		(string nomFichier, char subdelim, vector<double> localisation, double r_value, vector<int> & t_value, bool flag_d, bool flag_t, vector<tm> d_value)
	}
	if (flag_t) {
		mesReader(string("./data/measurements.csv"), ';', localisation, rayonEffectif, t_value, flag_d, flat_t, d_value);
	}
	else if (flag_d) {
		
		mesReader(string("./data/measurements.csv"), ';', localisation, rayonEffectif, t_value, flag_d, flat_t, d_value);
	}


	/*
	logReader log("./data/sensors.csv", ';');
	vector<string> result;
	do {
		result = log.next();
		for (int i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		
		cout << endl;
	} while (!result.empty());
	*/
	vector<double> localisation;
	vector<int> t_value;
	vector<tm> d_value;

	string date_string("04/05/2019-25/05/2019");

	size_t pos = date_string.find("-");
	string first_date = date_string.substr(0, pos);
	string second_date = date_string.substr(pos + 1, string::npos);
	tm time_one;
	tm time_two;
	strptime(first_date.c_str(), "%d/%m/%Y", &time_one);
	strptime(second_date.c_str(), "%d/%m/%Y", &time_two);


	d_value.push_back(time_one);
	d_value.push_back(time_two);
	
	int annee = 1;
	int mois = 0;
	int jour = 10;
	int heure = 0;
	vector<int> tempoEtendue;
		tempoEtendue.push_back(annee);
		tempoEtendue.push_back(mois);
		tempoEtendue.push_back(jour);
		tempoEtendue.push_back(heure);

		measurementsReader mesReader2(string("./data/measurements.csv"), ';', localisation, -1, tempoEtendue, true, false, d_value);

		/*vector<string> result2;
		do {
			result2 = mesReader2.next();
			for (int i = 0; i < result2.size(); i++) {
				cout << result2[i] << " ";
			}

			cout << endl;
		} while (!result2.empty());*/

		double x = 45.6;
		double y = 2.5;
		vector<double> localisation2;
		localisation2.push_back(x);
		localisation2.push_back(y);

		measurementsReader mesReader3(string("./data/measurements.csv"), ';', localisation2, 70, tempoEtendue, false, false, d_value);

		vector<string> result3;
		do {
			result3 = mesReader3.next();
			for (int i = 0; i < result3.size(); i++) {
				cout << result3[i] << " ";
			}

			cout << endl;
		} while (!result3.empty());

}