#include "ecu_relay.h"

/**
 * @brief    initializing the relay : direction and default status
 * @param relay
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType relay_initialize (const relay_t *relay)
{
    std_ReturnType ret = E_OK ;
    if (NULL == relay)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        pin_config_t relay_config = { .port = relay->port , .pin = relay->pin , .logic = relay->status , .direction = OUTPUT};
        ret = gpio_pin_initialize( &relay_config );
    }
    
    return ret ;
}

/**
 * 
 * @param relay
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType relay_turn_on (const relay_t *relay)
{
    std_ReturnType ret = E_OK ;
    if (NULL == relay)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        pin_config_t relay_config = { .port = relay->port , .pin = relay->pin , .logic = relay->status };
        ret = gpio_pin_write_logic( &relay_config , HIGH);
    }
    
    return ret ;
}

/**
 * 
 * @param relay
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType relay_turn_off (const relay_t *relay)
{
    std_ReturnType ret = E_OK ;
    if (NULL == relay)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        pin_config_t relay_config = { .port = relay->port , .pin = relay->pin , .logic = relay->status };
        ret = gpio_pin_write_logic( &relay_config , LOW);
    }
    
    return ret ;
}