#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <time.h>
#include <ctime>
#include "../lib/optionparser.h"
#include "./logReader.h"
#include "../lib/util.h"

using namespace std;

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

	// Première possibilité : données brutes
	if (options[LOCALISATION]) {
		string localisation = options[LOCALISATION].arg;
		cout << localisation << endl;
		string rayon, etendueT, etendueD;
		bool flag_r = false, flag_t = false, flag_d = false;

		if (options[RAYON]) {
			cout << "afficher r" << endl;
			rayon = options[RAYON].arg;
			flag_r = true;
		}
	}
	if (options[ETENDUE_T]) {
		etendueT = options[ETENDUE_T].arg;
		flag_t = true;
	}
	if (options[ETENDUE_D]) {
		etendueD = options[ETENDUE_D].arg;
		flag_d = true;
		size_t pos = etendueD.find("-");
		string first_date = etendueD.substr(0, pos);
		string second_date = etendueD.substr(pos + 1, string::npos);
		tm time_one;
		tm time_two;
		strptime(first_date.c_str(), "%d/%m/%Y", &time_one);
		strptime(second_date.c_str(), "%d/%m/%Y", &time_two);
	}



}