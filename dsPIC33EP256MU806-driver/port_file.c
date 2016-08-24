
/*
 * File    : port_file.c
 * Author  : JJ
 * Project : ATW_frame_work
 * Created on January 22, 2015, 11:20 AM
 */
#include "../main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void port_init()
{
    TRISDbits.TRISD10   = 0;      //onboard LED
    TRISDbits.TRISD9    = 0;      //5v ON/OFF
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void led_blink(int time)
{
    TestLED   = 0;
    __delay_ms(time);
    TestLED   = 1;
    __delay_ms(time);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void ExtINT_init()
{
    ANSELBbits.ANSB14   =   0;
    TRISBbits.TRISB14   =   1;
    IFS1bits.INT1IF     =   0;
    INTCON2bits.INT1EP  =   1;
    _INT1IP             =   6;
    _INT1R              =   0b0101110;
    IEC1bits.INT1IE     =   1;
    INTCON2bits.GIE     =   1;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __attribute__((__interrupt__,auto_psv)) _INT0Interrupt(void)
{
    IFS0bits.INT0IF =   0;
    printf("~");
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern volatile bool mpuInterrupt;
void __attribute__((__interrupt__,auto_psv)) _INT1Interrupt(void)
{
    IFS1bits.INT1IF =   0;
     mpuInterrupt   = true;
//    printf("*");
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



