
#include "ChessClient.h"
#include <sstream>
#include <iostream>
#include "LoadingBar.h"
#include "Helpers.h"

const string ChessClient::defaultHost = "";
const string ChessClient::title = "CheZ";

using std::stringstream;


ChessClient::ChessClient(void) : host(defaultHost) {
}

//if this is called, when the application loads it will automatically connect to autoHost
ChessClient::ChessClient(string autoHost) : host(autoHost) {
	
}


ChessClient::~ChessClient(void) {
	//settings.saveToFile();
	delete lang;
	delete defaultMap;
}

const string ChessClient::getUserID(){
	string str = Helpers::getRandom(USER_ID_SIZE, Helpers::RAND_LOWER | Helpers::RAND_UPPER | Helpers::RAND_NUM);
	cout << "Generated user id: " << str << endl;
	return str;
}

int ChessClient::start(){
	return onStart(); //this is pretty ulgy...
}

int ChessClient::onStart(){
	state = State::NotStarted;

	stringstream wconv(settings.get("width"));
	stringstream hconv(settings.get("height"));
	stringstream aaconv(settings.get("antiAlias"));
	stringstream frconv(settings.get("framerate"));

	wconv >> width;
	hconv >> height;
	aaconv >> antiAliasLevel;
	frconv >> framerate;

	sf::VideoMode vm(width, height);
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = antiAliasLevel;

	window = new sf::RenderWindow(vm, title, (settings.get("fullscreen") == "true") ? sf::Style::Fullscreen : sf::Style::Close, contextSettings);

	if(settings.get("framerate") == "vsync"){
		window->setVerticalSyncEnabled(true);
	}else{
		window->setFramerateLimit(framerate);
	}

	lang = new Language("language.lang", settings.get("lang"));

	return onLoad();
}

int ChessClient::onLoad(){
	state = State::Loading;

	sf::VertexArray windowBG(sf::Quads, 4);
	windowBG[0].position = sf::Vector2f(0, 0);
	windowBG[1].position = sf::Vector2f(width, 0);
	windowBG[2].position = sf::Vector2f(width, height);
	windowBG[3].position = sf::Vector2f(0, height);

	windowBG[0].color = sf::Color::Color(0, 200, 0, 255); //sf::Color::Color(0x0, 0x88, 0x0, 0xff);
	windowBG[1].color = sf::Color::Color(0, 200, 0, 255); //sf::Color::Color(0x0, 0x88, 0x0, 0xff);
	windowBG[2].color = sf::Color::Color(0, 125, 0, 255); //sf::Color::Color(0x0, 0x88, 0x0, 0xff);
	windowBG[3].color = sf::Color::Color(0, 125, 0, 255); //sf::Color::Color(0x0, 0x88, 0x0, 0xff);

	int barWidth = width/2;
	int barHeight = 50;

	LoadingBar loadingBar((width - barWidth)/2,  (height - barHeight)/2, barWidth, barHeight, 10, 0);
	
	//sf::Thread loaderThread();
	sf::Font loadingFont;
	if(!loadingFont.loadFromFile("ARLRDBD.TTF")){
		cout << "Failed to load font ARLRDBD.TTF.";
		cin.get();
		return 1;
	}
	sf::Text loadingText(lang->get(Language::Dicio::LOADING_TEXT), loadingFont, 30);

	sf::FloatRect bounds = loadingText.getGlobalBounds();
	
	cout << "Coords are (" << bounds.top << "," << bounds.left << "," << bounds.width << "," << bounds.height << ")\n";

	loadingText.setPosition((width - bounds.width)/2, ((height - barHeight)/2 - 2*bounds.height));

	cout << "Creating tilemap\n";

	defaultMap = new Tilemap(texCountX, texCountY, texWidth, texHeight, "res/tilemap.png");

	resources.add(defaultMap, "tilemap");

	sf::Thread loadTextures(&Tilemap::load, defaultMap);
	loadTextures.launch();
	
	//resources.load(); //TODO!

	sf::Sprite horse;
	horse.setColor(sf::Color::Green);

	while(window->isOpen()){

		sf::Event e;
		while(window->pollEvent(e)){
			if(e.type == sf::Event::Closed){
				window->close();
			}
		}


		window->clear();
		window->draw(windowBG);
		if(defaultMap->completed < 1){
			loadingBar.draw(window, sf::RenderStates::Default);
			loadingBar.setCompletion(resources.getLoadCompletion());
			window->draw(loadingText);
		}else{
			horse.setTexture(*defaultMap->get(4,0));
			window->draw(horse);
		}
		window->display();
	}

	settings.saveToFile();

	return 0;
}


