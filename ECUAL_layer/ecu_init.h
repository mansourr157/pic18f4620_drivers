/* 
 * File:   ecu_init.h
 * Author: Mansour
 *
 * Created on October 27, 2023, 9:29 PM
 */

#ifndef ECU_INIT_H
#define	ECU_INIT_H

/*   section: Includes  */

#include "LED/ecu_led.h"
#include "BUTTON/ecu_button.h"
#include "RELAY/ecu_relay.h"
#include "DC_MOTOR/ecu_dc_motor.h"
#include "7_SEGMENT/_7_seg.h"
#include "KeyPad/ecu_keypad.h"
#include "CHAR_LCD/char_lcd.h"


/*   section: Macros  */


/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

//extern keypad_t keypad1 ;
extern char_lcd_4b_t lcd1 ;
//extern char_lcd_8b_t lcd2 ;
extern led_t led1 ;
extern led_t led2 ;
extern led_t led3 ;
extern led_t led4 ;
extern led_t led5 ;
extern led_t led6 ;
extern  button_t btn1 ;
extern  button_t btn2 ;
extern  button_t btn3 ;
extern  button_t btn4 ;
extern dc_motor_t motor1 ;
extern dc_motor_t motor2 ;

/*   section: Function declarations  */

std_ReturnType ecu_objects_init (void) ;

#endif	/* ECU_INIT_H */

