/*
 * DIO_interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Zengy
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

//***********************************************************
//*********************Public defenitions********************
//***********************************************************

/******************Port macros*************************/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/******************Value macros**********************/
#define HIGH 1 //High value for AVR
#define LOW 0 //Low value for AVR

/******************Direction macros****************/
#define INPUT 0 // Input direction for AVR
#define OUTPUT 1 // Output direction for AVR

/******************Pin macros********************/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

//***********************************************************
//*********************Public functions**********************
//***********************************************************


/*
 * port_indx  : Port index
 * pin_indx   : Pin index
 * val        : Value
 * dir        : Direction
 *
 */
void DIO_SetPinDir(u8 port_indx, u8 pin_indx, u8 val); // set pin direction (input,output) for AVR
void DIO_SetPinVal(u8 port_indx, u8 pin_indx, u8 dir); // set pin value (high,low) value for AVR
void DIO_SetPortDir(u8 port_indx, u8 val); // set port direction (input,output) for AVR
void DIO_SetPortVal(u8 port_indx, u8 val); // set port value (high,low) for AVR
void DIO_TogglePinVal(u8 port_indx, u8 pin_indx); // toggles the pin value from high to low or vice versa
void DIO_SetNippleVal(u8 port_indx, u8 nipple, u8 val); // to set 4 pins value
void DIO_SetNippleDir(u8 port_indx, u8 nipple, u8 dir); // sets 4 pins direction
void DIO_AssignPortVal(u8 port_indx, u8 val); //assigns a value to a port
void DIO_AssignNippleVal(u8 port_indx, u8 nipple, u8 val); //assgin certain value to high/low nipple of a port
u8 DIO_GetPinVal(u8 port_indx, u8 pin_indx); // get pin value (high,low) from a pin for AVR



#endif /* DIO_INTERFACE_H_ */
