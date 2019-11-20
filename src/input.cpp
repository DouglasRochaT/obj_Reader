#include <SDL.h>
#include "structs.h"
#include <iostream>

void eventHandler(bool &quit, double &zoom, Mouse &mouse, Obj obj){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			quit = true;
		} else if(event.type == SDL_MOUSEBUTTONDOWN){
			mouse.buttonPressed = true;
		} else if(event.type == SDL_MOUSEBUTTONUP){
			mouse.buttonPressed = false;
		} else if(event.type == SDL_MOUSEWHEEL && event.wheel.y > 0 && zoom > 1){
			zoom -= (obj.offset.y + 1) / 10;
		} else if(event.type == SDL_MOUSEWHEEL && event.wheel.y < 0){
			zoom += (obj.offset.y + 1) / 10;
		}
	}
}

Point2D getRotationFromCursor(SDL_Window* window, Mouse &currentPos, Mouse oldPos, Point2D currentRot) {
	if(currentPos.buttonPressed){
		currentRot.x += (currentPos.y - oldPos.y) / 5;
		currentRot.y += (currentPos.x - oldPos.x) / 5;
	}
	return currentRot;
}
