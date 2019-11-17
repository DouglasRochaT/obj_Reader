#include <glfw3.h>
#include "structs.h"

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset) {
	void* zoomp = glfwGetWindowUserPointer(window);
	double *zoom = static_cast<double*>(zoomp);
	*zoom -= yOffset / 10;
	if(*zoom < 1) {
		*zoom = 1;
	}
}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {}

Point2D getRotationFromCursor(GLFWwindow* window, Point2D currentPos, Point2D oldPos, Point2D currentRot) {
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		currentRot.x += (currentPos.y - oldPos.y) / 5;
		currentRot.y += (currentPos.x - oldPos.x) / 5;
	}
	return currentRot;
}

void inputSettings(GLFWwindow* window){
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scrollCallBack);
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);
	glfwSetCursorPos(window, 180.0, -180.0);
}