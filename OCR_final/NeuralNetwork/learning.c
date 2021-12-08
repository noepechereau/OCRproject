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
#include "read.h"
#include "../sudoku_detection/grille_detection.h"
#include "../rotation/rotation.h"


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
    int w = image->w;
    int h = image->h;
    double* list = malloc(w*h*sizeof(double));
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
    double learningRate = 0.50;

    char path[50];
    int x = (rand() % 9) + 1;
    int y = rand() % 2 ;
    snprintf(path,50,"bmp/%d_%d.bmp",x,y);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = Image_Load(path);
    image = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ARGB8888,0);
    ApplyCorrection(image);

    double* inputs = image_for_train(image);


    double* expected = calloc(9, sizeof(double)) ;
    expected[x-1] = 1 ;

    learn(network,learningRate,inputs,expected);

}
/*
int main()
{
	NeuralNetwork* network = GenerateNetwork(784, 150, 9);
	for (int i = 0; i < 50000; i++)
	{
		learnOneTime(network);
		printf("%d", i);
	}
	writeNetwork(network);
}
	*/
