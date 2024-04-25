/********************************************************
Shift Detection using image correlation

By: Jesse Yeomans and Tyler Swenson
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include <malloc.h>  
#include <memory.h>

#include "read-pgm.h"
#include "write-pgm.h"

#include "minimal.h"


#include "shift-image.h"
#include "zero-padding.h"
#include "center-low-freq.h"

#include "dft.h"
#include "idft.h"


#define max(x, y) ((x>y) ? (x):(y))
#define min(x, y) ((x<y) ? (x):(y))


int Width;
int Height;
int maxraw;

int PaddedWidth, PaddedHeight;

image_t* InputImage;
image_t* ShiftedImage;

image_t* ZeropaddedImage;

image_t* Output;

complex_t* DFT;
complex_t* IDFT;


int x_shift;
int y_shift;


int main(int argc, char **argv)
{
  int i, j;
  //FILE *fp;




  // Assign main arguments for testing
  argc = 4;
  argv[1] = "test-img.pgm";
  argv[2] = "shifted-image.pgm";
  argv[3] = "Output.pgm";

  if (argc != 4){
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

  
  //ReadPGM(fp);
  ReadPGM(InputFileName, &Width, &Height, &maxraw, &InputImage);
  printf("Read Image: width: %d, height: %d\n\n", Width, Height);


  PaddedWidth = (2 * Width) - 1;
  PaddedHeight = (2 * Height) - 1;

  
  // TODO: our application here 

  // DFT and IDFT Testing
  // DFT2D(InputImage, Width, Height, &DFT);
  // IDFT2D(DFT, Width, Height, &IDFT, &Output);
  // WritePGM(OutputFileName, Width, Height, Output);


  // Image Shifting
  image_shift_info_t shift_info = {
    .InImage = InputImage,
    .Width = Width,
    .Height = Height,
    .ShiftX = x_shift,
    .ShiftY = y_shift,
    .OutImage = &ShiftedImage,
  };

  ShiftImage(&shift_info);
  // WritePGM(ShiftedFileName, Width, Height, ShiftedImage);


  
  // -------------------------------------------------------------------- //
  //                                                                      //
  //                          Zero Padding                                //
  //                                                                      //
  // -------------------------------------------------------------------- //


  // zeropad_info_t ZeropadInfo = {
  //   .InImage = InputImage,
  //   .Width = Width,
  //   .Height = Height,
  //   .PaddedWidth = PaddedWidth,
  //   .PaddedHeight = PaddedHeight,
  //   .OutImage = &ZeropaddedImage,
  // };

  // Zeropad(&ZeropadInfo);
  // WritePGM("Zeropad.pgm", PaddedWidth, PaddedHeight, ZeropaddedImage);

  // center_low_freq_info_t CenterInfo = {
  //   .InImage = ZeropaddedImage,
  //   .Width = Width,
  //   .Height = Height,
  // };

  // CenterLowFrequencies(&CenterInfo);
  // WritePGM("CenterLowFreq.pgm", PaddedWidth, PaddedHeight, ZeropaddedImage);



  // DFT2D(ZeropaddedImage, PaddedWidth, PaddedHeight, &DFT);
  // IDFT2D(DFT, PaddedWidth, PaddedHeight, &IDFT, &Output);
  // WritePGM(OutputFileName, PaddedWidth, PaddedHeight, Output);

  // -------------------------------------------------------------------- //
  //                                                                      //
  //                          Zero Padding End                            //
  //                                                                      //
  // -------------------------------------------------------------------- //
  


  

  free(InputImage);
  free(ShiftedImage);
  free(ZeropaddedImage);
  free(Output);

  free(DFT);
  free(IDFT);

  return (0);
}


