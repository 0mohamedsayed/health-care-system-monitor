/*
 * USART_config.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Askar
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_


/**************USART initialization configurations*****************/
#define RX_ENABLE 1 // Rx enable in initialization function
#define TX_ENABLE 1 // Tx enable in initialization function
#define BAUD_RATE 115200 // baud rate value desired
#define Fosc 8000000 //crystal frequency
#define DATA_BITS 8 // data bits received or sent, enter the number of data bits directly
#define RX_INTERRUPT_ENABLE 0 // enable on receive interrupt
#define TX_INTERRUPT_ENABLE 0 // enable on sent interrupt
#define UDR_EMPTY_INTERRUPT_ENABLE 0 // enable UDR tx buffer clear interrupt
#define SYNC_MODE 0 // enabling sync mode, WARNING: REQUIERS CLOCK
#define PARITY_BITS DISABLED // choosing parity bits
#define STOP_BITS 1 // choosing stop bits 1,2

#endif /* USART_CONFIG_H_ */
