#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "learning.h"

void learn(NeuralNetwork* network, double v, int* inputs, double* expected)
{
    for (size_t i = 0; i < network->inputNumber; i++)
    {
        network->activations[i] = inputs[i];
    }

    forwardProp(network);

    backProp(network, v, expected);
}