#ifndef __IDFT_H__
#define __IDFT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>

#include "minimal.h"


void IDFT2D(image_t Output, int Width, int Height, complex_t* DFT)
{
    int x, y;
    int u, v;
    double AngleX, AngleY;
    double CosValue, SinValue;
    double DFT_Real, DFT_Imag;

    double MN_Inverse;
    complex_t Sum;

    complex_t* IDFT_Image;



    if (!DFT)
    {
        printf("No DFT provided\n");
        exit(1);
    }

    if (!Output)
    {
        Output = (image_t) malloc(sizeof(image_t) * Width * Height);
        if (!Output)
        {
            printf("Could not allocate memory for IDFT\n");
            exit(1);
        }
    }

    IDFT_Image = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
    if (!IDFT_Image)
    {
        printf("Could not allocate memory for IDFT_Image\n");
        exit(1);
    }


    MN_Inverse = 1 / (double)(Width * Height);
    



    for (u = 0; u < Width; u++)
    {
        for (v = 0; v < Height; v++)
        {
            Sum.Real = 0;
            Sum.Imag = 0;

            for (x = 0; x < Width; x++)
            {
                AngleX = 2 * PI * u * x / (double) Width;

                for (y = 0; y < Height; y++)
                {
                    AngleY = 2 * PI * v * y / (double) Height;

                    CosValue = cos(AngleX + AngleY);
                    SinValue = sin(AngleX + AngleY);

                    DFT_Real = DFT[y * Width + x].Real;
                    DFT_Imag = DFT[y * Width + x].Imag;

                    Sum.Real += (DFT_Real * CosValue) - (DFT_Imag * SinValue);
                    Sum.Imag += (DFT_Real * SinValue) - (DFT_Imag * CosValue);
                

                }
            }


            IDFT_Image[v * Width + u].Real = Sum.Real;
            IDFT_Image[v * Width + u].Imag = Sum.Imag;



        }
    }

    

    double Real, Imag, Mag;

    for (x = 0; x < Width; x++)
    {
        for (y = 0; y < Height; y++)
        {
            Real = IDFT_Image[x * Height + y].Real;
            Imag = IDFT_Image[x * Height + y].Imag;

            Output[x * Height + y] = round(Real * MN_Inverse);
        }
    }



}




#endif