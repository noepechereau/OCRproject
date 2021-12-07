#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "builtin.h"

int writeList(double* data, size_t size, char* name)
{
    FILE* fp;
    fp = fopen(name, "w");
    if (fp == NULL)
    	return 1;
    fwrite(data, sizeof(double) * size, 1, fp);
    fclose(fp);
    return 0;
}

double* readList(char* name, size_t size)
{
    FILE *fp;
    fp = fopen(name, "r");
    if (fp != NULL)
    {
        double* data = malloc(sizeof(double) * size);
        if (data == NULL)
            errx(1, "Memory allocation failed");
        fread(data, sizeof(double) * size, 1, fp);
        fclose(fp);
        return data;
    }
    return NULL;
}

int writeNetwork(NeuralNetwork* network)
{
    FILE *netFp;
    netFp = fopen("save/network.save", "w");
    if (netFp == NULL)
    	return 1;
    fwrite(network, sizeof(size_t) * 4, 1, netFp);
    fclose(netFp);
    if (writeList(network->activations, network->inputNumber + network->hiddenNumber + network->outputNumber, "save/activations.save") == 1)
    	return 1;
    if (writeList(network->bias, network->hiddenNumber + network->outputNumber, "save/bias.save") == 1)
    	return 1;
    if (writeList(network->hiddenWeights, network->hiddenNumber * network->outputNumber, "save/hiddenWeights.save") == 1)
    	return 1;
    if (writeList(network->inputWeights, network->inputNumber * network->hiddenNumber, "save/inputWeights.save") == 1)
    	return 1;
    if (writeList(network->asciiOutputs, network->outputNumber, "save/asciiOutputs.save") == 1)
    	return 1;
    return 0;
}

NeuralNetwork* readNetwork()
{
    FILE* netFp;
    netFp = fopen("save/network.save", "r");
    if(netFp == NULL)
        return NULL;
    NeuralNetwork* network = malloc(sizeof(NeuralNetwork));
    if (network == NULL)
        errx(1, "Memory allocation failed");
    fread(network, sizeof(size_t) * 4, 1, netFp);
    
    //network->activations = malloc(sizeof(double) * (network->inputNumber + network->hiddenNumber + network->outputNumber));
    network->activations = readList("save/activations.save", network->inputNumber + network->hiddenNumber + network->outputNumber);
    if (network->activations == NULL)
        errx(1, "Unable to load activations\n");
    
    //network->bias = malloc(sizeof(double) * (network->hiddenNumber + network->outputNumber));
    network->bias = readList("save/bias.save", network->hiddenNumber + network->outputNumber);
    if (network->bias == NULL)
        errx(1, "Unable to load bias\n");
    
    //network->inputWeights = malloc(sizeof(double) * (network->inputNumber * network->hiddenNumber));
    network->inputWeights = readList("save/inputWeights.save", network->inputNumber * network->hiddenNumber);
    if (network->inputWeights == NULL)
        errx(1, "Unable to load inputWeights\n");
    
    //network->hiddenWeights = malloc(sizeof(double) * (network->hiddenNumber * network->outputNumber));
    network->hiddenWeights = readList("save/hiddenWeights.save", network->hiddenNumber * network->outputNumber);
    if (network->hiddenWeights == NULL)
        errx(1, "Unable to load hiddenWeights\n");
    
    //network->asciiOutputs = malloc(sizeof(double) * network->outputNumber);
    network->asciiOutputs = readList("save/asciiOutputs.save", network->outputNumber);
    if (network->asciiOutputs == NULL)
        errx(1, "Unable to load asciiOutputs\n");
    
    return network;
}
