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


SDL_Surface* Detect_RLSA_Block(SDL_Surface* image, int n)
{
    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image);
    SDL_LockSurface(image_temp);

    int c = 0;
    int c2 = 0;
    bool breaking = false;

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            if (c == 255)
            {
                for (int x2 = x-n; x2 <= x + n; x2++)
                {
                    for (int y2 = y-n; y2 <= y + n; y2++)
                        if (Pixel_Exist(image,x2,y2))
                        {
                            c2 = Pixel_GetR(SDL_GetPixel32(image,x2,y2));
                            if (c2 == 0)
                            {
                                SDL_PutPixel32(image_temp,x,y,Pixel_RGBto32(255,0,0
                                        ,0));
                                breaking = true;
                                break;
                            }
                        }
                    if (breaking)
                    {
                        breaking = false;
                        break;
                    }
                }
            }
        }
    }
    SDL_UnlockSurface(image);
    SDL_UnlockSurface(image_temp);
    return image_temp;
}

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
            printf("debug DrawLine left\n");
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
            printf("debug DrawLine top\n");
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
            printf("debug DrawLine right\n");
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
            printf(" DrawLine top\n");
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
