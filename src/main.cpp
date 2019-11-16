#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "structs.h"
#include "resources.h"
#include "render.h"
#include "input.h"

int main() {

	std::string filename = "handgun.obj";

	Obj object;
	object.numVertex = countLines(filename, "v");
	object.numNormals = countLines(filename, "vn");
	object.numFaces = countLines(filename, "f");
	object.vertex = new Point3D[object.numVertex];
	if(object.numNormals > 0){
		object.normal = new Point3D[object.numNormals];
	}
	object.face = new Face[object.numFaces];

	std::cout << "Loading vertexes...\n";
	getVertexElements(filename, object.vertex, "v");
	std::cout << "Loading normals...\n";
	if(object.numNormals > 0){
		getVertexElements(filename, object.normal, "vn");
	}
	std::cout << "Loading faces...\n";
	getVertexPerFace(filename, object);
	getFaceElements(filename, object);


	std::cout << "Number of Vertex: " << object.numVertex << "\nNum of Normals: " << object.numNormals << "\nNumber of Faces: " << object.numFaces << '\n';

	/*for(int i = 0; i < object.numVertex; i++){
		std::cout << "Vertex " << i << ":\n";
		std::cout << object.vertex[i].x << ", " << object.vertex[i].y << ", " << object.vertex[i].z << "\n\n";
	}

	for(int i = 0; i < object.numFaces; i++){
		std::cout << "Face " << i << " (" << object.face[i].vertexPerFace << " vertex):\n";
		for(int j = 0; j < object.face[i].vertexPerFace; j++){
			std::cout << "Vertex " << object.face[i].vertex[j] << ":\n";
			std::cout << object.vertex[object.face[i].vertex[j]].x << ", " << object.vertex[object.face[i].vertex[j]].y << ", " << object.vertex[object.face[i].vertex[j]].z << "\n";
		}
		std::cout << "\n\n";
	}*/


	Point2D mouse = { 0, 0 }, oldMouse = { 0, 0 }, rotation = { 0, 0 };

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "WINDOLOS", NULL, NULL);
	glfwMakeContextCurrent(window);
	double zoom = 1; void* zoomp = &zoom;
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