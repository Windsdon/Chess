/// I_* are screen items
/// This is a background. It can be of a plain color, a 2 color gradient or a texture

#pragma once

#include "SFML/Graphics.hpp"
#include "Screen.h"
#include "ResourcePack.h"
#include <iostream>

using namespace std;
	
class I_Background : public ScreenItem {
	public:
		I_Background(ResourcePack* pack): needsUpdate(true), type(Type::Plain), ScreenItem(pack) {color = sf::Color::White;};

		void setGradientColor(sf::Color a, sf::Color b) {gradientColor1 = a; gradientColor2 = b;}; //sets the gradient color
		void setColor(sf::Color c) {color = sf::Color::White;}; //sets the plain color... color
		void setTexture(sf::Texture *texture) {this->texture = texture;}; //sets the texture

		virtual void draw(sf::RenderWindow*);
		virtual void update(sf::RenderWindow*) {}; //do nothing on update, as it's just a background

		enum Type {
			Plain,
			Gradient,
			Texture,
			ColoredTexture
		};

		void setType(Type type) {this->type = type; needsUpdate = true;}; //sets the type
		const Type getType() const {return type;};

	private:
		Type type;
		bool needsUpdate;
		sf::VertexArray gradient;
		sf::RectangleShape rectangle;

		sf::Color gradientColor1;
		sf::Color gradientColor2;

		sf::Color color;

		sf::Texture *texture;
		sf::Sprite sprite;
};

