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
	unsigned short int numVertex;
	unsigned short int vertex[4];
	unsigned short int texture;
	unsigned short int normal;
};

struct Obj {
	int numVertex;
	int numNormals;
	int numFaces;
	unsigned short int vertexPerFace;
	Point3D* vertex;
	Point3D* normal;
	Face* face;
};

#endif // STRUCTS_H