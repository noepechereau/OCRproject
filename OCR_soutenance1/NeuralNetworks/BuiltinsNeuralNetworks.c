#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"BuiltinsNeuralNetworks.h"

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
    return (((double)rand() / (RAND_MAX)) * 2) - 1;
}


void printRes(double res, double x, double y)
{
    int cleanRes = 1;
    double percent = round(res * 10000) / 100; // transformation résultat de sortie en pourcentage 
    if (res < 0.5)
    {
        cleanRes = 0;
        percent = 100 - percent;
    }
    printf("	|   %d   |   %d   |   %d   |  %0.4f  |  %0.2f%%  |\n", (int)x, (int)y, cleanRes, res, percent);
}



void printNode(Node *node, char name)
{
    printf("		Node %c :\n", name);
    printf("      			activation = %f\n", *(node->activation));
    printf("    			bias = %f\n", *(node->bias));
}

void printNetwork(Node *h, Node *z)
{
    printf("\n");
    printf("	Nodes : \n\n");
    printNode(h, 'h');
    printNode(z, 'z');
    printf("\n");
    printf("\n");
    printf("	===============================================\n");
}


double updateNode(Node *node)
{
    double res = *(node->bias);
    for(size_t i = 0; i < node->neuronsLen; i += 2)
    {
        res += *(node->neurons[i]) * *(node->neurons[i + 1]);
    }
    res = sigmoid(res);
    return res;
}

void updateTreeNode(Node *h, Node *z)
{
    *(h->activation) = updateNode(h);
    *(z->activation) = updateNode(z);
}
