/********************************************************
Shift Detection using image correlation

By: Jesse Yeomans and Tyler Swenson
*********************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>


#include "minimal.h"

#include "read-pgm.h"
#include "write-pgm.h"

#include "shift-image.h"
#include "zero-padding.h"
#include "center-low-freq.h"

#include "dft.h"
#include "idft.h"

#include "cross-power-spectrum.h"
#include "image-correlation.h"



image_info_t f1;
image_info_t f2;
complex_t* Suv; // Power-Spectral-Density


int maxraw;
int x_shift, y_shift;
int calc_x_shift, calc_y_shift;


int main(int argc, char **argv)
{
    int ImageWidth, ImageHeight;

    
    // Assign main arguments for testing
    argc = 4;
    argv[1] = "test-img.pgm";
    argv[2] = "shifted-image.pgm";
    argv[3] = "Output.pgm";

    if (argc != 4) 
    {
        printf("Usage: MyProgram <input_ppm> <shifted_ppm> <output_ppm> \n");
        printf("       <input_ppm>: PGM file \n");
        printf("       <shifted_ppm>: PGM file \n");
        printf("       <output_ppm>: PGM file \n");
        exit(0);
    }

    char* InputFileName   = argv[1];
    char* ShiftedFileName = argv[2];
    char* OutputFileName  = argv[3];

    x_shift = 100;
    y_shift = 100;

    
    // Read in image
    ReadPGM(InputFileName, &ImageWidth, &ImageHeight, &maxraw, &(f1.Image));
    printf("Read Image: width: %d, height: %d\n\n", ImageWidth, ImageHeight);

    f1.Width = ImageWidth;
    f1.Height = ImageHeight;

    f2.Width = ImageWidth;
    f2.Height = ImageHeight;



    // TODO: our application here

    

    // Shift image
    //f2.Width = f1.Width;
    //f2.Height = f1.Height;

    image_shift_info_t shift_info = {
        .InImage = f1.Image,
        .Width = f1.Width,
        .Height = f1.Height,
        .ShiftX = x_shift,
        .ShiftY = y_shift,
        .OutImage = &(f2.Image),
    };

    ShiftImage(&shift_info);


    // Calculate DFT for both images
    dft_config_t dft1_config = {
        .Image = f1.Image,
        .Width = f1.Width,
        .Height = f1.Height,
        .OutDFT = &(f1.DFT),
    };

    DFT2D(&dft1_config);

    
    dft_config_t dft2_config = {
        .Image = f2.Image,
        .Width = f2.Width,
        .Height = f2.Height,
        .OutDFT = &(f2.DFT),
    };

    DFT2D(&dft2_config);


    // Calculate cross-power-spectrum between both images
    image_info_t ImageInfo1 = {
        .Image = (f1.Image),
        .Width = ImageWidth,
        .Height = ImageHeight,
        .DFT = (f1.DFT)
    };

    image_info_t ImageInfo2 = {
        .Image = (f2.Image),
        .Width = ImageWidth,
        .Height = ImageHeight,
        .DFT = (f2.DFT)
    };

    cross_power_info_t CrossPowerInfo = {
        .Image1 = &ImageInfo1,
        .Image2 = &ImageInfo2,
        .OutPowerSpectrum = &Suv,
    };
    CrossPowerSpectrum(&CrossPowerInfo);


    // Calculate Image Correlation
    image_correlation_info_t CorrelationInfo = {
        .S = Suv,
        .Width = ImageWidth,
        .Height = ImageHeight,
        .OutXShift = &calc_x_shift,
        .OutYShift = &calc_y_shift,
    };

    ImageCorrelation(&CorrelationInfo);




    free(f1.Image);
    free(f1.DFT);



    return (0);
}