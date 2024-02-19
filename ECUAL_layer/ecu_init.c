/* 
 * File:   ecu_init.h
 * Author: Mansour
 *
 * Created on October 27, 2023, 9:29 PM
 */

#include "ecu_init.h"

 // components objects

keypad_t keypad1 = {
  
    .keypad_rows[0].port =PORTB_INDEX ,
    .keypad_rows[1].port =PORTB_INDEX ,
    .keypad_rows[2].port =PORTB_INDEX ,
    .keypad_rows[3].port =PORTB_INDEX ,
    .keypad_rows[0].pin = PIN0 ,
    .keypad_rows[1].pin = PIN1 ,
    .keypad_rows[2].pin = PIN2 ,
    .keypad_rows[3].pin = PIN3 ,
    

    .keypad_columns[0].port =PORTB_INDEX ,
    .keypad_columns[1].port =PORTB_INDEX ,
    .keypad_columns[2].port =PORTB_INDEX ,
    .keypad_columns[3].port =PORTB_INDEX ,
    .keypad_columns[0].pin = PIN4 ,
    .keypad_columns[1].pin = PIN5 ,
    .keypad_columns[2].pin = PIN6 ,
    .keypad_columns[3].pin = PIN7 ,
    

};

char_lcd_4b_t lcd1 = {
 
.E.port = PORTC_INDEX ,
.E.pin = PIN7 ,
.E.direction = OUTPUT ,
.E.logic = LOW ,
 
.RS.port = PORTC_INDEX ,
.RS.pin = PIN1 ,
.RS.direction = OUTPUT ,
.RS.logic = LOW ,

.data[0].port = PORTD_INDEX ,
.data[0].pin = PIN0 ,
.data[0].direction = OUTPUT ,
.data[0].logic = LOW ,

.data[1].port = PORTD_INDEX ,
.data[1].pin = PIN1 ,
.data[1].direction = OUTPUT ,
.data[1].logic = LOW ,

.data[2].port = PORTD_INDEX ,
.data[2].pin = PIN2 ,
.data[2].direction = OUTPUT ,
.data[2].logic = LOW ,

.data[3].port = PORTD_INDEX ,
.data[3].pin = PIN3 ,
.data[3].direction = OUTPUT ,
.data[3].logic = LOW ,
    
};

char_lcd_8b_t lcd2 = {
 
.E.port = PORTB_INDEX ,
.E.pin = PIN3 ,
.E.direction = OUTPUT ,
.E.logic = LOW ,
 
.RS.port = PORTB_INDEX ,
.RS.pin = PIN2 ,
.RS.direction = OUTPUT ,
.RS.logic = LOW ,

.data[0].port = PORTC_INDEX ,
.data[0].pin = PIN0 ,
.data[0].direction = OUTPUT ,
.data[0].logic = LOW ,

.data[1].port = PORTC_INDEX ,
.data[1].pin = PIN1 ,
.data[1].direction = OUTPUT ,
.data[1].logic = LOW ,

.data[2].port = PORTC_INDEX ,
.data[2].pin = PIN2 ,
.data[2].direction = OUTPUT ,
.data[2].logic = LOW ,

.data[3].port = PORTC_INDEX ,
.data[3].pin = PIN3 ,
.data[3].direction = OUTPUT ,
.data[3].logic = LOW ,

.data[4].port = PORTC_INDEX ,
.data[4].pin = PIN4 ,
.data[4].direction = OUTPUT ,
.data[4].logic = LOW ,

.data[5].port = PORTC_INDEX ,
.data[5].pin = PIN5 ,
.data[5].direction = OUTPUT ,
.data[5].logic = LOW ,

.data[6].port = PORTC_INDEX ,
.data[6].pin = PIN6 ,
.data[6].direction = OUTPUT ,
.data[6].logic = LOW ,

.data[7].port = PORTC_INDEX ,
.data[7].pin = PIN7 ,
.data[7].direction = OUTPUT ,
.data[7].logic = LOW ,
    
};

led_t led1 = {
  .port =PORTD_INDEX ,
  .pin = PIN0 ,
  .status = LED_OFF 

};
led_t led2 = {
  .port =PORTC_INDEX ,
  .pin = PIN1 ,
  .status = LED_OFF 

};
led_t led3 = {
  .port =PORTC_INDEX ,
  .pin = PIN2 ,
  .status = LED_OFF 

};
led_t led4 = {
  .port =PORTC_INDEX ,
  .pin = PIN3 ,
  .status = LED_OFF 

};
led_t led5 = {
  .port =PORTC_INDEX ,
  .pin = PIN4 ,
  .status = LED_OFF 

};

led_t led6 = {
  .port =PORTC_INDEX ,
  .pin = PIN5 ,
  .status = LED_OFF 

};

button_t btn1 = {
  .port = PORTB_INDEX ,
  .pin = PIN4 ,
  .button_connection = ACTIVE_HIGH ,
  
};


button_t btn3 = {
  .port = PORTB_INDEX ,
  .pin = PIN6 ,
  .button_connection = ACTIVE_HIGH ,
  
};

dc_motor_t motor1 = {
  
    .motor_pins[0].port = PORTB_INDEX ,
    .motor_pins[0].pin = PIN4 ,
    .motor_pins[0].direction = OUTPUT ,
//    .motor_pins[0].logic = LOW ,
            
    .motor_pins[1].port = PORTB_INDEX ,
    .motor_pins[1].pin = PIN5 ,
    .motor_pins[1].direction = OUTPUT ,
//    .motor_pins[1].logic = LOW 
    
    
};
dc_motor_t motor2 = {
  
    .motor_pins[0].port = PORTB_INDEX ,
    .motor_pins[0].pin = PIN6 ,
    .motor_pins[0].direction = OUTPUT ,
//    .motor_pins[0].logic = LOW ,
            
    .motor_pins[1].port = PORTB_INDEX ,
    .motor_pins[1].pin = PIN7 ,
    .motor_pins[1].direction = OUTPUT ,
//    .motor_pins[1].logic = LOW 
    
    
};






std_ReturnType ecu_objects_init (void) {
    std_ReturnType ret = E_NOT_OK ;
    
        ret |= led_initialize(&led1) ;
//        ret |= led_initialize(&led2) ;
//        ret |= led_initialize(&led3) ;
//        ret |= led_initialize(&led4) ;
//        ret |= led_initialize(&led5) ;
//        ret |= led_initialize(&led6) ;
//        ret |= led_initialize(&led4) ;
//        ret |= button_initialize(&btn1) ;
//        ret |= button_initialize(&btn2) ;
//        ret |= button_initialize(&btn3) ;
//        ret |= button_initialize(&btn4) ;
//    ret |= lcd_4b_initialize(&lcd1) ;
//    ret |= dc_motor_initialize(&motor1) ;
//    ret |= dc_motor_initialize(&motor2) ;
//    
    return ret ;
}
