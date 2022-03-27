#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(byte,bit) byte|=(1<<bit)
#define CLEAR_BIT(byte, bit) (byte)&=~(1<<bit)
#define GET_BIT(byte, bit) (0x01&(byte>>bit))
#define TOGGLE_BIT(byte,bit) byte^=(1<<bit)
#define SET_BYTE(byte) byte=0xff;
#define CLEAR_BYTE(byte) byte=0x00;
#define SET_HIGH_NIBBLE(byte) byte|=0b11110000
#define CLEAR_HIGH_NIBBLE(byte) byte&=0b00001111
#define SET_LOW_NIBBLE(byte) byte|=0b00001111
#define CLEAR_LOW_NIBBLE(byte) byte&=0b11110000

#define ASSIGN_HIGH_NIBBLE(byte,number) \
CLEAR_LOW_NIBBLE(number);\
byte|=number;\
SET_LOW_NIBBLE(number);\
byte&=number

#define ASSIGN_LOW_NIBBLE(byte,number) \
CLEAR_HIGH_NIBBLE(number);\
byte|=number;\
SET_HIGH_NIBBLE(number);\
byte&=number


#endif
