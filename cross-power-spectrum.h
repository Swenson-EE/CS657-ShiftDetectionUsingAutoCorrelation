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


/*
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
    
    *(Info->OutPowerSpectrum) = DFT_F3;
}
*/

void CrossPowerSpectrum(cross_power_info_t* Info)
{
    complex_t *DFT1, *DFT2;
    double F1_Real, F1_Imag;
    double F2_Real, F2_Imag;
    double Mag;
    int Width, Height;
    complex_t *S;
    double S_Real, S_Imag;

    DFT1 = (Info->Image1)->DFT;
    DFT2 = (Info->Image2)->DFT;

    Width = (Info->Image1)->Width;
    Height = (Info->Image1)->Height;


    DEBUG_LOG(POWER_SPECTRUM_TAG, "Start");


    S = (complex_t*) malloc(sizeof(complex_t) * Width * Height);
    if (S)
    {
        *(Info->OutPowerSpectrum) = S;
    }
    else
    {
        printf("Could not allocate memory for S (Power Spectral Density)\n");
        exit(1);
    }

    

    complex_t Ns, Ds;
    double Mag1, Mag2;

    for (int i = 0; i < Width * Height; i++)
    {
        F1_Real = DFT1[i].Real;
        F1_Imag = DFT1[i].Imag;
        F2_Real = DFT2[i].Real;
        F2_Imag = DFT2[i].Imag;

        Mag1 = sqrt((F1_Real * F1_Real) + (F1_Imag * F1_Imag));
        Mag2 = sqrt((F2_Real * F2_Real) + (F2_Imag * F2_Imag));

        //S[i].Real = (F1_Real * F2_Real) - (F1_Imag * F2_Imag);
        //S[i].Imag = (F1_Real * F2_Imag) + (F1_Imag * F2_Real);

        

        // S_Real = (F1_Real * F2_Real) - (F1_Imag * F2_Imag);
        // S_Imag = (F1_Real * F2_Imag) + (F1_Imag * F2_Real);

        // Mag = sqrt( (S_Real * S_Real) + (S_Imag * S_Imag) );

        // S[i].Real = S_Real / Mag;
        // S[i].Imag = S_Imag / Mag;


        // Calculate cross-power numerator
        // Use conjugate of F2
        Ns.Real = (F1_Real * F2_Real) - (F1_Imag * (-F2_Imag));
        Ns.Imag = (F1_Real * (-F2_Imag)) + (F1_Imag * F2_Real);

        // Calculate cross-power denomenator
        Ds.Real = (F1_Real * F2_Real) - (F1_Imag * F2_Imag);
        Ds.Imag = (F1_Real * F2_Imag) + (F1_Imag * F2_Real);
        //Mag = sqrt( (Ds.Real * Ds.Real) + (Ds.Imag * Ds.Imag) );
        Mag = Mag1 * Mag2;

        // Put cross-power spectrum together
        S[i].Real = Ns.Real / Mag;
        S[i].Imag = Ns.Imag / Mag;

        
    }

    


    DEBUG_LOG(POWER_SPECTRUM_TAG, "End");
}



#endif