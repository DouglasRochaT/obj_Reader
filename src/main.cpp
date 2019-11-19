#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "structs.h"
#include "resources.h"
#include "render.h"
#include "input.h"

int main() {
	Obj object;
	std::string filename = "maya.obj";
	Point2D mouse = { 0, 0 }, oldMouse = { 0, 0 }, rotation = { 0, 0 };

	countLines(filename, object);
	object.vertex = new Point3D[object.numVertex];
	if(object.numNormals > 0){ object.normal = new Point3D[object.numNormals]; }
	object.face = new Face[object.numFaces];

	std::cout << "Loading vertexes...\n";
	getVertexElements(filename, object, "v");
	std::cout << "Loaded " << object.numVertex << " vertex!\n\n";
	std::cout << "Loading normals...\n";
	if(object.numNormals > 0){ getVertexElements(filename, object, "vn"); }
	std::cout << "Loaded " << object.numNormals << " normals!\n\n";
	std::cout << "Loading faces...\n";
	getVertexPerFace(filename, object);
	getFaceElements(filename, object);
	std::cout << "Loaded " << object.numFaces << " faces!\n\n";


	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "WINDOLOS", NULL, NULL);
	glfwMakeContextCurrent(window);
	double zoom = object.offset.y * 2; void* zoomp = &zoom;
	glfwSetWindowUserPointer(window, zoomp);

	renderSettings();
	inputSettings(window);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetCursorPos(window, &mouse.x, &mouse.y);
		rotation = getRotationFromCursor(window, mouse, oldMouse, rotation);
		drawObj(object, rotation, window);
		drawCompass(rotation);
		glfwGetCursorPos(window, &oldMouse.x, &oldMouse.y);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}