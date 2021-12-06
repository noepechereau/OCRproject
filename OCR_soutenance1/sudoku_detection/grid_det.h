#ifndef GRID_DET_H
#define GRID_DET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <err.h>

#include <math.h>

#include "../struct/pixel.h"

SDL_Surface* GridDetCut(SDL_Surface* image);

#endif //OCR_GRILLE_DETECTION_H_INCLUDED
