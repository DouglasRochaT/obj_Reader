#ifndef STRUCTS_H
#define STRUCTS_H

#define MENU_QUIT 0
#define MENU_START 1
#define MENU_OPTIONS 2
#define MENU_LOADING 3
#define MENU_ERROR 4
#define MENU_GLDISPLAY 5

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

struct Face {
	unsigned short int vertexPerFace;
	unsigned short int* vertex;
	unsigned short int texture;
	unsigned short int* normal;
};

struct Obj {
	int numVertex;
	int numNormals;
	int numFaces;
	Point3D offset;
	Point3D* vertex;
	Point3D* normal;
	Face* face;
};

struct Mouse {
	int x;
	int y;
	bool buttonPressed;
};

#endif // STRUCTS_H