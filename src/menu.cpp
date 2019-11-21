#include <SDL.h>
#include <iostream>
#include <string>
#include "structs.h"
#include "text.h"

void createButton(SDL_Renderer* renderer, SDL_Point mousePos, int x, int y, int w, int h, std::string text, SDL_Texture* font, int textX){
	SDL_Rect buttonRect = { x, y, w, h };
	if(SDL_PointInRect(&mousePos, &buttonRect)){
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
	} else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 64);
	}
	SDL_RenderFillRect(renderer, &buttonRect);
	double fontWidth = h*0.62;
	double fontHeight = h*0.8;
	writeText(renderer, text, font, x + textX, y + 5, fontWidth, fontHeight);
}

void menuDrawBackground(SDL_Renderer* render){
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_Rect rect = { -1, -1, 301, 401 };
	SDL_RenderFillRect(render, &rect);
	for(int i = 2; i < 400; i += 2){
		SDL_SetRenderDrawColor(render, 0, 100 - (i / 4), 200 - (i / 2), 255);
		SDL_Rect rect = { 1, i - 1, 297, 2 };
		SDL_RenderFillRect(render, &rect);
	}
}

void drawMenuQuitButton(SDL_Renderer* renderer, SDL_Point mousePos){
	SDL_Rect quitButtonRect = { 287, 3, 10, 10 };
	if(SDL_PointInRect(&mousePos, &quitButtonRect)){
		SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
	} else {
		SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
	}
	SDL_RenderFillRect(renderer, &quitButtonRect);
}

void drawMenu(SDL_Renderer* renderer, Mouse mouse, SDL_Texture* font, int menu){
	SDL_RenderClear(renderer);
	SDL_Point mousePos = { mouse.x, mouse.y };
	menuDrawBackground(renderer);
	drawMenuQuitButton(renderer, mousePos);
	if(menu == MENU_START){
		writeText(renderer, "Obj", font, 70, 20, 58, 93);
		writeText(renderer, "reader", font, 45, 120);
		createButton(renderer, mousePos, 50, 200, 200, 30, "Load .obj", font, 30);
		createButton(renderer, mousePos, 50, 250, 200, 30, "Options", font, 45);
		createButton(renderer, mousePos, 50, 300, 200, 30, "Exit", font, 65);
	} else if (menu == MENU_LOADING){
		writeText(renderer, "Loading...", font, 20, 180, 29, 46);
	} else if(menu == MENU_ERROR){
		writeText(renderer, "An error has occurred", font, 15, 160, 15, 21);
		writeText(renderer, "please select another", font, 15, 190, 15, 21);
		writeText(renderer, "file.", font, 125, 220, 15, 21);
		createButton(renderer, mousePos, 50, 260, 200, 30, "Ok", font, 85);
	}
	SDL_RenderPresent(renderer);
}