/*
 * LCD.c
 *
 *  Created on: Apr 23, 2021
 *      Author: Mohamed
 */

#undef F_CPU
#define F_CPU 8000000U

#include "StdTypes.h"
#include <util/delay.h>
#include "Utils.h"
#include "DIODrv.h"
#include "LCD.h"


#if BIT_MODE_4 == DISABLE

	void LCD_vidInit(void)
	{
		DIO_vidSetPortDir(PORT_DATA_NO , OUTPUT);
		DIO_vidSetPinDir(PORT_CTRL_NO , EN , OUTPUT);
		DIO_vidSetPinDir(PORT_CTRL_NO , RW , OUTPUT);
		DIO_vidSetPinDir(PORT_CTRL_NO , RS , OUTPUT);

		_delay_ms(50);
		LCD_vidCmd(CMD_FUNCTION_8BIT);
		LCD_vidCmd(CMD_DISPLAY_ON);
		LCD_vidCmd(CMD_ENTRY_MODE);
		LCD_vidCmd(CMD_CLEAR);
		LCD_vidCmd(CMD_HOME);


	}


	void LCD_vidCmd(uint8 cmd)
	{
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RS,LOW);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RW,LOW);

		DIO_vidWriteOnPort(PORT_DATA_NO,cmd);
		_delay_ms(1);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
		_delay_ms(5);

		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		_delay_ms(2);
	}

	void LCD_vidDispChar(uint8 data)
	{
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RS,HIGH);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RW,LOW);

		DIO_vidWriteOnPort(PORT_DATA_NO,data);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
		_delay_ms(5);

		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		_delay_ms(5);
	}

#elif BIT_MODE_4 == ENABLE


	void LCD_vidInit(void)
	{
		DIO_vidSetPinDir(PORT_DATA_NO , D4 , OUTPUT);
		DIO_vidSetPinDir(PORT_DATA_NO , D5 , OUTPUT);
		DIO_vidSetPinDir(PORT_DATA_NO , D6 , OUTPUT);
		DIO_vidSetPinDir(PORT_DATA_NO , D7 , OUTPUT);

		DIO_vidSetPinDir(PORT_CTRL_NO , EN , OUTPUT);
		DIO_vidSetPinDir(PORT_CTRL_NO , RW , OUTPUT);
		DIO_vidSetPinDir(PORT_CTRL_NO , RS , OUTPUT);
		_delay_ms(45);
		for (uint8 i=0;i<2;i++)
		{
			DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
			DIO_vidWriteOnPin(PORT_CTRL_NO,RS,LOW);
			DIO_vidWriteOnPin(PORT_CTRL_NO,RW,LOW);

			DIO_vidWriteOnPin(PORT_DATA_NO,D4,0);
			DIO_vidWriteOnPin(PORT_DATA_NO,D5,1);
			DIO_vidWriteOnPin(PORT_DATA_NO,D6,0);
			DIO_vidWriteOnPin(PORT_DATA_NO,D7,0);
			_delay_ms(1);
			DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
			_delay_ms(5);
			DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
			_delay_ms(1);
		}
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RS,LOW);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RW,LOW);

		DIO_vidWriteOnPin(PORT_DATA_NO,D4,0);
		DIO_vidWriteOnPin(PORT_DATA_NO,D5,0);
		DIO_vidWriteOnPin(PORT_DATA_NO,D6,0);
		DIO_vidWriteOnPin(PORT_DATA_NO,D7,1);
		_delay_ms(1);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
		_delay_ms(5);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		_delay_ms(1);

		LCD_vidCmd(CMD_DISPLAY_ON);
		LCD_vidCmd(CMD_ENTRY_MODE);
		LCD_vidCmd(CMD_CLEAR);
		LCD_vidCmd(CMD_HOME);

		_delay_ms(50);
	}

	void LCD_vidCmd(uint8 cmd)
	{
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RS,LOW);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RW,LOW);

		DIO_vidWriteOnPin(PORT_DATA_NO,D4,GetBit(cmd,4));
		DIO_vidWriteOnPin(PORT_DATA_NO,D5,GetBit(cmd,5));
		DIO_vidWriteOnPin(PORT_DATA_NO,D6,GetBit(cmd,6));
		DIO_vidWriteOnPin(PORT_DATA_NO,D7,GetBit(cmd,7));
		_delay_ms(1);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
		_delay_ms(5);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		_delay_ms(1);

		DIO_vidWriteOnPin(PORT_DATA_NO,D4,GetBit(cmd,0));
		DIO_vidWriteOnPin(PORT_DATA_NO,D5,GetBit(cmd,1));
		DIO_vidWriteOnPin(PORT_DATA_NO,D6,GetBit(cmd,2));
		DIO_vidWriteOnPin(PORT_DATA_NO,D7,GetBit(cmd,3));
		_delay_ms(1);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
		_delay_ms(5);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		_delay_ms(1);
	}

	void LCD_vidDispChar(uint8 data)
	{
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RS,HIGH);
		DIO_vidWriteOnPin(PORT_CTRL_NO,RW,LOW);

		DIO_vidWriteOnPin(PORT_DATA_NO,D4,GetBit(data,4));
		DIO_vidWriteOnPin(PORT_DATA_NO,D5,GetBit(data,5));
		DIO_vidWriteOnPin(PORT_DATA_NO,D6,GetBit(data,6));
		DIO_vidWriteOnPin(PORT_DATA_NO,D7,GetBit(data,7));
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
		_delay_ms(5);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		_delay_ms(5);

		DIO_vidWriteOnPin(PORT_DATA_NO,D4,GetBit(data,0));
		DIO_vidWriteOnPin(PORT_DATA_NO,D5,GetBit(data,1));
		DIO_vidWriteOnPin(PORT_DATA_NO,D6,GetBit(data,2));
		DIO_vidWriteOnPin(PORT_DATA_NO,D7,GetBit(data,3));
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,LOW);
		_delay_ms(5);
		DIO_vidWriteOnPin(PORT_CTRL_NO,EN,HIGH);
		_delay_ms(5);
	}

#endif
void LCD_vidDispString(uint8 *data)
{
	uint8 i=0 ;
	while (data[i]!=0) {
		LCD_vidDispChar(data[i]);
		i++;
		_delay_ms(1);
	}
}


