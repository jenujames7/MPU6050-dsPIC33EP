/*
 * File:   main.c
 * Author: Jenu James
 *
 * Created on August 22, 2016, 6:00 PM
 */
#include <p33EP256MU806.h>

#include "main.h"

#pragma config GWRP = OFF,          GSS = OFF,          GSSK = OFF,         FNOSC = PRIPLL
#pragma config IESO = OFF,          POSCMD = HS,        OSCIOFNC = OFF
#pragma config IOL1WAY = OFF,       FCKSM = CSECMD,     WDTPOST = PS32768
#pragma config WDTPRE = PR128,      PLLKEN = OFF,       WINDIS = OFF
#pragma config FWDTEN = OFF,        FPWRT = PWR128,     BOREN = ON
#pragma config ALTI2C1 = OFF,       ICS = PGD1,         RSTPRI = PF
#pragma config JTAGEN = OFF,        AWRP = OFF,         APL = OFF,          APLK = OFF

#define MPU6050_ADDRESS MPU6050_I2C_ADDRESS     // address pin grounded
/**************************************************************************************/
int main(void)
{
    PLLFBD              =   58;                 //60 MIPS, 20MHZ crystal
    CLKDIVbits.PLLPRE   =   3;  
    CLKDIVbits.PLLPOST  =   0;  
    
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    
    while (OSCCONbits.COSC!= 0b011);
    while (OSCCONbits.LOCK!= 1);
    
    __delay_ms(3000);
    SWDTEn;
    __C30_UART=1;

    port_init();
    uart1_init();       //115200 baud rate 
    i2c2_init();        //400Khz

    printf("\n\rWelcome_ MPU6050 DMP test \n");
    led_blink(500);
    printf("\t MPU6050_WHO_AM_I:[%x]\n\r",I2C2Read(MPU6050_I2C_ADDRESS,MPU6050_WHO_AM_I)); 
    
    if(I2C2Read(MPU6050_I2C_ADDRESS,MPU6050_WHO_AM_I)==0x68)
    {
        MPU6050_setup();
        while(true)
        {
            MPU6050_loop();
            ClrWdt();
        }
    }
    printf("MPU6050 Not found!!! \n");

    while(1) Idle();
    return (EXIT_SUCCESS);
}
/**************************************************************************************/



