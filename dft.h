#ifndef __DFT_H__
#define __DFT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>

#include "minimal.h"


typedef struct 
{
    image_t* Image;
    int Width;
    int Height;
    complex_t** OutDFT;
} dft_config_t;  


//void DFT2D(image_t* Image, int Width, int Height, complex_t** OutDFT)
void DFT2D(dft_config_t* config)
{
    int x, y;
    int u, v;

    complex_t* DFT;
    complex_t Sum;
    double Angle, PixelValue;

    
    image_t* Image;
    int Width, Height;

    Image = config->Image;
    Width = config->Width;
    Height = config->Height;



    DEBUG_LOG(DFT_TAG, "Start");

    
    if (!Image)
    {
        printf("No image provided");
        exit(1);
    }


    if (*(config->OutDFT))
    {
        DFT = *(config->OutDFT);
    }
    else
    {
        DFT = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
        if (!DFT)
        {
            printf("Could not allocate memory for DFT\n");
            exit(1);
        }

        *(config->OutDFT) = DFT;
    }


    // Calculate DFT for rows
    for (v = 0; v < Height; v++)
    {
        for (x = 0; x < Width; x++)
        {
            //DFT[v * Width + x].Real = 0;
            //DFT[v * Width + x].Imag = 0;
            Sum.Real = 0;
            Sum.Imag = 0;


            for (u = 0; u < Width; u++)
            {
                Angle = 2.0 * PI * ((double) (x * u)) / Width;
                PixelValue = (double) Image[v * Width + u];

                Sum.Real += PixelValue * cos(Angle);
                Sum.Imag += -PixelValue * sin(Angle);
            }

            DFT[v * Width + x] = Sum;

        }
    }


    // Calculate DFT for columns
    for (u = 0; u < Width; u++)
    {
        for (y = 0; y < Height; y++)
        {
            Sum.Real = 0;
            Sum.Imag = 0;

            for (v = 0; v < Height; v++)
            {
                Angle = 2.0 * PI * ((double) (y * v) / Height);
                PixelValue = (double) Image[v * Width + u];

                Sum.Real += PixelValue * cos(Angle);
                Sum.Imag += -PixelValue * sin(Angle);
            }

            DFT[y * Width + u].Real += Sum.Real;
            DFT[y * Width + u].Imag += Sum.Imag;
            

        }
    }
    
    

    DEBUG_LOG(DFT_TAG, "End");
}



#endif
