/* 
 * File:   hal_gpio.h
 * Author: Mansour
 *
 * Created on October 1, 2023, 3:06 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*   section: includes  */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
//#include "../regester_definitions.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"
#include "../std_libraries.h"
#include "../compiler.h"

/*   section: Macros  */

#define BIT_MASK     (uint8)1
#define PORT_MASK     (uint8)0xff
#define PIN_MAX                 8
#define PORT_MAX              5


/*   section: Macro Functions declarations */

#define HWREG8(_x) (*(volatile uint8*)(_x)) 
// BIT MANIPULATION
#define SET_BIT(REG_ADD,BIT_POS)         (REG_ADD  |=    (BIT_MASK<<BIT_POS))
#define CLEAR_BIT(REG_ADD,BIT_POS)     (REG_ADD  &= ~(BIT_MASK<<BIT_POS))
#define TOGGLE_BIT(REG_ADD,BIT_POS)  (REG_ADD  ^=    (BIT_MASK<<BIT_POS))
#define READ_BIT(REG_ADD,BIT_POS)      ((REG_ADD >> BIT_POS) & BIT_MASK )



/*   section: Data Types declarations */

typedef enum{
            LOW,
            HIGH        
}logic_t;

typedef enum{
            OUTPUT,
            INPUT        
}direction_t;

typedef enum{
            PIN0,
            PIN1,
            PIN2,
            PIN3,
            PIN4,
            PIN5,
            PIN6,
            PIN7
            
}pin_index_t;

typedef enum{
            PORTA_INDEX,
            PORTB_INDEX,
            PORTC_INDEX,
            PORTD_INDEX,
            PORTE_INDEX
            
            
}port_index_t;

typedef struct{
    uint8 port          :3 ;       /* @ref  port_index_t */
    uint8 pin           :3 ;       /* @ref  pin_index_t */
    uint8 direction   :1 ;       /* @ref  direction_t */
    uint8 logic         :1 ;       /* @ref  logic_t */              //it is the default logic on the pin  to set it use gpio_pin_initialize instead of gpio_pin_direction_initialize but it is not used when u want to write logic on the pin ,,,if u want to write a lgic on the pin use gpio_pin_write_logic and give it the logic u want as an arguement  
    
}pin_config_t;



/*   section: Function declarations  */

std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config , logic_t logic);
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config  , direction_t *direction);
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config , logic_t *logic);
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);

std_ReturnType gpio_port_direction_initialize(port_index_t port , uint8 direction);
std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8 *direction_status );
std_ReturnType gpio_port_write_logic(port_index_t port , uint8 logic );
std_ReturnType gpio_port_read_logic(port_index_t port , uint8 *logic );
std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

