#include "ResourcePack.h"
#include "Tilemap.h"
#include <iostream>

ResourcePack::ResourcePack(void) {
	loadComplete = false;
	resCount = 0;
}


ResourcePack::~ResourcePack(void) {
	cout << "Deleting resource pack\n";
	return; //borked this up. Figure out later.
	/*for(map<string, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it){
		delete it->second;
	}*/
}

void ResourcePack::add(Resource *res, string id){
	cout << "Resource added to the pack\n";
	resources.insert(pair<string, Resource*>(id, res));
	resCount++;
}

Resource* ResourcePack::get(string id){
	return resources[id];
}

void ResourcePack::load(){
	for(map<string, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it){
		//sf::Thread loader(&Resource::load, it->second); //if this doesn't work, try using new sf::Thread, because it may get out of scope
		//sf::Thread loader(Functor(), it->second);
		//loadingThreads.push_front(&loader); //I don't know if I really need to store these :S
		//cout << "Starting new loading thread\n";
		//loader.launch();
		it->second->load();
	}
}

bool ResourcePack::isLoaded(){
	if(loadComplete){
		return true;
	}
	for(map<string, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it){
		if(it->second->getLoadCompletion() != 1){
			return false;
		}
	}
	loadComplete = true;
	return true;
}

double ResourcePack::getLoadCompletion(){
	if(!resCount){
		return 1;
	}
	double c = 0;
	for(map<string, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it){
		c += it->second->getLoadCompletion()/resCount;
	}
	return c;
}