#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "ResourcePack.h"

using namespace std;

class Tilemap : public Resource {
	public:
		Tilemap(int xnum, int ynum, int w, int h, string file) : countX(xnum), countY(ynum), width(w), height(h), map(xnum*ynum), filename(file) {}; //parms are countX, countY, width, height
		~Tilemap(void);

		virtual void load(void); //loads the file passed to the constructor

		sf::Texture *get(int, int) const; //gets the texture

		double completed;

		virtual double getLoadCompletion();

	private:
		const int countX;
		const int countY;
		const int width;
		const int height;
		const string filename;

		vector<sf::Texture*> map;

		Tilemap(Tilemap&); //pointers! let's not allow copy

};

#endif

