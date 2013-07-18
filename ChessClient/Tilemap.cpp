#include "Tilemap.h"
#include <iostream>

Tilemap::~Tilemap(void) {
	cout << "Deleting tilemap textures" << endl;
	for(int i = 0; i < countX*countY; i++){
		delete map[i];
	}
}

void Tilemap::load(){
	sf::Image img;

	cout << "Loading tilemap " << filename << endl;
	if(!img.loadFromFile(filename)){
		cout << "Failed";
		cin.get();
		exit(1);
	}
	cout << "Success\n";

	for(int i = 0; i < countY; i++){
		for(int j = 0; j < countX; j++){
			int c = i*countX + j;
			cout << "Creating texture " << j << ", " << i << endl;
			completed = c / ((double) countX * countY);
			//cout << "Completed " << completed << endl;
			int xpos = j*width, ypos = i*height;
			map[c] = new sf::Texture();
			map[c]->loadFromImage(img, sf::IntRect(xpos, ypos, width, height));
			map[c]->setRepeated(true);
			map[c]->setSmooth(true);
		}
	}

	completed = 1;
	cout << "Finished loading.\n";
}

double  Tilemap::getLoadCompletion(){
	return completed;
}

sf::Texture *Tilemap::get(int x, int y) const{
	return map[y*countX + x];
}