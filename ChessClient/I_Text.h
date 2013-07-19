#pragma once

#include "SFML/Graphics.hpp"
#include "Screen.h"
#include <string>
#include "Font.h"

using namespace std;

class I_Text : public ScreenItem{
	public:
		I_Text(ResourcePack*, string); //

		void setTransform(const sf::Transform&); //this transform is multiplied by the objects's transformation on render

		virtual void draw(sf::RenderWindow*);
		virtual void update(sf::RenderWindow*) {}; //do nothin', it 'be' just text!

		void setText(const string &text) {object.setString(text);};
		void setColor(const sf::Color &color) {object.setColor(color);};
		void setStyle(const sf::Text::Style &style) {object.setStyle(style);};
		void setSize(unsigned int size) {object.setCharacterSize(size);};
		void setPosition(float x, float y) {object.setPosition(x, y);};
		void setPosition(sf::Vector2f v) {object.setPosition(v);};
		void setOrigin(sf::Vector2f);
		void setOrigin(float, float);

	private:
		Font *font;
		string text;
		sf::Transform *transf;
		sf::Text object;
};

