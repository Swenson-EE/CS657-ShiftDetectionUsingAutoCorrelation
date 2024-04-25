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

#include "dft.h"
#include "idft.h"


#define max(x, y) ((x>y) ? (x):(y))
#define min(x, y) ((x<y) ? (x):(y))


int xdim;
int ydim;
int maxraw;
image_t* image;
image_t* Output;

complex_t* DFT;
complex_t* IDFT;



int main(int argc, char **argv)
{
  int i, j;
  //FILE *fp;

  argc = 3;
  argv[1] = "test-img.pgm";
  argv[2] = "Output.pgm";

  if (argc != 3){
    printf("Usage: MyProgram <input_ppm> <output_ppm> \n");
    printf("       <input_ppm>: PGM file \n");
    printf("       <output_ppm>: PGM file \n");
    exit(0);              
  }

  char* InputFileName   = argv[1];
  char* OutputFileName  = argv[2];

  

  
  //ReadPGM(fp);
  ReadPGM(InputFileName, &xdim, &ydim, &maxraw, &image);

  printf("Read Image: width: %d, height: %d\n\n", xdim, ydim);

 
  // TODO: our application here 
  printf("dft start\n");
  DFT2D(image, xdim, ydim, &DFT);
  printf("dft finish\n");
  

  printf("idft start\n");
  //IDFT2D(&Output, xdim, ydim, DFT);
  IDFT2D(DFT, xdim, ydim, &IDFT, &Output);
  printf("idft finish\n");
  
  
  
  /* Begin writing PGM.... */
  //WritePGM(OutputFileName, xdim, ydim, image);
  WritePGM(OutputFileName, xdim, ydim, Output);

  free(image);
  free(Output);

  return (0);
}


