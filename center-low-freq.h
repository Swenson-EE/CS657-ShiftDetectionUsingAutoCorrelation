#ifndef __CENTER_LOW_FREQ_H__
#define __CENTER_LOW_FREQ_H__

#include "minimal.h"


typedef struct
{
    // image_t* InImage;
    // int Width;
    // int Height;
    image_info_t* ImageInfo;
} center_low_freq_info_t;



void CenterLowFrequencies(center_low_freq_info_t* Info)
{
    int x, y;

    image_t* Image;
    int Width;
    int Height;

    Image = (Info->ImageInfo)->Image;
    Width = (Info->ImageInfo)->Width;
    Height = (Info->ImageInfo)->Height;


    DEBUG_LOG(CENTER_FREQ_TAG, "Start");



    for (y = 0; y < Height; y++)
    {
        for (x = 0; x < Width; x++)
        {
            Image[y * Width + x] = (Image[y * Width + x]) * pow(-1, x + y);
        }
    }



    DEBUG_LOG(CENTER_FREQ_TAG, "End");
}







#endif