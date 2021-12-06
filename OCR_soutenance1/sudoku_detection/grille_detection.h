#ifndef OCR_GRILLE_DETECTION_H_INCLUDED
#define OCR_GRILLE_DETECTION_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <err.h>

#include <math.h>

#include "../struct/pixel.h"

void MakeHisto(SDL_Surface* image, int hCols[], int hRows[]);
void Find(int histo[], int size, int paraList[]);
void reSize(int wCase, int hCase, int x, int y,SDL_Surface* finalGrid,SDL_Surface* image);
SDL_Surface* GridDetect(SDL_Surface* image);
void drawHough (int *accu, SDL_Surface *image);
void drawIntersect(SDL_Surface *image, int *intersectList);
void detectAngle(SDL_Surface *image, int *accu, int *intersectList);
int parametricIntersect(float r1, int t1, float r2, int t2, int *x, int *y);
void recDetectLargestSquare(SDL_Surface *image, int *intersectList, int x1, int y1, int *x, int  *y, int *side);
void detectLargestSquare(SDL_Surface *image, int *intersectList, int *x, int  *y, int *side);
void drawLargestSquare(SDL_Surface *image, int *intersectList);
PixelBlock Detect_Grille(SDL_Surface* image, SDL_Renderer* renderer);
SDL_Surface *hough(SDL_Surface *image);

#endif //OCR_GRILLE_DETECTION_H_INCLUDED
