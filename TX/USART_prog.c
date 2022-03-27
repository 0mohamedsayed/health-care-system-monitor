/*
 * USART_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Askar
 */

#include "std_types.h"
#include "bit_math.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "USART_priv.h"

void USART_inti() //initialization of USART com. protocol
{
	u8 UCSRC_val=0;

	// choosing data bits
	#if (DATA_BITS == 5)
		CLEAR_BIT(UCSRB,UCSZ2);
		CLEAR_BIT(UCSRC_val,UCSZ1);
		CLEAR_BIT(UCSRC_val,UCSZ0);
		CLEAR_BIT(UCSRC_val,URSEL);
	#elif (DATA_BITS == 6)
		CLEAR_BIT(UCSRB,UCSZ2);
		CLEAR_BIT(UCSRC_val,UCSZ1);
		SET_BIT(UCSRC_val,UCSZ0);
		CLEAR_BIT(UCSRC_val,URSEL);
	#elif (DATA_BITS == 7)
		CLEAR_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC_val,UCSZ1);
		CLEAR_BIT(UCSRC_val,UCSZ0);
		CLEAR_BIT(UCSRC_val,URSEL);
	#elif (DATA_BITS == 8)
		CLEAR_BIT(UCSRB,UCSZ2);
		UCSRC_val|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	#elif (DATA_BITS == 9)
		SET_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC_val,UCSZ1);
		SET_BIT(UCSRC_val,UCSZ0);
		CLEAR_BIT(UCSRC_val,URSEL);
	#else
		CLEAR_BIT(UCSRB,UCSZ2);
		UCSRC_val|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	#endif

	//choosing stop bits
	#if (STOP_BITS == 1)
		CLEAR_BIT(UCSRC_val,USBS);
	#elif (STOP_BITS == 2)
		SET_BIT(UCSRC_val,USBS);
	#else
		CLEAR_BIT(UCSRC_val,USBS);
	#endif

	//choosing parity bit
	#if(PARITY_BITS == DISABLED)
		CLEAR_BIT(UCSRC_val,UPM1);
		CLEAR_BIT(UCSRC_val,UPM0);
	#elif (PARITY_BITS == ENABLED_ODD)
		UCSRC_val|=(1<<UPM1)|(1<<UPM0);
	#elif (PARITY_BITS == ENABLED_EVEN)
		SET_BIT(UCSRC_val,UPM1);
		CLEAR_BIT(UCSRC_val,UPM0);
	#endif
	//choosing asynchronous or synchronous
	#if SYNC_MODE
		SET_BIT(UCSRC_val,UMSEL);
	#else
		CLEAR_BIT(UCSRC_val,UMSEL);
	#endif

	//choosing interrupts
	#if (RX_INTERRUPT_ENABLE)
		SET_BIT(UCSRB,RXCIE);
	#else
		CLEAR_BIT(UCSRB,RXCIE);
	#endif

	#if(TX_INTERRUPT_ENABLE)
		SET_BIT(UCSRB,TXCIE);
	#else
		CLEAR_BIT(UCSRB,TXCIE);
	#endif

	#if(UDR_EMPTY_INTERRUPT_ENABLE)
		SET_BIT(UCSRB,UDRIE);
	#else
		CLEAR_BIT(UCSRB,UDRIE);
	#endif

	//enabling Tx and Rx
	#if(RX_ENABLE)
		SET_BIT(UCSRB,RXEN);
	#else
		CLEAR_BIT(UCSRB,RXEN);
	#endif

	#if(TX_ENABLE)
		SET_BIT(UCSRB,TXEN);
	#else
		CLEAR_BIT(UCSRB,TXEN);
	#endif

	//choosing baud rate

	UBRRL=51;
	UBRRH=0;

	//assigning UCSRC value into UCSRC register
	UCSRC=UCSRC_val;
}


u8 USART_ReceiveDataPolling() // receive data polling on RXC flag
{
	//waiting for data to be sent and UDR Rx buffer to be filled
	while((GET_BIT(UCSRA,RXC))==0);

	//returning data
	return UDR;
}

u8 USART_ReceiveDataINT() // receive data with RXC interrupt, WARNING ENABLE RXC INT
{
	//returning data
	return UDR;
}


void USART_SendDataPolling(u8 data) // send data polling on UDRE flag
{
	//waiting to UDR Tx buffer to be empty
	while((GET_BIT(UCSRA,UDRE))==0);

	//sending data
	UDR=data;
}

void USART_ReceieveStr(u8* str_data, u8 number) // receive number of elements
{
	u8 counter;
	for(counter=0;counter<number;counter++)
	{
		str_data[counter]=USART_ReceiveDataPolling();
	}
}

void USART_SendDataINT(u8 data) // send data with UDRE interrupt, WARNING ENABLE UDRE INT
{
	//sending data
	UDR=data;
}

void USART_SendStr(u8* str_data)
{
	u8 counter=0;
	while(str_data[counter]!='\0')
	{
		USART_SendDataPolling(str_data[counter]);
		counter++;
	}
}

void USART_SendInteger(volatile u16 Copy_u16Number) //this function to print direct integer number
{
	u8 Local_u8arrStrNumber[5]={10,10,10,10,10};
	u8 Local_u8Counter=4;
	if(Copy_u16Number==0)
	{
		Local_u8arrStrNumber[Local_u8Counter]=Copy_u16Number%10;
		Copy_u16Number/=10;
		Local_u8Counter--;
	}
	while(Copy_u16Number>0)
	{
		Local_u8arrStrNumber[Local_u8Counter]=Copy_u16Number%10;
		Copy_u16Number/=10;
		Local_u8Counter--;
	}
	for(Local_u8Counter=0;Local_u8Counter<5;Local_u8Counter++)
	{
		if(Local_u8arrStrNumber[Local_u8Counter]<=9)
		{
			USART_SendDataPolling((Local_u8arrStrNumber[Local_u8Counter]+48));
		}
	}
}

void USART_EnableRx() // enable rx during runtime
{
	SET_BIT(UCSRB,RXEN);

}

void USART_DisableRx() // disable rx during runtime
{
	CLEAR_BIT(UCSRB,RXEN);

}

void USART_EnableTx() // enable tx during runtime
{
	SET_BIT(UCSRB,TXEN);

}

void USART_DisableTx() // disable tx during runtime
{
	CLEAR_BIT(UCSRB,TXEN);

}
