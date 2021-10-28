#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"BuiltinsNeuralNetworks.h"
#include"BackPropagation.h"
#include"FileManagment.h"



void DemoNeural()
{
	srand(time(NULL));
    NetworkData data = 
    {
        .x = 1,
        .y = 0,
        .excpect = 1,
        .activations = {0, 0},
        .weights = {randd(), randd(), randd(), randd(), randd()},
        .bias = {randd(), randd()}
    };

    Node *h;

    h = malloc(sizeof(*h));

    h->bias = &data.bias[0];
    h->activation = &data.activations[0];
    h->neuronsLen = 4;

    h->neurons = malloc(sizeof(double *) * 4);
    
    h->neurons[0] = &data.x;
    h->neurons[1] = &data.weights[0];
    h->neurons[2] = &data.y;
    h->neurons[3] = &data.weights[1];

    Node *z;

    z = malloc(sizeof(*z));

    z->bias = &data.bias[1];
    z->activation = &data.activations[1];
    z->neuronsLen = 6;

    z->neurons = malloc(sizeof(double *) * 6);

    z->neurons[0] = &data.x;
    z->neurons[1] = &data.weights[2];
    z->neurons[2] = &data.activations[0];
    z->neurons[3] = &data.weights[3];
    z->neurons[4] = &data.y;
    z->neurons[5] = &data.weights[4];


    printf("\n	==== Initialisation of the neural network ====\n");
    printNetwork(h, z, &data);
    printf("\n");
    printf("\n	= Learning with v = 0.6 and 20000 iterations ==\n");
    learnAverage(h, z, &data, 0.6, 20000);
	printf("\n");
    printf("\n	=========== Network after learning ============\n");
    printNetwork(h, z, &data);
    printf("\n");

	printf("	             ***    Results    ***             \n\n");

	printf("	+-------+-------+-------+----------+----------+\n");
	printf("	|   X   |   Y   |   Z   |  Output  | Accuracy |\n");
	printf("	+-------+-------+-------+----------+----------+\n");

	for (double i = 0; i <= 1; i++)
	{
		for (double j = 0; j <= 1; j++)
		{
			data.x = i;
			data.y = j;
			updateTreeNode(h, z);
			printRes(*(z->activation), i, j);
		}
	}
	printf("	+-------+-------+-------+----------+----------+\n\n");

    // writeData(&data);

    free(h->neurons);
    free(z->neurons);
    free(h);
    free(z);
}
