#ifndef __IDFT_H__
#define __IDFT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>

#include "minimal.h"

/*
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
    



    // for (u = 0; u < Width; u++)
    // {
    //     for (v = 0; v < Height; v++)
    //     {
    //         Sum.Real = 0;
    //         Sum.Imag = 0;

    //         for (x = 0; x < Width; x++)
    //         {
    //             AngleX = 2 * PI * u * x / (double) Width;

    //             for (y = 0; y < Height; y++)
    //             {
    //                 AngleY = 2 * PI * v * y / (double) Height;

    //                 CosValue = cos(AngleX + AngleY);
    //                 SinValue = sin(AngleX + AngleY);

    //                 DFT_Real = DFT[y * Width + x].Real;
    //                 DFT_Imag = DFT[y * Width + x].Imag;

    //                 Sum.Real += (DFT_Real * CosValue) - (DFT_Imag * SinValue);
    //                 Sum.Imag += (DFT_Real * SinValue) - (DFT_Imag * CosValue);
    //             }
    //         }
    //         IDFT_Image[v * Width + u].Real = Sum.Real;
    //         IDFT_Image[v * Width + u].Imag = Sum.Imag;
    //     }
    // }

    for (v = 0; v < Height; v++)
    {
        for (u = 0; u < Width; u++)
        {
            Sum.Real = 0;
            Sum.Imag = 0;

            for (y = 0; y < Height; y++)
            {
                AngleY = 2 * PI * v * y / (double) Height;

                for (int x = 0; x < Width; x++)
                {
                    AngleX = 2 * PI * u * x / (double) Width;

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

    // for (x = 0; x < Width; x++)
    // {
    //     for (y = 0; y < Height; y++)
    //     {
    //         Real = IDFT_Image[x * Height + y].Real;
    //         Imag = IDFT_Image[x * Height + y].Imag;

    //         Output[x * Height + y] = round(Real * MN_Inverse);
    //     }
    // }

    for (y = 0; y < Height; y++)
    {
        for (x = 0; x < Width; x++)
        {
            Real = IDFT_Image[y * Width + x].Real;
            Imag = IDFT_Image[y * Width + x].Imag;

            Output[y * Width + x] = round(Real * MN_Inverse);
        }
    }



}
*/

void IDFT2D(complex_t* DFT, int Width, int Height, complex_t** OutIDFT, image_t** OutImage)
{
    int x, y;
    int u, v;
    double Angle, Mag;
    double CosValue, SinValue;
    double DFT_Real, DFT_Imag;

    double MN_Inverse;
    complex_t Sum;

    complex_t* IDFT_Image;
    image_t* Output;


    DEBUG_LOG(IDFT_TAG, "Start");


    if (!DFT)
    {
        printf("No DFT provided\n");
        exit(1);
    }


    if (*OutImage)
    {
        Output = *OutImage;
    }
    else
    {
        Output = (image_t*) malloc(sizeof(unsigned char) * Width * Height);

        if (!Output)
        {
            printf("Could not allocate memory for Output Image\n");
            exit(1);
        }

        (*OutImage) = Output;
    }

    
    if (*OutIDFT)
    {
        IDFT_Image = *OutIDFT;
    }
    else
    {
        IDFT_Image = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
        if (!IDFT_Image)
        {
            printf("Could not allocate memory for IDFT_Image\n");
            exit(1);
        }

        (*OutIDFT) = IDFT_Image;
    }


    MN_Inverse = 1 / (double)(Width * Height);


    // Calculate IDFT for rows
    for (y = 0; y < Height; y++)
    {
        for (x = 0; x < Width; x++)
        {
            Sum.Real = 0;
            Sum.Imag = 0;

            for (u = 0; u < Width; u++)
            {
                Angle = 2.0 * PI * ((double) (x * u) / Width);
                CosValue = cos(Angle);
                SinValue = sin(Angle);
                
                DFT_Real = DFT[y * Width + u].Real;
                DFT_Imag = DFT[y * Width + u].Imag;


                Sum.Real += (DFT_Real * CosValue) - (DFT_Imag * SinValue);
                Sum.Imag += (DFT_Real * SinValue) - (DFT_Real * CosValue);

            }
            Mag = sqrt((Sum.Real * Sum.Real) + (Sum.Imag * Sum.Imag));

            Output[y * Width + x] = (unsigned char) (255 * Mag * MN_Inverse);

        }
    }



    // Calculate IDFT for columns
    for (x = 0; x < Width; x++)
    {
        for (y = 0; y < Height; y++)
        {
            Sum.Real = 0;
            Sum.Imag = 0;

            for (v = 0; v < Height; v++)
            {
                Angle = 2.0 * PI * ((double) (y * v) / Height);
                CosValue = cos(Angle);
                SinValue = sin(Angle);

                DFT_Real = DFT[v * Width + x].Real;
                DFT_Imag = DFT[v * Width + x].Imag;

                Sum.Real += (DFT_Real * CosValue) - (DFT_Imag * SinValue);
                Sum.Imag += (DFT_Real * SinValue) + (DFT_Imag * CosValue);
            }

            Mag = sqrt((Sum.Real * Sum.Real) + (Sum.Imag * Sum.Imag));

            Output[y * Width + x] += (unsigned char) (255 * Mag * MN_Inverse);

        }
    }


    DEBUG_LOG(IDFT_TAG, "End");
}





#endif