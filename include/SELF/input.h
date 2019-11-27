#ifndef INPUT_H
#define INPUT_H

void eventHandler(int &menu, double &zoom, Mouse &mouse, Obj obj, int &resolutionSetting);
Point2D getRotationFromCursor(Mouse &currentPos, Mouse oldPos, Point2D currentRot);

#endif // INPUT_H