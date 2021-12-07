#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <err.h>
#include "builtin.h"

double sigmoideDerivate(double x)
{
    return x * (1 - x);
}


double sigmoid(double x)
{
   return 1 / (1 + exp(-x));
}

double randd()
{
    //srand(time(NULL)) ;
    return (((double)rand() / (RAND_MAX)) * 2) - 1;
}


NeuralNetwork* GenerateNetwork(size_t inputNumber, size_t hiddenNumber, size_t outputNumber)
{
    NeuralNetwork* network = malloc(sizeof(NeuralNetwork));
    if (network == NULL)
        errx(1, "Memory allocation failed");
    network->inputNumber = inputNumber;
    network->hiddenNumber = hiddenNumber;
    network->outputNumber = outputNumber;

    network->activations = calloc(inputNumber + hiddenNumber + outputNumber, sizeof(double));
    if (network->activations == NULL)
        errx(1, "Memory allocation failed");

    network->bias = malloc((hiddenNumber + outputNumber) * sizeof(double));
    if (network->bias == NULL)
        errx(1, "Memory allocation failed");
    for(size_t i = 0; i < hiddenNumber + outputNumber; i++)
    {
        network->bias[i] = randd();
    }

    network->inputWeights = malloc((inputNumber * hiddenNumber) * sizeof(double));
    if (network->inputWeights == NULL)
        errx(1, "Memory allocation failed");
    for(size_t i = 0; i < inputNumber * hiddenNumber; i++)
    {
        network->inputWeights[i] = randd();
    }

    network->hiddenWeights = malloc((outputNumber * hiddenNumber) * sizeof(double));
    if (network->hiddenWeights == NULL)
        errx(1, "Memory allocation failed");
    for(size_t i = 0; i < outputNumber * hiddenNumber; i++)
    {
        network->hiddenWeights[i] = randd();
    }

    network->asciiOutputs = malloc(outputNumber * sizeof(double));
    if(network->asciiOutputs == NULL)
        errx(1, "Memory allocation failed");
    for ( size_t i = 0 ; i < 9 ; i ++ ) 
    {
    	network->asciiOutputs[i] = (double)(i + 1) ;
    }

    return network;

}

void freeNetwork(NeuralNetwork* network)
{
    free(network->activations);

    free(network->bias);

    free(network->inputWeights);

    free(network->hiddenWeights);

    free(network->asciiOutputs);

    free(network);
}



void printList(double* list, size_t start, size_t len)
{
    printf("[");
    for (size_t i = start; i < len; i++)
    {
        if ( i % 28 == 0 ) 
        {
            printf("\n");
        }
        printf(" %f ", list[i]);
    }
    printf("]\n");
}



void printNetwork(NeuralNetwork* network)
{
    printf("=====Network=====\n");
    printf("Input : \n   ");
    printList(network->activations, 0, network->inputNumber);

    printf("Weights :");
    //printList(network->inputWeights, 0, network->inputNumber * network->hiddenNumber);


    printf("Hidden row : \n");
    printf("  Activations : \n    ");
    printList(network->activations, network->inputNumber, network->inputNumber + network->hiddenNumber);
    printf("  Bias : \n    ");
    printList(network->bias, 0, network->hiddenNumber);

    printf("Weights :\n");
    printList(network->hiddenWeights, 0, network->outputNumber * network->hiddenNumber);

    printf("Output : \n");
    printf("  Activations : \n    ");
    printList(network->activations, network->inputNumber + network->hiddenNumber, network->inputNumber + network->hiddenNumber + network->outputNumber);
    printf("  Bias : \n    ");
    printList(network->bias, network->hiddenNumber, network->hiddenNumber + network->outputNumber);
    
    printf("Ascii outputs : \n");
    printList(network->asciiOutputs, 0, network->outputNumber);

}
