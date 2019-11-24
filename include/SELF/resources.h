#ifndef RESOURCES_H
#define RESOURCES_H

void loadObj(Obj& obj, std::string filename);

#ifdef _WIN32
void hideConsole();
std::string getFileName();
#endif

#endif // RESOURCES_H