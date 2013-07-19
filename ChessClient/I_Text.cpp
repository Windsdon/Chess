#include "I_Text.h"
#include <iostream>

I_Text::I_Text(ResourcePack* pack, string font): ScreenItem(pack) {
	this->font = static_cast<Font*> (pack->get(font)); //we are sure it's a font!
	object.setFont(*(this->font));
}

void I_Text::setOrigin(sf::Vector2f vec){
	object.setOrigin(vec);
}

void I_Text::setOrigin(float x, float y){
	object.setOrigin(x,y);
}

void I_Text::setTransform(const sf::Transform &transform){
	if(transf != nullptr){
		delete transf;
	}
	transf = new sf::Transform(transform);
}

void I_Text::draw(sf::RenderWindow* window){
	string t = object.getString();
	//cout << "I'm drawing the text! " << t << endl;
	if(transf != nullptr){
		window->draw(object, *transf);
	}else{
		window->draw(object);
	}
}