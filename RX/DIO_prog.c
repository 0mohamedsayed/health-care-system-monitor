/*
 * DIO_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zengy
 */

/* including libraries that is needed for this driver*/

#include"std_types.h"
#include"DIO_priv.h"
#include"bit_math.h"
#include"DIO_interface.h"

//***********************************************************
//*********************Driver functions**********************
//***********************************************************

void DIO_SetPinDir(u8 port_indx, u8 pin_indx, u8 dir) // set pin direction (input,output) for AVR
{
	if(dir==INPUT)
	{
		switch(port_indx)
		{
		case PORTA:
			CLEAR_BIT(DDRA_REG,pin_indx);
			break;
		case PORTB:
			CLEAR_BIT(DDRB_REG,pin_indx);
			break;
		case PORTC:
			CLEAR_BIT(DDRC_REG,pin_indx);
			break;
		case PORTD:
			CLEAR_BIT(DDRD_REG,pin_indx);
			break;
		}
	}
	else if(dir==OUTPUT)
		{
			switch(port_indx)
			{
			case PORTA:
				SET_BIT(DDRA_REG,pin_indx);
				break;
			case PORTB:
				SET_BIT(DDRB_REG,pin_indx);
				break;
			case PORTC:
				SET_BIT(DDRC_REG,pin_indx);
				break;
			case PORTD:
				SET_BIT(DDRD_REG,pin_indx);
				break;
			}
		}

}
void DIO_SetPinVal(u8 port_indx, u8 pin_indx, u8 val) // set pin value (high,low) value for AVR
{
	if(val==LOW)
		{
			switch(port_indx)
			{
			case PORTA:
				CLEAR_BIT(PORTA_REG,pin_indx);
				break;
			case PORTB:
				CLEAR_BIT(PORTB_REG,pin_indx);
				break;
			case PORTC:
				CLEAR_BIT(PORTC_REG,pin_indx);
				break;
			case PORTD:
				CLEAR_BIT(PORTD_REG,pin_indx);
				break;
			}
		}
		if(val==HIGH)
			{
			switch(port_indx)
			{
			case PORTA:
				SET_BIT(PORTA_REG,pin_indx);
				break;
			case PORTB:
				SET_BIT(PORTB_REG,pin_indx);
				break;
			case PORTC:
				SET_BIT(PORTC_REG,pin_indx);
				break;
			case PORTD:
				SET_BIT(PORTD_REG,pin_indx);
				break;
			}
		}

}
void DIO_SetPortDir(u8 port_indx, u8 dir) // set port direction (input,output) for AVR
{
	if(dir==INPUT)
	{
		switch (port_indx)
		{
		case PORTA:
			CLEAR_BYTE(DDRA_REG);
			break;
		case PORTB:
			CLEAR_BYTE(DDRB_REG);
			break;
		case PORTC:
			CLEAR_BYTE(DDRC_REG);
			break;
		case PORTD:
			CLEAR_BYTE(DDRD_REG);
			break;
		}
	}
	if(dir==OUTPUT)
	{
		switch (port_indx)
		{
			case PORTA:
				SET_BYTE(DDRA_REG);
				break;
			case PORTB:
				SET_BYTE(DDRB_REG);
				break;
			case PORTC:
				SET_BYTE(DDRC_REG);
				break;
			case PORTD:
				SET_BYTE(DDRD_REG);
				break;
				}
	}
}
void DIO_SetPortVal(u8 port_indx, u8 val) // set port value (high,low) for AVR
{
	if(val==LOW)
		{
			switch (port_indx)
			{
			case PORTA:
				CLEAR_BYTE(PORTA_REG);
				break;
			case PORTB:
				CLEAR_BYTE(PORTB_REG);
				break;
			case PORTC:
				CLEAR_BYTE(PORTC_REG);
				break;
			case PORTD:
				CLEAR_BYTE(PORTD_REG);
				break;
			}
		}
		if(val==HIGH)
		{
			switch (port_indx)
			{
				case PORTA:
					SET_BYTE(PORTA_REG);
					break;
				case PORTB:
					SET_BYTE(PORTB_REG);
					break;
				case PORTC:
					SET_BYTE(PORTC_REG);
					break;
				case PORTD:
					SET_BYTE(PORTD_REG);
					break;
			}
		}
}

void DIO_TogglePinVal(u8 port_indx, u8 pin_indx) // toggles the pin value from high to low or vice versa
{
	switch(port_indx)
	{
	case PORTA:
		TOGGLE_BIT(PORTA_REG,pin_indx);
		break;
	case PORTB:
		TOGGLE_BIT(PORTB_REG,pin_indx);
		break;
	case PORTC:
		TOGGLE_BIT(PORTC_REG,pin_indx);
		break;
	case PORTD:
		TOGGLE_BIT(PORTD_REG,pin_indx);
		break;
	}
}


