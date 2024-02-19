/* 
 * File:   hal_tmr3.c
 * Author: Mansour
 *
 * Created on January 3, 2024, 6:37 AM
 */

#include "hal_tmr3.h"

uint16 tmr3_preload_value = 0 ;
void (*_TMR3_INTERRUPT_HANDLER_)(void) = NULL ;

std_ReturnType TMR3_Init (const tmr3_object_t *tmr3_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr3_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        /* DISABLE THE MODULE */
        _TMR3_DISABLE();
        
        /* CONFIGURE IF TIMER OR COUNTER AND THE SYNCHRONIZATION IF TIMER*/
        if (tmr3_obj->timer_counter_mode == TMR3_COUNTER_MODE)
        {
            _TMR3_COUNTER_MODE();
            
                    if(tmr3_obj->counter_senchronize == TMR3_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK )
                    {
                        _TMR3_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK();
                    }
                    else if (tmr3_obj->counter_senchronize == TMR3_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK)
                    {
                        _TMR3_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK();
                    }
                    else 
                    {
                        _TMR3_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK();
                    }
            
        }
        else if (tmr3_obj->timer_counter_mode == TMR3_TIMER_MODE)
        {
            _TMR3_TIMER_MODE();
        }
        else {/* Nothing */} 
        
        /* CONFIGURE PRESCALER */
        _TMR3_PRESCALER_SET(tmr3_obj->prescaler) ;
        
        /* CONFIGURE R\W NUMBER OF OPERATIONS */
        if(tmr3_obj->r_w_operations == TMR3_READ_WRITE_IN_ONE_OPERATIONS)
        {
            _TMR3_READ_WRITE_IN_ONE_OPERATION();
        }
        else if (tmr3_obj->r_w_operations == TMR3_READ_WRITE_IN_TWO_OPERATIONS)
        {
            _TMR3_READ_WRITE_IN_TWO_OPERATIONS();
        }
        else 
        {
            _TMR3_READ_WRITE_IN_TWO_OPERATIONS();
        }
            
        /* CONFIGURE THE PRELOADED VALUE */
        TMR3H = (uint8)( tmr3_obj->preload_value >> 8 ) ;
        TMR3L = (uint8)( tmr3_obj->preload_value  ) ;
        tmr3_preload_value = tmr3_obj->preload_value ;
        
        
        /* CONFIGURE THE INTERRUPT */
#if TMR3_INTERRUPT_CFG_ENABLE == 1
        
        TMR3_INTERRUPT_ENABLE();
        TMR3_INTERRUPT_CLEAR_FLAG();
        _TMR3_INTERRUPT_HANDLER_ = tmr3_obj->TMR3_INTERRUPT_HANDLER ;
        
        
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(tmr3_obj->interrupt_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TMR3_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        else if (tmr3_obj->interrupt_priority == LOW_PRIORITY)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            TMR3_INTERRUPT_LOW_PRIORITY_ENABLE();
        }
        else 
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TMR3_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#endif
        
        /* ENABLE THE MODULE */        
        _TMR3_ENABLE();
        
        
    }
    
    return ret ; 
    
}

std_ReturnType TMR3_DeInit (const tmr3_object_t *tmr3_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr3_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        _TMR3_DISABLE();
        
#if TMR3_INTERRUPT_CFG_ENABLE == 1
        TMR3_INTERRUPT_DISABLE();
#endif
        
    }
    return ret ; 
    
}


std_ReturnType TMR3_write_Value (const tmr3_object_t *tmr3_obj , uint16 value) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr3_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        TMR3H = (uint8)( value >> 8 ) ;
        TMR3L = (uint8)(value) ;
    }
    return ret ; 
    
}

std_ReturnType TMR3_read_Value (const tmr3_object_t *tmr3_obj , uint16 *value) 
{
    std_ReturnType ret = E_OK ;
    if( (NULL == tmr3_obj) || (NULL == value) )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        uint8 tmr3L = TMR3L ;
        uint8 tmr3H = TMR3H ;
        *value = (uint16)( tmr3L + (tmr3H<<8) ) ;
    }
    return ret ; 
    
}

 void TMR3_ISR(void)
 {

#if TMR3_INTERRUPT_CFG_ENABLE == 1

     TMR3_INTERRUPT_CLEAR_FLAG();
     
     TMR3H = (uint8)(tmr3_preload_value >> 8 ) ;
     TMR3L = (uint8)(tmr3_preload_value) ;
     
     if(_TMR3_INTERRUPT_HANDLER_)
         _TMR3_INTERRUPT_HANDLER_();

#endif

 }
