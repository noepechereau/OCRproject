#ifndef OCR_ROTATION_H_INCLUDED
#define OCR_ROTATION_H_INCLUDED

#ifdef _WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif
#include <stdbool.h>
#include "../type/pixel.h"

void Image_Rotate(SDL_Surface* image, double angle);

#endif //OCR_ROTATION_H_INCLUDED
