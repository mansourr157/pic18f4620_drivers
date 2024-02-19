/* 
 * File:   hal_eeprom.h
 * Author: Mansour
 *
 * Created on December 6, 2023, 12:30 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*   section: Includes  */


//#include "../interrupts/mcal_interrupt_cfg.h"
#include "../mcal_std_types.h"
//#include "pic18f4620.h"


/*   section: Macros  */

#define ACCESS_FLASH_PROGRAM_MEMORY  1
#define ACCESS_DATA_EEPROM_MEMORY      0

#define ACCESS_CONFIGURATION_REGISTERS       1
#define ACCESS_FLASH_OR_EEPROM_MEMORY     0 

#define ALLOW_WRITE_CYCLES_TO_FLASH_OR_EEPROM     1
#define INHIBITS_WRITE_CYCLES_TO_FLASH_OR_EEPROM  0

#define INITIATE_THE_ERASE_WRITE_CYCLE  1
#define WRITE_COMPLETED                           0

#define INITIATE_THE_READ_CYCLE              1
#define READ_COMPLETED                           0

/*   section: Macro Functions declarations */


/*   section: Data Types declarations */


/*   section: Function declarations  */

std_ReturnType EEPROM_WriteByte( uint16 dAdd , uint8 data ) ;
std_ReturnType EEPROM_ReadByte( uint16 dAdd , uint8 *data ) ; 

#endif	/* HAL_EEPROM_H */

