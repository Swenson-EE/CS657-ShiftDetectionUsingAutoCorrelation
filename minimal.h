#ifndef __MINIMAL_H__
#define __MINIMAL_H__



#define DEBUG       1



//#define LOG(TAG, MESSAGE, ...) printf("%s: %s\n", TAG, MESSAGE, ##__VA_ARGS__)
#define LOG(TAG, MESSAGE, ...) printf("%s: ", TAG); \
    printf(MESSAGE, ##__VA_ARGS__); \
    printf("\n")

#if DEBUG
    #define DEBUG_LOG(TAG, MESSAGE, ...) LOG(TAG, MESSAGE, ##__VA_ARGS__)
#else
    #define DEBUG_LOG(TAG, MESSAGE, ...)
#endif



#define SHIFT_IMAGE_TAG             "ShiftImage"
#define DFT_TAG                     "DFT"
#define IDFT_TAG                    "IDFT"

#define READ_PGM_TAG                "READ_PGM"
#define WRITE_PGM_TAG               "WRITE_PGM"




#define PI 3.14159265359



typedef struct 
{
    double Real;
    double Imag;
} complex_t;

typedef unsigned char image_t; 





#endif