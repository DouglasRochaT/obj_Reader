#ifndef RENDER_H
#define RENDER_H

#include <glfw3.h>
#include "structs.h"

void drawCompass(Point2D rot);
void drawObj(Obj obj, Point2D rot, GLFWwindow* window);
void renderSettings();

#endif // RENDER_H