/* 
 * File:   ecu_dc_motor.h
 * Author: Mansour
 *
 * Created on October 21, 2023, 5:25 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*   section: Includes  */

#include "ecu_dc_motor_cfg.h" 
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*   section: Macros  */

#define DC_MOTOR_PIN_1          0x00U
#define DC_MOTOR_PIN_2          0x01U

/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

typedef enum {
            MOTOR_OFF ,
            MOTOR_ON
}motor_status_t;


typedef struct {
            pin_config_t motor_pins[2] ;
}dc_motor_t;



/*   section: Function declarations  */

std_ReturnType dc_motor_initialize ( dc_motor_t *motor ) ;
std_ReturnType dc_motor_move_right ( dc_motor_t *motor ) ;
std_ReturnType dc_motor_move_left ( dc_motor_t *motor ) ;
std_ReturnType dc_motor_stop ( dc_motor_t *motor ) ;

#endif	/* ECU_DC_MOTOR_H */

