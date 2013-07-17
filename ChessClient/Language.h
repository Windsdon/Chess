#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>
#include <vector>

using namespace std;


class Language {
	public:
		Language(string, string);

		enum Dicio {
			LOADING_TEXT
		};

		const string get(Dicio);

	private:
		static const string reference[];
		vector<string> lang; //contains the sentences
		static const int size;
};

#endif

