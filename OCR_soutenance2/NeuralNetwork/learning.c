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

int main()
{
    NeuralNetwork* network = GenerateNetwork(784,20,9) ;
    printNetwork(network) ;
    SDL_Init(SDL_INIT_VIDEO);
    char path[50];
    double v = 0.15 ;

    
    /*for (int x = 0 ; x < 95 ; x ++ ) 
    {
        snprintf(path,50,"../images/image%d/%d_%d.jpg",i,i,x);
        SDL_Surface* image = IMG_Load(path);
   
        double* expected = calloc(9, sizeof(double)) ;
        expected[i-1] = 1 ;  

        double* inputs = image_for_train(image);
        learn(network,v,inputs,expected) ;
    }*/

    for ( int i = 0 ; i < 50000 ; i ++ ) 
    {
        //srand(time(NULL));
        int x = (rand() % 9) + 1;
        //srand(time(NULL));
        int y = rand() % 95;
        printf("%d %d\n",x,y) ;
        snprintf(path,50,"../images/%d_%d.jpg",x,y);
        SDL_Surface* image = IMG_Load(path);
   
        double* expected = calloc(9, sizeof(double)) ;
        expected[x-1] = 1 ;  

        double* inputs = image_for_train(image);
        for (int j = 775; j < 784; j++)
        {
            inputs[j] = 0;
        }
        learn(network,v,inputs,expected) ;

    }

    /*for (int x = 0 ; x < 95 ; x ++ ) 
    {
        snprintf(path,50,"../images/image%d/%d_%d.jpg",j,j,x);
        SDL_Surface* image = IMG_Load(path);
   
        double* expected = calloc(9, sizeof(double)) ;
        expected[j-1] = 1 ;  

        double* inputs = image_for_train(image);
        learn(network,v,inputs,expected) ;
    }*/

    snprintf(path,50,"../images/%d_%d.jpg",7,6);
    SDL_Surface* image = IMG_Load(path);
    double* inputs = image_for_train(image);
    for (size_t i = 0; i < network->inputNumber; i++)
    {
        network->activations[i] = inputs[i];
    }
    forwardProp(network);

    printNetwork(network) ;
    
    return 0 ;
}
