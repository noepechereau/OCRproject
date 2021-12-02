#include "builtin.h"
#include "backprop.h"
#include "forwardprop.h"
#ifndef LEARNING_H
#define LEARNING_H

void learn(NeuralNetwork* network, double v, int* inputs, double* expected);

#endif