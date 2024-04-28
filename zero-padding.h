#ifndef __ZERO_PADDING_H__
#define __ZERO_PADDING_H__


#include "minimal.h"




typedef struct {
    // image_t* InImage;
    // int Width;
    // int Height;
    // int PaddedWidth;
    // int PaddedHeight;
    // image_t** OutImage;
    image_info_t* OriginalImageInfo;
    image_info_t* PaddedImageInfo;
} zeropad_info_t;




void Zeropad(zeropad_info_t* PaddingInfo)
{
    int x, y;           // x, y
    image_t *InImage, *OutputImage;
    image_info_t *InInfo, *OutInfo;
    int Width, Height;
    int PaddedWidth, PaddedHeight;
    
    DEBUG_LOG(ZERO_PAD_TAG, "Start");

    InInfo = PaddingInfo->OriginalImageInfo;
    OutInfo = PaddingInfo->PaddedImageInfo;


    InImage = InInfo->Image;
    Width = InInfo->Width;
    Height = InInfo->Height;
    PaddedWidth = OutInfo->Width;
    PaddedHeight = OutInfo->Height;

    DEBUG_DATA_LOG(ZERO_PAD_TAG, "Width: %d, Height: %d", Width, Height);
    DEBUG_DATA_LOG(ZERO_PAD_TAG, "PaddedWidth: %d, PaddedHeight: %d", PaddedWidth, PaddedHeight);



    if (OutInfo->Image)
    {
        OutputImage = (OutInfo->Image);
    }
    else
    {
        OutputImage = (image_t*) malloc(sizeof(image_t) * PaddedWidth * PaddedHeight);
        if (!OutputImage)
        {
            DEBUG_LOG(ZERO_PAD_TAG, "Could not allocate memory for OutputImage");
            exit(1);
        }
        
        (OutInfo->Image) = OutputImage;
    }


    // for (y = 0; y < PaddedHeight; y++)
    // {
    //     for (x = 0; x < PaddedHeight; x++)
    //     {
    //         OutputImage[y * PaddedWidth + x] = 0;
    //     }
    // }



    // for (y = 0; y < Height; y++)
    // {
    //     for (x = 0; x < Width; x++)
    //     {
    //         OutputImage[y * PaddedWidth + x] = (PaddingInfo->InImage)[y * Width + x];
    //     }
    // }

    for (y = 0; y < PaddedHeight; y++)
    {
        for (x = 0; x < PaddedWidth; x++)
        {
            if (x < Width && y < Height)
            {
                OutputImage[y * PaddedWidth + x] = InImage[y * Width + x];
            }
            else
            {
                OutputImage[y * PaddedWidth + x] = 0;
            }
        }
    }


    DEBUG_LOG(ZERO_PAD_TAG, "End");
}









#endif