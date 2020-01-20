#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ROWS = 20;
const int COLUMNS = 20;

const int SCREEN_WIDTH = 500; // must be multiples of 10
const int SCREEN_HEIGHT = 500; // must be multiples of 10

const int GRID_SLOT_HEIGHT = SCREEN_HEIGHT/ROWS;
const int GRID_SLOT_WIDTH = SCREEN_WIDTH/COLUMNS;


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

//SDL_Texture* blankGridSlot = NULL;

void init();

void loadMedia();

void cleanUp();

void drawRectangle(int x, int y, int w, int h);

class GridSlot {
  private:
	int xpos;
	int ypos;
	int width;
	int height;
	SDL_Rect collider;
	SDL_Texture* currentTexture;
  public:
	GridSlot();
	void init(int x, int y, int w, int h);
	void setTexture(SDL_Texture* textureToSet);
	void render();
};

void createGrid();

void drawGrid();

vector<GridSlot> theGrid;

void init() {
	SDL_Init(SDL_INIT_VIDEO);

	// set texture filtering to linear
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gWindow = SDL_CreateWindow("blank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
}

void loadMedia() {
//	SDL_Surface* tempSurface;
//	tempSurface = IMG_Load("blankGridSlot.png");
//	blankGridSlot = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
//	SDL_FreeSurface(tempSurface);
}

void cleanUp() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}

void drawRectangle(int x, int y, int w, int h) {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_Rect drawRect = {x, y, w, h};
	SDL_RenderDrawRect(gRenderer, &drawRect);
}

GridSlot::GridSlot() {
	xpos = 0;
	ypos = 0;
	width = 0;
	height = 0;
	collider = {xpos, ypos, width, height};
	currentTexture = NULL;
}

void GridSlot::init(int x, int y, int w, int h) {
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	collider = {xpos, ypos, width, height};
}

void GridSlot::setTexture(SDL_Texture* textureToSet) {
	currentTexture = textureToSet;
}

void GridSlot::render() {
	if (currentTexture != NULL) {
		
	}
	else {
		drawRectangle(xpos, ypos, width, height);
	}
}

void createGrid() {
	int xPosition = 0;
	int yPosition = 0;
	for (size_t i = 0; i < ROWS; i++) {
		for(size_t j = 0; j < COLUMNS; j++) {
			GridSlot tempGridSlot;
			tempGridSlot.init(xPosition, yPosition, GRID_SLOT_WIDTH, GRID_SLOT_HEIGHT);
			theGrid.push_back(tempGridSlot);
			xPosition += GRID_SLOT_WIDTH;
		}
		yPosition += GRID_SLOT_HEIGHT;
		xPosition = 0;
	}
}

void drawGrid() {
	for (size_t i = 0; i < theGrid.size(); i++) {
		theGrid[i].render();
	}
}

int main(int argc, char* args[]) {
	init();
	loadMedia();
	createGrid();
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
		
		drawGrid();
		
		SDL_RenderPresent(gRenderer);
	}
	cleanUp();
}