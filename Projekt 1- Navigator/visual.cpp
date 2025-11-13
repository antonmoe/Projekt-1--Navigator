#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <math.h>
#include "head.h"


using namespace std;


int visualize(){

	// Visualisierung
	// 1) Init
	if (SDL_Init(SDL_INIT_VIDEO)) {
		cout << "Window initialization is successfull.\n";
	}
	else {
		cout << SDL_GetError();
		SDL_Quit();
		return -1;
	}

	// 2) create window

	SDL_Window* window = nullptr;
	window = SDL_CreateWindow("SDL3 Start", 1900, 1000,
		SDL_WINDOW_VULKAN | SDL_WINDOW_HIGH_PIXEL_DENSITY);
	if (window == nullptr) {
		cout << "ERROR creating window\n";
		SDL_Quit();
		return -1;
	}
	else cout << "Window created successfully.\n";

	// 3 Write to surface directly
	 // You may not combine this with 3D or the rendering API on this window.


	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	if (renderer == nullptr) {
		cout << "ERROR: could not open renderer\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	double n = 49.0167000; // Nördliche Grenze
	double w = 8.3867740; // Östliche Grenze
	double s = 49.0103670; // Südliche Grenze
	double o = 8.4036180; // Westliche Grenze


	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; !adjList.empty() && i < adjList.size(); i++) {
		int b = 1920 * (adjList.at(i)->lon - w) / (o - w); //Formel zur bestimmung der x-Position auf Bildschirm
		int h = 1080 - 1080 * (adjList.at(i)->lat - s) / (n - s);  //Formel zur bestimmung der x-Position auf Bildschirm
		int p = -2;
		while (p < 3) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			SDL_RenderLine(renderer, b - 2, h + p, b + 2, h + p);
			SDL_Delay(10);
			p++;
		}
		for (int nb = 0; !adjList.at(i)->neighbors.empty() && nb < adjList.at(i)->neighbors.size(); nb++) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			int bn = 1920 * (adjList.at(i)->neighbors.at(nb).first->lon - w) / (o - w); //Formel zur bestimmung der x-Position auf Bildschirm
			int hn = 1080 - 1080 * (adjList.at(i)->neighbors.at(nb).first->lat - s) / (n - s);  //Formel zur bestimmung der x-Position auf Bildschirm
			SDL_RenderLine(renderer, b, h, bn, hn);

			SDL_Delay(10);
		}


		
	}


	SDL_RenderPresent(renderer);


	SDL_Delay(5000); // 5 Sekunden warten
	// 4) Clean up & close
	// 4) Clean up & close


	int close = 0;
	cin >> close;
	if (close == 1) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_Quit();
	return 0;

}


