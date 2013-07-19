#include "Font.h"
#include <iostream>


Font::Font(string file): filename(file), loaded(false) {
}


Font::~Font(void) {
	//TODO :D
	//maybe this isn't necessary, as the font is deleted if this gets out of scope or deleted
}

void Font::load(){
	loaded = false;

	cout << "Loading font " << filename << endl;

	if(!loadFromFile(filename)){
		cout << "Failed to load font " << filename << endl;
		return;
	}else{
		cout << "Font loaded.\n";
	}

	loaded = true;
}

double Font::getLoadCompletion(){
	if(loaded){
		return 1;
	}else{
		return 0;
	}
}
