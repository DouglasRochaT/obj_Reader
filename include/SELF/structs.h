#ifndef STRUCTS_H
#define STRUCTS_H

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
	int numVertex = 0;
	int numNormals = 0;
	int numFaces = 0;
	Point3D offset;
	Point3D* vertex;
	Point3D* normal;
	Face* face;
};

#endif // STRUCTS_H