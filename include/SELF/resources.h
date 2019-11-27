#ifndef RESOURCES_H
#define RESOURCES_H

void loadObj(Obj& obj, std::string filename, SDL_Renderer* renderer, SDL_Texture* font);
void hideConsole();
std::string getFileName();

#endif //RESOURCES_H