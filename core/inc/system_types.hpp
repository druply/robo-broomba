/*
 * datatypes.h
 *
 *  Created on: Apr 3, 2019
 *      Author: rortega2
 */



#include <stdint.h>


#ifndef boolean
#define boolean boolean
typedef unsigned char boolean;
#endif /* kcg_bool */

#ifndef __cplusplus

#ifndef bool
#define bool bool
typedef unsigned char bool;
#endif /* kcg_bool */

#endif


#ifndef uint64
#define uint64 uint64
typedef unsigned long long uint64;
#endif /* kcg_uint64 */

#ifndef uint32
#define uint32 uint32
typedef unsigned long uint32;
#endif /* kcg_uint32 */

#ifndef uint16
#define uint16 uint16
typedef unsigned short uint16;
#endif /* kcg_uint16 */

#ifndef uint8
#define uint8 uint8
typedef unsigned char uint8;
#endif /* kcg_uint8 */


#ifndef int32
#define int32 int32
typedef signed long int32;
#endif /* kcg_int32 */

#ifndef int16
#define int16 int16
typedef signed short int16;
#endif /* kcg_int16 */

#ifndef int8
#define int8 int8
typedef signed char int8;
#endif /* kcg_int8 */


typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16		vint16; /* 16 bits */
typedef volatile int32		vint32; /* 32 bits */

typedef volatile uint8		vuint8;  /*  8 bits */
typedef volatile uint16		vuint16; /* 16 bits */
typedef volatile uint32		vuint32; /* 32 bits */


#define ENABLE		1U
#define	TRUE		(uint8_t)1
#define	FALSE		(uint8_t)0



#define Tx_OK			0
#define Tx_NOK			1

