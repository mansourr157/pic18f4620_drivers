/* 
 * File:   hal_tmr0.c
 * Author: Mansour
 *
 * Created on December 24, 2023, 5:25 PM
 */

#include "hal_tmr0.h"

static void ( *_TMR0_INTERRUPT_HANDLER_) (void) = NULL ;
static uint16 timer0_preload = 0 ;

std_ReturnType TMR0_Init (const tmr0_object_t *tmr0_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr0_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        /* DISABLE THE MODULE */
        _TMR0_DISABLE() ;
        
        /* CONFIGURE IF IN TIME MODE OR COUNTER MODE AND THE EDGE OF THE COUNTER */
        if ( TMR0_TIMER_MODE == tmr0_obj->timer_counter_mode)
        {
            _TMR0_TIMER_MODE();
        }
        else if ( TMR0_COUNTER_MODE == tmr0_obj->timer_counter_mode)
        {
            _TMR0_COUNTER_MODE();
            SET_BIT( TRISA ,PIN4);
            if( TMR0_COUNTER_RISING_EDGE == tmr0_obj->counter_edge)
            {
                _TMR0_COUNTER_RISING_EDGE();
            }
            else if ( TMR0_COUNTER_FALLING_EDGE == tmr0_obj->counter_edge)
            {
                _TMR0_COUNTER_FALLING_EDGE();
            }
            else { /* Nothing */ }
        }
        else { /* Nothing */ }
        
        /* CONFIGURE THE REGISTER SIZE */
        if ( TMR0_8BIT_MODE == tmr0_obj->register_size)
        {
            _TMR0_8BIT_MODE() ;
        }
        else if ( TMR0_16BIT_MODE == tmr0_obj->register_size) 
        {
            _TMR0_16BIT_MODE() ;
        }
        else { /* Nothing */ }
        
        /* CONFIGURE THE PRESCALER */
        if ( TMR0_PRESCALER_ENABLE  == tmr0_obj->prescaler_satus)
        {
            _TMR0_PRESCALER_ON();
            _TMR0_PRESCALER_SELECT(tmr0_obj->prescaler);
        }
        else if ( TMR0_PRESCALER_DISABLE == tmr0_obj->prescaler_satus)
        {
            _TMR0_PRESCALER_OFF();
        }
        else { /* Nothing */ }
        
        /* Assign the preload value */
        TMR0H = (uint8)( (tmr0_obj->preload_value) >> 8 ) ;
        TMR0L=  (uint8)(tmr0_obj->preload_value) ;
        timer0_preload = tmr0_obj->preload_value ;
        
        /* CONFIGURE THE INTERRUPT */
#if TMR0_INTERRUPT_CFG_ENABLE == 1
        
        TMR0_INTERRUPT_ENABLE();
        TMR0_INTERRUPT_CLEAR_FLAG();
        _TMR0_INTERRUPT_HANDLER_ = tmr0_obj->TMR0_INTERRUPT_HANDLER ;
        
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE

        INTERRUPT_PriorityLevelsEnable();
        
        if (HIGH_PRIORITY == tmr0_obj->interrupt_priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TMR0_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        else if (LOW_PRIORITY == tmr0_obj->interrupt_priority) 
        {
            INTERRUPT_GlobalInterruptHighEnable();           // IN THE LOW INTERRUPT WE SHOULD ALSO ENABLE GIE(GIEH)
            INTERRUPT_GlobalInterruptLowEnable();
            TMR0_INTERRUPT_LOW_PRIORITY_ENABLE();
        }
        else 
        {          
            INTERRUPT_GlobalInterruptHighEnable();
            TMR0_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
            
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif

    
#endif 
        
        /* ENABLE THE MODULE  */
        _TMR0_ENABLE() ;
    }
    return ret ; 
    
}

std_ReturnType TMR0_DeInit (const tmr0_object_t *tmr0_obj) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr0_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        _TMR0_DISABLE();
#if TMR0_INTERRUPT_CFG_ENABLE == 1
        TMR0_INTERRUPT_DISABLE();
#endif
    }
    return ret ; 
    
}

std_ReturnType TMR0_write_Value (const tmr0_object_t *tmr0_obj , uint16 value) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == tmr0_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        TMR0H = (uint8)(value >> 8) ;
        TMR0L = (uint8)(value) ;
    }
    return ret ; 
    
}

std_ReturnType TMR0_read_Value (const tmr0_object_t *tmr0_obj , uint16 *value) 
{
    std_ReturnType ret = E_OK ;
    if( (NULL == tmr0_obj ) || (NULL == value ) )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        uint8 valueL = TMR0L ;
        uint8 valueH = TMR0H ;
        *value =   (uint16)( valueL | (valueH << 8) ); 
    }
    return ret ; 
    
}


void TMR0_ISR(void)
{
    
#if TMR0_INTERRUPT_CFG_ENABLE == 1
    TMR0_INTERRUPT_CLEAR_FLAG();
    
    TMR0H = (uint8)(timer0_preload >> 8 );
    TMR0L = (uint8)(timer0_preload);
    
    if(_TMR0_INTERRUPT_HANDLER_)
        _TMR0_INTERRUPT_HANDLER_();
#endif
        
}
