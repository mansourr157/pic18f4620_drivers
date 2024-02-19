/* 
 * File:   hal_tmr0.h
 * Author: Mansour
 *
 * Created on December 24, 2023, 5:25 PM
 */

#ifndef HAL_TMR0_H
#define	HAL_TMR0_H


/*   section: Includes  */

#include "pic18f4620.h"
#include "../../GPIO/hal_gpio.h"
#include "../../mcal_std_types.h"
#include "../../../MCAL_layer/interrupts/mcal_internal_interrupts.h"

/*   section: Macros  */

#define TMR0_8BIT_MODE   1
#define TMR0_16BIT_MODE 0

#define TMR0_TIMER_MODE      0
#define TMR0_COUNTER_MODE 1

#define TMR0_COUNTER_RISING_EDGE    0
#define TMR0_COUNTER_FALLING_EDGE  1

#define TMR0_PRESCALER_ENABLE  0
#define TMR0_PRESCALER_DISABLE 1 

/*   section: Macro Functions declarations */
#define _TMR0_ENABLE() (T0CONbits.TMR0ON = 1)
#define _TMR0_DISABLE() (T0CONbits.TMR0ON = 0)

#define _TMR0_8BIT_MODE() (T0CONbits.T08BIT = 1)
#define _TMR0_16BIT_MODE() (T0CONbits.T08BIT = 0)

#define _TMR0_TIMER_MODE() (T0CONbits.T0CS = 0)
#define _TMR0_COUNTER_MODE() (T0CONbits.T0CS = 1)

#define _TMR0_COUNTER_RISING_EDGE() (T0CONbits.T0SE = 0)
#define _TMR0_COUNTER_FALLING_EDGE() (T0CONbits.T0SE = 1)

#define _TMR0_PRESCALER_ON() (T0CONbits.PSA = 0)
#define _TMR0_PRESCALER_OFF() (T0CONbits.PSA = 1)

#define _TMR0_PRESCALER_SELECT(_X) (T0CONbits.T0PS = _X)



/*   section: Data Types declarations */

typedef enum {
    
    PSA1_2 ,
    PSA1_4 ,
    PSA1_8 ,
    PSA1_16 ,
    PSA1_32,
    PSA1_64 ,
    PSA1_128 ,
    PSA1_256 
    
}tmr0_prescaler_t;

typedef struct {
    
    uint16 preload_value ;
    tmr0_prescaler_t prescaler  ; 
    uint8 register_size :1 ;
    uint8 timer_counter_mode :1 ;
    uint8 counter_edge :1 ;
    uint8 prescaler_satus :1 ;
    
#if TMR0_INTERRUPT_CFG_ENABLE == 1 
    uint8 interrupt_priority :1 ;
    void ( *TMR0_INTERRUPT_HANDLER) (void) ;  
#endif
    
    
}tmr0_object_t;

/*   section: Function declarations  */

std_ReturnType TMR0_Init (const tmr0_object_t *tmr0_obj) ; 
std_ReturnType TMR0_DeInit (const tmr0_object_t *tmr0_obj) ;

std_ReturnType TMR0_write_Value (const tmr0_object_t *tmr0_obj , uint16 value) ; 
std_ReturnType TMR0_read_Value (const tmr0_object_t *tmr0_obj , uint16 *value) ; 

#endif	/* HAL_TMR0_H */

