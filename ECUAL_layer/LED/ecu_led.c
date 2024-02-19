/* 
 * File:   LED.c
 * Author: Mansour
 *
 * Created on October 1, 2023, 3:45 PM
 */

#include "ecu_led.h"

/**
 * @brief    initializing the led
 * @param led : pointer to the led configurations @ref led_t
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType led_initialize(const led_t *led){
    std_ReturnType ret =E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        pin_config_t _pin_config =
        {
          .port = led ->port , .pin = led->pin , .logic = led->status , .direction = OUTPUT   
        };
        
        ret = gpio_pin_initialize(&_pin_config);
    }
    return ret ;
}

/**
 * @brief   turn the led on
 * @param led : pointer to the led configurations @ref led_t
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType led_turn_on(const led_t *led){
    std_ReturnType ret =E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        pin_config_t _pin_config =
        {
          .port = led ->port , .pin = led->pin , .logic = led->status , .direction = OUTPUT   
        };
        
        ret = gpio_pin_write_logic(&_pin_config , HIGH);
    }
    return ret ;
}

/**
 * @brief   turn the led off
 * @param led : pointer to the led configurations @ref led_t
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType led_turn_off(const led_t *led){
    std_ReturnType ret =E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        pin_config_t _pin_config =
        {
          .port = led ->port , .pin = led->pin , .logic = led->status , .direction = OUTPUT   
        };
        
        ret = gpio_pin_write_logic(&_pin_config , LOW);
    }
    return ret ;
}

/**
 * @brief   toggle the led status
 * @param led : pointer to the led configurations @ref led_t
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType led_toggle(const led_t *led){
    std_ReturnType ret =E_OK ;
    if(NULL == led)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        pin_config_t _pin_config =
        {
          .port = led ->port , .pin = led->pin , .logic = led->status , .direction = OUTPUT   
        };
        
        ret = gpio_pin_toggle_logic( &_pin_config);
    }
    return ret ;
}