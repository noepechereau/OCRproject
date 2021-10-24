#include <stdio.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct Node Node
struct Node
{
	double* activation;
	double* bias;
	size_t nbInputs;
	double** acts;
	double** weights;
}

Node newNode(double *inputs, size_t nbInputs);

#endif
