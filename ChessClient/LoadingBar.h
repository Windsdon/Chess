#ifndef LOADINGBAR_H
#define LOADINGBAR_H

#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;
class LoadingBar {
	public:
		LoadingBar(int, int, int, int, int, double);
		//~LoadingBar(void);
		
		const sf::Color borderColor;
		const sf::Color boxColor;

		void setCompletion(double);

	public:
		void draw(sf::RenderWindow *, const sf::RenderStates& states);

	private:


		const int x;
		const int y;
		const int width;
		const int height;
		const int division;
		double c;
		float boxWidth;

		const float spacing;
		const int borderWidth;

		sf::RectangleShape border;
		vector<sf::RectangleShape> boxes;

};

#endif