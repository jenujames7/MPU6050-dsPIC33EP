/* 
 * File:   main.h
 * Author: user
 *
 * Created on March 23, 2015, 4:41 PM
 */

#ifndef MAIN_H
#define	MAIN_H

    #define Enable      1
    #define Disable     0

    #define FOSCR       120000000UL
    #define FCY         FOSCR/2
    #define FP          FOSCR/2

    #define DMP_Hz      20
    #define HZ_val      200/DMP_Hz-1

    #include <xc.h> 
    #include <float.h> 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <math.h>
    #include <dsp.h>
    #include <p33EP256MU806.h>
    #include <libpic30.h>
    #include <time.h>
    #include <i2c.h>
    #include <time.h>
    #include <uart.h>

    #include "MPU_6050 driver/MPU6050.h"

    #include "dsPIC33EP256MU806 driver/port_header.h"
    #include "dsPIC33EP256MU806 driver/uart_header.h"
    #include "dsPIC33EP256MU806 driver/i2c_header.h" 

    #define M_PI PI
    #define SWDTEn    RCONbits.SWDTEN =   1
    #define SWDTDis   RCONbits.SWDTEN =   0

    #define TestLED                  LATDbits.LATD10
    #define Pwr5v                    LATDbits.LATD9

typedef struct
{
    unsigned int U1Rx  :1;
}UART_ACK;

        typedef void prog_void;
        typedef char prog_char;
        typedef unsigned char prog_uchar;
        typedef int8_t prog_int8_t;
        typedef uint8_t prog_uint8_t;
        typedef int16_t prog_int16_t;
        typedef uint16_t prog_uint16_t;
        typedef int32_t prog_int32_t;
        typedef uint32_t prog_uint32_t;
        
        #define strcpy_P(dest, src) strcpy((dest), (src))
        #define strcat_P(dest, src) strcat((dest), (src))
        #define strcmp_P(a, b) strcmp((a), (b))
        
        #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
        #define pgm_read_word(addr) (*(const unsigned short *)(addr))
        #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
        #define pgm_read_float(addr) (*(const float *)(addr))
        
        #define pgm_read_byte_near(addr) pgm_read_byte(addr)
        #define pgm_read_word_near(addr) pgm_read_word(addr)
        #define pgm_read_dword_near(addr) pgm_read_dword(addr)
        #define pgm_read_float_near(addr) pgm_read_float(addr)
        #define pgm_read_byte_far(addr) pgm_read_byte(addr)
        #define pgm_read_word_far(addr) pgm_read_word(addr)
        #define pgm_read_dword_far(addr) pgm_read_dword(addr)
        #define pgm_read_float_far(addr) pgm_read_float(addr)


void MPU6050_loop() ;
uint8_t MPU6050_dmpInitialize();
uint8_t MPU6050_dmpGetLinearAccelInWorld(struct VectorInt16 *v,struct VectorInt16 *vReal,struct Quaternion *q) ;
uint8_t MPU6050_dmpGetLinearAccel(struct VectorInt16 *v, struct VectorInt16 *vRaw, struct VectorFloat *gravity);
uint8_t MPU6050_dmpGetAccel(struct VectorInt16 *v, const uint8_t* packet) ;
uint8_t MPU6050_dmpGetGravity(struct VectorFloat *v,struct Quaternion *q) ;
uint8_t MPU6050_dmpGetEuler(float *data, struct Quaternion *q) ;
uint8_t MPU6050_dmpGetQuaternion_integer(int16_t *data, const uint8_t* packet) ;
uint8_t MPU6050_dmpGetQuaternion(struct Quaternion *q, const uint8_t* packet);
uint8_t MPU6050_dmpGetYawPitchRoll(float *data, struct Quaternion *q,struct VectorFloat *gravity) ;
uint16_t MPU6050_dmpGetFIFOPacketSize() ;
void MPU6050_setup() ;
void dmpDataReady();


#endif	/* MAIN_H */

