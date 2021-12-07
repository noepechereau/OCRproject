#include <err.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "grille_detection.h"
#include "grid_det.h"
#include "../image_system/image_system.h"
#include "../image_system/color_system.h"
#include "../image_system/image_manipulation.h"

SDL_Surface* GridDetCut(SDL_Surface* image)
{
    SDL_Surface* newCase = NULL;

    void SetCase(int wCase, int hCase, int x, int y)
    {
        newCase = SDL_CreateRGBSurface(0,wCase,hCase,32,0,0,0,0);
        int _x = x;
        int _y = y;
        for(int i = 0; i < wCase; i++)
        {
            for(int j = 0; j < hCase; j++)
            {
                //printf(" i:%u j:%u x:%u y:%u \n",i,j,_x,_y);
                Uint32 pixel = get_pixel(image, _x, _y);
                put_pixel(newCase, i, j, pixel);
                _y += 1;
                if(_y == (y + hCase))
                {
                    _y = y;
                    _x += 1;
                }
            }
        }
    }

    void GridCutout(SDL_Surface *image)
    {
        int width = image->w;
        int height = image->h;
        int wCase = width / 9;
        int hCase = height /9;
        int width2 = wCase * 9;
        int height2 = hCase * 9;
        int m1 = 0;
        int m2 = 0;
        for(int i = 0; i < width2; i += wCase)
        {
            for(int j = 0; j < height2; j += hCase)
            {
                SetCase(wCase,hCase,i,j);
                char str[13] = "Cases/";
                str[6] = m1 + '0';
                str[7] = m2 + '0';
                SDL_SaveBMP(newCase, str);
                //printf("saved\n");
                m2 += 1;
                if(m2 == 9)
                {
                    m2 = 0;
                }
            }
            m1 += 1;
        }
    }
    image = GridDetect(image);
    GridCutout(image);

    SDL_FreeSurface(newCase);
    return image;
}
