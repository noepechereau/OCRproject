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

/*
#include<stdio.h>

#ifndef BUILTINS_NEURAL_NETWORKS_H
#define BUILTINS_NEURAL_NETWORKS_H

////////////STRUCT
typedef struct Node Node;
struct Node
{
    double * activation;
    double *bias;
    size_t neuronsLen;
    double **neurons;
};
typedef struct NetworkData NetworkData;
struct NetworkData
{
    double excpect;
    double x;
    double y;
    double activations[2];
    double weights[5];
    double bias[2];
};


double sigmoideDerivate(double x) ;
double sigmoid(double x);
double randd();
void printRes(double res, double x, double y);
void printNode(Node *node, char name);
void printNetwork(Node *h, Node *z);
void updateTreeNode(Node *h, Node *z);
double updateNode(Node *node);

#endif
*/
