#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>

using namespace std;

struct Mouse {
	double x;
	double y;
};

struct Point {
	double x;
	double y;
	double z;
};

struct Face {
	int vertex[3];
	int normal;
};

void mouseCallBack(GLFWwindow* window, double x, double y){
}

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset){
}

int main(){

	Point vertex[8] = {{-0.5, -0.5, -0.5},
	                   {-0.5, -0.5,  0.5},
					   {-0.5,  0.5, -0.5},
					   {-0.5,  0.5,  0.5},
					   { 0.5, -0.5, -0.5},
					   { 0.5, -0.5,  0.5},
					   { 0.5,  0.5, -0.5},
					   { 0.5,  0.5,  0.5}};

	Point normals[8] = {{ 0.0,  0.0,  1.0},
						{ 0.0,  0.0, -1.0},
						{ 0.0,  1.0,  0.0},
						{ 0.0, -1.0,  0.0},
						{ 1.0,  0.0,  0.0},
						{-1.0,  0.0,  0.0}};


	Face faces[12] = {{{0, 6, 4}, 1},
					  {{0, 2, 6}, 1},
					  {{0, 3, 2}, 5},
					  {{0, 1, 3}, 5},
					  {{2, 7, 6}, 2},
					  {{2, 3, 7}, 2},
					  {{4, 6, 7}, 4},
					  {{4, 7, 5}, 4},
					  {{0, 4, 5}, 3},
					  {{0, 5, 1}, 3},
					  {{1, 5, 7}, 0},
					  {{1, 7, 3}, 0}};


					  
	Mouse mouse = {0, 0};

	double zoom = 1;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "WINDOLOS", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	
	//light
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glColor3d(1, 1, 1);
	GLfloat light_position[] = { 0.0f, 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	

	//input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //CHANGE TO GLFW_CURSOR_DISABLED
	//glfwSetScrollCallback(window, scrollCallBack);
	glfwSetCursorPos(window, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		glfwGetCursorPos(window, &mouse.x, &mouse.y);
		//glRotated(5, (mouse.y - oldMouse.y), (mouse.x - oldMouse.x), 0.0);

		//double rotationX = fmod(mouse.y, 360.0) - 180;
		//double rotationY = 

		glLoadIdentity();
		glPushMatrix();
		glRotated(-mouse.y/2, 1.0, 0.0, 0.0);
		glRotated(-mouse.x/2, 0.0, 1.0, 0.0); // this is all right
		//glRotated(fmod(-mouse.x, 90), 0.0, 0.0, 1.0);

		//cout << rotationX << '\n';

		glBegin(GL_TRIANGLES);
		for(int i = 0; i < 12; i++){
			glNormal3d(normals[faces[i].normal].x, normals[faces[i].normal].y, normals[faces[i].normal].z);
			glVertex3d(vertex[faces[i].vertex[0]].x/zoom, vertex[faces[i].vertex[0]].y/zoom, vertex[faces[i].vertex[0]].z/zoom);
			glVertex3d(vertex[faces[i].vertex[1]].x/zoom, vertex[faces[i].vertex[1]].y/zoom, vertex[faces[i].vertex[1]].z/zoom);
			glVertex3d(vertex[faces[i].vertex[2]].x/zoom, vertex[faces[i].vertex[2]].y/zoom, vertex[faces[i].vertex[2]].z/zoom);
		}
		glEnd();



		glPopMatrix();
		glfwSwapBuffers(window);

		glfwPollEvents();
		
	}

	std::cout << glGetError();

	glfwTerminate();
	return 0;
		
}