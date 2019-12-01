#include <iostream>
#include <string>
#include <SDL.h>

void writeText(SDL_Renderer *render, int text, SDL_Texture *font, int x, int y, int w = 39, int h = 62) {
	std::string stringText = std::to_string(text);
	for(size_t i = 0; stringText[i] != 0; i++) {
		SDL_Rect textCut = { (stringText[i] - 33) * 78, 0, 78, 124};
		SDL_Rect textPos = { x + ((w - 2) * static_cast<int>(i)), y, w, h};
		SDL_RenderCopy(render, font, &textCut, &textPos);
	}
}

void writeText(SDL_Renderer* render, std::string text, SDL_Texture* font, int x, int y, int w = 39, int h = 62){
	for(unsigned long long i = 0; text[i] != 0; i++){
		SDL_Rect textCut = { (text[i] - 33) * 78, 0, 78, 124};
		SDL_Rect textPos = { x + ((w - 2) * static_cast<int>(i)), y, w, h };
		SDL_RenderCopy(render, font, &textCut, &textPos);
	}
}

void writeLoadingText(SDL_Renderer* renderer, std::string text, SDL_Texture* font, int x, int y, int w = 39, int h = 62){
	writeText(renderer, text, font, x, y, w, h);
	SDL_RenderPresent(renderer);
}