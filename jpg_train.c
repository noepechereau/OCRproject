#include <stdio.h>
#include <string.h>

#include "SDL2/SDL_image.h"
#include "useful/basics.h"
#include "image_system/image_system.h"
#include "image_system/image_manipulation.h"
#include "image_system/color_system.h"

int* image_for_train(SDL_Surface* image)
{
    int* list = malloc(28*28*sizeof(int));
    int w = image->w;
    int h = image->h;
    int c;
    int index = 0;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image, j, i));
            if (c <= 125)
                list[index] = 1;
            else
                list[index] = 0;
            index++;
        }
     }
    return list;
}
