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
PixelBlock Detect_Grille(SDL_Surface* image, SDL_Renderer* renderer);

#endif //OCR_GRILLE_DETECTION_H_INCLUDED
