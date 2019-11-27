#include <SDL.h>
#include <SDL_opengl.h>
#include "structs.h"
#include <iostream>
#include <string>

void drawCompass(Point2D rot){
	glLineWidth(2.0);
	glTranslated(-0.90, -0.90, 0.0);
	glRotated(-rot.x/5, 1.0, 0.0, 0.0);
	glRotated(-rot.y/5, 0.0, 1.0, 0.0);
	glTranslated(0.90, 0.90, 0.0);
	glDisable(GL_LIGHT0);
	glBegin(GL_LINES);
	//---X axis---//
	glColor3d(255, 0, 0);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.80, -0.90, 0.0);
	//---Y axis---//
	glColor3d(0, 255, 0);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.90, -0.80, 0.0);
	//---Z axis---//
	glColor3d(0, 0, 255);
	glVertex3d(-0.90, -0.90, 0.0);
	glVertex3d(-0.90, -0.90, -0.10);
	glEnd();
	glLoadIdentity();
}

void drawObj(Obj obj, Point2D rot, double zoom) {
	glRotated(-rot.x/5, 1.0, 0.0, 0.0);
	glRotated(-rot.y/5, 0.0, 1.0, 0.0);
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

void setRendererSettings(){
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glColor3d(1, 1, 1);
	GLfloat light_position[] = { 0.0f, 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glClearColor(0.1, 0.1, 0.11, 255);
}

void drawEverything(Obj object, Point2D rotation, SDL_Window* mainWindow, double zoom, int resolution){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int fourByThreeProportionHeight = stoi(resList[1][resolution]);
	int fourByThreeProportionWidth = fourByThreeProportionHeight *1.3;
	glViewport((stoi(resList[0][resolution])/2) - fourByThreeProportionWidth / 2, 0, fourByThreeProportionWidth, fourByThreeProportionHeight);
	drawObj(object, rotation, zoom);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, stoi(resList[1][resolution])*1.3, stoi(resList[1][resolution]));
	drawCompass(rotation);
	SDL_GL_SwapWindow(mainWindow);
}