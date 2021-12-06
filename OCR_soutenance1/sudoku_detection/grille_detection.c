#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../image_system/image_system.h"
#include "../image_system/color_system.h"

#include "grille_detection.h"

#define M_PI 3.14159265358979323846


#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)
#define COUNT 315
#define MARGIN 5
#define SIDE_MARGIN 7
#define THETAS 91
#define HOUGH_MARGIN 5
#define SQUARE_MARGIN 10

void MakeHisto(SDL_Surface* image, int hCols[], int hRows[])
{
    int width = image->w;
    int height = image->h;


    for(int x = 0; x < width;x++) //Histo of Columns
    {
        int sum = 0;
        int max = 0;
        for(int y = 0; y < height; y++)
        {
            Uint32 pixel = get_pixel(image,x,y);

            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r,&g,&b);

            if(r + g + b < 500)
                sum++;
            else
            {
                if(sum > max)
                    max = sum;
                sum = 0;
            }
        }
        if(max > (width / 4)) //Detection cols
            hCols[x] = max;
        else
            hCols[x] = 0;
    }

    for(int y = 0; y < height;y++) //Histo of Rows
    {
        int sum = 0;
        int max = 0;
        for(int x = 0; x < width; x++)
        {
            Uint32 pixel = get_pixel(image,x,y);

            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r,&g,&b);

            if(r + g + b < 500)
                sum++;
            else
            {
                if(sum > max)
                    max = sum;
                sum = 0;
            }
        }
        if(max > (height / 4)) //Detection rows
            hRows[y] = max;
        else
            hRows[y] = 0;
    }
    //for(int i = 0; i < width; i++)
    //printf("%u ",hCols[i]);

}


void Find(int histo[], int size, int paraList[])
{
    //Find first index and the size of width or height


    int find = 0;

    int indexDebut = 0;
    int indexFin = 0;

    int taille = 0;

    int i = 0;

    while(find == 0)
    {
        if(histo[i] != 0)
        {
            indexDebut = i;
            find = 1;
        }
        i++;
    }

    i = size;
    find = 0;
    while(find == 0)
    {
        if(histo[i] != 0)
        {
            indexFin = i;
            find = 1;
        }
        i--;
    }
    taille = indexFin - indexDebut;
    paraList[0] = indexDebut;
    paraList[1] = taille;
}

void reSize(int wCase, int hCase, int x, int y,SDL_Surface* finalGrid,SDL_Surface* image)
{
    int _x = x;
    int _y = y;
    for(int i = 0; i < wCase; i++)
    {
        for(int j = 0; j < hCase; j++)
        {
            //printf(" i:%u j:%u x:%u y:%u \n",i,j,_x,_y);
            Uint32 pixel = get_pixel(image, _x, _y);
            put_pixel(finalGrid, i, j, pixel);
            _y += 1;
            if(_y == (y + hCase))
            {
                _y = y;
                _x += 1;
            }
        }
    }
}

SDL_Surface* GridDetect(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    int hCols[width];
    int hRows[height];
    int paraListCols[2];
    int paraListRows[2];

    MakeHisto(image,hCols,hRows);
    Find(hCols, width-1, paraListCols);
    Find(hRows, height-1, paraListRows);

    printf("%u %u \n", paraListCols[0], paraListCols[1]);
    printf("%u %u \n", paraListRows[0], paraListRows[1]);

    SDL_Surface* finalGrid = SDL_CreateRGBSurface(0,paraListCols[1], paraListRows[1],32,0,0,0,0);

    reSize(paraListCols[1], paraListRows[1], paraListCols[0], paraListRows[0], finalGrid, image);

    SDL_SaveBMP(finalGrid, "grid.bmp");

    return finalGrid;
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

