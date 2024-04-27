#ifndef __IMAGE_CORRELATION_H__
#define __IMAGE_CORRELATION_H__

#include "minimal.h"

#include "idft.h"

#include "write-pgm.h"



typedef struct 
{
    complex_t* S;
    int Width;
    int Height;
    int* OutXShift;
    int* OutYShift;
    
} image_correlation_info_t;

void ImageCorrelation(image_correlation_info_t* Info)
{
    image_t* AutocorrelationImage = NULL;
    complex_t* IDFT = NULL;

    complex_t* S = NULL;
    int Width, Height;
    int XShift, YShift;

    S = Info->S;
    Width = Info->Width;
    Height = Info->Height;

    DEBUG_LOG(IMAGE_CORRELATION_TAG, "Start");



    IDFT2D(S, Width, Height, &IDFT, &AutocorrelationImage);



    //WritePGM("ImageCorrelation.pgm", Width, Height, AutocorrelationImage);
    int x, y;
    double Mag = 0, MaxMag = 0;
    double Real, Imag;
    int x_shift = 0, y_shift = 0;

    for (y = 0; y < Height; y++)
    {
        for (x = 0; x < Width; x++)
        {
            Real = IDFT[y * Width + x].Real;
            Imag = IDFT[y * Width + x].Imag;

            Mag = sqrt( (Real * Real) + (Imag * Imag) );
            //printf("x: %d, y: %d, Mag: %lf\n", x, y, Mag);
            //printf("x: %d, y: %d, Real: %lf, Imag: %lf, Mag: %lf\n", x, y, Real, Imag, Mag);
            //Mag = Real;
            if (Real > MaxMag)
            {
                printf("New max mag (x: %d, y: %d, Mag: %lf)\n", x, y, Mag);
                MaxMag = Real;
                x_shift = x;
                y_shift = y;
                //printf("New y_shift: %d\n", y);
            }

        }
    }

    printf("x_shift: %d, y_shift: %d\n", x_shift, y_shift);

    DEBUG_LOG(IMAGE_CORRELATION_TAG, "End");
}



#endif