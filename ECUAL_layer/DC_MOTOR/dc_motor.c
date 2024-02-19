/* 
 * File:   ecu_dc_motor.c
 * Author: Mansour
 *
 * Created on October 21, 2023, 5:25 PM
 */

#include "ecu_dc_motor.h"


/**
 * 
 * @param motor
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType dc_motor_initialize ( dc_motor_t *motor ) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == motor)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
       
        ret   = gpio_pin_initialize(&(motor->motor_pins[0] )  );
        ret |= gpio_pin_initialize(& (motor->motor_pins[1] ) );
    }
    
    return ret ;
}

/**
 * 
 * @param motor
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType dc_motor_move_right ( dc_motor_t *motor ) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == motor)
    {
        ret = E_NOT_OK ;
    }
    else 
    {   
        motor->motor_pins[0].direction = OUTPUT ;
        motor->motor_pins[1].direction = OUTPUT ;
        
        ret   = gpio_pin_write_logic(& (motor->motor_pins[0]) , HIGH);
        ret |= gpio_pin_write_logic(&(motor->motor_pins[1]) , LOW);
    }
    
    return ret ;
}

/**
 * 
 * @param motor
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType dc_motor_move_left ( dc_motor_t *motor ) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == motor)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        ret   = gpio_pin_write_logic(&(motor->motor_pins[0] ) , LOW );
        ret |= gpio_pin_write_logic(&(motor->motor_pins[1] ) , HIGH );
    }
    
    return ret ;
}

/**
 * 
 * @param motor
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType dc_motor_stop ( dc_motor_t *motor ) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == motor)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        ret   = gpio_pin_write_logic(&(motor->motor_pins[0] ) , LOW );
        ret |= gpio_pin_write_logic(&(motor->motor_pins[1] ) , LOW );
    }
    
    return ret ;
}

