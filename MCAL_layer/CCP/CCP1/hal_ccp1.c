/* 
 * File:   hal_ccp1.c
 * Author: Mansour
 *
 * Created on January 11, 2024, 1:11 AM
 */

#include "hal_ccp1.h"

static void ( *_CCP1_INTERRUPT_HANDLER_ ) (void) = NULL ;
static std_ReturnType CCP1_CONFIGURE_INTERRUPT(const ccp1_t *ccp1_obj);
static std_ReturnType CCP1_CONFIGURE_PIN_DIRECTION(const ccp1_t *ccp1_obj);
static std_ReturnType CCP1_CONFIGURE_TIMERS(const ccp1_t *ccp1_obj) ;
static std_ReturnType CCP1_CONFIGURE_PWM(const ccp1_t *ccp1_obj);

//////////////////////////////////////////////////////////////////////////////
std_ReturnType CCP1_Init(const ccp1_t *ccp1_obj) 
{
    std_ReturnType ret = E_OK ; 
    if (NULL == ccp1_obj)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        /* Disable The Module */
        CCP1_MODE_SELECT(CCP1_MODULE_DISABLE) ;
        
        /* Select the module mode */
        CCP1_MODE_SELECT(ccp1_obj->mode) ;

        /* Configure the pin direction */
        CCP1_CONFIGURE_PIN_DIRECTION(ccp1_obj);

        /* Configure the timers for capture and compare */
        CCP1_CONFIGURE_TIMERS(ccp1_obj);

        /* Configure the PWM  */                                                                        
#if CCP1_CFG_MODE_SELECT == CCP1_CFG_PWM_MODE
        CCP1_CONFIGURE_PWM(ccp1_obj);
#endif

    /* Configure The Interrupt */
#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE || CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE
        CCP1_CONFIGURE_INTERRUPT(ccp1_obj);
#endif        
        
    }
    
    return ret ;
}

std_ReturnType CCP1_DeInit(const ccp1_t *ccp1_obj) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp1_obj)
    {
        ret = E_NOT_OK ;
    }
    
    else
    {      
       CCP1_MODE_SELECT(CCP1_MODULE_DISABLE) ;
#if CCP1_INTERRUPT_CFG_ENABLE == 1
      CCP1_INTERRUPT_DISABLE();  
#endif       
    }
    
    return ret ;
}


/////////////////////////////////////////////////////////////////////////////

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE
std_ReturnType CCP1_capture_get_value( uint16 *capture_value)
{
    std_ReturnType ret = E_OK ;
    if ( NULL == capture_value)
    {
        ret = E_NOT_OK ;
    }
    
    else
    {      
        ccp1_register_t ccp1_res = { .CCP1_16B = 0 };
        ccp1_res.CCP1H = CCPR1H ;
        ccp1_res.CCP1L = CCPR1L ;
        *capture_value = ccp1_res.CCP1_16B ;
    }
    
    return ret ;
}

#endif 

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE  
std_ReturnType CCP1_compare_set_value(uint16 *compare_value)
{
    std_ReturnType ret = E_OK ;
    if (NULL == compare_value)
    {    
        ret = E_NOT_OK ;
    }
    
    else
    {      
        ccp1_register_t ccp1_comp_val = { .CCP1_16B = *compare_value };
        CCPR1H = ccp1_comp_val.CCP1H ;
        CCPR1L = ccp1_comp_val.CCP1L ;
        
    }
    
    return ret ;
}

#endif 

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_PWM_MODE 
std_ReturnType CCP1_pwm_set_duty_cycle(const ccp1_t *ccp1_obj , uint8 duty_cycle_percentage)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp1_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        uint16 L_Value  = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)duty_cycle_percentage / 100.0));
        
        CCP1CONbits.DC1B = (uint8)(L_Value & 0x0003) ;      /* Configure the Duty cycle */
        CCPR1L = (uint8)(L_Value >>2);                                   /* Configure the Duty cycle */
 
    }
    
    return ret ;
}
#endif 



/////////////////////////////////////////////////////////////////////////////
#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE || CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE

