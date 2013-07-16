#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>

using namespace std;
using namespace std::tr1;

class Settings{
	public:
		//loads the default configuration file
		Settings(void);

		const string & get(const string &);
		void set(const string, const string);
		void fillDefault(void);

		string & operator[](const string &);

		static bool generateFile(void);

		bool saveToFile();

		static const string filename;
	private:
		map<string, string> config;
		map<string, string> initial;
};

#endif
