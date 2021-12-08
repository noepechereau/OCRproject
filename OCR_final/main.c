#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <err.h>

#include "NeuralNetwork/datasaving.h"
#include "NeuralNetwork/read.h"
#include "rotation/rotation.h"
#include "sudoku_detection/grille_detection.h"
#include "useful/basics.h"
#include "image_system/image_system.h"
#include "image_system/image_manipulation.h"
#include "NeuralNetwork/builtin.h"
#include "NeuralNetwork/learning.h"
#include "SudokuSolver/sudoku.h"


int main()
{

	NeuralNetwork * network = readNetwork() ;
	SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = Image_Load("images/image_02.bmp");

    SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          image->w, image->h, 0);
	
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    //image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

    ApplyCorrection(image);

    SDL_Surface* image_rlsa = Detect_RLSA_Block(image,7);
    //SDL_Delay(500);

    Image_ToRenderer(image, renderer);

    PixelBlock grille = Detect_Grille(image_rlsa, renderer);
    //SDL_RenderPresent(renderer);


    Case_Save(grille.right_top.x, grille.left_top.x, grille.left_bottom.y,
              grille.left_top.y, image, "grille.bmp");
    SDL_Surface* Grille = Image_Load("grille.bmp");
    Image_ToRenderer(Grille, renderer);
    Save_Cases(Grille);

    char path[50];

    for (int i = 0; i<81; i++)
    {
        snprintf(path, 50, "cases/case_%d.bmp", i);
        SDL_Surface* digit = Image_Load(path);
        double* mat = image_for_train(digit);
        double* case_r = resize(mat, digit->w, digit->h);
        for (size_t j = 0; j < 784; j++)
        {
        	if (j % 28 == 21 || j % 28 == 0)
        	{
        		case_r[j] = (double) 0;
        	}
        }
        int count = 0;
        for (size_t j = 0; j < 784; j++)
        {
        	if (case_r[j] == 1)
        		count += 1;
        }
        //printList(case_r, 0, 784);
        for ( size_t j = 0 ; j < network->inputNumber ; j++ ) 
	    {
	    	network->activations[j] = case_r[j] ;
	    }
	    forwardProp(network) ;
	    if (count < 30)
	    {
	    	for ( size_t j = 0 ; j < 9 ; j++ ) 
	    	{
	    		network->activations[784+150+j] = 0 ;
	    	}
	    }
	    printList(network->activations,784+150,784+150+9);
	    double activations[9] ;
	    }
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(image);
    SDL_FreeSurface(image_rlsa);
    SDL_DestroyRenderer(renderer);
    PauseSDL();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}
