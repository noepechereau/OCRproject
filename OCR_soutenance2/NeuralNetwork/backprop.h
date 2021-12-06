#ifndef BACKPROP_H
#define BACKPROP_H
#include "builtin.h"

double delta(double error, double d, double v);
double* outputError(NeuralNetwork* network, double* expected, double* res);
double hiddenRes(NeuralNetwork* network, size_t i, double* outputError);
double* hiddenError(NeuralNetwork* network, double* outputError, double* res);
double* outputWeightDelta(NeuralNetwork* network, double* errors, double v, double* res);
double* biasDelta(size_t len, double* errors, double v, double* res);
double* hiddenWeightDelta(NeuralNetwork* network, double* errors, double v, double* res);
void backProp(NeuralNetwork* network, double v, double* expected);

#endif
