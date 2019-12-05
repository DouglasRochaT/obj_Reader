#ifndef STRUCTS_H
#define STRUCTS_H

#define MENU_QUIT 0
#define MENU_START 1
#define MENU_OPTIONS 2
#define MENU_OPTIONS_RESOLUTION 3
#define MENU_LOADING 4
#define MENU_ERROR 5
#define MENU_GLDISPLAY 6

#include <iostream>
const std::string resList[2][12] = { { "640", "800", "1024", "1152", "1280", "1280", "1280", "1280", "1360", "1440", "1600", "1920" },
{ "360", "600", "768",  "864",  "720",  "768",  "800",  "1024", "768",  "900",  "900",  "1080" } };

struct Screen {
	int x;
	int y;
	int wScale;
	int hScale;
};

struct Point2D {
	double x;
	double y;
};

struct Point3D {
	double x;
	double y;
	double z;
};

struct Mtl {
	std::string name;
	std::string fileName;
	SDL_Surface* tga;
};

struct Face {
	unsigned short int vertexPerFace;
	unsigned short int* vertex;
	unsigned short int* texture;
	unsigned short int* normal;
};

struct Texture {
	Point2D coord;
	std::string material;
};

struct Obj {
	int numVertex;
	int numNormals;
	int numFaces;
	int numTextures;
	int numMtl;
	unsigned int* textureID;
	Point3D size;
	Point3D offset;
	Point3D* vertex;
	Point3D* normal;
	Texture* texture;
	Face* face;
	Mtl* mtl;
};

struct Mouse {
	int x;
	int y;
	bool buttonPressed;
};

#endif //STRUCTS_H