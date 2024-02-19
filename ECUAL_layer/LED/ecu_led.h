/* 
 * File:   LED.h
 * Author: Mansour
 *
 * Created on October 1, 2023, 3:45 PM
 */

#ifndef LED_H
#define	LED_H


/*   section: Includes  */

#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/*   section: Macros  */


/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

typedef enum {
            LED_OFF ,
            LED_ON
}led_status;

typedef struct {
            uint8 port       : 3 ;
            uint8 pin        : 3 ;
            uint8 status    : 1 ;
            uint8 reserved : 1 ;
            
}led_t;

/*   section: Function declarations  */

std_ReturnType led_initialize(const led_t *led);
std_ReturnType led_turn_on(const led_t *led);
std_ReturnType led_turn_off(const led_t *led);
std_ReturnType led_toggle(const led_t *led);


#endif	/* LED_H */

