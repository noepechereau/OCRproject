#include <stdio.h>
#include "../struct/pixel.h"
#include <SDL2/SDL.h>
#include "../image_preprocessing/headers/preprocessing.h"
#include "headers/NeuralNetworkTools.h"
#include "headers/ForwardProp.h"
#include <err.h>


int* image_to_arrint(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;

    int* chr_image = malloc(width * height *sizeof(int));
    if(chr_image == NULL)
        errx(1, "Memory allocation failed get pixel");

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int pixelColor = Pixel_GetR(SDL_GetPixel32(image, i, j));
            Uint32 pixel = SDL_GetPixel32(image, i, j);
            if (pixelColor < 128) // cornercase idea : what if it's written white on black (block detection wouldn't work anyway)
            {
                chr_image[i * height + j] = 1;
            }
            else
            {
                chr_image[i * height + j] = 0;
            }
        }
    }
    return chr_image;
}


int* resize(int* chr, int widthChr, int heightChr)
{
    int* chr_resized = malloc(Neural_Network_Entry_Size * Neural_Network_Entry_Size * sizeof(int));
    if(chr_resized == NULL)
        errx(1, "Memory allocation failed resize");

    double newRatioX = (double) (widthChr) / Neural_Network_Entry_Size;
    double newRatioY = (double) (heightChr) / Neural_Network_Entry_Size;


    for (int i = 0; i < Neural_Network_Entry_Size; i++)
    {
        for (int j = 0; j < Neural_Network_Entry_Size; j++)
        {
            int resX = i * newRatioX;
            int resY = j * newRatioY;

            if(resX >= widthChr || resY >= heightChr)
            {
                chr_resized[i * Neural_Network_Entry_Size + j] = 0;
            }
            else
            {
                chr_resized[i * Neural_Network_Entry_Size + j] = chr[resX * heightChr + resY];
            }
        }
    }
    return chr_resized;
}
