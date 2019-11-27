#include <SDL.h>
#include <iostream>
#include <string>
#include "structs.h"
#include "text.h"

void createButton(SDL_Renderer* renderer, SDL_Point mousePos, int x, int y, int w, int h, std::string text, SDL_Texture* font, int textX, int fontWidth = NULL, int fontHeight = NULL){
	SDL_Rect buttonRect = { x, y, w, h };
	if(SDL_PointInRect(&mousePos, &buttonRect)){
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
	} else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 64);
	}
	SDL_RenderFillRect(renderer, &buttonRect);
	if(fontWidth == NULL){fontWidth = static_cast<int>(h*0.62);}
	if(fontHeight == NULL){fontHeight = static_cast<int>(h*0.8);}
	writeText(renderer, text, font, x + textX, y + 5, fontWidth, fontHeight);
}

void menuDrawBackground(SDL_Renderer* render){
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_Rect rect = { -1, -1, 301, 401 };
	SDL_RenderFillRect(render, &rect);
	for(int i = 2; i < 400; i += 2){
		SDL_SetRenderDrawColor(render, 16, 81 - (i / 6), 140 - (i / 3), 255);
		SDL_Rect rect = { 1, i - 1, 297, 2 };
		SDL_RenderFillRect(render, &rect);
	}
}

void drawMenuQuitButton(SDL_Renderer* renderer, SDL_Point mousePos, int windowWidth){
	SDL_Rect quitButtonRect = { windowWidth - 13, 3, 10, 10 };
	if(SDL_PointInRect(&mousePos, &quitButtonRect)){
		SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
	} else {
		SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
	}
	SDL_RenderFillRect(renderer, &quitButtonRect);
}

void drawMainMenuButtons(SDL_Renderer* renderer, SDL_Point mousePos, SDL_Texture* font){
	writeText(renderer, "Obj", font, 70, 20, 58, 93);
	writeText(renderer, "reader", font, 45, 120);
	createButton(renderer, mousePos, 50, 200, 200, 30, "Load .obj", font, 30);
	createButton(renderer, mousePos, 50, 250, 200, 30, "Options", font, 45);
	createButton(renderer, mousePos, 50, 300, 200, 30, "Exit", font, 65);
}

void drawLoadingMenu(SDL_Renderer* renderer, SDL_Texture* font){
	writeText(renderer, "Loading...", font, 20, 180, 29, 46);
}

void drawErrorWarning(SDL_Renderer* renderer, SDL_Point mousePos, SDL_Texture* font){
	writeText(renderer, "An error has occurred", font, 15, 160, 15, 21);
	writeText(renderer, "please select another", font, 15, 190, 15, 21);
	writeText(renderer, "file.", font, 125, 220, 15, 21);
	createButton(renderer, mousePos, 50, 260, 200, 30, "Ok", font, 85);
}

void drawOptionsMenu(SDL_Renderer* renderer, SDL_Point mousePos, SDL_Texture* font, int resolution){
	writeText(renderer, "Options", font, 90, 20, 20, 30);
	writeText(renderer, "Resolution", font, 60, 100, 20, 30);
	std::string resolutionButtonText = resList[0][resolution] + "x" + resList[1][resolution];
	createButton(renderer, mousePos, 50, 140, 200, 30, resolutionButtonText, font, 45);
	createButton(renderer, mousePos, 50, 350, 200, 30, "Back", font, 68);
}

void drawMenu(SDL_Renderer* renderer, Mouse mouse, SDL_Texture* font, int menu, int resolution){
	SDL_RenderClear(renderer);
	SDL_Point mousePos = { mouse.x, mouse.y };
	menuDrawBackground(renderer);
	drawMenuQuitButton(renderer, mousePos, 300);
	if(menu == MENU_START){
		drawMainMenuButtons(renderer, mousePos, font);
	} else if (menu == MENU_LOADING){
		drawLoadingMenu(renderer, font);
	} else if(menu == MENU_ERROR){
		drawErrorWarning(renderer, mousePos, font);
	} else if(menu == MENU_OPTIONS || menu == MENU_OPTIONS_RESOLUTION){
		drawOptionsMenu(renderer, mousePos, font, resolution);
	} 
	SDL_RenderPresent(renderer);
}

void drawResolutionMenuBackground(SDL_Renderer* renderer){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect rect = { -1, -1, 501, 201 };
	SDL_RenderFillRect(renderer, &rect);
	for(int i = 2; i < 200; i += 2){
		SDL_SetRenderDrawColor(renderer, 16, 81 - (i / 3), 140 - (i / 1.5), 255);
		SDL_Rect rect = { 1, i - 1, 497, 2 };
		SDL_RenderFillRect(renderer, &rect);
	}
}

void drawResolutionMenuButtons(SDL_Renderer* renderer, Mouse mouse, SDL_Texture* font) {
	SDL_Point mousePos = {mouse.x, mouse.y};
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			std::string buttonText = resList[0][(i*4) + j] + "x" + resList[1][(i*4) + j];
			int xSpacing;
			if((i * 4) + j <= 1){xSpacing = 10;}
			else if((i * 4) + j == 7 || (i * 4) + j == 11){xSpacing = -1;}
			else{xSpacing = 5;}
			createButton(renderer, mousePos, (j * 120) + 20, (i * 50) + 35, 100, 30, buttonText, font, xSpacing, 13, 20);
		}
	}
}

void drawResolutionMenu(SDL_Renderer* renderer, Mouse mouse, SDL_Texture* font){
	SDL_Point mousePos = {mouse.x, mouse.y};
	SDL_RenderClear(renderer);
	drawResolutionMenuBackground(renderer);
	drawMenuQuitButton(renderer, mousePos, 500);
	drawResolutionMenuButtons(renderer, mouse, font);
	SDL_RenderPresent(renderer);
}