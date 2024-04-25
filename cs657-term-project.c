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



image_info_t f1;
image_info_t f2;

int maxraw;
int x_shift, y_shift;


int main(int argc, char **argv)
{
    
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
    ReadPGM(InputFileName, &(f1.Width), &(f1.Height), &maxraw, &(f1.Image));
    printf("Read Image: width: %d, height: %d\n\n", f1.Width, f1.Height);


    // TODO: our application here

    // Shift image
    f2.Width = f1.Width;
    f2.Height = f1.Height;

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





    free(f1.Image);
    free(f1.DFT);



    return (0);
}