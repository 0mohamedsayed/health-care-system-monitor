/*
 * DIODrv.c
 *
 *  Created on: Apr 15, 2021
 *      Author: Muhammad
 */

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIODrv.h"

// use port number A,B,C,D
// use pin number PIN0..7
//use direction INPUT , OUTPUT , INPULLUP

void DIO_vidSetPinDir(uint8 port_no , uint8 pin_no , uint8 dir) {
	switch(port_no) {
	case A:
		if (dir==0) ClrBit(DDRA,pin_no);
		else if (dir==1) SetBit(DDRA,pin_no);
		else if (dir==2) {ClrBit(DDRA,pin_no); SetBit(PORTA,pin_no);}
		break;
	case B:
			if (dir==0) ClrBit(DDRB,pin_no);
			else if (dir==1) SetBit(DDRB,pin_no);
			else if (dir==2) {ClrBit(DDRB,pin_no); SetBit(PORTB,pin_no);}
			break;
	case C:
			if (dir==0) ClrBit(DDRC,pin_no);
			else if (dir==1) SetBit(DDRC,pin_no);
			else if (dir==2) {ClrBit(DDRC,pin_no); SetBit(PORTC,pin_no);}
			break;
	case D:
			if (dir==0) ClrBit(DDRD,pin_no);
			else if (dir==1) SetBit(DDRD,pin_no);
			else if (dir==2) {ClrBit(DDRD,pin_no); SetBit(PORTD,pin_no);}
			break;
	}
}

void DIO_vidSetPortDirMask(uint8 port_no , uint8 DirMask) {
	switch (port_no){
	case A:
			DDRA=DirMask;
			break;
	case B:
			DDRB=DirMask;
			break;
	case C:
			DDRC=DirMask;
			break;
	case D:
			DDRD=DirMask;
			break;
	}
}

void DIO_vidSetPortDir(uint8 port_no , uint8 dir) {
	switch (port_no){
	case A:
		if (dir==0)      {DDRA=0;}
		else if (dir==1) {DDRA=0xFF;}
		else if (dir==2) {DDRA=0; PORTA=0xFF;}
		break;
	case B:
		if (dir==0)      {DDRB=0;}
		else if (dir==1) {DDRB=0xFF;}
		else if (dir==2) {DDRB=0; PORTB=0xFF;}
		break;
	case C:
			if (dir==0)      {DDRC=0;}
			else if (dir==1) {DDRC=0xFF;}
			else if (dir==2) {DDRC=0; PORTC=0xFF;}
			break;
	case D:
			if (dir==0)      {DDRD=0;}
			else if (dir==1) {DDRD=0xFF;}
			else if (dir==2) {DDRD=0; PORTD=0xFF;}
			break;
	}
}

void DIO_vidWriteOnPin(uint8 port_no , uint8 pin_no , uint8 level) {
	switch(port_no) {
	case A:
		if (level==0) ClrBit(PORTA,pin_no);
		else if (level==1) SetBit(PORTA,pin_no);
		break;
	case B:
			if (level==0) ClrBit(PORTB,pin_no);
			else if (level==1) SetBit(PORTB,pin_no);
			break;
	case C:
			if (level==0) ClrBit(PORTC,pin_no);
			else if (level==1) SetBit(PORTC,pin_no);
			break;
	case D:
			if (level==0) ClrBit(PORTD,pin_no);
			else if (level==1) SetBit(PORTD,pin_no);
			break;
	}
}

void DIO_vidWriteOnPort(uint8 port_no , uint8 level) {
	switch (port_no){
			case A:
					PORTA=level;
					break;
			case B:
					PORTB=level;
					break;
			case C:
					PORTC=level;
					break;
			case D:
					PORTD=level;
					break;
		}
}

/*void DIO_vidWriteOnPort(uint8 port_no , uint8 level) {
	switch (port_no){
		case A:
			if (level==0)      {PORTA=0;}
			else if (level==1) {PORTA=0xFF;}
			break;
		case B:
			if (level==0)      {PORTB=0;}
			else if (level==1) {PORTB=0xFF;}
				break;
		case C:
				if (level==0)      {PORTC=0;}
				else if (level==1) {PORTC=0xFF;}
				break;
		case D:
				if (level==0)      {PORTD=0;}
				else if (level==1) {PORTD=0xFF;}
				break;
	}
}*/

uint8 DIO_u8ReadFromPin(uint8 port_no , uint8 pin_no) {
	uint8 temp;
	switch(port_no) {
		case A:
				temp=PINA;
				break;
		case B:
				temp=PINB;
				break;
		case C:
				temp=PINC;
				break;
		case D:
				temp=PIND;
				break;
		default : //Do Nothing
				break;
		}
	return temp;
}

uint8 DIO_u8ReadFromPort(uint8 port_no) {
	uint8 temp;
	switch(port_no) {
		case A:
				temp=PINA;
				break;
		case B:
				temp=PINB;
				break;
		case C:
				temp=PINC;
				break;
		case D:
				temp=PIND;
				break;

		default : //Do Nothing
				break;
		}
	return temp;
}
