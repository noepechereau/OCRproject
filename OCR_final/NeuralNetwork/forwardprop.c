#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "forwardprop.h"


void updateNode(NeuralNetwork* network, size_t i)
{
    if (i < network->inputNumber) 
        errx(1, "Bad node");
        
    double* weights = NULL;
    size_t len = 0;
    double* activations = NULL;
    double b = network->bias[i - network->inputNumber];
    
    if (i >= network->inputNumber + network->hiddenNumber)
    {
        weights = &(network->hiddenWeights[(i - (network->inputNumber + network->hiddenNumber)) * network->hiddenNumber]);
        activations = &(network->activations[network->inputNumber]);
        len = network->hiddenNumber;

    }
    else
    {
        weights = &(network->inputWeights[(i - network->inputNumber) * network->inputNumber]);
        activations = network->activations;
        len = network->inputNumber;
    }

    for (size_t i = 0; i < len; i++)
    {
        b += activations[i] * weights[i];
    }

    network->activations[i] = sigmoid(b);

}

void forwardProp(NeuralNetwork* network)
{
    for (size_t i = network->inputNumber; i < network->inputNumber + network->hiddenNumber + network->outputNumber; i++)
    {
        updateNode(network, i);
    }
}
