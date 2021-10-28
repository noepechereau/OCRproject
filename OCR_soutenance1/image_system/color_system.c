#include <SDL2/SDL.h>
#include "stdbool.h"
#include "image_system.h"
#include <stdlib.h>
#include "../useful/basics.h"

uint8_t Pixel_GetR(Uint32 c)
{
    return  c >> 16;
}

uint8_t Pixel_GetG(Uint32 c)
{
    return c >> 8;
}

uint8_t Pixel_GetB(Uint32 c)
{
    return c;
}

//Return UInt32 color from RGBA color
Uint32 Pixel_RGBto32(int a, int r, int g, int b)
{
  Uint32 c;
  c = a;
  c <<= 8;
  c |= r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}


int Pixel_absRGB(double c)
{
    if (c > 255)
    {
        return 255;
    }

    if (c < 0)
    {
        return 0;
    }

    return (int) c;
}

bool Pixel_Exist(SDL_Surface* image, int x, int y)
{
    if (x < 0 || x >= image->w || y < 0 || y >= image->h)
        return false;
    return true;
}

Uint32 Pixel_Grayscale(Uint32 color)
{
    int r = Pixel_GetR(color);
    int g = Pixel_GetG(color);
    int b = Pixel_GetB(color);
    int gray = (r + g + b) / 3;
    return Pixel_RGBto32(255,gray,gray,gray);
}


Uint32 Pixel_Treshold(Uint32 color, int n)
{
    int r = Pixel_GetR(color);
    if (r > n)
        return Pixel_RGBto32(255,255,255,255);
    else
        return Pixel_RGBto32(255,0,0,0);
}

Uint32 Pixel_Convolution(SDL_Surface* image,int matrix[3][3], int x, int y, double factor)
{
    Uint32 color = 0;
    double r = 0;
    int k = 0;
    int l = 0;

    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (Pixel_Exist(image,j,i))
            {
                color = SDL_GetPixel32(image,j,i);
                r += Pixel_GetR(color) * matrix[k][l]* factor;
            }
            l++;
        }
        k++;
        l = 0;
    }

    return Pixel_RGBto32(255,Pixel_absRGB(r),Pixel_absRGB(r),Pixel_absRGB(r));
}
