#ifndef GLMENUTEXT_H
#define GLMENUTEXT_H

void writeText(SDL_Renderer *render, int text, SDL_Texture *font, int x, int y, int w = 39, int h = 62);
void writeText(SDL_Renderer* render, std::string text, SDL_Texture* font, int x, int y, int w = 39, int h = 62);

#endif //!GLMENUTEXT_H