#pragma once
#include "Screen.h"

#include "SFML/System.hpp";
#include "I_Text.h"

class I_FPScounter : public I_Text {
	public:
		I_FPScounter(ResourcePack* pack, string font, int updateTimeMS): I_Text(pack, font), tfps(0), tcps(0), fps(0), cps(0), updateTime(updateTimeMS) {I_Text::setText("");};

		virtual void draw(sf::RenderWindow*);
		virtual void update(sf::RenderWindow*);

	private:
		sf::Clock count;

		const double updateTime;

		int tfps;
		int tcps;

		int fps;
		int cps;
};

