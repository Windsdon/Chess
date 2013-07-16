
#include "ChessClient.h"
#include <sstream>
#include <iostream>

const string ChessClient::defaultHost = "";
const string ChessClient::title = "CheZ";

using std::stringstream;


ChessClient::ChessClient(void) : host(defaultHost) {

}

//if this is called, when the application loads it will automatically connect to autoHost
ChessClient::ChessClient(string autoHost) : host(autoHost) {

}


ChessClient::~ChessClient(void) {
	//TODO
}

const string ChessClient::getUserID(){
	return "lol";
}

int ChessClient::start(){
	return onStart(); //this is pretty ulgy...
}

int ChessClient::onStart(){
	state = State::NotStarted;

	stringstream wconv(settings.get("width"));
	stringstream hconv(settings.get("height"));
	stringstream aaconv(settings.get("antiAlias"));

	wconv >> width;
	hconv >> height;
	aaconv >> antiAliasLevel;

	sf::VideoMode vm(width, height);
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = antiAliasLevel;

	window = new sf::RenderWindow(vm, title, sf::Style::Close, contextSettings);

	return onLoad();
}

int ChessClient::onLoad(){
	state = State::Loading;

	sf::VertexArray windowBG(sf::Quads, 4);
	windowBG[0].position = sf::Vector2f(0, 0);
	windowBG[1].position = sf::Vector2f(width, 0);
	windowBG[2].position = sf::Vector2f(width, height);
	windowBG[3].position = sf::Vector2f(0, height);

	windowBG[0].color = sf::Color::Color(0, 200, 0, 255); //sf::Color::Color(0x0, 0x8, 0x0, 0xff);
	windowBG[1].color = sf::Color::Color(0, 200, 0, 255); //sf::Color::Color(0x0, 0x8, 0x0, 0xff);
	windowBG[2].color = sf::Color::Color(0, 125, 0, 255); //sf::Color::Color(0x0, 0xa, 0x0, 0xff);
	windowBG[3].color = sf::Color::Color(0, 125, 0, 255); //sf::Color::Color(0x0, 0xa, 0x0, 0xff);

	

	while(window->isOpen()){

		sf::Event e;
		while(window->pollEvent(e)){
			if(e.type == sf::Event::Closed){
				window->close();
			}
		}

		window->clear();
		window->draw(windowBG);
		window->display();
	}

	settings.saveToFile();

	cin.get();

	return 0;
}


