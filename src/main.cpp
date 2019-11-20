#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>
#include "structs.h"
#include "resources.h"
#include "render.h"
#include "input.h"

void drawEverything(Obj object, Point2D rotation, SDL_Window* mainWindow, double zoom){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawObj(object, rotation, mainWindow, zoom);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawCompass(rotation);
	SDL_GL_SwapWindow(mainWindow);
}

void loadObj(Obj &obj, std::string filename){
	countLines(filename, obj);
	obj.vertex = new Point3D[obj.numVertex];
	if(obj.numNormals > 0){ obj.normal = new Point3D[obj.numNormals]; }
	obj.face = new Face[obj.numFaces];
	std::cout << "Loading vertexes...\n";
	getVertexElements(filename, obj, "v");
	std::cout << "Loaded " << obj.numVertex << " vertex!\n\n";
	std::cout << "Loading normals...\n";
	if(obj.numNormals > 0){ getVertexElements(filename, obj, "vn"); }
	std::cout << "Loaded " << obj.numNormals << " normals!\n\n";
	std::cout << "Loading faces...\n";
	getVertexPerFace(filename, obj);
	getFaceElements(filename, obj);
	std::cout << "Loaded " << obj.numFaces << " faces!\n\n";
}

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	Obj object;
	std::string filename = "batman.obj";
	Mouse mouse = { 0, 0, false }, oldMouse = { 0, 0, false };
	Point2D rotation = { 0, 0 };

	loadObj(object, filename);

	SDL_Window* mainWindow = SDL_CreateWindow("my sdl window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext glContext = SDL_GL_CreateContext(mainWindow);
	double zoom = (object.offset.y == 0) ? 1 : object.offset.y * 2;
	bool quit = false;

	renderSettings();
	while(!quit) {
		eventHandler(quit, zoom, mouse, object);
		SDL_GetMouseState(&mouse.x, &mouse.y);
		rotation = getRotationFromCursor(mainWindow, mouse, oldMouse, rotation);

		drawEverything(object, rotation, mainWindow, zoom);
		
		SDL_GetMouseState(&oldMouse.x, &oldMouse.y);
	}
	SDL_Quit();
	return 0;
}