#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "structs.h"

void eventHandler(bool &quit, double &zoom, Mouse &mouse, Obj obj);
Point2D getRotationFromCursor(SDL_Window* window, Mouse &currentPos, Mouse oldPos, Point2D currentRot);

#endif // INPUT_H