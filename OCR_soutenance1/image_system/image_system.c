#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../useful/basics.h"
#include "image_system.h"


#define MARGE 10;

void Image_ToRenderer(SDL_Surface * image, SDL_Renderer* renderer)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == NULL) {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
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


Uint8 *pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}


void Case_Save(int x, int x2, int y, int y2, SDL_Surface* image, char* name)
{
    SDL_Rect rect;
    rect.y = y2 + MARGE;
    rect.x = x2 + MARGE;
    rect.w = x - x2 - 2*MARGE;
    rect.h = y - y2 - 2*MARGE;

    SDL_Surface* new_image = SDL_CreateRGBSurface(0,rect.w, rect.h, 32,0,0,0,0);

    SDL_BlitScaled(image, &rect, new_image, NULL);
    SDL_SaveBMP(new_image, name);
    SDL_FreeSurface(new_image);
}
void Save_Cases(SDL_Surface* image)
{
    int wc = image->w/9;
    int hc = image->h/9;
    int index = 0;

    for (int i = 0; i < image->h; i+= hc)
    {
        for (int j = 0; j < image->w; j+= wc)
        {
            if (index == 81)
                break;
            char str1[19];
            snprintf(str1, 19, "cases/case_%d.bmp", index);
            Case_Save(j+wc, j, i+wc, i, image, str1);
            index++;
        }
    }
}
