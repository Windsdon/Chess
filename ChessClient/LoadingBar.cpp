#include "LoadingBar.h"
#include <iostream>
#include <math.h>

LoadingBar::LoadingBar(int x, int y, int w = 400, int h = 50, int numBars = 10, double completion = 0):	
	x(x), y(y), width(w), height(h), division(numBars), c(completion), borderWidth(5),
	borderColor(0, 0xdd, 0, 0xff), boxColor(0, 0xdd, 0, 0xff), spacing(2), boxes(numBars){

		border.setOutlineColor(borderColor);
		border.setOutlineThickness(borderWidth);
		border.setPosition(sf::Vector2f(x, y));
		border.setSize(sf::Vector2f(width, height));
		border.setFillColor(sf::Color::Transparent);
		boxWidth = (width - (numBars - 1)*spacing)/numBars;

		for(int i = 0; i < boxes.size(); i++){
			boxes[i].setFillColor(boxColor);
			boxes[i].setSize(sf::Vector2f(boxWidth - borderWidth*2, height - borderWidth*2));
			boxes[i].setPosition(sf::Vector2f(i*(boxWidth + spacing) + x + borderWidth, y + borderWidth));
			//cout << "Added new box\n";
		}
}

void LoadingBar::draw(sf::RenderWindow *window, const sf::RenderStates& states){
	int numDisplay = floor(division*c);

	//cout << "Drawing " << numDisplay << " squares\n";

	//draw the squares
	for(int i = 0; i < numDisplay; i++){
		//cout << "The size is " << boxes[i].getSize().x << ", " << boxes[i].getSize().y << "\n";
		window->draw(boxes[i], states);
	}

	//draw the border
	window->draw(border, states);

	//cout << "Let's draw this shit! The border is (" << border.getSize().x << "," << border.getSize().y << ")\n";
	
}

void LoadingBar::setCompletion(double c){
	this->c = c < 1 ? c : 1;
}
