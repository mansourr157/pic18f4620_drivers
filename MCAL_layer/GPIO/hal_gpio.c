/* 
 * File:   hal_gpio.c
 * Author: Mansour
 *
 * Created on October 1, 2023, 3:06 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_register[] = {&TRISA , &TRISB , &TRISC , &TRISD , &TRISE};
volatile uint8 *port_register[] = {&PORTA , &PORTB , &PORTC , &PORTD , &PORTE};
volatile uint8 *lat_register[]  = {&LATA , &LATB , &LATC , &LATD , &LATE};



/**
 * @brief    initializing the direction of the pin OUTPUT or INPUT  @ref direction_t
 * @param _pin_config   pointer to the configurations @ref pin_config
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config)
{
    std_ReturnType ret = E_OK ;
    
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX-1)
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
            switch (_pin_config ->direction)
                    {

                       case OUTPUT : 
                           CLEAR_BIT( *tris_register[ _pin_config ->port ] , _pin_config ->pin);
                           break;

                       case INPUT : 
                           SET_BIT( *tris_register[ _pin_config ->port ] , _pin_config ->pin);
                           break;

                       default: ret  = E_NOT_OK ;
                   }
    }
    
    return ret ;
}

#endif


/**
 * @brief    writing the logic on the pin HIGH or LOW                 @ref logic_t
 * @param _pin_config   pointer to the configurations                 @ref pin_config
 * @param logic             the logic that the user want to write      @ref logic_t
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config , logic_t logic)
{
    std_ReturnType ret = E_OK ;

    if(NULL == _pin_config || _pin_config->pin > PIN_MAX-1 )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        switch ( logic )
        {
            
            case HIGH : SET_BIT(*lat_register[_pin_config ->port] , _pin_config ->pin) ;
                break;
            
            case LOW : CLEAR_BIT(*lat_register[_pin_config ->port] , _pin_config ->pin) ;
                break;
            
            default:     ret = E_NOT_OK ;

        }
    }
    return ret;
}
#endif

/**
 * @brief    initializing the pin : (OUTPUT or INPUT) and (HIGH or LOW)  @ref direction_t  logic_t 
 * @param _pin_config   pointer to the configurations @ref pin_config
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config)
{   
    std_ReturnType ret = E_OK ;
    if(NULL == _pin_config || _pin_config ->pin > PIN_MAX -1)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
       ret    = gpio_pin_direction_initialize (_pin_config);
       ret  |= gpio_pin_write_logic (_pin_config , _pin_config ->logic);
    }
    return ret;
}
#endif

/**
 * @brief    toggle the bin logic
 * @param _pin_config   pointer to the configurations @ref pin_config
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    std_ReturnType ret = E_OK ;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX-1)
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        TOGGLE_BIT( *lat_register[_pin_config ->port] ,_pin_config ->pin) ;
    }
}
#endif

/**
 * @brief    get the direction of the pin in a pointer  @ref direction_t
 * @param _pin_config   pointer to the configurations @ref pin_config
 * @param direction       pointer to @ref direction_t data to get the direction in it
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config , direction_t *direction)
{
     std_ReturnType ret = E_OK ;
    
    if(NULL == _pin_config  || _pin_config->pin > PIN_MAX-1)
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *direction = READ_BIT( *tris_register[_pin_config ->port], _pin_config ->pin );
    }
     return ret;
}
#endif

/**
 * @brief    get the logic of the pin in a pointer  @ref logic_t
 * @param _pin_config   pointer to the configurations @ref pin_config
 * @param logic             pointer to @ref logic_t data to get the logic in it
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config , logic_t *logic)
{   
    std_ReturnType ret = E_OK ;
    if(NULL == _pin_config  || _pin_config->pin > PIN_MAX-1)
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *logic = READ_BIT( *port_register[_pin_config ->port], _pin_config ->pin );
    }
    return ret;
}
#endif

////////////////////////////////////////////////////////////////////

/**
 * @brief    initializing the direction of the port
 * @param port              @ref port_index_t
 * @param direction       direction taken from user
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_direction_initialize(port_index_t port , uint8 direction)
{   
    std_ReturnType ret = E_OK ;
    if(port > PORT_MAX -1 )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *tris_register[port] = direction ;
    }
    return ret ;
}
#endif

/**
 * @brief    getting the direction of the port
 * @param port                      @ref port_index_t
 * @param direction_status     pointer to take the direction status in 
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8 *direction_status )
{   
    std_ReturnType ret = E_OK ;
    if(port > PORT_MAX -1  )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *direction_status = *tris_register[port] ;
    }
    return ret;
}
#endif

/**
 * @brief    writting the logic of the port
 * @param port       @ref port_index_t
 * @param logic         logic taken from user
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_write_logic(port_index_t port , uint8 logic )
{
    std_ReturnType ret = E_OK ;
    if(port > PORT_MAX - 1 )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *lat_register[port] = logic ;
    }
    return ret ; 
}
#endif

/**
 * @brief    getting the logic of the port
 * @param port      @ref port_index_t
 * @param logic     pointer to take the logic in
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_read_logic(port_index_t port , uint8 *logic )
{
    std_ReturnType ret = E_OK ;
    if(port > PORT_MAX - 1 )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
       *logic = *port_register[port]  ;
    }
    return ret ; 
}
#endif

/**
 * @brief    toggle the logic of the port
 * @param port       @ref port_index_t
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    std_ReturnType ret = E_OK ;
    if(port > PORT_MAX - 1 )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *lat_register[port] ^= PORT_MASK ;
    }
    return ret ; 
}
#endif
