#include<stdlib.h>

#ifndef NEURAL_NETWORK_TOOLS_H
#define NEURAL_NETWORK_TOOLS_H

#define Neural_Network_Entry_Size 28

typedef struct ListSet ListSet;
struct ListSet
{
    size_t size;
    double* data;
};

double sigmoid(double x);
double sigmoideDerivate(double x);

typedef struct NeuralNetwork NeuralNetwork;
struct NeuralNetwork
{
    size_t inputNumber;
    size_t hidenNumber;
    size_t outputNumber;
    ListSet* activations;
    ListSet* inputWeights;
    ListSet* hidenWeights;
    ListSet* bias;
    ListSet* asciiOutputs;
};

double randd();

void freeNetwork(NeuralNetwork* network);
NeuralNetwork* GenerateNetwork(size_t inputNumber, size_t hidenNumber, size_t outputNumber, double * asciiOutputs);
void printList(double* list, size_t len);
void printNetwork(NeuralNetwork* network);

#endif
