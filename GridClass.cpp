#include "GridClass.h"

GridSlot::GridSlot() {
	xpos = 0;
	ypos = 0;
	width = 0;
	height = 0;
	collider = {xpos, ypos, width, height};
	currentTexture = NULL;
	int red;
}

void GridSlot::init(int x, int y, int w, int h) {
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	collider = {xpos, ypos, width, height};
	red = 0;
}

void GridSlot::setRenderer(SDL_Renderer* rendererToSet) {
	renderer = rendererToSet;
}

void GridSlot::setTexture(SDL_Texture* textureToSet) {
	currentTexture = textureToSet;
}

void GridSlot::drawRectangle(int x, int y, int w, int h) {
	SDL_SetRenderDrawColor(renderer, red, 0x00, 0x00, 0xFF);
	SDL_Rect drawRect = {x, y, w, h};
	if (red > 0) {
		SDL_RenderFillRect(renderer, &drawRect);
	}
	else {
		SDL_RenderDrawRect(renderer, &drawRect);
	}
	
}

void GridSlot::render() {
	if (currentTexture != NULL) {
		SDL_Rect dest = {xpos, ypos, width, height};
		SDL_RenderCopy(renderer, currentTexture, NULL, &dest);
	}
	else {
		drawRectangle(xpos, ypos, width, height);
	}
}

void GridSlot::makeRed() {
	red = 200;
}

GridClass::GridClass() {
	renderer = NULL;
	columns = 0;
	rows = 0;
	screenWidth = 0;
	screenHeight = 0;
	gridSlotHeight = 0;
	gridSlotWidth = 0;
}

void GridClass::init(int c, int r, int sW, int sH) {
	columns = c;
	rows = r;
	screenWidth = sW;
	screenHeight = sH;
	gridSlotWidth = screenWidth/columns;
	gridSlotHeight = screenHeight/rows;
}

void GridClass::setRenderer(SDL_Renderer* rendererToSet) {
	renderer = rendererToSet;
}

void GridClass::createGrid() {
	int xPosition = 0;
	int yPosition = 0;
	for (size_t i = 0; i < rows; i++) {
		for(size_t j = 0; j < columns; j++) {
			GridSlot tempGridSlot;
			tempGridSlot.setRenderer(renderer);
			tempGridSlot.init(xPosition, yPosition, gridSlotWidth, gridSlotHeight);
			theGrid.push_back(tempGridSlot);
			xPosition += gridSlotWidth;
		}
		yPosition += gridSlotHeight;
		xPosition = 0;
	}
}

void GridClass::drawGrid() {
	for (size_t i = 0; i < theGrid.size(); i++) {
		theGrid[i].render();
	}
}

GridSlot& GridClass::getGridSlot(int x, int y) {
	GridSlot& temp = theGrid[x + (y * columns)];
	return temp;
}