#include <stdbool.h>
#ifdef _WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif
#include "../image_system/image_system.h"
#include "../image_system/color_system.h"
#include "../useful/builtin.h"
#include "grille_detection.h"


PixelBlock Detect_Grille(SDL_Surface* image, SDL_Renderer* renderer)
{

    SDL_LockSurface(image);

    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int c = 0;
    int x = 0;
    int y = image->h/2;
    while (x < image->w)
    {
        c = Pixel_GetR(SDL_GetPixel32(image, x, y));
        if (c == 0)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawLine(renderer, x, 0, x, image->h);
            x1 = x;
            x++;
            break;
        }
        else
            x++;
    }
    while(y > 0)
    {
        c = Pixel_GetR(SDL_GetPixel32(image, x, y));
        if (c == 255)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawLine(renderer, 0,y, image->w, y);
            y1 = y;
            y++;
            break;
        }
        else
            y--;
    }
    while (x < image->w)
    {
        c = Pixel_GetR(SDL_GetPixel32(image, x, y));
        if (c == 255)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawLine(renderer, x, 0, x, image->h);
            x2 = x;
            x--;
            break;
        }
        else
            x++;
    }
    while(y < image->h)
    {
        c = Pixel_GetR(SDL_GetPixel32(image, x, y));
        if (c == 255 || y == image->h+1)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawLine(renderer, 0,y, image->w, y);
            y2 = y;
            break;
        }
        else
            y++;
    }


    PixelBlock grille_block = {{x1,y1},{x2,y1},{x2,y2},{x1,y2}};

    SDL_UnlockSurface(image);
    return grille_block;

}
