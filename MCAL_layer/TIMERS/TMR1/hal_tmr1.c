/* 
 * File:   hal_tmr1.c
 * Author: Mansour
 *
 * Created on December 31, 2023, 8:36 PM
 */

#include "hal_tmr1.h"

uint16 tmr1_preload_value = 0 ;
void (*_TMR1_INTERRUPT_HANDLER_)(void) = NULL ;

std_ReturnType TMR1_Init (const tmr1_object_t *tmr1_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr1_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        /* DISABLE THE MODULE */
        _TMR1_DISABLE();
        
        /* CONFIGURE IF TIMER OR COUNTER AND THE SYNCHRONIZATION IF TIMER*/
        if (tmr1_obj->timer_counter_mode == TMR1_COUNTER_MODE)
        {
            _TMR1_COUNTER_MODE();
            
                    if(tmr1_obj->counter_senchronize == TMR1_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK )
                    {
                        _TMR1_COUNTER_SYNCHRONIZE_EXTERNAL_CLOCK();
                    }
                    else if (tmr1_obj->counter_senchronize == TMR1_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK)
                    {
                        _TMR1_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK();
                    }
                    else 
                    {
                        _TMR1_COUNTER_DONT_SYNCHRONIZE_EXTERNAL_CLOCK();
                    }
            
        }
        else if (tmr1_obj->timer_counter_mode == TMR1_TIMER_MODE)
        {
            _TMR1_TIMER_MODE();
        }
        else {/* Nothing */} 
        
        /* CONFIGURE PRESCALER */
        _TMR1_PRESCALER_SET(tmr1_obj->prescaler) ;
        
        /* CONFIGURE R\W NUMBER OF OPERATIONS */
        if(tmr1_obj->r_w_operations == TMR1_READ_WRITE_IN_ONE_OPERATIONS)
        {
            _TMR1_READ_WRITE_IN_ONE_OPERATION();
        }
        else if (tmr1_obj->r_w_operations == TMR1_READ_WRITE_IN_TWO_OPERATIONS)
        {
            _TMR1_READ_WRITE_IN_TWO_OPERATIONS();
        }
        else 
        {
            _TMR1_READ_WRITE_IN_TWO_OPERATIONS();
        }
            
        /* CONFIGURE THE OSCILLATOR  */
        if(tmr1_obj->tmr1_oscillator_status == TMR1_OSCILLATOR_ENABLE )
        {
            _TMR1_OSCILLATOR_ENABLE();
        }
        else if (tmr1_obj->tmr1_oscillator_status == TMR1_OSCILLATOR_DISABLE)
        {
            _TMR1_OSCILLATOR_DISABLE();
        }
        else 
        {
            _TMR1_OSCILLATOR_DISABLE();
        }
        
        
        /* CONFIGURE THE PRELOADED VALUE */
        TMR1H = (uint8)( tmr1_obj->preload_value >> 8 ) ;
        TMR1L = (uint8)( tmr1_obj->preload_value  ) ;
        tmr1_preload_value = tmr1_obj->preload_value ;
        
        /* CONFIGURE THE INTERRUPT */
#if TMR1_INTERRUPT_CFG_ENABLE == 1
        
        TMR1_INTERRUPT_ENABLE();
        TMR1_INTERRUPT_CLEAR_FLAG();
        _TMR1_INTERRUPT_HANDLER_ = tmr1_obj->TMR1_INTERRUPT_HANDLER ;
        
        
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(tmr1_obj->interrupt_priority == HIGH_PRIORITY )
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TMR1_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        else if (tmr1_obj->interrupt_priority == LOW_PRIORITY)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            TMR1_INTERRUPT_LOW_PRIORITY_ENABLE();
        }
        else 
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TMR1_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#endif
        
        /* ENABLE THE MODULE */        
        _TMR1_ENABLE();
    }
    return ret ; 
    
}

std_ReturnType TMR1_DeInit (const tmr1_object_t *tmr1_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr1_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        _TMR1_DISABLE();
        
#if TMR1_INTERRUPT_CFG_ENABLE == 1
        TMR1_INTERRUPT_DISABLE();
#endif
        
    }
    return ret ; 
    
}

std_ReturnType TMR1_write_Value (const tmr1_object_t *tmr1_obj , uint16 value) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr1_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        TMR1H = (uint8)( value >> 8 ) ;
        TMR1L = (uint8)(value) ;
    }
    return ret ; 
    
}
std_ReturnType TMR1_read_Value (const tmr1_object_t *tmr1_obj , uint16 *value) 
{
    std_ReturnType ret = E_OK ;
    if( (NULL == tmr1_obj) || (NULL == value) )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        uint8 tmr1L = TMR1L ;
        uint8 tmr1H = TMR1H ;
        *value = (uint16)( tmr1L + (tmr1H<<8) ) ;
    }
    return ret ; 
    
}

 void TMR1_ISR(void)
 {
#if TMR1_INTERRUPT_CFG_ENABLE == 1
     
     TMR1_INTERRUPT_CLEAR_FLAG();
     
     TMR1H = (uint8)(tmr1_preload_value >> 8 ) ;
     TMR1L = (uint8)(tmr1_preload_value) ;
     
     if(_TMR1_INTERRUPT_HANDLER_)
         _TMR1_INTERRUPT_HANDLER_();
     
#endif
 }
