/* 
 * File:   hal_tmr2.c
 * Author: Mansour
 *
 * Created on January 1, 2024, 4:45 AM
 */

#include "hal_tmr2.h"

static uint8 Lpreload ;
static void (*_TMR2_INTERRUPT_HANDLER_) (void) = NULL ;

std_ReturnType TMR2_Init (const tmr2_object_t *tmr2_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr2_obj ) 
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        /* DISABLE THE MODULE */
        TMR2_DISABLE();
        
        /* CONFIGURE THE PRELOADED VALUE */
        TMR2 = tmr2_obj->preload_value ;
        Lpreload = tmr2_obj->preload_value ;
        
        /* CONFIGURE THE PRESCALER VALUE */
        TMR2_PRESCALER_SELECT(tmr2_obj->prescaler) ;
        
        /* CONFIGURE THE POSTSCALER VALUE */
        TMR2_POSTSCALER_SELECT(tmr2_obj->postscaler) ;
        
        /* CONFIGURE THE INTERRUPT */
#if TMR2_INTERRUPT_CFG_ENABLE == 1

        TMR2_INTERRUPT_ENABLE();
        _TMR2_INTERRUPT_HANDLER_ = tmr2_obj->TMR2_INTERRUPT_HANDLER ;
        TMR2_INTERRUPT_CLEAR_FLAG();
        
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        
        INTERRUPT_PriorityLevelsEnable();
        if(tmr2_obj->priority == HIGH_PRIORITY )
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TMR2_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        else if(tmr2_obj->priority == LOW_PRIORITY )
        {
            INTERRUPT_GlobalInterruptHighEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            TMR2_INTERRUPT_LOW_PRIORITY_ENABLE();
        }
        else 
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TMR2_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
                    
#else
        
        INTERRUPT_GlobalInterruptEnable() ;
        INTERRUPT_PeripheralInterruptEnable() ;
        
#endif
        
#endif
    
        /* ENABLE THE MODULE */
        TMR2_ENABLE();
        
    }
    return ret ; 
    
}

std_ReturnType TMR2_DeInit (const tmr2_object_t *tmr2_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr2_obj ) 
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        
        TMR2_DISABLE() ;
#if TMR2_INTERRUPT_CFG_ENABLE == 1
        TMR2_INTERRUPT_DISABLE();
#endif
                
    }
    return ret ; 
    
}


std_ReturnType TMR2_write_Value (const tmr2_object_t *tmr2_obj , uint8 value) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr2_obj ) 
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        TMR2 = value ;
    }
    return ret ; 
    
}

std_ReturnType TMR2_read_Value (const tmr2_object_t *tmr2_obj , uint8 *value) 
{
    std_ReturnType ret = E_OK ;
    if( (NULL == tmr2_obj) || (NULL == value) ) 
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *value = TMR2 ;
    }
    return ret ; 
    
}

void TMR2_ISR (void) 
{
#if TMR2_INTERRUPT_CFG_ENABLE == 1

    TMR2_INTERRUPT_CLEAR_FLAG();
    TMR2 = Lpreload ;
    if(_TMR2_INTERRUPT_HANDLER_)
        _TMR2_INTERRUPT_HANDLER_();
    
#endif
}