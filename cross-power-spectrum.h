#ifndef __CROSS_POWER_SPECTRUM_H__
#define __CROSS_POWER_SPECTRUM_H__

#include "minimal.h"
#include "dft.h"

typedef struct
{
    image_info_t* Image1;
    image_info_t* Image2;
    complex_t** OutPowerSpectrum;
} cross_power_info_t;

void CrossPowerSpectrum(cross_power_info_t* Info)
{
    complex_t* DFT1 = (Info->Image1)->DFT;
    complex_t* DFT2 = (Info->Image2)->DFT;
    
    double DFT1_Re1, DFT1_Im1;
    double DFT2_Re2, DFT2_Im2;
    double mag;
    int Width = (Info->Image1)->Width;
    int Height = (Info->Image1)->Height;

    complex_t* DFT_F3 = (complex_t*) malloc(sizeof(complex_t) * (Width * Height));

    for(int index = 0; index < (Width * Height); index++)
    {
        DFT1_Re1 = DFT1[index].Real;
        DFT1_Im1 = DFT1[index].Imag;
        DFT2_Re2 = DFT2[index].Real;
        DFT2_Im2 = DFT2[index].Imag;

        DFT_F3[index].Real = (DFT1_Re1 * DFT2_Re2) - (DFT1_Im1 * DFT2_Im2);
        DFT_F3[index].Imag = (DFT1_Re1 * DFT2_Im2) + (DFT1_Im1 * DFT2_Re2);

        mag = sqrt((DFT_F3[index].Real * DFT_F3[index].Real) + (DFT_F3[index].Imag * DFT_F3[index].Imag));

        DFT_F3[index].Real /= mag;
        DFT_F3[index].Imag /= mag;
    }
    
    *OutPowerSpectrum = DFT_F3;
}

#endif