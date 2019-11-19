#include <glfw3.h>
#include "structs.h"
#include <iostream>

void drawCompass(Point2D rot){
	glLineWidth(2.0);
	glClearColor(0.08, 0.08, 0.08, 255);
	glPushMatrix();
	glTranslated(-0.90, -0.90, 0.0);
	glRotated(-rot.x, 1.0, 0.0, 0.0);
	glRotated(rot.y, 0.0, 1.0, 0.0);
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
	glPopMatrix();
}

void drawObj(Obj obj, Point2D rot, GLFWwindow* window) {
	void* zoomp = glfwGetWindowUserPointer(window);
	double *zoom = static_cast<double*>(zoomp);
	glPushMatrix();
	glRotated(-rot.x, 1.0, 0.0, 0.0);
	glRotated(rot.y, 0.0, 1.0, 0.0);
	glTranslated(-obj.offset.x / *zoom, -obj.offset.y / *zoom, -obj.offset.z / *zoom);
	glColor3d(1, 1, 1);
	glEnable(GL_LIGHT0);
	for(int i = 0; i < obj.numFaces; i++) {
		glBegin(GL_POLYGON);
		for(int j = 0; j < obj.face[i].vertexPerFace; j++){
			if(obj.numNormals > 0){ glNormal3d(obj.normal[obj.face[i].normal[j]].x, obj.normal[obj.face[i].normal[j]].y, obj.normal[obj.face[i].normal[j]].z); }
			glVertex3d(obj.vertex[obj.face[i].vertex[j]].x / *zoom, obj.vertex[obj.face[i].vertex[j]].y / *zoom, obj.vertex[obj.face[i].vertex[j]].z / *zoom);
		}
		glEnd();
	}
	glPopMatrix();
}

void renderSettings(){
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glColor3d(1, 1, 1);
	GLfloat light_position[] = { 0.0f, 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}