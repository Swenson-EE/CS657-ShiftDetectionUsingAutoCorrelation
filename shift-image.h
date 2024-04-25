#ifndef __SHIFT_IMAGE_H__
#define __SHIFT_IMAGE_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>

#include "minimal.h"



typedef struct {
    image_t* InImage;
    int Width;
    int Height;
    int ShiftX;
    int ShiftY;
    image_t** OutImage;
} image_shift_info_t;


void ShiftImage(image_shift_info_t* shift_info)
{
    // image_t* temp = (image_t*) malloc(sizeof(image_t) * shift_info->Width * shift_info->Height);
    // if (!temp)
    // {
    //     printf("Could not allocate space for temp\n");
    //     exit(1);
    // }
    int x, y;
    int CurrentIndex, NewX, NewY, NewIndex;
    image_t* ShiftedImage;


    DEBUG_LOG("ShiftImage", "Start");
    shift_info->Width = 0;

    if (*(shift_info->OutImage))
    {
        ShiftedImage = *(shift_info->OutImage);
    }
    else
    {
        ShiftedImage = (image_t*) malloc(sizeof(image_t) * (shift_info->Width) * (shift_info->Height));
        if (!ShiftedImage)
        {
            printf("Could not allocate memory for ShiftedImage\n");
            exit(1);
        }

        (*shift_info->OutImage) = ShiftedImage;
    }



    for (y = 0; y < (shift_info->Height); y++)
    {
        for (x = 0; x < (shift_info->Width); x++)
        {
            CurrentIndex = y * (shift_info->Width) + x;
            NewX = (x + (shift_info->ShiftX)) % (shift_info->Width);
            NewY = (y + (shift_info->ShiftY)) % (shift_info->Height);
            NewIndex = NewY * (shift_info->Width) + NewX;
            
            ShiftedImage[NewIndex] = (shift_info->InImage)[CurrentIndex];
        }
    }
    

    


    DEBUG_LOG("ShiftImage", "End");
}










#endif
