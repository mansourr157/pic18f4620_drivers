/* 
 * File:   ecu_button.h
 * Author: Mansour
 *
 * Created on October 19, 2023, 4:18 PM
 */


#ifndef BUTTON_H
#define	BUTTON_H

/*   section: Includes  */

#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/*   section: Macros  */


/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

typedef enum{
            BUTTON_PRESSED ,
            BUTTON_RELEASED
}button_status_t;

typedef enum{
            ACTIVE_HIGH ,
            ACTIVE_LOW
}button_active_t;

typedef struct {
    
    uint8  port                        :3 ;
    uint8  pin                         :3 ;
    uint8 button_status          :1 ;
    uint8 button_connection   :1 ;
            
}button_t;


/*   section: Function declarations  */

std_ReturnType button_initialize(const button_t *button);
std_ReturnType button_read_status(const button_t *btn , button_status_t *btn_status);

#endif	/* BUTTON_H */



