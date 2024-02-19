/* 
 * File:   ecu_keypad.h
 * Author: Mansour
 *
 * Created on October 27, 2023, 8:32 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*   section: Includes  */

#include "ecu_keypad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*   section: Macros  */

#define KEYPAD_ROWS           4
#define KEYPAD_COLUMNS     4

/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

typedef struct {
    
    pin_config_t keypad_rows[KEYPAD_ROWS];
    pin_config_t keypad_columns[KEYPAD_COLUMNS];
    
}keypad_t;

/*   section: Function declarations  */

std_ReturnType keypad_initialize ( keypad_t *keypad);
std_ReturnType keypad_return_button ( keypad_t *keypad , uint8 *button);



#endif	/* ECU_KEYPAD_H */

