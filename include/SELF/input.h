#ifndef INPUT_H
#define INPUT_H

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
Point2D getRotationFromCursor(GLFWwindow* window, Point2D currentPos, Point2D oldPos, Point2D currentRot);
void inputSettings(GLFWwindow* window);

#endif // INPUT_H