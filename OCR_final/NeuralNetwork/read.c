#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <err.h>

#include "../struct/pixel.h"
#include "../image_system/color_system.h"

//include for test
#include "../rotation/rotation.h"
#include "../sudoku_detection/grille_detection.h"
#include "../useful/basics.h"
#include "../image_system/image_system.h"
#include "../image_system/image_manipulation.h"
#include "../sudoku_detection/grid_det.h"


double* resize(double* digit, int widthdigit, int heightdigit)
{
    double* case_resized = malloc(784 * sizeof(double));
    if(case_resized == NULL)
        errx(1, "Memory allocation failed resize");

    double newRatioX = (double) (widthdigit) / 28;
    double newRatioY = (double) (heightdigit) / 28;


    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            int resX = i * newRatioX;
            int resY = j * newRatioY;

            if(resX >= widthdigit || resY >= heightdigit)
            {
                case_resized[i * 28 + j] = 0;
            }
            else
            {
                case_resized[i * 28 + j] = digit[resX * heightdigit + resY];
            }
        }
    }
    return case_resized;
}
