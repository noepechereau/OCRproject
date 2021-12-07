#include<stdlib.h>

#ifndef BUILTIN_H
#define BUILTIN_H

#define Neural_Network_Entry_Size 28

double sigmoid(double x);
double sigmoideDerivate(double x);

typedef struct NeuralNetwork NeuralNetwork;
struct NeuralNetwork
{
    size_t inputNumber;
    size_t hiddenNumber;
    size_t outputNumber;
    double* activations;
    double* inputWeights;
    double* hiddenWeights;
    double* bias;
    double* asciiOutputs;
};

double randd();

void freeNetwork(NeuralNetwork* network);
NeuralNetwork* GenerateNetwork(size_t inputNumber, size_t hiddenNumber, size_t outputNumber);
void printList(double* list, size_t start, size_t len);
void printNetwork(NeuralNetwork* network);

#endif
