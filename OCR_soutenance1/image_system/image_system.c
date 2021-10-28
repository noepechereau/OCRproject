#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../useful/basics.h"


void Image_ToRenderer(SDL_Surface * image, SDL_Renderer* renderer)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

SDL_Surface* Image_Load(char* path)
{
    if (!FileExist(path))
    {
        exit(1);
    }

    return SDL_LoadBMP(path);
}

SDL_Surface* Image_Copy(SDL_Surface* image)
{
    return SDL_ConvertSurface(image, image->format, SDL_SWSURFACE);
}
void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32*)p = pixel;
}
Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32*)p;
}
void Case_Save(int x, int x2, int y, int y2, SDL_Surface* image, char* name)
{
    SDL_Rect rect;
    rect.y = y2;
    rect.x = x2;
    rect.w = x - x2;
    rect.h = y - y2;

    SDL_Surface* new_image = SDL_CreateRGBSurface(0,rect.w, rect.h, 32,0,0,0,0);

    SDL_BlitSurface(image, &rect, new_image, NULL);
    SDL_SaveBMP(new_image, name);
}
void Save_Cases(SDL_Surface* image)
{
    int wc = image->w/9;
    int hc = image->h/9;
    int index = 0;

    while (index < 80)
    {
        for (int i = 3; i < image->h-3; i+= hc)
        {
            for (int j = 3; j < image->w-3; j+= wc)
            {
                char str1[19];
                snprintf(str1, 19, "cases/case_%d.bmp", index);
                Case_Save(j+wc, j, i+wc, i, image, str1);
                index++;
            }
        }
    }
}
