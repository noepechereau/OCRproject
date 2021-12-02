#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <err.h>
#include "backprop.h"

double* outputError(NeuralNetwork* network, double* expected, double* res)
{
    double* outputs = &(network->activations[network->inputNumber + network->hiddenNumber]);
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        res[i] = (expected[i] - outputs[i]) * sigmoideDerivate(outputs[i]);
    }
    return res;
}

double* biasDelta(size_t len, double* errors, double v, double* res)
{
    for (size_t i = 0; i < len; i++)
    {
        res[i] += delta(errors[i], 1, v);
    }
    return res;
}

double hiddenRes(NeuralNetwork* network, size_t i, double* outputError)
{
    double* weights = &(network->hiddenWeights[i * network->outputNumber]);
    double d = 0;
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        d += outputError[i] * weights[i];
    }
    return d * sigmoideDerivate(network->activations[i]);
}

double* hiddenError(NeuralNetwork* network, double* outputError, double* res)
{
    for(size_t i = 0; i < network->hiddenNumber; i++)
    {
        res[i] = hiddenRes(network, i, outputError);
    }
    return res;
}

double* outputWeightDelta(NeuralNetwork* network, double* errors, double v, double* res)
{
    for(size_t i = 0; i < network->outputNumber; i++)
    {
        for(size_t j = 0; j < network->hiddenNumber; j++)
        {
            res[(i * network->hiddenNumber) + j] += delta(errors[i], network->activations[network->inputNumber + j], v);
        }
    }
    return res;
}

double* hiddenWeightDelta(NeuralNetwork* network, double* errors, double v, double* res)
{
    for(size_t i = 0; i < network->hiddenNumber; i++)
    {
        for (size_t j = 0; j < network->inputNumber; j++)
        {
            res[(i * network->inputNumber) + j] += delta(errors[i], network->activations[j], v);
        }
    }
    return res;
}

double delta(double error, double d, double v)
{
    return error * d * v;
}

void backProp(NeuralNetwork* network, double v, double* expected)
{
	double* biasDeltaHidden = calloc(network->hiddenNumber, sizeof(double));
    double* biasDeltaOut = calloc(network->outputNumber, sizeof(double));
    double* deltaOut = calloc(network->outputNumber * network->hiddenNumber, sizeof(double));
    double* deltaHidden = calloc(network->hiddenNumber * network->inputNumber, sizeof(double));
    if(biasDeltaHidden == NULL || biasDeltaOut == NULL || deltaOut == NULL || deltaHidden == NULL)
        errx(1, "Memory allocation failed learn");

	double* outError = calloc(network->outputNumber, sizeof(double));
    if(outError == NULL)
        errx(1, "Memory allocation failed find delta 1");
    outputError(network, expected, outError);

    double* hidError = calloc(network->hiddenNumber, sizeof(double));
    if(hidError == NULL)
        errx(1, "Memory allocation failed find delta 2");
    hiddenError(network, outError, hidError);
    
    biasDelta(network->hiddenNumber, hidError, v, biasDeltaHidden);
    biasDelta(network->outputNumber, outError, v, biasDeltaOut);
    outputWeightDelta(network, outError, v, deltaOut);
    hiddenWeightDelta(network, hidError, v, deltaHidden);
    
    for (size_t i = 0; i < network->hiddenNumber; i++)
    {
        network->bias[i] += biasDeltaHidden[i];
    }

    for (size_t i = 0; i < network->outputNumber; i++)
    {
        network->bias[i + network->hiddenNumber] += biasDeltaOut[i];
    }

    for (size_t i = 0; i < network->hiddenNumber * network->inputNumber; i++)
    {
        network->inputWeights[i] += deltaHidden[i];
    }

    for (size_t i = 0; i < network->hiddenNumber * network->outputNumber; i++)
    {
        network->hiddenWeights[i] += deltaOut[i];
    }
    
    free(biasDeltaHidden);
    free(biasDeltaOut);
    free(deltaHidden);
    free(deltaOut);
    free(outError);
    free(hidError);
}