void DIO_SetNippleDir(u8 port_indx, u8 nipple, u8 dir) // sets 4 pins direction
{
	if(nipple==HIGH)
	{
		if(dir==OUTPUT)
		{
			switch(port_indx)
			{
			case PORTA:
				DDRA_REG|=0b11110000;
				break;
			case PORTB:
				DDRB_REG|=0b11110000;
				break;
			case PORTC:
				DDRC_REG|=0b11110000;
				break;
			case PORTD:
				DDRD_REG|=0b11110000;
				break;
			}
		}
		if(dir==INPUT)
		{
			switch(port_indx)
			{
			case PORTA:
				DDRA_REG&=0b00001111;
				break;
			case PORTB:
				DDRB_REG&=0b00001111;
				break;
			case PORTC:
				DDRC_REG&=0b00001111;
				break;
			case PORTD:
				DDRD_REG&=0b00001111;
				break;
			}
		}
	}
	else if(nipple==LOW)
	{
		if(dir==OUTPUT)
		{
			switch(port_indx)
			{
			case PORTA:
				DDRA_REG|=0b00001111;
				break;
			case PORTB:
				DDRB_REG|=0b00001111;
				break;
			case PORTC:
				DDRC_REG|=0b00001111;
				break;
			case PORTD:
				DDRD_REG|=0b00001111;
				break;
			}
		}
		if(dir==INPUT)
		{
			switch(port_indx)
			{
			case PORTA:
				DDRA_REG&=0b11110000;
				break;
			case PORTB:
				DDRB_REG&=0b11110000;
				break;
			case PORTC:
				DDRC_REG&=0b11110000;
				break;
			case PORTD:
				DDRD_REG&=0b11110000;
				break;
			}

		}
	}
}

void DIO_SetNippleVal(u8 port_indx, u8 nipple, u8 val) // to set 4 pins value
{
if(nipple==HIGH)
{
	if(val==HIGH)
	{
		switch(port_indx)
		{
		case PORTA:
			PORTA_REG|=0b11110000;
			break;
		case PORTB:
			PORTB_REG|=0b11110000;
			break;
		case PORTC:
			PORTC_REG|=0b11110000;
			break;
		case PORTD:
			PORTD_REG|=0b11110000;
			break;
		}
	}
	if(val==LOW)
	{
		switch(port_indx)
		{
		case PORTA:
			PORTA_REG&=0b00001111;
			break;
		case PORTB:
			PORTB_REG&=0b00001111;
			break;
		case PORTC:
			PORTC_REG&=0b00001111;
			break;
		case PORTD:
			PORTD_REG&=0b00001111;
			break;
		}
	}
}
else if(nipple==LOW)
{
	if(val==HIGH)
	{
		switch(port_indx)
		{
		case PORTA:
			PORTA_REG|=0b00001111;
			break;
		case PORTB:
			PORTB_REG|=0b00001111;
			break;
		case PORTC:
			PORTC_REG|=0b00001111;
			break;
		case PORTD:
			PORTD_REG|=0b00001111;
			break;
		}
	}
	if(val==LOW)
	{
		switch(port_indx)
		{
		case PORTA:
			PORTA_REG&=0b11110000;
			break;
		case PORTB:
			PORTB_REG&=0b11110000;
			break;
		case PORTC:
			PORTC_REG&=0b11110000;
			break;
		case PORTD:
			PORTD_REG&=0b11110000;
			break;
		}

	}

	}
}

void DIO_AssignPortVal(u8 port_indx, u8 val) //assigns a value to a port
{
	switch(port_indx)
	{
	case PORTA:
		PORTA_REG=val;
		break;
	case PORTB:
		PORTB_REG=val;
		break;
	case PORTC:
		PORTC_REG=val;
		break;
	case PORTD:
		PORTD_REG=val;
		break;

	}
}


void DIO_AssignNippleVal(u8 port_indx, u8 nipple, u8 val)
{
	if(nipple==HIGH)
	{
		{
			switch(port_indx)
			{
			case PORTA:
				ASSIGN_HIGH_NIBBLE(PORTA_REG,val);
				break;
			case PORTB:
				ASSIGN_HIGH_NIBBLE(PORTB_REG,val);
				break;
			case PORTC:
				ASSIGN_HIGH_NIBBLE(PORTC_REG,val);
				break;
			case PORTD:
				ASSIGN_HIGH_NIBBLE(PORTD_REG,val);
				break;
			}
		}
	}
	else if(nipple==LOW)
	{
			switch(port_indx)
			{
			case PORTA:
				ASSIGN_LOW_NIBBLE(PORTA_REG,val);
				break;
			case PORTB:
				ASSIGN_LOW_NIBBLE(PORTB_REG,val);
				break;
			case PORTC:
				ASSIGN_LOW_NIBBLE(PORTC_REG,val);
				break;
			case PORTD:
				ASSIGN_LOW_NIBBLE(PORTD_REG,val);
				break;
			}
		}
	}


u8 DIO_GetPinVal(u8 port_indx, u8 pin_indx) // get pin value (high,low) from a pin for AVR
{
	u8 pin_value=0;
	switch(port_indx)
	{
	case PORTA:
		pin_value=(PINA_REG)&(1<<pin_indx);
		break;
	case PORTB:
		pin_value=(PINB_REG)&(1<<pin_indx);
		break;
	case PORTC:
		pin_value=(PINC_REG)&(1<<pin_indx);
		break;
	case PORTD:
		pin_value=(PIND_REG)&(1<<pin_indx);
		break;
	}
	return pin_value;
}
