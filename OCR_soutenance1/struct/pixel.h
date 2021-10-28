#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

typedef struct pixel pixel;
struct pixel
{
    int x;
    int y;
};

typedef struct PixelBlock PixelBlock;
struct PixelBlock
{
    pixel left_top;
    pixel right_top;
    pixel left_bottom;
    pixel right_bottom;
};


#endif // PIXEL_H_INCLUDED
