#ifndef GRIDCLASS_H
#define GRIDCLASS_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

class GridSlot {
  private:
	SDL_Renderer* renderer;
	int xpos;
	int ypos;
	int width;
	int height;
	SDL_Rect collider;
	SDL_Texture* currentTexture;
  public:
	GridSlot();
	void init(int x, int y, int w, int h);
	void setRenderer(SDL_Renderer* rendererToSet);
	void setTexture(SDL_Texture* textureToSet);
	void drawRectangle(int x, int y, int w, int h);
	void render();
};

class GridClass {
  private:
	SDL_Renderer* renderer;
	int columns;
	int rows;

	int screenWidth; // must be multiples of COLUMNS
	int screenHeight; // must be multiples of ROWS

	int gridSlotHeight;
	int gridSlotWidth;
	
	std::vector<GridSlot> theGrid;
  public:
	GridClass();
	void init(int c, int r, int sW, int sH);
	void setRenderer(SDL_Renderer* rendererToSet);
	void createGrid();
	void drawGrid();
};
#endif