#include <stdbool.h>
#ifdef _WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif
#include <math.h>
#include "../image_system/image_system.h"
#include "../image_system/color_system.h"
#include "../useful/builtin.h"
#include "rotation.h"

SDL_Surface* Image_Rotate(SDL_Surface* image, double angle)
{
    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image_temp);

    Uint32 color;
    double xp;
    double yp;
    angle = angle * M_PI / 180;
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    int center_x = (int) image->w / 2;
    int center_y = (int) image->h / 2;

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            xp = (x - center_x) * cos_angle - (y - center_y) * sin_angle + center_x;
            yp = (x - center_x) * sin_angle + (y - center_y) * cos_angle + center_y;
            if (Pixel_Exist(image_temp, (int) xp, (int) yp))
            {
                color = SDL_GetPixel32(image_temp, (int) xp, (int) yp);
                SDL_PutPixel32(image, x, y, color);
            }
            else
            {
                SDL_PutPixel32(image,x,y,4294967295);
            }
        }
    }


    SDL_UnlockSurface(image_temp);
    return image_temp;
}
