#ifndef RESOURCEPACK_H
#define RESOURCEPACK_H

#include <string>
#include <map>
#include <list>
#include "SFML/System.hpp"

using namespace std;

class Resource {
	public:
		virtual void load() = 0;
		virtual double getLoadCompletion() = 0;
};

class ResourcePack{
	public:
		ResourcePack(void);
		~ResourcePack(void); //calling this destroys every Loadable!

		void add(Resource *, string);
		Resource* get(string);

		void load(); //creates a thread for each Loadable and returns imediately

		bool isLoaded();

		double getLoadCompletion();

		struct Functor {
			void operator()(Resource* arg){
				arg->load();
			}
		};

	private:
		map<string, Resource*> resources;
		list<sf::Thread> loadingThreads;
		ResourcePack(ResourcePack&); //let's not allow copy :P
		bool loadComplete;
		int resCount;


};

#endif

