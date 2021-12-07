
#include <SDL2/SDL.h>
#include "image_system.h"
#include "color_system.h"

//------------------------------------------------------------------------
//---- OPERATION FUNCTIONS ON IMAGE
//------------------------------------------------------------------------

void Image_GrayScale(SDL_Surface* image)
{
    Uint32 color = 0;
    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = SDL_GetPixel32(image,x,y);
            color = Pixel_Grayscale(color);
            SDL_PutPixel32(image,x,y,color);
        }
    }
}

Uint32 Pixel_Threshold(Uint32 color, int threshold)
{
    int gray = Pixel_GetR(color);
    if (gray <= threshold)
        return Pixel_RGBto32(255,0,0,0);
    return Pixel_RGBto32(255,255,255,255);
}


//Useful function for Otsu Binarization
int* Image_GetHistogram(SDL_Surface* image)
{
    int *histogram = calloc(256, sizeof(int));
    Uint32 color;
    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = SDL_GetPixel32(image, x, y);
            histogram[Pixel_GetR(color)]++;
        }
    }
    return histogram;
}

//Return the Thresold to apply on the image
int Image_GetThreshold(SDL_Surface* image)
{
    int threshold = 0;
    double current_max = 0.;
    int sum = 0;
    int sum_background = 0;
    int weight_background = 0;
    int nb_pixels = image->h * image->w;

    int* histogram = Image_GetHistogram(image);
    for (int i = 0; i < 256; i++)
        sum += i * histogram[i];

    for (int i = 0; i < 256; i++)
    {
        weight_background += histogram[i];
        int weight_foreground = nb_pixels - weight_background;
        if (weight_background == 0 || weight_foreground == 0)
            continue;

        sum_background += i * histogram[i];
        int sum_foreground = sum - sum_background;

        double f_weight_background = weight_background;
        double f_weight_foreground = weight_foreground;
        double mean_background = sum_background / f_weight_background;
        double mean_foreground = sum_foreground / f_weight_foreground;
        double mean_diff = mean_background - mean_foreground;

        double variance = f_weight_background *
                          f_weight_foreground *
                          mean_diff * mean_diff;
        if (variance > current_max)
        {
            current_max = variance;
            threshold = i;
        }
    }

    free(histogram);
    return threshold;
}

//General image Threshold
void Image_Threshold(SDL_Surface* image, int threshold)
{
    Uint32 color;
    int threshold_temp = threshold;

    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image_temp);

    if (threshold == -1)
        threshold_temp = Image_GetThreshold(image);

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = SDL_GetPixel32(image,x,y);
            color = Pixel_Threshold(color,threshold_temp);
            SDL_PutPixel32(image,x,y,color);
        }
    }
    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}

void Image_Convolution(SDL_Surface* image, int matrix[3][3], double factor)
{
    Uint32 color = 0;

    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image_temp);

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = Pixel_Convolution(image_temp,matrix,x,y,factor);
            SDL_PutPixel32(image,x,y,color);
        }
    }

    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}

void Image_Median(SDL_Surface* image)
{
    Uint32 color = 0;

    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image_temp);

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = Pixel_Median(image_temp, x, y);
            SDL_PutPixel32(image, x, y, color);
        }
    }

    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}

//Apply all the useful correction to the image before bloc detection
void ApplyCorrection(SDL_Surface* image)
{
    int blur[3][3] = {
                        {1,2,1},
                        {2,4,2},
                        {1,2,1},
                    };

    int sharpen[3][3] = {
                        {0,-1,0},
                        {-1,5,-1},
                        {0,-1,0},
                     };

    SDL_LockSurface(image);

    Image_GrayScale(image);

    Image_Convolution(image,blur,0.0625);
    Image_Convolution(image,sharpen,1);

    Image_Threshold(image,Image_GetThreshold(image));

    SDL_UnlockSurface(image);
}


