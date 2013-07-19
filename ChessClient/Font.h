#pragma once
#include "SFML/Graphics.hpp"
#include "ResourcePack.h"
#include <string>

using namespace std;

class Font : public sf::Font, public Resource {
	public:
		Font(string); //construct from file
		~Font(void);

		virtual void load();
		virtual double getLoadCompletion();

	private:
		bool loaded;
		//sf::Font font;
		string filename;
};

