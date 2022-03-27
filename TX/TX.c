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
int counter=0,flag10=0,flag=1;
char test[4];
int temp ;
int temp_flag=0,heart_flag=0, flag_finish=0;



// wifi functions
void ESP8266_VidInit();
void ESP8266_VidConnectToWiFi(u8* SSID, u8* Password);
void ESP8266_VidConnectToSrvTcp(u8* Copy_u8Domain, u8* Copy_u8Port);

void ESP8266_VidSendHB(u8 Copy_u8HB);
void ESP8266_VidSendPR(u8 Copy_u8PR);

//-------------------------------------------
//ADC functions-----------------------
void ADC_Init();

void ADC_Temp_Init(void);
//int ADC_Read(char channel);


int main() {
	sei();
	ESP8266_VidInit();  //intilize wifi
	ESP8266_VidConnectToWiFi("sayed","11112222");  //connect to wifi


	ADC_Init();    // adc intilize for heart beat
	TCCR0=0x03;     //timers
	TIMSK|=0x01;


	while (1) {

		if (flag_finish==1)
		{
			//wifi part sends the data in the variable
						// we will send variable (bpm )for heart beat
			// we will send variable (temp)for temprature

			 ESP8266_VidSendHB(bpm);
			 ESP8266_VidSendPR(temp);


			flag_finish=0;
		}



	}
}





void ADC_Init()  // intilizing adc for heart beat
{

	ClrBit(DDRA, 1);  // make ADC channel pin input for heart
	ADCSRA = 0x8F;  // enable ADC with frequency 8M/128  and interrupt enable
	ADMUX = 0x40; //set reference VCC
}



void ADC_Temp_Init(void)   // intilizing adc for temp
{
	ClrBit(DDRA,0);  // make ADC channel pin input
	ADCSRA=0x8F;  // enable ADC with frequency 8M/128
	ADMUX=0x40; //set reference VCC
}


ISR(ADC_vect)
{  if (heart_flag==1)
   {
	AinLow = (int) ADCL;
	Ain = ADCH * 256;
	Ain = Ain + AinLow;
	if (Ain>=650)
	{ bpm++;}

	//bpm is the variable i want send for tmepreature;
    }
   else if(temp_flag==1)
	{
	  temp=ADCL*2.5; // 2.5 is the step size 2.5mV
	  	temp/=10; // LM35 return 10mv / celsius
	  	_delay_ms(50);

	  	flag_finish=1;

	  	//temp is the variable i want send for tmepreature

	}
}

ISR(TIMER0_OVF_vect)
{
	flag10++;
	if (flag10<5000)
	{
		if (temp_flag==1 && heart_flag==0)
	     {
		     ADC_Init();      //changing temp initlization to heart intilization

	     }
		if (counter==100)
		{
			counter=0;
			temp_flag=0;
			heart_flag=1;
			SetBit(ADCSRA,ADSC);

		}
		else
		{
			counter++;
		}
	}
	else
	{
		ADC_Temp_Init();
		temp_flag=1;
		heart_flag=0;
		SetBit(ADCSRA,ADSC);

		/*
		LCD_vidCmd(CMD_CLEAR);
		LCD_vidCmd(CMD_HOME);
		itoa(bpm,test,10);
		LCD_vidDispString((uint8*) test);
		LCD_vidDispString((uint8*) " Finish");*/
		flag=0;

		flag10=0;
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

void ESP8266_VidSendHB(u8 Copy_u8HB)
{
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	if(((Copy_u8HB/10)/10)==0)
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=59\r\n" );
	}
	else
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=60\r\n" );
	}
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/TransmitterHB.php?data=");
	USART_SendInteger(Copy_u8HB);
	USART_SendStr((u8 *)"\r\n");
	_delay_ms( 1000 );
	_delay_ms( 1000 );


}
void ESP8266_VidSendPR(u8 Copy_u8PR)
{
	ESP8266_VidConnectToSrvTcp ("162.253.155.226", "80" );
	if(((Copy_u8PR/10)/10)==0)
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=59\r\n" );
	}
	else
	{
		USART_SendStr( (u8 *) "AT+CIPSEND=60\r\n" );
	}
	_delay_ms( 100 );

	USART_SendStr( (u8 *) "GET http://eece2023.freevar.com/TransmitterPR.php?data=");
	USART_SendInteger(Copy_u8PR);
	USART_SendStr((u8 *)"\r\n");
	_delay_ms( 1000 );
	_delay_ms( 1000 );


}





