#include "I_FPScounter.h"
#include <stdio.h>
#include <iostream>

void I_FPScounter::draw(sf::RenderWindow *window){
	tfps++;
	I_Text::draw(window);
	return;
}

void I_FPScounter::update(sf::RenderWindow*){
	tcps++;
	if(count.getElapsedTime().asMilliseconds() >= updateTime){
		//cout << "FPS ticked.\n";
		count.restart();
		fps = tfps*(1000/updateTime);
		//cout << fps << " ";
		cps = tcps*(1000/updateTime);
		//cout << cps << endl;

		tfps = 0;
		tcps = 0;

		char buffer[30];

		sprintf_s(buffer, 30, "FPS %2d\nCPS %2d", fps, cps);
	
		string f(buffer);

		I_Text::setText(f);

		//cout << f << endl;
	}
}