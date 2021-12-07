#ifndef DATASAVING_H
#define DATASAVING_H
#include "builtin.h"

int writeList(double* data, size_t size, char* name);
int writeNetwork(NeuralNetwork* network);
double* readList(char* name, size_t size);
NeuralNetwork* readNetwork();

#endif
