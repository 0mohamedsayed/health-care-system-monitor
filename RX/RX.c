/*
 * main.c
 *
 *  Created on: May 1, 2021
 *      Author: Mohamed
 */

#include "StdTypes.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include "DIODrv.h"
#include "Utils.h"
#include "LCD.h"


#include "std_types.h"
#include "bit_math.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include <avr/delay.h>


#define F_CPU 8000000UL
#define RESET_PORT PORTA
#define RESET_PIN PIN0

#define SetBit(Var,BitNum) (Var|=(1<<BitNum))     // this is for heat sens.
#define ClrBit(Var,BitNum) (Var&=~(1<<BitNum))     // this is for heat sens.



int Ain, AinLow,bpm=0;
char test[4];
char test2[4];
int temp ;
int  flag_begin=0, flag_final=0;
u8* arr1,arr2;





// wifi functions
void ESP8266_VidInit();
void ESP8266_VidConnectToWiFi(u8* SSID, u8* Password);
void ESP8266_VidConnectToSrvTcp(u8* Copy_u8Domain, u8* Copy_u8Port);

u8 ESP8266_u8GetHB(u8* arr);
u8 ESP8266_u8GetPR(u8* arr);

//-------------------------------------------



int main() {
	DDRB=0xff;
	DIO_vidWriteOnPort(PORTB,0x00);
	sei();
	ESP8266_VidInit();  //intilize wifi
	ESP8266_VidConnectToWiFi("sayed","11112222");  //connect to wifi
	LCD_vidInit();


	while (1) {

		if (flag_begin==0)
		{
			LCD_vidCmd(CMD_CLEAR);
			LCD_vidCmd(CMD_HOME);
			LCD_vidDispString((uint8*) " put ur finger");
			LCD_vidCmd(CMD_SECONED_LINE);
    		LCD_vidDispString((uint8*) " please wait");


			flag_begin=1;
			_delay_ms(2000);
		}

        // i recived the varibles in bpm and temp
		 bpm=ESP8266_u8GetHB(arr1);
		  temp=ESP8266_u8GetPR(arr2 );

		if (flag_final==1)
				{
		        	if((temp>37) ||(bpm>=100)||(bpm<60))
			       {
			       	DIO_vidWriteOnPort(PORTB,0x01);
				     _delay_ms(2000);
				     DIO_vidWriteOnPort(PORTB,0x00);

			         }


					LCD_vidCmd(CMD_CLEAR);
					LCD_vidCmd(CMD_HOME);
					LCD_vidDispString((uint8*)"Bpm=");
		    		itoa(bpm,test,10);
		    		LCD_vidDispString((uint8*) test);

		    		LCD_vidCmd(CMD_SECONED_LINE);
		    		LCD_vidDispString((uint8*)"temp=");
		    		itoa(temp,test2,10);
		    		LCD_vidDispString((uint8*) test2);


		    		//need to down to the next line the crusor

		    		LCD_vidDispString((uint8*) " Finish");






		    		flag_final=0;
                    _delay_ms(5000);
					flag_begin=0;

				}


	    }
}







//the function of wifi---------------------
void ESP8266_VidInit()
{
	//disable echo
	USART_SendStr( (u8 *)"ATE0\r\n" );
	_delay_ms( 1000 );

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	USART_SendStr( (u8 *)"AT\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (u8 *)"AT+CWMODE=1\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (u8 *) "AT+CIPMODE=0\r\n" );
	_delay_ms( 1000 );

	USART_SendStr( (u8 *) "AT+CIPMUX=0\r\n" );
	_delay_ms( 1000 );

}

void ESP8266_VidConnectToWiFi(u8* SSID, u8* Password)
{
	USART_SendStr( (u8 *) "AT+CWJAP_CUR=\"" );
	USART_SendStr( (u8 *) SSID );
	USART_SendStr( (u8 *) "\",\"" );
	USART_SendStr( (u8 *) Password);
	USART_SendStr( (u8 *) "\"\r\n");
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );
	_delay_ms( 1000 );

}

void ESP8266_VidConnectToSrvTcp(u8* Copy_u8Domain, u8* Copy_u8Port)
{
	USART_SendStr( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	USART_SendStr( (u8 *) Copy_u8Domain );
	USART_SendStr( (u8 *) "\"," );
	USART_SendStr( (u8 *) Copy_u8Port );
	USART_SendStr( (u8 *) "\r\n" );
	_delay_ms( 1000 );

}

u8 ESP8266_u8GetHB(u8* arr)
{
	u8 result=0;
	u8 i=0;
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	USART_SendStr( (u8 *) "AT+CIPSEND=55\r\n" );
	_delay_ms( 100 );
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/RecieverHB.php?line=0\r\n");

	for(i=0;i<45;i++)
	{
		arr[i]=USART_ReceiveDataPolling();
	}
	result = (arr[38]-48)*10+(arr[39]-48);
	if(arr[40]>47 && arr[40]<58)
	{
		result = (arr[38]-48)*100+(arr[39]-48)*10+(arr[40]-48);
	}
	return result;
}
u8 ESP8266_u8GetPR(u8* arr)
{
	u8 result=0;
	u8 i=0;
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	USART_SendStr( (u8 *) "AT+CIPSEND=55\r\n" );
	_delay_ms( 100 );
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/RecieverPR.php?line=0\r\n");

	for(i=0;i<45;i++)
	{
		arr[i]=USART_ReceiveDataPolling();
	}
	result = (arr[38]-48)*10+(arr[39]-48);
	if(arr[40]>47 && arr[40]<58)
	{
		result = (arr[38]-48)*100+(arr[39]-48)*10+(arr[40]-48);
	}

	flag_final=1; //to enter the if after it
	return result;
}






