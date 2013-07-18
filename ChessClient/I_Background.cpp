#include "I_Background.h"
#include <iostream>

using namespace std;

void I_Background::draw(sf::RenderWindow *window){
	//cout << "Drawing background with type " << ((int) type) << endl;

	sf::Vector2f size = window->getDefaultView().getSize();

	if(type == Type::Gradient){
		if(needsUpdate){
			cout << "Updating Background\n";
			//cin.get();
			needsUpdate = false;
			gradient.setPrimitiveType(sf::Quads);
			gradient.clear();
			gradient.append(sf::Vertex(sf::Vector2f(0, 0          ), gradientColor1));
			gradient.append(sf::Vertex(sf::Vector2f(size.x, 0     ), gradientColor1));
			gradient.append(sf::Vertex(sf::Vector2f(size.x, size.y), gradientColor2));
			gradient.append(sf::Vertex(sf::Vector2f(0, size.y     ), gradientColor2));
		}

		window->draw(gradient);
		return;
	}

	if(type == Type::Plain){
		if(needsUpdate){
			cout << "Updating Background\n";
			//cin.get();
			needsUpdate = false;
			rectangle.setSize(size);
			rectangle.setFillColor(color);
			rectangle.setTexture(NULL);
		}
		window->draw(rectangle);
		return;
	}

	if(type == Type::Texture || type == Type::ColoredTexture){
		if(needsUpdate){
			cout << "Updating Background\n";
			//cin.get();
			needsUpdate = false;
			if(type == Type::Texture){
				sprite.setColor(sf::Color::Transparent);
			}else{
				sprite.setColor(color);
			}
			sprite.setTexture(*texture, true);
			sprite.setScale(size.x/texture->getSize().x, size.y/texture->getSize().y);
		}

		window->draw(sprite);
	}


}