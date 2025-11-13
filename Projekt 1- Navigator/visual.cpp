#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <math.h>
using namespace std;

int visual() {



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
	window = SDL_CreateWindow("SDL3 Start", 1920, 1080,
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

	int n = 0; // Nördliche Grenze
	int o = 0; // Östliche Grenze
	int s = 0; // Südliche Grenze
	int w = 0; // Westliche Grenze
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // color for cls
	SDL_RenderClear(renderer); // cls

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; !nodelist.empty() && i < nodelist.size(); i++) {
		int h = (1920 * nodelist.at(i).lat - w) / (o - w); //Formel zur bestimmung der x-Position auf Bildschirm
		int b = 1080 - 1080 * (nodelist.at(i).lon - s) / (n - s);  //Formel zur bestimmung der x-Position auf Bildschirm
		int p = -2;
		while (p < 3) {
			SDL_RenderLine(renderer, h + p, b - 2, h + p, b + 2);
			p++;

			if (i < nodelist.at(i).neigbours.at(i).id) {
				int hn = (1920 * nodelist.at(i).neigbours.at(i).lat - w) / (o - w); //Formel zur bestimmung der x-Position auf Bildschirm
				int bn = 1080 - 1080 * (nodelist.at(i).neigbours.at(i).lon - s) / (n - s);  //Formel zur bestimmung der x-Position auf Bildschirm
				SDL_RenderLine(renderer, h, b, hn, bn);
			}
		}


	}
	int p = -2;
	while (p < 3) {

		SDL_RenderLine(renderer, 300 + p, 196, 300 + p, 200);
		p++;
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