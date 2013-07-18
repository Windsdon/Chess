#ifndef SCREEN_H
#define SCREEN_H

#include "SFML/Graphics.hpp"
#include <string>
#include <map>
#include <list>
#include "ResourcePack.h"


class ScreenItem {
	public:
		virtual void draw(sf::RenderWindow*, ResourcePack*) const = 0;
		virtual void setVisible(bool) = 0;
		virtual bool isVisible() const = 0;
		virtual void update(sf::RenderWindow*);
};

using namespace std;

class Screen {
	public:
		Screen(sf::RenderWindow *window, ResourcePack *pack, string id): active(false), window(window), components(0), pack(pack), id(id) {};
		~Screen(void); //destroys all of it's contents

		void addComponent(ScreenItem*);
		int numComponents() const;

		virtual void draw() const;

		void setActive(bool active) {this->active = active;}; //don't use this directly if you are using a ScreenManager!
		bool isActive(void) const {return active;};

		virtual bool onUpdate(); //this default function updates every item. If it returns false, the program should terminate.

		const string &getID() const {return id;};

	protected:
		bool active; //if it's being rendered or not
		sf::RenderWindow *window;
		int components;

		ResourcePack *pack;

		list<ScreenItem*> items;

		const string id; //the ID of this window
};

class ScreenManager {
	public:
		ScreenManager(sf::RenderWindow *window, ResourcePack* pack): window(window), pack(pack) {};

		//void setResourcePack(); //not used, set in the constructor
		const ResourcePack* getResourcePack() const {return pack;};

		void add(Screen*); //adds a new screen
		Screen *get(string); //gets screen by id
		Screen *getActive(); //returns the first active (and possibly only) window
		void draw(); //draws the currently active window
		void setActive(Screen*); //get by the screen
		void setActive(string); //get by the identifier
		bool update(); //updates the active screen and return it's onUpdate(). False means the program should end

		Screen* create(); //returns a new, default screen

	private:
		sf::RenderWindow *window;
		ResourcePack *pack;
		map<string, Screen*> screens;

		ScreenManager(ScreenManager&); //can't copy!
};

#endif