/* 
 * File:   hal_tmr1.h
 * Author: Mansour
 *
 * Created on December 31, 2023, 8:36 PM
 */

#ifndef HAL_TMR1_H
#define	HAL_TMR1_H

/*   section: Includes  */
#include "../../../MCAL_layer/interrupts/mcal_internal_interrupts.h"
#include "../../mcal_std_types.h"

/*   section: Macros  */

#define TMR1_TIMER_MODE      0
#define TMR1_COUNTER_MODE 1         // RISING EDGE

#define TMR1_OSCILLATOR_ENABLE 1
#define TMR1_OSCILLATOR_DISABLE 0

///
#define TMR1_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK 0     // IF IN COUNTER MODE && EXTERNAL TMR1 OSCILLATOR 
#define TMR1_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK 1 

#define TMR1_READ_WRITE_IN_TWO_OPERATIONS 0  
#define TMR1_READ_WRITE_IN_ONE_OPERATIONS 1
///

/*   section: Macro Functions declarations */

#define _TMR1_ENABLE() (T1CONbits.TMR1ON = 1)
#define _TMR1_DISABLE() (T1CONbits.TMR1ON = 0)

#define _TMR1_TIMER_MODE() (T1CONbits.TMR1CS = 0)
#define _TMR1_COUNTER_MODE() (T1CONbits.TMR1CS = 1)      // RISING EDGE

#define _TMR1_OSCILLATOR_ENABLE() (T1CONbits.T1OSCEN = 1)
#define _TMR1_OSCILLATOR_DISABLE() (T1CONbits.T1OSCEN = 0)

#define _TMR1_PRESCALER_SET(_X) (T1CONbits.T1CKPS = _X)

#define TMR1_SYSTEM_CLOCK_STATUS_BIT() (T1CONbits.T1RUN)


#define _TMR1_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK() (T1CONbits.T1SYNC = 0)   
#define _TMR1_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK() (T1CONbits.T1SYNC = 1)

#define _TMR1_READ_WRITE_IN_TWO_OPERATIONS() (T1CONbits.RD16 = 0)   
#define _TMR1_READ_WRITE_IN_ONE_OPERATION() (T1CONbits.RD16 = 1)


/*   section: Data Types declarations */

typedef enum {
    
    TMR1_PSA1_1 ,
    TMR1_PSA1_2 ,
    TMR1_PSA1_4 ,
    TMR1_PSA1_8 
    
}tmr1_prescaler_t;

typedef struct {
    
    uint16 preload_value ;            
    tmr1_prescaler_t prescaler  ; 
    uint8 timer_counter_mode :1 ;
    
    uint8 tmr1_oscillator_status :1 ;           //X
    uint8 counter_senchronize :1 ;             //X
    uint8 r_w_operations :1 ;                     //X
    
#if TMR1_INTERRUPT_CFG_ENABLE == 1 
    uint8 interrupt_priority :1 ;
    void ( *TMR1_INTERRUPT_HANDLER) (void) ;  
#endif
    
    
}tmr1_object_t;

/*   section: Function declarations  */

std_ReturnType TMR1_Init (const tmr1_object_t *tmr1_obj) ; 
std_ReturnType TMR1_DeInit (const tmr1_object_t *tmr1_obj) ;

std_ReturnType TMR1_write_Value (const tmr1_object_t *tmr1_obj , uint16 value) ; 
std_ReturnType TMR1_read_Value (const tmr1_object_t *tmr1_obj , uint16 *value) ; 

#endif	/* HAL_TMR1_H */

