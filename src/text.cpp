#include <iostream>
#include <string>
#include <SDL.h>

void writeText(SDL_Renderer* render, std::string text, SDL_Texture* font, int x, int y, int w = 39, int h = 62){
	unsigned long long i = 0;
	while(text[i] != 0){
		SDL_Rect textCut = { (text[i] - 33) * 78, 0, 78, 124 };
		SDL_Rect textPos = { x + ((w - 2) * static_cast<int>(i)), y, w, h };
		SDL_RenderCopy(render, font, &textCut, &textPos);
		i++;
	}
}