#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include "structs.h"
#include "resources.h"
#include "render.h"
#include "input.h"
#include "text.h"
#include "menu.h"

int main(){
	hideConsole();
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Obj object = {0, 0, 0, {0, 0}, nullptr, nullptr, nullptr};
	std::string filename;
	Mouse mouse = { 0, 0, false }, oldMouse = { 0, 0, false };
	Point2D rotation = { 0, 0 };
	double zoom;
	int menu = MENU_START;

	//---main menu window---//
	SDL_Window* menuWindow = SDL_CreateWindow("Obj Reader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 400, SDL_WINDOW_BORDERLESS);
	SDL_Renderer* menuRenderer = SDL_CreateRenderer(menuWindow, 0, SDL_RENDERER_ACCELERATED);
	
	//---resolution menu window---//
	SDL_Window* resolutionMenuWindow;// = SDL_CreateWindow("Resolution Options", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 200, SDL_WINDOW_BORDERLESS);
	SDL_Renderer* resolutionMenuRenderer;// = SDL_CreateRenderer(resolutionMenuWindow, 0, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(menuRenderer, SDL_BLENDMODE_BLEND);
	SDL_Window* glWindow = nullptr;
	SDL_GLContext glContext;
	SDL_Texture* font = IMG_LoadTexture(menuRenderer, "resources/font.png");

	while(menu != MENU_QUIT){
		eventHandler(menu, zoom, mouse, object);
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if(menu == MENU_START){
			//--start menu---//
			drawMenu(menuRenderer, mouse, font, menu);
		} else if(menu == MENU_OPTIONS){
			drawMenu(menuRenderer, mouse, font, menu);
		} else if(menu == MENU_OPTIONS_RESOLUTION){
			resolutionMenuWindow = SDL_CreateWindow("Resolution Options", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 200, SDL_WINDOW_BORDERLESS);
			resolutionMenuRenderer = SDL_CreateRenderer(resolutionMenuWindow, 0, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawBlendMode(resolutionMenuRenderer, SDL_BLENDMODE_BLEND);
			while(menu == MENU_OPTIONS_RESOLUTION){
				eventHandler(menu, zoom, mouse, object);
				SDL_GetMouseState(&mouse.x, &mouse.y);
				drawMenu(menuRenderer, mouse, font, menu);
				drawResolutionMenu(resolutionMenuRenderer, mouse);
			}
			SDL_DestroyRenderer(resolutionMenuRenderer);
			SDL_DestroyWindow(resolutionMenuWindow);
		} else if(menu == MENU_LOADING){
			//---loading menu---//
			filename = getFileName();
			drawMenu(menuRenderer, mouse, font, menu);
			loadObj(object, filename);
			if(object.numVertex){
				//---preparing openGL window and closing menu window---//
				SDL_DestroyRenderer(menuRenderer);
				SDL_DestroyWindow(menuWindow);
				glWindow = SDL_CreateWindow("Obj Reader - Displaying 3D Model", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
				glContext = SDL_GL_CreateContext(glWindow);
				renderSettings();
				zoom = (object.offset.y == 0) ? 1 : object.offset.y * 2;
				menu = MENU_GLDISPLAY;
			} else {
				//---error handler---//
				menu = MENU_ERROR;
			}
		} else if(menu == MENU_ERROR){
			//---error menu---//
			drawMenu(menuRenderer, mouse, font, menu);
		} else if(menu == MENU_GLDISPLAY){
			//---openGL menu---//
			rotation = getRotationFromCursor(glWindow, mouse, oldMouse, rotation);
			drawEverything(object, rotation, glWindow, zoom);
		}
		SDL_GetMouseState(&oldMouse.x, &oldMouse.y);
	}
	SDL_Quit();
	return 0;
}