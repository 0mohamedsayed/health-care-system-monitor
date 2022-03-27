/*
 * USART_priv.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Askar
 */

#ifndef USART_PRIV_H_
#define USART_PRIV_H_

/********UART comm. protocol registers**************/
#define UBRRH (*(volatile u8*)0x40)
#define UCSRC (*(volatile u8*)0x40)
#define UBRRL (*(volatile u8*)0x29)
#define UDR (*(volatile u8*)0x2C)
#define UCSRB (*(volatile u8*)0x2A)
#define UCSRA (*(volatile u8*)0x2B)


/*************UCSRC bits************/
#define URSEL 7
#define UMSEL 6
#define UPM1 5
#define UPM0 4
#define USBS 3
#define UCSZ1 2
#define UCSZ0 1
#define UCPOL 0

/************UCSRB bits*************/
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN 4
#define TXEN 3
#define UCSZ2 2
#define RXB8 1
#define TXB8 0

/*********UCSRA bits******************/
#define RXC 7
#define TXC 6
#define UDRE 5
#define FE 4
#define DOR 3
#define PE 2
#define U2X 1
#define MPCM 0


/***********Parity configs***********/
#define DISABLED 0
#define ENABLED_EVEN 1
#define ENABLED_ODD 2



#endif /* USART_PRIV_H_ */
