#include "Settings.h"
#include "ChessClient.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <regex>

const string Settings::filename = "user.settings";

//warning! this does NOT clear the file!
bool Settings::generateFile(){
	ifstream reader(filename);

	if(!reader.is_open()){
		ofstream outputFile(filename);
		outputFile << "# Chess config file\n";
	}else{
		cout << "Could not generate output: File exists\n";
	}

	return true;

}

Settings::Settings(void){

	cout << "Loading settings \n";

	Settings::generateFile();

	ifstream reader(filename);

	if(!reader.is_open()){
		throw invalid_argument("Config file doesn't exist");
	}

	regex emptyLine(" *");
	regex commentLine(" *#+.*");
	regex validLine("([A-Za-z0-9_-]+)=([^=]*)");

	for(string line; getline(reader, line);){
		cmatch result;

		if(regex_match(line, emptyLine) || regex_match(line, commentLine) || !regex_match(line.c_str(), result, validLine)){
			cout << "Skipped invalid/empty/comment line\n";
			continue;
		}

		cout << result[1] << " - " << result[2] << "\n";

		if(config.find(result[1]) == config.end()){
			config.insert(pair<string, string>(result[1], result[2]));
		}
	}

	fillDefault(); //now that we loaded, we set what was not present
}

//sets to default what is not already set
void Settings::fillDefault(){
	cout << "Loading default configuration\n";
	initial.insert(pair<string, string>("userID", ChessClient::getUserID())); //if there is no ID, this will automatically fill it
	initial.insert(pair<string, string>("width", "1280"));
	initial.insert(pair<string, string>("height", "720"));
	initial.insert(pair<string, string>("antiAlias", "2"));
	initial.insert(pair<string, string>("fullscreen", "false"));
	initial.insert(pair<string, string>("framerate", "60"));
	initial.insert(pair<string, string>("lang", "EN"));

	for(map<string, string>::iterator it = initial.begin(); it != initial.end(); ++it){
		if(config.find(it->first) == config.end()){
			cout << "Default key not found. Loading from default.\n";
			config.insert(pair<string, string>(it->first, it->second));
		}else{
			cout << "Default key found. Skipping\n";
		}
	}
}

bool Settings::saveToFile(){
	if(remove(filename.c_str())){
		cout << "Failed to delete config file\n";
		cin.get();
	}

	Settings::generateFile();

	ofstream outputFile(filename);

	outputFile << "# Chess config file\n";

	for(map<string, string>::iterator it = config.begin(); it != config.end(); ++it){
		cout << "Writing line for " << it->first << " with value " << it->second << endl;
		outputFile << it->first << "=" << it->second << endl;
	}

	return true; //should add check to see if it worked later
}

const string & Settings::get(const string & key){
	cout << "Requested key " << key << "\n";

	if(config.find(key) == config.end()){
		cout << "Could not find the key '" << key << "'\n";
		cin.get();
		exit(1);
	}else{
		cout << "the key was found\n";
	}

	try{
		return config.find(key)->second;
	}catch(exception &e){
		cout << "Fatal exception";
	}
}

string & Settings::operator[](const string & key){
	cout << "Requested key " << key << "\n";
	return config[key];
}