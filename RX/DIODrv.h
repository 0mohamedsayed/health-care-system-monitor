

#ifndef DIODRV_H_
#define DIODRV_H_

#define INPUT    0
#define OUTPUT   1
#define INPULLUP 2

#define HIGH 1
#define LOW  0

#define A 1
#define B 2
#define C 3
#define D 4

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


extern void DIO_vidSetPinDir(uint8 port_no , uint8 pin_no , uint8 dir);
extern void DIO_vidSetPortDir(uint8 port_no , uint8 dir);
extern void DIO_vidSetPortDirMask(uint8 port_no , uint8 DirMask);

extern void DIO_vidWriteOnPin(uint8 port_no , uint8 pin_no , uint8 level);
extern void DIO_vidWriteOnPort(uint8 port_no , uint8 level);
//extern void DIO_vidWriteOnPortMask(uint8 port_no , uint8 level);

extern uint8 DIO_u8ReadFromPin(uint8 port_no , uint8 pin_no);
extern uint8 DIO_u8ReadFromPort(uint8 port_no);





#endif /* DIODRV_H_ */
