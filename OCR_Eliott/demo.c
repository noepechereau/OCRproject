#include <stdio.h>
#include <string.h>

#include "rotation/rotation.h"
#include "sudoku_detection/grille_detection.h"
#include "useful/builtin.h"
#include "image_system/image_system.h"
#include "image_system/image_manipulation.h"

void ImageDemo()
{
    char path[99] = {0};
    char rlsa[2] = {0};
    char angle[3] = {0};
    Console_ReadString(path,"\nImage path : ", 99);
    /*Console_ReadString(angle,"Rotation (angle in degree) :", 3);
    double ang = sscanf("%ls", angle);*/
    Console_ReadString(rlsa,"Show RLSA (y or n) :", 2);


    //------------------------------------------------------------------------
    //---- SDL INIT
    //------------------------------------------------------------------------
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = Image_Load(path);
    SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          image->w, image->h, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


    //------------------------------------------------------------------------
    //---- PREPARE TO GRILLE DETECTION
    //------------------------------------------------------------------------

    ApplyCorrection(image);
    //Image_Rotate(image, ang);
    SDL_Surface* image_rlsa = Detect_RLSA_Block(image,7);
    if (strcmp(rlsa,"y"))
    {
        Image_ToRenderer(image_rlsa, renderer);
    }
    else
    {
        Image_ToRenderer(image,renderer);
    }

    //------------------------------------------------------------------------
    //---- GRILLE DETECTION
    //------------------------------------------------------------------------

    PixelBlock grille = Detect_Grille(image_rlsa, renderer);

    SDL_Rect rect;
    rect.y = grille.left_top.y;
    rect.x = grille.left_top.x;
    rect.w = grille.right_top.x - grille.left_top.x;
    rect.h = grille.left_bottom.y - grille.left_top.y;

    SDL_Surface* new_image = SDL_CreateRGBSurface(0,rect.w, rect.h, 32,0,0,0,0);

    int h = SDL_BlitSurface(image, &rect, new_image, NULL);
    printf("%d %s\n",h,  SDL_GetError());
    SDL_SaveBMP(new_image, "out.bmp");

    SDL_RenderPresent(renderer);

    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    PauseSDL();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}
