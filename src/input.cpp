#include <SDL.h>
#include "structs.h"
#include <iostream>

void eventHandler(int &menu, double &zoom, Mouse &mouse, Obj obj){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT: menu = MENU_QUIT; break;
			case SDL_MOUSEBUTTONDOWN: 
				mouse.buttonPressed = true;
				{ //start block
					SDL_Point mousePos = { mouse.x, mouse.y };
					SDL_Rect quitButtonRect = { 288, 2, 10, 10 };
					if(SDL_PointInRect(&mousePos, &quitButtonRect)){ menu = MENU_QUIT;}
					if(menu == MENU_START){
						SDL_Rect loadObjButtonRect = {50, 200, 200, 30};
						if(SDL_PointInRect(&mousePos, &loadObjButtonRect)){ menu = MENU_LOADING; }
						SDL_Rect optionsButtonRect = { 50, 250, 200, 30 };
						if(SDL_PointInRect(&mousePos, &optionsButtonRect)){ menu = MENU_OPTIONS; }
						SDL_Rect exitButtonRect = { 50, 300, 200, 30 };
						if(SDL_PointInRect(&mousePos, &exitButtonRect)){ menu = MENU_QUIT; }
					} else if(menu == MENU_ERROR){
						SDL_Rect okButtonRect = { 50, 260, 200, 30 };
						if(SDL_PointInRect(&mousePos, &okButtonRect)){ menu = MENU_START; }
					} else if(menu == MENU_OPTIONS){
						SDL_Rect backButtonRect = { 50, 350, 200, 30 };
						if(SDL_PointInRect(&mousePos, &backButtonRect)){ menu = MENU_START; }
						SDL_Rect resolutionButtonRect = { 50, 140, 200, 30 };
						if(SDL_PointInRect(&mousePos, &resolutionButtonRect)){ menu = MENU_OPTIONS_RESOLUTION; }
					} else if(menu == MENU_OPTIONS_RESOLUTION){
						SDL_Rect quitResolutionMenuButtonRect = { 487, 3, 10, 10 };
						if(SDL_PointInRect(&mousePos, &quitResolutionMenuButtonRect)){ menu = MENU_OPTIONS; }
					}
				} //end block (for some godforsaken reason i couldnt declare mousePos and quitButtonRect without this block)
			break;
			case SDL_MOUSEBUTTONUP: mouse.buttonPressed = false; break;
			case SDL_MOUSEWHEEL:
				if(menu == MENU_GLDISPLAY){
					if(event.wheel.y > 0 && zoom > 1){
						zoom -= (obj.offset.y + 1) / 10;
					} else if(event.wheel.y < 0){
						zoom += (obj.offset.y + 1) / 10;
					}
				}
			break;
		}
	}
}

Point2D getRotationFromCursor(SDL_Window* window, Mouse &currentPos, Mouse oldPos, Point2D currentRot) {
	if(currentPos.buttonPressed){
		currentRot.x += (currentPos.y - oldPos.y);
		currentRot.y += (currentPos.x - oldPos.x);
	}
	return currentRot;
}
