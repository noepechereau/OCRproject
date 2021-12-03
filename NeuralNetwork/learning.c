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

int main()
{
	NeuralNetwork* network = GenerateNetwork(25, 15, 9);
	
	/*
	printList(network->activations,0,25+15+9) ;
	printf("\n\n") ;
	printList(network->inputWeights,0,25*15) ;
	printf("\n\n") ;
	printList(network->hiddenWeights,0,15*9) ;
	printf("\n\n") ;
	printList(network->bias,0,25+9) ;
	printf("\n\n") ;
	printList(network->asciiOutputs,0,9) ;
	printf("\n\n") ;
	*/
	printf("%d\n",randd()) ;
	printf("%d\n",randd()) ;
	printf("%d\n",randd()) ;
	
	//printNetwork(network);
	double v = 0.02;
	double expected[9] = {0, 0, 1, 0, 0, 0, 0, 0, 0};
        int inputs[25] = {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0};
	//printNetwork(network);
    	learn(network, v, inputs, expected);
    	printf("\n\n\n\n\n");
	//printNetwork(network);
	
	/*
	printList(network->activations,0,25+15+9) ;
	printf("\n\n") ;
	printList(network->inputWeights,0,25*15) ;
	printf("\n\n") ;
	printList(network->hiddenWeights,0,15*9) ;
	printf("\n\n") ;
	printList(network->bias,0,25+9) ;
	printf("\n\n") ;
	printList(network->asciiOutputs,0,9) ;
	printf("\n\n") ;
	*/
	
	
	/*double* outError = calloc(network->outputNumber, sizeof(double));
    outputError(network, expected, outError);
    //printList(outError, 0, network->outputNumber);
    printf("\n") ;
    
    double* hidError = calloc(network->hiddenNumber, sizeof(double));
    hiddenError(network, outError, hidError);
    //printList(hidError, 0, network->hiddenNumber);
    printf("\n") ;
    
    double* biasDeltaHidden = calloc(network->hiddenNumber, sizeof(double));
    biasDelta(network->hiddenNumber, hidError, v, biasDeltaHidden);
    //printList(biasDeltaHidden, 0, network->hiddenNumber);
    printf("\n") ;
    
    double* biasDeltaOut = calloc(network->outputNumber, sizeof(double));
    biasDelta(network->outputNumber, outError, v, biasDeltaOut);
    //printList(biasDeltaOut, 0, network->outputNumber);
    printf("\n") ;
    
    double* deltaOut = calloc(network->outputNumber * network->hiddenNumber, sizeof(double));
    outputWeightDelta(network, outError, v, deltaOut);
    //printList(deltaOut, 0, network->outputNumber * network->hiddenNumber);
    printf("\n") ;
    
    double* deltaHidden = calloc(network->hiddenNumber * network->inputNumber, sizeof(double));
    hiddenWeightDelta(network, hidError, v, deltaHidden);
    //printList(deltaHidden, 0, network->hiddenNumber * network->inputNumber);
    forwardProp(network);
    
    outputError(network, expected, outError);
    //printList(outError, 0, network->outputNumber);
    printf("\n") ;
    
    
    hiddenError(network, outError, hidError);
    //printList(hidError, 0, network->hiddenNumber);
    printf("\n") ;
    

    biasDelta(network->hiddenNumber, hidError, v, biasDeltaHidden);
    //printList(biasDeltaHidden, 0, network->hiddenNumber);
    printf("\n") ;
    

    biasDelta(network->outputNumber, outError, v, biasDeltaOut);
    //printList(biasDeltaOut, 0, network->outputNumber);
    printf("\n") ;
    
 
    outputWeightDelta(network, outError, v, deltaOut);
    //printList(deltaOut, 0, network->outputNumber * network->hiddenNumber);
    printf("\n") ;
    
 
    hiddenWeightDelta(network, hidError, v, deltaHidden);
    //printList(deltaHidden, 0, network->hiddenNumber * network->inputNumber);
    
    free(outError);
    free(hidError);
    free(biasDeltaHidden);
    free(biasDeltaOut);
    free(deltaOut);
    free(deltaHidden);*/

    freeNetwork(network);
    return 0;
}
