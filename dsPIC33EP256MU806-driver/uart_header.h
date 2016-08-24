/*
 * File:   uart_header.h
 * Author: user
 *
 * Created on April 24, 2015, 5:39 PM
 */

#ifndef UART_HEADER_H
#define	UART_HEADER_H

#define UART1_RXN_PRIORITY          IPC2bits.U1RXIP     =   4
#define UART1_RX_INTR_EN            IEC0bits.U1RXIE     =   1
#define UART1_RX_INTR_DIS           IEC0bits.U1RXIE     =   0
#define UART1_RX_INTR_FLAG_CLEAR    IFS0bits.U1RXIF     =   0
#define UART1_RX_INTR_FLAG          IFS0bits.U1RXIF

#define UART1_TXN_PRIORITY          IPC3bits.U1TXIP     =   2
#define UART1_TXN_INTR_EN           IEC0bits.U1TXIE     =   1
#define UART1_TXN_INTR_DIS          IEC0bits.U1TXIE     =   0
#define UART1_TXN_INTR_FLAG_CLEAR   IFS0bits.U1TXIF     =   0
#define UART1_TXN_INTR_FLAG         IFS0bits.U1TXIF

#define UART2_RXN_PRIORITY          IPC7bits.U2RXIP     =   2
#define UART2_RXN_PRIORITY          IPC7bits.U2RXIP     =   2
#define UART2_RX_INTR_EN            IEC1bits.U2RXIE     =   1
#define UART2_RX_INTR_DIS           IEC1bits.U2RXIE     =   0
#define UART2_RX_INTR_FLAG_CLEAR    IFS1bits.U2RXIF     =   0
#define UART2_RX_INTR_FLAG          IFS1bits.U2RXIF

#define UART2_TXN_PRIORITY          IPC7bits.U2TXIP     =   2
#define UART2_TXN_INTR_EN           IEC1bits.U2TXIE     =   1
#define UART2_TXN_INTR_DIS          IEC1bits.U2TXIE     =   0
#define UART2_TXN_INTR_FLAG_CLEAR   IFS1bits.U2TXIF     =   0
#define UART2_TXN_INTR_FLAG         IFS1bits.U2TXIF

#define UART3_RXN_PRIORITY          IPC20bits.U3RXIP    =   4
#define UART3_RX_INTR_EN            IEC5bits.U3RXIE     =   1
#define UART3_RX_INTR_DIS           IEC5bits.U3RXIE     =   0
#define UART3_RX_INTR_FLAG_CLEAR    IFS5bits.U3RXIF     =   0
#define UART3_RX_INTR_FLAG          IFS5bits.U3RXIF

#define UART3_TXN_PRIORITY          IPC20bits.U3TXIP    =   2
#define UART3_TXN_INTR_EN           IEC5bits.U3TXIE     =   1
#define UART3_TXN_INTR_DIS          IEC5bits.U3TXIE     =   0
#define UART3_TXN_INTR_FLAG_CLEAR   IFS5bits.U3TXIF     =   0
#define UART3_TXN_INTR_FLAG         IFS5bits.U3TXIF
    
#define UART4_RXN_PRIORITY          IPC22bits.U4RXIP    =   3
#define UART4_RX_INTR_EN            IEC5bits.U4RXIE     =   1
#define UART4_RX_INTR_DIS           IEC5bits.U4RXIE     =   0
#define UART4_RX_INTR_FLAG_CLEAR    IFS5bits.U4RXIF     =   0
#define UART4_RX_INTR_FLAG          IFS5bits.U4RXIF

#define UART4_TXN_PRIORITY          IPC22bits.U4TXIP    =   2
#define UART4_TXN_INTR_EN           IEC5bits.U4TXIE     =   1
#define UART4_TXN_INTR_DIS          IEC5bits.U4TXIE     =   0
#define UART4_TXN_INTR_FLAG_CLEAR   IFS5bits.U4TXIF     =   0
#define UART4_TXN_INTR_FLAG         IFS5bits.U4TXIF

void uart1_init();
void uart1_Tx( char);
void uart1_string_Tx( char *);
unsigned char uart1_Rx(void );
void uart1_flushout();
void uart1_Tx_len( char *ptr,uint8_t len);

#ifdef	__cplusplus
extern "C" {
#endif

    
#ifdef	__cplusplus
}
#endif

#endif	/* UART_HEADER_H */

