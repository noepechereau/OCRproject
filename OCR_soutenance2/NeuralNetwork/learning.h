#ifndef LEARNING_H
#define LEARNING_H
#include "builtin.h"
#include "backprop.h"
#include "forwardprop.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../struct/pixel.h"

void learn(NeuralNetwork* network, double v, double* inputs, double* expected);
double* image_for_train(SDL_Surface* image);

#endif