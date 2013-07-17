#include "Language.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std::tr1;

const string Language::reference[] = {
	"LOADING_TEXT"
};

const int Language::size = 1;

Language::Language(string file, string lang): lang(size) {
	regex languageIdentifier("\\[(.*),(.*)\\]");
	//regex languageIdentifier("^\\[([a-zA-Z_]+),([^\\]]+)]$");
	regex commentLine("^ *#+.*$");
	regex validLine("^([A-Za-z_]+) (.*)$");

	ifstream reader(file);

	if(!reader.is_open()){
		cout << "\n\n**********************\nLanguage file doesn't exist\n**********************\n";
		cin.get();
		exit(1); //yep, fatal failure
	}

	bool languageFound = false;

	for(string line; getline(reader, line);){
		cmatch result;

		if(languageFound){
			if(regex_match(line, languageIdentifier)){
				break;
			}
			if(!regex_match(line, commentLine) && regex_match(line.c_str(), result, validLine)){
				cout << "Parsing line\n";
				int i;
				for(i = 0; i < size; i++){
					if(reference[i] == result[1]){
						cout << "Found match. Inserting at " << i << "\n";
						this->lang[i] = result[2];
						//lang.insert(i, result[2]);
						break;
					}
				}

				if(i == size){
					cout << "Could not find match (invalid reference). " << result[1] << endl;
				}
			}else{
				cout << "Skipped comment or invalid line\n";
			}
		}else{
			if(regex_match(line.c_str(), result, languageIdentifier)){
				cout << "Found language " << result[2] << "\n";

				if(result[1] == lang){
					cout << "Language selected\n";
					languageFound = true;
				}

			}
		}
	}

	if(!languageFound){
		cout << "\n\n**********************\nInvalid language\n**********************\n";
		cin.get();
		exit(1); //yep, fatal failure
	}
}

const string Language::get(Language::Dicio t){
	try{
		cout << "Trying to get string " << (int) t << endl;
		return lang[(int) t];
	}catch(out_of_range &e){
		cout << "Failed to open string\n";
	}
}