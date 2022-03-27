/*
 * StdTypes.h
 *
 *  Created on: Apr 15, 2021
 *      Author: Mohamed
 */

#ifndef STDTYPES_H_
#define STDTYPES_H_


typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef char sint8;
typedef short int sint16;
typedef int sint32;
typedef float sfloat32;
typedef double sfloat64;

typedef enum
{
	Err_OK=0,
	Err_INV_IN,
	Err_INV_OP,
	Err_GEN_NOK,
}StdErr_t;


#endif /* STDTYPES_H_ */
