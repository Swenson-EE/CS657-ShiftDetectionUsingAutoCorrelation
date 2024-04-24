#ifndef __WRITE_PGM_H__
#define __WRITE_PGM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
//#include <malloc.h>  

#include "minimal.h"



void WritePGM(char* FileName, int xdim, int ydim, image_t* image)
{
    int i,j;

    FILE* fp;

    /* Begin writing PGM.... */
    printf("Begin writing PGM.... \n");
    if ((fp=fopen(FileName, "wb")) == NULL){
        printf("write pgm error....\n");
        exit(0);
    }


    fprintf(fp, "P5\n%d %d\n%d\n", xdim, ydim, 255);
    for (j=0; j<ydim; j++)
        for (i=0; i<xdim; i++) {
            fputc(image[j*xdim+i], fp);
        }

    fclose(fp);
  
}



#endif