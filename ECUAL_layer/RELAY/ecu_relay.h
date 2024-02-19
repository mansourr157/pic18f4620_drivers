/* 
 * File:   ecu_relay.h
 * Author: Mansour
 *
 * Created on October 21, 2023, 4:23 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*   section: Includes  */

#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*   section: Macros  */


/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

typedef enum {
            RELAY_OFF,
            RELAY_ON
}relay_status_t;

typedef struct {
    
    uint8 port           :3;
    uint8 pin            :3;
    uint8 status       :3;
    uint8 reserved    :1;
    
}relay_t;
/*   section: Function declarations  */

std_ReturnType relay_initialize (const relay_t *relay);
std_ReturnType relay_turn_on (const relay_t *relay);
std_ReturnType relay_turn_off (const relay_t *relay);

#endif	/* ECU_RELAY_H */

