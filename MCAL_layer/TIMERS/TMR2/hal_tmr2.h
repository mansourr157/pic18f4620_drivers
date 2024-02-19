/* 
 * File:   hal_tmr2.h
 * Author: Mansour
 *
 * Created on January 1, 2024, 4:45 AM
 */

#ifndef HAL_TMR2_H
#define	HAL_TMR2_H


/*   section: Includes  */
#include "../../mcal_std_types.h"
#include "../../interrupts/mcal_internal_interrupts.h"

/*   section: Macros  */


/*   section: Macro Functions declarations */

#define TMR2_ENABLE() (T2CONbits.TMR2ON = 1)
#define TMR2_DISABLE() (T2CONbits.TMR2ON = 0)

#define TMR2_PRESCALER_SELECT(_X) (T2CONbits.T2CKPS = _X)
#define TMR2_POSTSCALER_SELECT(_X) (T2CONbits.TOUTPS = _X)

/*   section: Data Types declarations */

typedef enum {
    
    TMR2_PRESCALER1_1 ,
    TMR2_PRESCALER1_4 ,
    TMR2_PRESCALER1_16 
            
}tmr2_prescaler_t;


typedef enum {
    
    TMR2_POSTSCALER1_1 ,
    TMR2_POSTSCALER1_2 ,
    TMR2_POSTSCALER1_3 ,
    TMR2_POSTSCALER1_4 ,
    TMR2_POSTSCALER1_5 ,
    TMR2_POSTSCALER1_6 ,
    TMR2_POSTSCALER1_7 ,
    TMR2_POSTSCALER1_8 ,
    TMR2_POSTSCALER1_9 ,
    TMR2_POSTSCALER1_10 ,
    TMR2_POSTSCALER1_11 ,
    TMR2_POSTSCALER1_12 ,
    TMR2_POSTSCALER1_13 ,
    TMR2_POSTSCALER1_14 ,
    TMR2_POSTSCALER1_15 ,
    TMR2_POSTSCALER1_16 
    
}tmr2_postscaler_t;


typedef struct {
    
#if TMR2_INTERRUPT_CFG_ENABLE == 1
    void (*TMR2_INTERRUPT_HANDLER)(void) ;
    uint8 priority : 1 ;
#endif
    
    uint8 preload_value ;
    tmr2_prescaler_t prescaler ;
    tmr2_postscaler_t postscaler ;
    
}tmr2_object_t;

/*   section: Function declarations  */

std_ReturnType TMR2_Init (const tmr2_object_t *tmr2_obj) ; 
std_ReturnType TMR2_DeInit (const tmr2_object_t *tmr2_obj) ;

std_ReturnType TMR2_write_Value (const tmr2_object_t *tmr2_obj , uint8 value) ; 
std_ReturnType TMR2_read_Value (const tmr2_object_t *tmr2_obj , uint8 *value) ; 

#endif	/* HAL_TMR2_H */

