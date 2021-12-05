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

void drawHough (int *accu, SDL_Surface *image)
{
  int width = image->w;
  int height = image->h;
  int rhos = sqrt(width*width + height*height);
  int thetaDeg;
  float rho;
  int x,y;
  Uint32 pixel = SDL_MapRGB(image->format,255,0,0);

  for (rho = 0; rho < rhos; rho++)
    {
      for (thetaDeg = 0; thetaDeg < THETAS; thetaDeg++)
        {
	  int val = accu[(int)rho + thetaDeg * rhos];
	  if (val > COUNT)
            {
	      for(x = 0; x < width; x++)
                {
		  y = (int)(rho - x * cosf(degToRad(thetaDeg))/sinf(degToRad(thetaDeg)));
		  if (y<0) y = 0;
		  else if (y>height) y = height;
		  put_pixel(image,x,y,pixel);
                }
	      if (thetaDeg == 0)
                {
		  for(y = 0; y < height; y++)
                    {
		      x = (int)(rho - y * sinf(degToRad(thetaDeg))/cosf(degToRad(thetaDeg)));
		      if (x<0) x = 0;
		      else if (x>width) x = width;
		      put_pixel(image,x,y,pixel);
                    }
                }
            }
        }
    }
}

int parametricIntersect(float r1, int t1, float r2, int t2, int *x, int *y)
{
  float ct1=cosf(degToRad(t1));
  float st1=sinf(degToRad(t1));
  float ct2=cosf(degToRad(t2));
  float st2=sinf(degToRad(t2));
  float d=ct1*st2-st1*ct2;
  if(d!=0.0f)
    {   
      *x=(int)((st2*r1-st1*r2)/d);
      *y=(int)((-ct2*r1+ct1*r2)/d);
      return(1);
    }
  else 
    {
      return(0);
    }
}

