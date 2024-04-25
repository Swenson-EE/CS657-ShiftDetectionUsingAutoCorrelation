#ifndef __MINIMAL_H__
#define __MINIMAL_H__



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include <malloc.h>  
#include <memory.h>


#define DEBUG       1
#define DEBUG_DATA  1



//#define LOG(TAG, MESSAGE, ...) printf("%s: %s\n", TAG, MESSAGE, ##__VA_ARGS__)
#define LOG(TAG, MESSAGE, ...) printf("%s: ", TAG); \
    printf(MESSAGE, ##__VA_ARGS__); \
    printf("\n")

#if DEBUG
    #define DEBUG_LOG(TAG, MESSAGE, ...) LOG(TAG, MESSAGE, ##__VA_ARGS__)
#else
    #define DEBUG_LOG(TAG, MESSAGE, ...)
#endif


#if DEBUG_DATA
    #define DEBUG_DATA_LOG(TAG, MESSAGE, ...) LOG(TAG, MESSAGE, ##__VA_ARGS__)
#else
    #define DEBUG_DATA_LOG(TAG, MESSAGE, ...)
#endif




#define SHIFT_IMAGE_TAG             "SHIFT IMAGE"
#define DFT_TAG                     "DFT"
#define IDFT_TAG                    "IDFT"
#define ZERO_PAD_TAG                "ZERO PADDING"
#define CENTER_FREQ_TAG             "CENTER FREQ"

#define READ_PGM_TAG                "READ PGM"
#define WRITE_PGM_TAG               "WRITE PGM"




#define PI 3.14159265359



typedef struct 
{
    double Real;
    double Imag;
} complex_t;

typedef unsigned char image_t; 




typedef struct
{
    image_t* Image;
    int Width;
    int Height;
    complex_t* DFT;
} image_info_t;





#endif