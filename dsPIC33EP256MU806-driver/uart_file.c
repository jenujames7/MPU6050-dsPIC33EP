
 /*
 * File    : uart_file.c
 * Author  : JJ
 * Project : ATW_frame_work
 * Created on January 22, 2015, 11:20 AM
 */

#include "../main.h"
#include "uart_header.h"

UART_ACK ServerSettings;
//==============================================================================
void uart1_init()
{
    U1MODE =  UART_IDLE_CON
            & UART_DIS_WAKE & UART_IrDA_DISABLE
            & UART_MODE_SIMPLEX & UART_UEN_00
            & UART_UXRX_IDLE_ONE & UART_DIS_LOOPBACK & UART_BRGH_FOUR
            & UART_DIS_ABAUD & UART_NO_PAR_8BIT & UART_1STOPBIT;

    U1STA  = UART_INT_TX & UART_IrDA_POL_INV_ZERO
            & UART_TX_ENABLE & UART_INT_RX_CHAR & UART_SYNC_BREAK_DISABLED
            & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR;

//    U1BRG  = 389;             //389 = 9600,UART_BRGH_SIXTEEN, 60MIPS,9600
    U1BRG  = 129;               //129 = 115200 UART_BRGH_FOUR, 60MIPS,115200
    UART1_TXN_INTR_FLAG_CLEAR;
    
    UART1_RX_INTR_EN;
    UART1_RX_INTR_FLAG_CLEAR;
    
    UART1_RXN_PRIORITY;

    _RP85R  =   0b000001;           //U1TX RP85R/RE5
    _U1RXR  =   0b1010110;          //U1RX RPI86/RE6
    ANSELEbits.ANSE5 = 0;
    ANSELEbits.ANSE6 = 0;
    U1MODEbits.UARTEN   =   1;
}
//==============================================================================
void uart1_Tx( char value)
{
    U1TXREG     =   value;

    while(!UART1_TXN_INTR_FLAG);
    UART1_TXN_INTR_FLAG_CLEAR;
}
//==============================================================================
void uart1_string_Tx( char *ptr)
{
    while(*ptr)
        uart1_Tx(*ptr++);
}
//==============================================================================
unsigned char uart1_Rx(void )
{
    unsigned char response;
    UART1_RX_INTR_FLAG_CLEAR;
    while(!UART1_RX_INTR_FLAG);
    response        =   U1RXREG;
    return response;
}
//==============================================================================
void __attribute__((__interrupt__,auto_psv)) _U1RXInterrupt(void)
{
    UART1_RX_INTR_FLAG_CLEAR;
    U1STAbits.OERR = 0;
    unsigned char rxByte;
    rxByte        =   U1RXREG;
    
    if((rxByte == '\n')||(rxByte == '\r'))
        ServerSettings.U1Rx = true;
}
//==============================================================================
void __attribute__((__interrupt__,auto_psv)) _U1ErrInterrupt(void)
{
    _U1EIF = 0;
}
//==============================================================================
void __attribute__((__interrupt__,auto_psv)) _U1TXInterrupt(void)
{
    UART1_TXN_INTR_FLAG_CLEAR;
}
//==============================================================================
void uart1_flushout()
{
    U1STAbits.OERR = 0;
    char i=0, j;
    while(i++<5)
       j = U1RXREG;
}
//==============================================================================
void uart1_Tx_len( char *ptr,uint8_t len)
{
    while(len--)
        uart1_Tx(*ptr++);
}
//==============================================================================


