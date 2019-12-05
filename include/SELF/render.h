#ifndef RENDER_H
#define RENDER_H

void setRendererSettings(unsigned int* TextureID, int size);
void drawEverything(Obj object, Point2D rotation, SDL_Window* mainWindow, double zoom, int resolution);

#endif //RENDER_H