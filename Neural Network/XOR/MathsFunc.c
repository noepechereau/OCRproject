#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Types.h"
#include "MathsFunc.h"

double sigmoid(double net)
{
	return 1 / (1 + exp(net));
}

double sigmoidD(double net)
{
	return sigmoid(net) * (1 - sigmoid(net));
}

double rdm()
{
	return ((double)rand()) / RAND_MAX;
}

double activationValue(Node Node)
{
	double net;
	net = 
	return sigmoid();
}