static std_ReturnType CCP1_CONFIGURE_INTERRUPT(const ccp1_t *ccp1_obj)
{
     std_ReturnType ret = E_OK ;
    if (NULL == ccp1_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        
#if CCP1_INTERRUPT_CFG_ENABLE == 1
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLEAR_FLAG() ;
        _CCP1_INTERRUPT_HANDLER_ = ccp1_obj->CCP1_INTERRUPT_HANDLER ;
        
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable ();
        if (HIGH_PRIORITY == ccp1_obj->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_INTERRUPT_HIGH_PRIORITY_ENABLE () ;
        }
        else if (LOW_PRIORITY == ccp1_obj->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            CCP1_INTERRUPT_LOW_PRIORITY_ENABLE () ;
        }
        else 
        {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_INTERRUPT_HIGH_PRIORITY_ENABLE () ;
        }
#else
        INTERRUPT_GlobalInterruptEnable ();
        INTERRUPT_PeripheralInterruptEnable ();
#endif
        
#endif      

    }
     
     return ret ;
}
#endif


static std_ReturnType CCP1_CONFIGURE_PIN_DIRECTION(const ccp1_t *ccp1_obj)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp1_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {   
        
#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE
        if ( ccp1_obj->mode == CCP1_CAPTURE_1_FALLING_EDG || 
             ccp1_obj->mode == CCP1_CAPTURE_1_RISING_EDG   || 
             ccp1_obj->mode == CCP1_CAPTURE_4_RISING_EDG   || 
             ccp1_obj->mode == CCP1_CAPTURE_16_RISING_EDG         )
        {
            TRISCbits.RC2 = 1 ;
        }
        
#endif

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE
        if ( ccp1_obj->mode == CCP1_COMPARE_HIGH_ON_MATCH || 
             ccp1_obj->mode == CCP1_COMPARE_LOW_ON_MATCH   || 
             ccp1_obj->mode == CCP1_COMPARE_TOGGLE_ON_MATCH   || 
             ccp1_obj->mode == CCP1_COMPARE_SPECIAL_EVENT_ON_MATCH   || 
             ccp1_obj->mode == CCP1_COMPARE_SOFTWARE_INTERRUPT_ON_MATCH         )
        {
            TRISCbits.RC2 = 0 ;
        }
        
#endif
        
#if CCP1_CFG_MODE_SELECT == CCP1_CFG_PWM_MODE
        if ( ccp1_obj->mode == CCP1_PWM_MODE  )
        {
            TRISCbits.RC2 = 0 ;          
        }
        
#endif
    
        
    }
    
    return ret ;
}


static std_ReturnType CCP1_CONFIGURE_TIMERS(const ccp1_t *ccp1_obj)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp1_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {   
          
#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE 
        if (CCP1_CCP2_TMR1_CAPTURE == ccp1_obj->timer_capture)
        {       
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 0 ;
        }
        else if (CCP1_CCP2_TMR3_CAPTURE == ccp1_obj->timer_capture)
        {          
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 1 ;
        }
        else if (CCP1_TMR1_CCP2_TMR3_CAPTURE == ccp1_obj->timer_capture)
        {          
            T3CONbits.T3CCP1 = 1 ;
            T3CONbits.T3CCP2 = 0 ;
        }
        else { /* Nothing */ } 
        
#endif

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE

        
        if (CCP1_CCP2_TMR1_COMPARE == ccp1_obj->timer_compare)
        {
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 0 ;
                    
        }
        else if (CCP1_CCP2_TMR3_COMPARE == ccp1_obj->timer_compare)
        {           
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 1 ;
        }
        else if (CCP1_TMR1_CCP2_TMR3_COMPARE == ccp1_obj->timer_compare)
        {           
            T3CONbits.T3CCP1 = 1 ;
            T3CONbits.T3CCP2 = 0 ;
        }
        else { /* Nothing */ } 
        
#endif
        
    }
    
    return ret ;
}

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_PWM_MODE 
static std_ReturnType CCP1_CONFIGURE_PWM(const ccp1_t *ccp1_obj)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp1_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {   
         if ( ccp1_obj->mode == CCP1_PWM_MODE  )
        {
            
            PR2 = (uint8)( (_XTAL_FREQ)/ ( ccp1_obj->pwm_freq_KHZ * 1000*4.0* ccp1_obj->tmr2_PSCA * ccp1_obj->tmr2_POSTSCA )  -1 ) ;                /* Configure the period */
             ret = CCP1_pwm_set_duty_cycle(ccp1_obj , ccp1_obj->duty_cycle_percentage) ;
            
        }
       
         
    }
    
    return ret ;
}
#endif

/////////////////////////////////////////////////////////////////////////////
 void CCP1_ISR(void) 
 {
     
#if CCP1_INTERRUPT_CFG_ENABLE == 1
     CCP1_INTERRUPT_CLEAR_FLAG();
     if(_CCP1_INTERRUPT_HANDLER_)
         _CCP1_INTERRUPT_HANDLER_();
#endif 
     
 }