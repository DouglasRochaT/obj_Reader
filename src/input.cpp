#include <SDL.h>
#include "structs.h"
#include <iostream>

int quitButtonMouseEvent(SDL_Point mousePos, int menu){
	SDL_Rect quitButtonRect = { 288, 2, 10, 10 };
	if(SDL_PointInRect(&mousePos, &quitButtonRect)){ return MENU_QUIT;}
	return menu;
}

int menuStartMouseEvent(SDL_Point mousePos, int menu){
	SDL_Rect loadObjButtonRect = {50, 200, 200, 30};
	if(SDL_PointInRect(&mousePos, &loadObjButtonRect)){ return MENU_LOADING; }
	SDL_Rect optionsButtonRect = { 50, 250, 200, 30 };
	if(SDL_PointInRect(&mousePos, &optionsButtonRect)){ return MENU_OPTIONS; }
	SDL_Rect exitButtonRect = { 50, 300, 200, 30 };
	if(SDL_PointInRect(&mousePos, &exitButtonRect)){ return MENU_QUIT; }
	return menu;
}

int menuErrorMouseEvent(SDL_Point mousePos, int menu){
	SDL_Rect okButtonRect = { 50, 260, 200, 30 };
	if(SDL_PointInRect(&mousePos, &okButtonRect)){ return MENU_START; }
	return menu;
}

int menuOptionsMouseEvent(SDL_Point mousePos, int menu){
	SDL_Rect backButtonRect = { 50, 350, 200, 30 };
	if(SDL_PointInRect(&mousePos, &backButtonRect)){ return MENU_START; }
	SDL_Rect resolutionButtonRect = { 50, 140, 200, 30 };
	if(SDL_PointInRect(&mousePos, &resolutionButtonRect)){ return MENU_OPTIONS_RESOLUTION; }
	return menu;
}

int menuOptionsResolutionMouseEvent(SDL_Point mousePos, int menu, int &resolutionSetting){
	SDL_Rect quitResolutionMenuButtonRect = { 487, 3, 10, 10 };
	if(SDL_PointInRect(&mousePos, &quitResolutionMenuButtonRect)){ return MENU_OPTIONS; }
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 4; j++){
			SDL_Rect resolutionButtonRect = {(j * 120) + 20, (i * 50) + 35, 100, 30};
			if(SDL_PointInRect(&mousePos, &resolutionButtonRect)){ 
				resolutionSetting = i*4 + j; 
				return MENU_OPTIONS; 
			}
		}
	}
	return menu;
}

void mouseWheelEvent(SDL_Event event, int menu, double &zoom, Obj obj){
	if(menu == MENU_GLDISPLAY){
		if(event.wheel.y > 0 && zoom > obj.size.y / 2){
			zoom -= (obj.size.y + 1) / 10;
		} else if(event.wheel.y < 0){
			zoom += (obj.size.y + 1) / 10;
		}
	}
}

void eventHandler(int &menu, double &zoom, Mouse &mouse, Obj obj, int &resolutionSetting){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT: menu = MENU_QUIT; break;
			case SDL_MOUSEBUTTONDOWN: 
				mouse.buttonPressed = true;
				{ //start block
					SDL_Point mousePos = {mouse.x, mouse.y};
					menu = quitButtonMouseEvent(mousePos, menu);
					switch(menu){
						case MENU_START:
							menu = menuStartMouseEvent(mousePos, menu); break;
						case MENU_ERROR:
							menu = menuErrorMouseEvent(mousePos, menu); break;
						case MENU_OPTIONS:
							menu = menuOptionsMouseEvent(mousePos, menu); break;
						case MENU_OPTIONS_RESOLUTION:
							menu = menuOptionsResolutionMouseEvent(mousePos, menu, resolutionSetting); break;
					}
				} //end block
			break;
			case SDL_MOUSEBUTTONUP: mouse.buttonPressed = false; break;
			case SDL_MOUSEWHEEL:
				mouseWheelEvent(event, menu, zoom, obj);
			break;
		}
	}
}

Point2D getRotationFromCursor(Mouse &currentPos, Mouse oldPos, Point2D currentRot) {
	if(currentPos.buttonPressed){
		currentRot.x += (currentPos.y - oldPos.y);
		currentRot.y += (currentPos.x - oldPos.x);
	}
	return currentRot;
}
