#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "builtin.h"

int writeList(double* data, size_t size, char* name)
{
    FILE *fp;
    fp = fopen(name, "w");
    if (fp == NULL) return 1;
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
    network->activations = readList("save/activations.save", network->inputNumber + network->hiddenNumber + network->outputNumber);
    network->hiddenWeights = readList("save/hWeights.save", "save/hWeights_l.save");
    network->inputWeights = readList("save/iWeights.save", "save/iWeights_l.save");
    network->bias = readList("save/bias.save", "save/bias_l.save");
    network->asciiOutputs = readList("save/outAscii.save", "save/outAscii_l.save");

    if (network->bias == NULL)
        printf("Unable to load bias\n");

    if (network->hidenWeights == NULL)
        printf("Unable to load hiden weights\n");

    if (network->inputWeights == NULL)
        printf("Unable to load input wieghts\n");

    if (network->activations == NULL)
        printf("Unable to load activations\n");

    if (network->asciiOutputs == NULL)
        printf("Unable to load ascii output\n");

    return network;
}
