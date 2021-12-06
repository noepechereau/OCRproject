#ifndef READ_H
#define READ_H

#include"NeuralNetworkTools.h"
#include "../../type/pixel.h"
#include "../../type/data.h"
#include <SDL2/SDL.h>

int* image_to_arrint(SDL_Surface* image);
int* resize(int* chr, int widthChr, int heightChr);

#endif
