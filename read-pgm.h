#ifndef __READ_PGM_H__
#define __READ_PGM_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
//#include <malloc.h>  

#include "minimal.h"



void ReadPGM(char* FileName, int* xdimension, int* ydimension, int* MaxRaw, image_t** Image)
{
    int c;
    int i,j;
    int val;
    int xdim, ydim, maxraw;
    unsigned char *line;
    char buf[1024];
    FILE* fp;


    /* begin reading PGM.... */
    //printf("begin reading PGM.... \n");
    DEBUG_LOG(READ_PGM_TAG, "Begin reading PGM (%s)", FileName);
    if ((fp=fopen(FileName, "rb"))==NULL)
    {
        printf("read error...\n");
        exit(0);
    }
    


    while ((c=fgetc(fp)) == '#')
        fgets(buf, 1024, fp);
    ungetc(c, fp);

    if (fscanf(fp, "P%d\n", &c) != 1) {
        printf ("read error ....");
        exit(0);
    }
    if (c != 5 && c != 2) {
        printf ("read error ....");
        exit(0);
    }

    if (c==5) {
        while ((c=fgetc(fp)) == '#')
            fgets(buf, 1024, fp);
        ungetc(c, fp);
        if (fscanf(fp, "%d%d%d",&xdim, &ydim, &maxraw) != 3) {
            printf("failed to read width/height/max\n");
            exit(0);
        }
        printf("Width=%d, Height=%d \nMaximum=%d\n",xdim,ydim,maxraw);

        *Image = (unsigned char*)malloc(sizeof(unsigned char)*xdim*ydim);
        getc(fp);

        line = (unsigned char *)malloc(sizeof(unsigned char)*xdim);
        for (j=0; j<ydim; j++) {
            fread(line, 1, xdim, fp);
            for (i=0; i<xdim; i++) {
                (*Image)[j*xdim+i] = line[i];
            }
        }
        free(line);

    }

    else if (c==2) {
        while ((c=fgetc(fp)) == '#')
            fgets(buf, 1024, fp);
        ungetc(c, fp);
        if (fscanf(fp, "%d%d%d", &xdim, &ydim, &maxraw) != 3) {
            printf("failed to read width/height/max\n");
            exit(0);
        }
        printf("Width=%d, Height=%d \nMaximum=%d,\n",xdim,ydim,maxraw);

        *Image = (unsigned char*)malloc(sizeof(unsigned char)*xdim*ydim);
        getc(fp);

        for (j=0; j<ydim; j++)
            for (i=0; i<xdim; i++) {
                fscanf(fp, "%d", &val);
                (*Image)[j*xdim+i] = val;
            }

    }

    fclose(fp);


    *xdimension = xdim;
    *ydimension = ydim;
    *MaxRaw = maxraw;
}



#endif