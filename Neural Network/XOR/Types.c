#include <stdio.h>
#include <stdlib.h>

#include "Types.h"
#include "MathsFunc.h"

Node newNode(double *inputs, size_t nbInputs)
{
	Node *node;
	
	node = malloc(sizeof(*node));
	
	node->activation = 0.5;
	node->bias = rdm();
	node->nbInputs = nbInputs;
	
	node->acts = malloc(sizeof(double*) * nbInputs);
	node->weights = malloc(sizeof(double*) * nbInputs);
	
	for (size_t i = 0; i < nbInputs; i++)
	{
		node->acts[i] = inputs[i];
		node->weights[i] = rdm();
	}
	
	return node;
}