void detectAngle(SDL_Surface *image, int *accu, int *intersectList)
{
  int width = image->w;
  int height = image->h;
  int rhos = sqrt(width*width + height*height);
  int t1,t2;
  float r1,r2;
  int x,y;

  for (r1 = 0; r1 < rhos; r1++)
    {
      for (t1 = 0; t1 < THETAS; t1++)
        {
	  int val = accu[(int)r1 + t1 * rhos];
	  if (val > COUNT)
            {
	      for (r2 = 0; r2 < rhos; r2++)
                {
		  for (t2 = 0; t2 < THETAS; t2++)
                    {
		      int val = accu[(int)r2 + t2 * rhos];
		      if (val > COUNT && t1 != t2 && parametricIntersect(r1, t1, r2, t2, &x, &y))
                        {
			  if(x >= 0 && y >= 0 && x < width && y < height)
                            {
			      intersectList[x + y * width] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}


void drawIntersect(SDL_Surface *image, int *intersectList)
{
  int width = image->w;
  int height = image->h;
  int x,y;


  Uint32 pixel = SDL_MapRGB(image->format,0,255,0);

  for (x = 0; x < width; x++)
    {
      for (y = 0; y < height; y++)
        {
	  if (intersectList[x + y * width] == 1)
            {
	      for (int i = 0; i < 3; i++)
                {
		  for (int j = 0; j < 3; j++)
                    {
		      if (x+i < width && y+i < height)
                        {
			  put_pixel(image,x+i,y+j,pixel);
                        }
		      else
                        {
			  put_pixel(image,x,y,pixel);
                        }
                    }
                }
            }
        }
    }
}

void recDetectLargestSquare(SDL_Surface *image, int *intersectList, int x1, int y1, int *x, int  *y, int *side)
{
  int width = image->w;
  int height = image->h;
  int sideX, sideY;

  for (int x2 = x1 + 1; x2 < width; x2++)
    {
      for (int y2 = x1 + 1; y2 < height; y2++)
        {
	  for (int i = -MARGIN; i < MARGIN; i++)
            {
	      if (y1 + i >= 0 && y1 + i < height && intersectList[x2 + (y1+i) * width] == 1)
                {
		  sideX = abs(x2-x1);
		  //printf("(%d,%d):%d",x2,*x,sideX);
                
		  for (int i = -MARGIN; i < MARGIN; i++)
                    {
		      if (x1 + i >= 0 && x1 + i < width && intersectList[(x1+i) + y2 * width] == 1)
                        {
			  sideY = abs(y2-y1);
                        }
		      //printf("%d,%d\n",sideX,sideY);
		      if (sideX > sideY - SIDE_MARGIN && sideX < sideY + SIDE_MARGIN && sideX > *side + SQUARE_MARGIN)
                        {
			  *side = sideX;
			  *x = x1;
			  *y = y1;
                        }
                    }
                }
            }
        }
    }
}

void detectLargestSquare(SDL_Surface *image, int *intersectList, int *x, int  *y, int *side)
{
  int width = image->w;
  int height = image->h;
  for (int i = 0; i < width; i++)
    {
      for (int j = 0; j < height; j++)
        {
	  if (intersectList[i + j * width] == 1)
            {
	      recDetectLargestSquare(image,intersectList,i,j,x,y,side);
            }
        }
    }
}

void drawLargestSquare(SDL_Surface *image, int *intersectList)
{
  int x = 0;
  int y = 0;
  int side = 0;

  detectLargestSquare(image,intersectList,&x,&y,&side);
  printf("%d,%d:%d\n",x,y,side);

  Uint32 pixel = SDL_MapRGB(image->format,255,0,0);

  for (int i = x; i < x + side; i++)
    {
      put_pixel(image,i,y,pixel);
      put_pixel(image,i,y+side,pixel);
    }

  for (int i = y; i < y + side; i++)
    {
      put_pixel(image,x,i,pixel);
      put_pixel(image,x+side,i,pixel);
    }
}


void cutImage(SDL_Surface *image, int *intersectList)
{
  int x = 0;
  int y = 0;
  int side = 0;

  detectLargestSquare(image,intersectList,&x,&y,&side);

  int size = side/9;

  printf("yeeessssss");

  for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
        {
	  SDL_Surface *number = SDL_CreateRGBSurface(0,size,size,32,0,0,0,0);
	  for (int k = 0; k < size; k++)
            {
	      for (int l = 0; l < size; l++)
                {
		  Uint32 pixel = get_pixel(image,x + (i * size) + k, y + (j * size) + l);
		  put_pixel(number,k,l,pixel);
                }
            }
	  char path[100];
	  snprintf(path,sizeof(path), "tmp/number_%d%d.png",i,j);
	  IMG_SavePNG(number,path);
        }
    }
}

SDL_Surface *hough(SDL_Surface* image)
{     
  int width = image->w;
  int height = image->h;
  int rhos = sqrt(width*width + height*height);

  int thetaDeg;
  float rho;
  int x,y;
  Uint32 pixel;
  Uint8 r, g, b;
    
  int *tmp = calloc(rhos*THETAS, sizeof(int));
  if (tmp == NULL)
    errx(1, "Not enough Memory!");
    
  int *intersectList = calloc(width*height,sizeof(int));
  if (intersectList == NULL)
    errx(1, "Not enough Memory!");
  
  for (x = 0; x < width; x++)
    {
      for (y = 0; y < height; y++)
	{
	  pixel = get_pixel(image, x, y);
	  r = pixel >> 16 & 0xFF;
	  g = pixel >> 8 & 0xFF;
	  b = pixel & 0xFF;
	  int pixel_value = (r+g+b);
                  
	  if (pixel_value == 765)
	    {
	      for(thetaDeg = 0; thetaDeg < THETAS; thetaDeg++)
		{
		  float thetaRad = degToRad(thetaDeg);
		  rho = x * cosf(thetaRad) + y * sinf(thetaRad);
		  tmp[(int)rho + thetaDeg * rhos]++;
		}
	    }
	}
    }

  for (int rho = HOUGH_MARGIN; rho < rhos-HOUGH_MARGIN+1; rho++)
    {
      for (int theta = HOUGH_MARGIN; theta < THETAS-HOUGH_MARGIN+1; theta++)
        {
	  int i = -HOUGH_MARGIN;
	  int j = -HOUGH_MARGIN;
	  int val = tmp[rhos + theta * rhos];
            
	  if (val > COUNT)
            {
	      while(i < HOUGH_MARGIN+1)
                {
		  while(j < HOUGH_MARGIN+1)
                    {
		      if (i != 0 && j != 0)
                        {
			  tmp[rho + i + (theta + j) * rhos] = 0;
                        }
		      j++;
		    }
		  i++;
                }
            }
        }
    }
  SDL_Surface *hough1 = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  SDL_Surface *hough2 = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  SDL_BlitSurface(image, NULL, hough1, NULL);
  SDL_BlitSurface(image, NULL, hough2, NULL);

  drawHough(tmp,hough1);
  IMG_SavePNG(hough1, "hough.png");

  detectAngle(image,tmp,intersectList);
  IMG_SavePNG(image, "houghdetectAngles.png");

  drawIntersect(hough1,intersectList);
  IMG_SavePNG(hough1, "houghIntersect.png");

  drawLargestSquare(hough2,intersectList);
  IMG_SavePNG(hough2, "houghLargestSquare.png");

  cutImage(image,intersectList);

  free(tmp);

  free(intersectList);

  return image; 
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

