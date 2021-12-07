#ifndef OCR_ROTATION_H_INCLUDED
#define OCR_ROTATION_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../struct/pixel.h"

SDL_Surface* Image_Rotate(SDL_Surface* image, double angle);

#endif //OCR_ROTATION_H_INCLUDED
