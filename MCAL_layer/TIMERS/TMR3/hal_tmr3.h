/* 
 * File:   hal_tmr3.h
 * Author: Mansour
 *
 * Created on January 3, 2024, 6:37 AM
 */

#ifndef HAL_TMR3_H
#define	HAL_TMR3_H


/*   section: Includes  */
#include "../../../MCAL_layer/interrupts/mcal_internal_interrupts.h"
#include "../../mcal_std_types.h"

/*   section: Macros  */
#define TMR3_TIMER_MODE      0
#define TMR3_COUNTER_MODE 1         // RISING EDGE after first falling edge

#define TMR3_READ_WRITE_IN_TWO_OPERATIONS 0  
#define TMR3_READ_WRITE_IN_ONE_OPERATIONS 1

#define TMR3_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK 0     // IF IN COUNTER MODE && EXTERNAL TMR1 OSCILLATOR 
#define TMR3_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK 1 

/*   section: Macro Functions declarations */
#define _TMR3_ENABLE() (T3CONbits.TMR3ON = 1)
#define _TMR3_DISABLE() (T3CONbits.TMR3ON = 0)

#define _TMR3_TIMER_MODE() (T3CONbits.TMR3CS = 0)
#define _TMR3_COUNTER_MODE() (T3CONbits.TMR3CS = 1)      // RISING EDGE

#define _TMR3_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK() (T3CONbits.T3SYNC = 0)   
#define _TMR3_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK() (T3CONbits.T3SYNC = 1)

#define _TMR3_READ_WRITE_IN_TWO_OPERATIONS() (T3CONbits.RD16 = 0)   
#define _TMR3_READ_WRITE_IN_ONE_OPERATION() (T3CONbits.RD16 = 1)

#define _TMR3_PRESCALER_SET(_X) (T3CONbits.T3CKPS = _X)


/*   section: Data Types declarations */
typedef enum {
    
    TMR3_PSA1_1 ,
    TMR3_PSA1_2 ,
    TMR3_PSA1_4 ,
    TMR3_PSA1_8 
    
}tmr3_prescaler_t;

typedef struct {
    
    uint16 preload_value ;            
    tmr3_prescaler_t prescaler  ; 
    uint8 timer_counter_mode :1 ;
    
    uint8 counter_senchronize :1 ;             //X
    uint8 r_w_operations :1 ;                     //X
    
#if TMR3_INTERRUPT_CFG_ENABLE == 1 
    uint8 interrupt_priority :1 ;
    void ( *TMR3_INTERRUPT_HANDLER) (void) ;  
#endif
    
    
}tmr3_object_t;

/*   section: Function declarations  */

std_ReturnType TMR3_Init (const tmr3_object_t *tmr3_obj) ; 
std_ReturnType TMR3_DeInit (const tmr3_object_t *tmr3_obj) ;

std_ReturnType TMR3_write_Value (const tmr3_object_t *tmr3_obj , uint16 value) ; 
std_ReturnType TMR3_read_Value (const tmr3_object_t *tmr3_obj , uint16 *value) ; 


#endif	/* HAL_TMR3_H */

