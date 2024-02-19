/* 
 * File:   mcal_std_types.h
 * Author: Mansour
 *
 * Created on October 1, 2023, 3:30 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/*   section: Includes  */

#include "../MCAL_layer/std_libraries.h"
#include "../MCAL_layer/compiler.h"


/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

typedef  unsigned char uint8 ;
typedef  unsigned short uint16 ;
typedef  unsigned long uint32 ;

typedef  signed char sint8 ;
typedef  signed short sint16 ;
typedef  signed long sint32 ;

typedef uint8 std_ReturnType ;

/*   section: Macros declarations */

#define STD_HIGH                0x01
#define STD_LOW                 0x00

#define STD_ON                    0x01
#define STD_OFF                  0x00

#define STD_ACTIVE             0x01
#define STD_IDLE                 0x00

#define CONFIG_ENABLE      0x01
#define CONFIG_DISABLE     0x00

#define E_OK                   (std_ReturnType)0x00
#define E_NOT_OK           (std_ReturnType)0x01

/*   section: Function declarations  */

#endif	/* MCAL_STD_TYPES_H */

