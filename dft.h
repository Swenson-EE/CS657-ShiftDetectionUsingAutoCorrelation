#ifndef __DFT_H__
#define __DFT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>

#include "minimal.h"


void DFT2D(image_t Image, int Width, int Height, complex_t** DFT)
{
    int x, y;
    int u, v;
    complex_t Sum;
    double Angle;
    printf("1\n");
    if (!DFT)
    {
        *DFT = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
        if (!DFT)
        {
            printf("Could not allocate memory for DFT\n");
            exit(1);
        }
    }
    printf("2\n");   

    // for (u = 0; u < Width; u++)
    // {
    //     for (v = 0; v < Height; v++)
    //     {
    //         Sum.Real = 0;
    //         Sum.Imag = 0;

    //         for (x = 0; x < Width; x++)
    //         {
    //             for (y = 0; y < Height; y++)
    //             {
    //                 Angle = -2 * PI * (( u * x / (double) Width) + ( v * y / (double) Height ));

    //                 Sum.Real += (Image[x * Height + y] * cos(Angle));
    //                 Sum.Imag += (Image[x * Height + y] * sin(Angle));

    //             }
    //         }

    //         //DFT[u * Height + v] = Sum;
    //         (*DFT)[u * Height + v].Real = Sum.Real;
    //         (*DFT)[u * Height + v].Imag = Sum.Imag;
    //     }
    // }

    for (v = 0; v < Height; v++) 
    {
        for (u = 0; u < Width; u++) 
        {
            Sum.Real = 0;
            Sum.Img = 0;

            for (y = 0; y < Height; y++) 
            {
                for (x = 0; x < Width; x++) {

                    Angle = -2 * PI * ((v * y / (double) Height) + (u * x / (double) Width));

                    Sum.Real += (Image[y * Width + x] * cos(Angle));
                    Sum.Imag += (Image[y * Width + x] * sin(Angle));
                }
            }

            (*DFT)[v * Width + u].Real = Sum.Real;
            (*DFT)[v * Width + u].Imag = Sum.Imag;
        }
    }

    printf("3\n");

}


#endif
