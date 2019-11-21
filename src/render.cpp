#include <SDL.h>
#include <SDL_opengl.h>
#include "structs.h"
#include <iostream>

void drawCompass(Point2D rot){
	glLineWidth(2.0);
	glTranslated(-0.90, -0.90, 0.0);
	glRotated(-rot.x, 1.0, 0.0, 0.0);
	glRotated(-rot.y, 0.0, 1.0, 0.0);
	glTranslated(0.90, 0.90, 0.0);
	glDisable(GL_LIGHT0);
	glBegin(GL_LINES);
	glColor3d(255, 0, 0);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.80, -0.90, 0.0);
	glColor3d(0, 255, 0);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.90, -0.80, 0.0);
	glColor3d(0, 0, 255);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.90, -0.90, -0.10);
	glEnd();
	glLoadIdentity();
}

void drawObj(Obj obj, Point2D rot, SDL_Window* window, double zoom) {
	glRotated(-rot.x, 1.0, 0.0, 0.0);
	glRotated(-rot.y, 0.0, 1.0, 0.0);
	glTranslated(-obj.offset.x / zoom, -obj.offset.y / zoom, -obj.offset.z / zoom);
	glColor3d(1, 1, 1);
	glEnable(GL_LIGHT0);
	for(int i = 0; i < obj.numFaces; i++) {
		glBegin(GL_POLYGON);
		for(int j = 0; j < obj.face[i].vertexPerFace; j++){
			if(obj.numNormals > 0){ glNormal3d(obj.normal[obj.face[i].normal[j]].x, obj.normal[obj.face[i].normal[j]].y, obj.normal[obj.face[i].normal[j]].z); }
			glVertex3d(obj.vertex[obj.face[i].vertex[j]].x / zoom, obj.vertex[obj.face[i].vertex[j]].y / zoom, obj.vertex[obj.face[i].vertex[j]].z / zoom);
		}
		glEnd();
	}
	glLoadIdentity();
}

void renderSettings(){
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glColor3d(1, 1, 1);
	GLfloat light_position[] = { 0.0f, 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glClearColor(0.1, 0.1, 0.11, 255);
}

void drawEverything(Obj object, Point2D rotation, SDL_Window* mainWindow, double zoom){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawObj(object, rotation, mainWindow, zoom);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawCompass(rotation);
	SDL_GL_SwapWindow(mainWindow);
}