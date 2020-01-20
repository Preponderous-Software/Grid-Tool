#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "GridClass.h"

using namespace std;

const int COLUMNS = 20;
const int ROWS = 10;

const int SCREEN_WIDTH = 1000; // must be multiples of COLUMNS
const int SCREEN_HEIGHT = 500; // must be multiples of ROWS

const int GRID_SLOT_HEIGHT = SCREEN_HEIGHT/ROWS;
const int GRID_SLOT_WIDTH = SCREEN_WIDTH/COLUMNS;


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

GridClass theGrid;

void init();

void cleanUp();

void init() {
	SDL_Init(SDL_INIT_VIDEO);

	// set texture filtering to linear
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gWindow = SDL_CreateWindow("blank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	theGrid.init(COLUMNS, ROWS, SCREEN_WIDTH, SCREEN_HEIGHT);
	theGrid.setRenderer(gRenderer);
	
	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
}

void cleanUp() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {
	init();
	theGrid.createGrid();
	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		
		theGrid.drawGrid();
		
		SDL_RenderPresent(gRenderer);
	}
	cleanUp();
}