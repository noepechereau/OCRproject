#ifndef OCR_GRILLE_DETECTION_H_INCLUDED
#define OCR_GRILLE_DETECTION_H_INCLUDED

#ifdef _WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif
#include <stdbool.h>
#include "../type/pixel.h"

PixelBlock Detect_Grille(SDL_Surface* image, SDL_Renderer* renderer);

#endif //OCR_GRILLE_DETECTION_H_INCLUDED
