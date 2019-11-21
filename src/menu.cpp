#include <SDL.h>
#include "structs.h"

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

void drawMenu(SDL_Renderer* renderer, Mouse mouse){
	SDL_RenderClear(renderer);
	SDL_Point mousePos = { mouse.x, mouse.y };
	menuDrawBackground(renderer);
	drawMenuQuitButton(renderer, mousePos);
	SDL_RenderPresent(renderer);
}