#ifndef __DFT_H__
#define __DFT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>

#include "minimal.h"

/*
void DFT2D(image_t Image, int Width, int Height, complex_t** DFT)
{
    int x, y;
    int u, v;
    complex_t Sum;
    double Angle;
    printf("1\n");
    if (!(*DFT))
    {
        *DFT = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
        if (!(*DFT))
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
        //printf("V: %d\n", v);

        for (u = 0; u < Width; u++) 
        {
            //printf("U: %d\n", u);
            Sum.Real = 0;
            Sum.Imag = 0;

            for (y = 0; y < Height; y++) 
            {
                //printf("y: %d\n", y);
                for (x = 0; x < Width; x++) {

                    Angle = -2 * PI * ((v * y / (double) Height) + (u * x / (double) Width));

                    Sum.Real += (Image[y * Width + x] * cos(Angle));
                    Sum.Imag += (Image[y * Width + x] * sin(Angle));
                }
            }

            //printf("2.1\n");

            //(*DFT)[v * Width + u].Real = Sum.Real;
            //(*DFT)[v * Width + u].Imag = Sum.Imag;
            (*DFT)[v * Width + u] = Sum;

            //printf("2.2\n");
        }
    }

    

}
*/

void DFT2D(image_t* Image, int Width, int Height, complex_t** OutDFT)
{
    int x, y;
    int u, v;

    complex_t* DFT;
    complex_t Sum;
    double Angle;
    
    /*
    if (!(*DFT))
    {
        *DFT = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
        if (!(*DFT))
        {
            printf("Could not allocate memory for DFT\n");
            exit(1);
        }
    }
    */
    if (!Image)
    {
        printf("No image provided");
        exit(1);
    }


    if (!(*OutDFT))
    {
        DFT = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
        if (!DFT)
        {
            printf("Could not allocate memory for DFT\n");
            exit(1);
        }
    }


    // Calculate DFT for rows
    for (y = 0; y < Height; y++)
    {
        for (u = 0; u < Width; u++)
        {
            DFT[y * Width + u].Real = 0;
            DFT[y * Width + u].Imag = 0;

            for (x = 0; x < Width; x++)
            {
                Angle = (2 * PI * u * x) / Width;
                
                DFT[y * Width + u].Real += Image[y * Width + x] * cos(Angle);
                DFT[y * Width + u].Imag += -Image[y * Width + x] * sin(Angle);
            }
        }
    }

    // Calculate DFT for columns
    for (x = 0; x < Width; x++)
    {
        for (v = 0; v < Height; v++)
        {
            for (y = 0; y < Height; y++)
            {
                Angle = (2 * PI * v * y) / Height;

                DFT[v * Width + x].Real += Image[y * Width + x] * cos(Angle);
                DFT[v * Width + x].Imag += -Image[y * Width + x] * sin(Angle);
            }
        }
    }






    *OutDFT = DFT;
}



#endif
