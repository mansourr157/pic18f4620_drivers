/* 
 * File:   ecu_button.c
 * Author: Mansour
 *
 * Created on October 19, 2023, 4:18 PM
 */

#include "ecu_button.h"

/**
 * @brief    initializing button
 * @param btn
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType button_initialize(const button_t *btn)
{
std_ReturnType ret =E_OK ;
    if(NULL == btn)
    {
        ret = E_NOT_OK ;
    }
    else
    {   
        pin_config_t btn_config = { .port =btn->port , .pin = btn->pin , .direction = INPUT };
        gpio_pin_direction_initialize(&btn_config);
    } 
        return ret ;
}

/**
 * @brief    read the button status
 * @param btn
 * @param btn_status
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType button_read_status(const button_t *btn , button_status_t *btn_status)
 {

    std_ReturnType ret =E_OK ;
    if(NULL == btn || NULL == btn_status)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        pin_config_t btn_config = { .port =btn->port , .pin = btn->pin , .direction = INPUT };
        logic_t logic = LOW;
        ret = gpio_pin_read_logic(&btn_config , &logic );
        
        if (HIGH == logic)
        {
            if (ACTIVE_HIGH == btn->button_connection)
                {
                    *btn_status = BUTTON_PRESSED ;
                }
            else if (ACTIVE_LOW == btn->button_connection)
                {
                    *btn_status = BUTTON_RELEASED ;
                }
        }
        else if (LOW == logic)
        {
            if (ACTIVE_HIGH == btn->button_connection)
                {
                    *btn_status = BUTTON_RELEASED ;
                }
            else if (ACTIVE_LOW == btn->button_connection)
                {
                    *btn_status = BUTTON_PRESSED ;
                }
        }
        
    } 
    return ret ;
}