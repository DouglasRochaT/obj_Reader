#ifndef RENDER_H
#define RENDER_H

#include "structs.h"

void drawCompass(Point2D rot);
void drawObj(Obj obj, Point2D rot, SDL_Window* window, double zoom);
void renderSettings();

#endif // RENDER_H