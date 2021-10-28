#ifndef OCR_GRILLE_DETECTION_H_INCLUDED
#define OCR_GRILLE_DETECTION_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../struct/pixel.h"

PixelBlock Detect_Grille(SDL_Surface* image, SDL_Renderer* renderer);

#endif //OCR_GRILLE_DETECTION_H_INCLUDED
