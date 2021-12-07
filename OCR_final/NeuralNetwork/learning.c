#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <time.h>
#include "learning.h"
#include "SDL2/SDL_image.h"
#include "../useful/basics.h"
#include "../image_system/image_system.h"
#include "../image_system/image_manipulation.h"
#include "../image_system/color_system.h"
#include "datasaving.h"

void learn(NeuralNetwork* network, double v, double* inputs, double* expected)
{
    for (size_t i = 0; i < network->inputNumber; i++)
    {
        network->activations[i] = inputs[i];
    }

    forwardProp(network);

    backProp(network, v, expected);
}

double* image_for_train(SDL_Surface* image)
{
    double* list = malloc(784*sizeof(double));
    int w = image->w;
    int h = image->h;
    int c;
    int index = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image, j, i));
            if (c == 0)
                list[index] = (double)1;
            else
                list[index] = (double)0;
            index++;
        }
     }
    return list;
}


void learnOneTime(NeuralNetwork* network)
{
    double learningRate = 0.15;

    char path[50];
    int x = (rand() % 9) +1;
    int y = rand() % 900 + 2;
    snprintf(path,50,"database/realdata%d-%d.bmp",y,x);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = Image_Load(path);
    image = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ARGB8888,0);
    ApplyCorrection(image);

    double* inputs = image_for_train(image);


    double* expected = calloc(9, sizeof(double)) ;
    expected[x-1] = 1 ;

    learn(network,learningRate,inputs,expected);

}
int main ()
{
    int itterations = 0 ;
    NeuralNetwork* network = GenerateNetwork(784,150,9) ;
    for (int i = 0 ; i < 100000 ; i ++)
    {
        learnOneTime(network) ;
        printf("%d\n",itterations) ;
        itterations ++ ;
    }
    writeNetwork(network) ;
    char path[50];
    snprintf(path,50,"database/realdata950-%d.bmp",1);
    SDL_Surface* image = Image_Load(path);
	image = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ARGB8888,0);
	ApplyCorrection(image);

	double* inputs = image_for_train(image);
	for ( size_t i = 0 ; i < network->inputNumber ; i++ ) 
	    {
	    	network->activations[i] = inputs[i] ;
	    }
	forwardProp(network) ;
	printList(network->activations,784+150,784+150+9);
	
	
	snprintf(path,50,"database/realdata950-%d.bmp",2);
    image = Image_Load(path);
	image = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ARGB8888,0);
	ApplyCorrection(image);

	inputs = image_for_train(image);
	for ( size_t i = 0 ; i < network->inputNumber ; i++ ) 
	    {
	    	network->activations[i] = inputs[i] ;
	    }
	forwardProp(network) ;
	printList(network->activations,784+150,784+150+9);
	
	snprintf(path,50,"database/realdata950-%d.bmp",3);
    image = Image_Load(path);
	image = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ARGB8888,0);
	ApplyCorrection(image);

	inputs = image_for_train(image);
	for ( size_t i = 0 ; i < network->inputNumber ; i++ ) 
	    {
	    	network->activations[i] = inputs[i] ;
	    }
	forwardProp(network) ;
	printList(network->activations,784+150,784+150+9);
	
	
	
}
