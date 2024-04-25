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

#include "dft.h"
#include "idft.h"


#define max(x, y) ((x>y) ? (x):(y))
#define min(x, y) ((x<y) ? (x):(y))


int xdim;
int ydim;
int maxraw;
image_t* image;
image_t* ShiftedImage;
image_t* Output;

complex_t* DFT;
complex_t* IDFT;


int x_shift;
int y_shift;


int main(int argc, char **argv)
{
  int i, j;
  //FILE *fp;

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
  ReadPGM(InputFileName, &xdim, &ydim, &maxraw, &image);

  printf("Read Image: width: %d, height: %d\n\n", xdim, ydim);

  
  // TODO: our application here 

  image_shift_info_t shift_info = {
    .InImage = image,
    .Width = xdim,
    .Height = ydim,
    .ShiftX = x_shift,
    .ShiftY = y_shift,
    .OutImage = &ShiftedImage,
  };

  ShiftImage(&shift_info);
  WritePGM(ShiftedFileName, xdim, ydim, ShiftedImage);

  

  DFT2D(image, xdim, ydim, &DFT);
  

  //IDFT2D(&Output, xdim, ydim, DFT);
  IDFT2D(DFT, xdim, ydim, &IDFT, &Output);
  
  
  
  /* Begin writing PGM.... */
  //WritePGM(OutputFileName, xdim, ydim, image);
  WritePGM(OutputFileName, xdim, ydim, Output);

  free(image);
  free(ShiftedImage);
  free(Output);

  free(DFT);
  free(IDFT);

  return (0);
}


