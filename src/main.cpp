#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "structs.h"
#include "resources.h"
#include "render.h"
#include "input.h"
#include "text.h"
#include "menu.h"

int main(){
	//hideConsole(); //This is annoying for debug //sorry
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Obj object = { 0, 0, 0, 0, 0, nullptr, {0, 0}, {0, 0, 0}, nullptr, nullptr, nullptr, nullptr, nullptr};
	std::string filename;
	Mouse mouse = { 0, 0, false }, oldMouse = { 0, 0, false };
	Point2D rotation = { 0, 0 };
	double zoom;
	int menu = MENU_START, userResolution = 1;

	//---main menu window---//
	SDL_Window* menuWindow = SDL_CreateWindow("Obj Reader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 400, SDL_WINDOW_BORDERLESS);
	SDL_Renderer* menuRenderer = SDL_CreateRenderer(menuWindow, 0, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(menuRenderer, SDL_BLENDMODE_BLEND);
	
	//---resolution menu window---//
	SDL_Window* resolutionMenuWindow;
	SDL_Renderer* resolutionMenuRenderer;

	//---openGL window---//
	SDL_Window* glWindow = nullptr;
	SDL_GLContext glContext;

	//---fonts---//
	SDL_Texture* logo = IMG_LoadTexture(menuRenderer, "resources/LogoObjReader.png");
	SDL_Texture* font = IMG_LoadTexture(menuRenderer, "resources/font.png");
	SDL_Texture* resolutionMenuFont;
	
	//===================================LOOP===================================//
	while(menu){
		eventHandler(menu, zoom, mouse, object, userResolution);
		SDL_GetMouseState(&mouse.x, &mouse.y);
		switch(menu){
		case MENU_START:
			drawMenu(menuRenderer, mouse, font, logo, menu, userResolution); break;
		case MENU_OPTIONS:
			drawMenu(menuRenderer, mouse, font, logo, menu, userResolution); break;
		case MENU_OPTIONS_RESOLUTION:
			resolutionMenuWindow = SDL_CreateWindow("Resolution Options", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 200, SDL_WINDOW_BORDERLESS);
			resolutionMenuRenderer = SDL_CreateRenderer(resolutionMenuWindow, 0, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawBlendMode(resolutionMenuRenderer, SDL_BLENDMODE_BLEND);
			resolutionMenuFont = IMG_LoadTexture(resolutionMenuRenderer, "resources/font.png");
			while(menu == MENU_OPTIONS_RESOLUTION){
				eventHandler(menu, zoom, mouse, object, userResolution);
				SDL_GetMouseState(&mouse.x, &mouse.y);
				drawResolutionMenu(resolutionMenuRenderer, mouse, resolutionMenuFont);
			}
			SDL_DestroyRenderer(resolutionMenuRenderer);
			SDL_DestroyWindow(resolutionMenuWindow); break;
		case MENU_LOADING:
			filename = getFileName();
			drawMenu(menuRenderer, mouse, font, logo, menu, userResolution);
			loadObj(object, filename, menuRenderer, font);
			if(object.numVertex){
				//preparing gl window
				SDL_DestroyRenderer(menuRenderer);
				SDL_DestroyWindow(menuWindow);
				glWindow = SDL_CreateWindow("Obj Reader - Displaying 3D Model", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, stoi(resList[0][userResolution]), stoi(resList[1][userResolution]), SDL_WINDOW_OPENGL);
				glContext = SDL_GL_CreateContext(glWindow);
				glGenTextures(object.numMtl, object.textureID);
				setRendererSettings(object.textureID, object.numMtl);
				zoom = object.size.y;
				menu = MENU_GLDISPLAY;
			} else {
				menu = MENU_ERROR;
			} break;
		case MENU_ERROR:
			drawMenu(menuRenderer, mouse, font, logo, menu, userResolution); break;
		case MENU_GLDISPLAY:
			while(menu){
				eventHandler(menu, zoom, mouse, object, userResolution);
				SDL_GetMouseState(&mouse.x, &mouse.y);
				SDL_CaptureMouse(SDL_TRUE);
				rotation = getRotationFromCursor(mouse, oldMouse, rotation);
				drawEverything(object, rotation, glWindow, zoom, userResolution);
				SDL_GetMouseState(&oldMouse.x, &oldMouse.y);
			}
			SDL_DestroyWindow(glWindow); break;
		}
	}
	SDL_Quit();
	return 0;
}