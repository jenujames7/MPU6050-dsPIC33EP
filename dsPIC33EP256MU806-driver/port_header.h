/* 
 * File:   port_header.h
 * Author: user
 *
 * Created on April 24, 2015, 5:50 PM
 */

#ifndef PORT_HEADER_H
#define	PORT_HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

void port_init();
void led_blink(int);
void ExtINT_init();

#ifdef	__cplusplus
}
#endif

#endif	/* PORT_HEADER_H */

