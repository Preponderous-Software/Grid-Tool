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
	SDL_Texture* currentTexture;
	int red;
	bool solidFlag;
	bool buttonFlag;
  public:
	SDL_Rect collider;
	GridSlot();
	void init(int x, int y, int w, int h);
	void setRenderer(SDL_Renderer* rendererToSet);
	void setTexture(SDL_Texture* textureToSet);
	void drawRectangle(int x, int y, int w, int h);
	void render();
	void makeRed();
	void setSolidFlag(bool setter);
	void setButtonFlag(bool setter);
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
	std::vector<GridSlot> solidSlots;
	std::vector<GridSlot> buttonSlots;
	GridClass();
	void init(int c, int r, int sW, int sH);
	void setRenderer(SDL_Renderer* rendererToSet);
	void createGrid();
	void drawGrid();
	GridSlot& getGridSlot(int x, int y);
};
#endif