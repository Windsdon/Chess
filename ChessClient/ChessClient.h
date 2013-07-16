#ifndef CHESSCLIENT_H
#define CHESSCLIENT_H


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <list>
#include <string>
#include "Settings.h"

using namespace std;

class ChessClient {
	public:
		explicit ChessClient(void);
		/*
		* @param The server address.
		*/
		explicit ChessClient(string);
		~ChessClient(void);

		int start(); //initiates the client, creating the window

		static const string getUserID(); //returns a unique ID. DO NOT mistake this for Settings['id']. This one generates a random string, that's all.

	private:
		int onStart(); //creates the window and subsystems
		int onLoad(); //loads the essentials for the interface (such as buttons images)
		//void onLoop(); //returns only when state is State::ExitRequested
		//void onRender(); //render everything, blocks update threads while rendering
		//void onEvent(); //checks for the events every update
		//void onExit(); //destroys all resources, called inside the destructor
		//void exit(); //sets state to ExitRequested, forcing the application to end
		//void forceExit(); //should not be called. Forces the program to end without freeing the resources

		enum State {
			NotStarted, //the default state
			Loading, //loading resources
			Connecting, //connecting to the server
			Running, //inside the sever, doesn't matter if in game or on waiting room
			ExitRequested //tells onLoop() to stop
		};

		State state; //the current state of the application

		string host; //the server to connect to

		Settings settings;

		sf::RenderWindow *window;

		int width;
		int height;
		int antiAliasLevel;

		static const string defaultHost; //the default host

		static const string title;

		
};

#endif