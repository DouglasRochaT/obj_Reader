#ifndef INPUT_H
#define INPUT_H

void eventHandler(int &menu, double &zoom, Mouse &mouse, Obj obj);
Point2D getRotationFromCursor(SDL_Window* window, Mouse &currentPos, Mouse oldPos, Point2D currentRot);

#endif // INPUT_H