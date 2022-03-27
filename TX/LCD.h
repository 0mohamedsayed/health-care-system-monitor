/*
 * LCD.h
 *
 *  Created on: Apr 23, 2021
 *      Author: Mohamed
 */

#ifndef LCD_H_
#define LCD_H_

#define DISABLE 0
#define ENABLE 1
#define BIT_MODE_4 DISABLE // Enable it for 4 bit mode


//configure this macros according your HW connection
#define PORT_DATA_NO D
#define PORT_CTRL_NO C
#define RS PIN7
#define EN PIN5
#define RW PIN6

#if BIT_MODE_4 == ENABLE
#define D4 PIN4
#define D5 PIN5
#define D6 PIN6
#define D7 PIN7
#endif

#define CMD_DISPLAY_OFF       0x08          // turn display off
#define CMD_RESET             0x30          // reset the LCD
#define CMD_SET_CURSOR        0x80          // set cursor position
#define CMD_CLEAR             0x01          // replace all characters with ASCII 'space'
#define CMD_HOME              0x80          // return cursor to first position on first line
#define CMD_ENTRY_MODE        0x06          // shift cursor from left to right on read/write
#define CMD_FUNCTION_8BIT     0x38          // 8-bit data, 2-line display, 5 x 7 font
#define CMD_DISPLAY_ON        0x0C          // display on, cursor off, don't blink character
#define CMD_SECONED_LINE      0xC0

extern void LCD_vidInit(void);
extern void LCD_vidCmd(uint8 cmd);
extern void LCD_vidDispChar(uint8 data);
extern void LCD_vidDispString(uint8 *data);


#endif /* LCD_H_ */
