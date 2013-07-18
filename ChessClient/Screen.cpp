#include "Screen.h"

Screen::~Screen(void) {
	//TODO
}

void Screen::addComponent(ScreenItem *item){
	items.push_front(item);
	components++;
}

int Screen::numComponents() const{
	return components;
}

void Screen::draw() const{
	for(list<ScreenItem*>::const_iterator it = items.begin(); it != items.end(); ++it){
		(*it)->draw(window, pack);
	}
}

bool Screen::onUpdate(){
	for(list<ScreenItem*>::const_iterator it = items.begin(); it != items.end(); ++it){
		(*it)->update(window);
	}

	sf::Event e;
	while(window->pollEvent(e)){
		if(e.type == sf::Event::Closed){
			return false;
		}
	}

	return true;
}

void ScreenManager::add(Screen *screen){
	screens.insert(pair<string, Screen*>(screen->getID(), screen));
}

Screen *ScreenManager::get(string id){
	map<string, Screen*>::iterator locate = screens.find(id);

	if(locate == screens.end()){
		throw invalid_argument("No such screen");
		return nullptr;
	}

	return locate->second;
}

Screen *ScreenManager::getActive(){
	for(map<string, Screen*>::iterator it = screens.begin(); it != screens.end(); ++it){
		if(it->second->isActive()){
			return it->second;
		}
	}

	throw exception("There is no active screen");

	return nullptr;
}

void ScreenManager::draw() {
	Screen *ptr = getActive();
	if(ptr != nullptr){
		ptr->draw();
	}
}

void ScreenManager::setActive(string id){
	for(map<string, Screen*>::iterator it = screens.begin(); it != screens.end(); ++it){
		if(it->first == id){
			it->second->setActive(true);
		}else{
			it->second->setActive(false);
		}
	}
}

void ScreenManager::setActive(Screen *screen){
	for(map<string, Screen*>::iterator it = screens.begin(); it != screens.end(); ++it){
		if(it->second == screen){
			it->second->setActive(true);
		}else{
			it->second->setActive(false);
		}
	}
}

bool ScreenManager::update(){
	Screen *ptr = getActive();
	if(ptr != nullptr){
		return ptr->onUpdate();
	}

	return false; //no active screen, end it!
}
