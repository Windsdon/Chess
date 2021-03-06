
#include "ChessClient.h"
#include <sstream>
#include <iostream>
#include "LoadingBar.h"
#include "Helpers.h"
#include "I_Background.h"
#include "I_FPScounter.h"
#include "Font.h"

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

	timePerTick = 1.0/ticksPerSecond;

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

	LoadingBar loadingBar((width - barWidth)/2,  (height - barHeight)/2, barWidth, barHeight, 20, 0);

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
	Font *font = new Font("ARLRDBD.TTF");
	Font *fpsfont = new Font("res/erbos_draco_1st_open_nbp.ttf");

	resources.add(defaultMap, "tilemap");
	resources.add(font, "font");
	resources.add(fpsfont, "fpsfont");

	//sf::Thread loadTextures(&Tilemap::load, defaultMap);
	//loadTextures.launch();

	sf::Thread loadResources(&ResourcePack::load, &resources); //TODO - Add each loading in a different thread
	loadResources.launch();

	//resources.load(); //TODO

	while(state == State::Loading && window->isOpen()){

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
			//load complete! let's loop!
			state = State::Running;
			/*sf::Text k("Testando", *(static_cast<Font*>((resources.get("fpsfont")))), 30);
			k.setColor(sf::Color::Blue);
			k.setPosition(0, 0);
			window->draw(k);*/
		}
		window->display();
	}

	if(state == State::Running){
		//we create the screen manager
		manager = new ScreenManager(window, &resources);

		//and add the screens to it
		//should probably add this to the loading bar :/
		cout << "Creating screens\n";

		Screen *testScreen = new Screen(window, &resources, "Test");

		I_Background *bg = new I_Background(&resources);
		I_FPScounter *fpscounter = new I_FPScounter(&resources, "fpsfont", 1000);

		fpscounter->setPosition(0,0);
		fpscounter->setColor(sf::Color::Yellow);
		fpscounter->setSize(20);
		fpscounter->setVisible(true);

		bg->setType(I_Background::Type::Gradient);
		bg->setVisible(true);
		bg->setGradientColor(sf::Color::Black, sf::Color::White);

		testScreen->addComponent(bg);
		testScreen ->addComponent(fpscounter);

		manager->add(testScreen);
		manager->setActive(testScreen);

		//start the rendering thread
		window->setActive(false);
		sf::Thread *rendering = new sf::Thread(&ChessClient::render, this);
		rendering->launch();
	}

	while(state == State::Running){
		//onRender();
		onLoop();
	}

	settings.saveToFile();

	delete window;

	return 0;
}

void ChessClient::onLoop(){
	//cout << "Game loop\n";
	sf::Event e;
	tickClock.restart();
	while(window->pollEvent(e)){
		//cout << "Event";
		if(e.type == sf::Event::Closed){
			cout << "*** Exit requested\n";
			state = State::ExitRequested;
		}
	}

	readMutex.lock();
	if(!manager->update()){
		cout << "Ending\n";
		state = State::ExitRequested;
	}
	readMutex.unlock();

	double dk = tickClock.getElapsedTime().asSeconds();
	double k = timePerTick - dk;
	if(k < 0){
		cout << "Can't keep up at 20cps!\n";
	}else{
		sf::sleep(sf::seconds(k));
	}
}

void ChessClient::onRender(){
	window->clear();

	readMutex.lock();
	manager->draw();
	readMutex.unlock();

	window->display();
}

void ChessClient::render(){
	//activate the window on this thread
	cout << "*** Render thread started\n";
	window->setActive(true);
	while(state == State::Running){
		onRender();
	}
}