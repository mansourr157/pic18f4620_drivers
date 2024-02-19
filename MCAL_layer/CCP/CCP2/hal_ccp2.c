/* 
 * File:   hal_ccp2.c
 * Author: Mansour
 *
 * Created on January 11, 2024, 1:11 AM
 */

#include "hal_ccp2.h"

static void ( *_CCP2_INTERRUPT_HANDLER_ ) (void) = NULL ;
static std_ReturnType CCP2_CONFIGURE_INTERRUPT(const ccp2_t *ccp2_obj);
static std_ReturnType CCP2_CONFIGURE_PIN_DIRECTION(const ccp2_t *ccp2_obj);
static std_ReturnType CCP2_CONFIGURE_TIMERS(const ccp2_t *ccp2_obj) ;
static std_ReturnType CCP2_CONFIGURE_PWM(const ccp2_t *ccp2_obj);

////////////////////////////////////////////////////

  std_ReturnType CCP2_Init(const ccp2_t *ccp2_obj) 
{
    std_ReturnType ret = E_OK ; 
    if (NULL == ccp2_obj)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        /* Disable The Module */
        CCP2_MODE_SELECT(CCP2_MODULE_DISABLE) ;
        
        /* Select the module mode */
        CCP2_MODE_SELECT(ccp2_obj->mode) ;
        
        /* Configure the pin direction */
        CCP2_CONFIGURE_PIN_DIRECTION(ccp2_obj);

        /* Configure the timers for capture and compare */
        CCP2_CONFIGURE_TIMERS(ccp2_obj);

        /* Configure the PWM  */                                                                    
#if CCP2_CFG_MODE_SELECT == CCP2_CFG_PWM_MODE
        CCP2_CONFIGURE_PWM(ccp2_obj);
#endif

    /* Configure The Interrupt */
#if CCP2_CFG_MODE_SELECT == CCP2_CFG_CAPTURE_MODE || CCP2_CFG_MODE_SELECT == CCP2_CFG_COMPARE_MODE
        CCP2_CONFIGURE_INTERRUPT(ccp2_obj);
#endif
        
    }
    
    return ret ;
}
  

std_ReturnType CCP2_DeInit(const ccp2_t *ccp2_obj) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp2_obj)
    {
        ret = E_NOT_OK ;
    }
    
    else
    {      
       CCP2_MODE_SELECT(CCP2_MODULE_DISABLE) ;
#if CCP2_INTERRUPT_CFG_ENABLE == 1
      CCP2_INTERRUPT_DISABLE();  
#endif       
    }
    
    return ret ;
}


/////////////////////////////////////////////////////////////////////////////

#if CCP2_CFG_MODE_SELECT == CCP2_CFG_CAPTURE_MODE
std_ReturnType CCP2_capture_get_value( uint16 *capture_value)
{
    std_ReturnType ret = E_OK ;
    if ( NULL == capture_value)
    {
        ret = E_NOT_OK ;
    }
    
    else
    {      
        ccp2_register_t ccp2_res = { .CCP2_16B = 0 };
        ccp2_res.CCP2H = CCPR2H ;
        ccp2_res.CCP2L = CCPR2L ;
        *capture_value = ccp2_res.CCP2_16B ;
    }
    
    return ret ;
}

#endif 

#if CCP2_CFG_MODE_SELECT == CCP2_CFG_COMPARE_MODE  
std_ReturnType CCP2_compare_set_value(uint16 *compare_value)
{
    std_ReturnType ret = E_OK ;
    if (NULL == compare_value)
    {
        ret = E_NOT_OK ;
    }
    
    else
    {      
        ccp2_register_t ccp2_comp_val = { .CCP2_16B = *compare_value };
        CCPR2H = ccp2_comp_val.CCP2H ;
        CCPR2L = ccp2_comp_val.CCP2L ;
        
    }
    
    return ret ;
}

#endif 

#if CCP2_CFG_MODE_SELECT == CCP2_CFG_PWM_MODE 
std_ReturnType CCP2_pwm_set_duty_cycle(const ccp2_t *ccp2_obj , uint8 duty_cycle_percentage)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp2_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        uint16 L_Value  = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)duty_cycle_percentage / 100.0));    
        
        CCP2CONbits.DC2B = (uint8)(L_Value & 0x0003) ;      /* Configure the Duty cycle */
        CCPR2L = (uint8)(L_Value >>2);                                   /* Configure the Duty cycle */
 
    }
    
    return ret ;
}

#endif 



///////////////////////////////////////////////   Static function definitions
#if CCP2_CFG_MODE_SELECT == CCP2_CFG_CAPTURE_MODE || CCP2_CFG_MODE_SELECT == CCP2_CFG_COMPARE_MODE

static std_ReturnType CCP2_CONFIGURE_INTERRUPT(const ccp2_t *ccp2_obj)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp2_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        #if CCP2_INTERRUPT_CFG_ENABLE == 1
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLEAR_FLAG() ;
        _CCP2_INTERRUPT_HANDLER_ = ccp2_obj->CCP2_INTERRUPT_HANDLER ;
        
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable ();
        if (HIGH_PRIORITY == ccp2_obj->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_INTERRUPT_HIGH_PRIORITY_ENABLE () ;
        }
        else if (LOW_PRIORITY == ccp2_obj->priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            CCP2_INTERRUPT_LOW_PRIORITY_ENABLE () ;
        }
        else 
        {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_INTERRUPT_HIGH_PRIORITY_ENABLE () ;
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

static std_ReturnType CCP2_CONFIGURE_PIN_DIRECTION(const ccp2_t *ccp2_obj)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp2_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {   
        
#if CCP2_CFG_MODE_SELECT == CCP2_CFG_CAPTURE_MODE
        if ( ccp2_obj->mode == CCP2_CAPTURE_1_FALLING_EDG || 
             ccp2_obj->mode == CCP2_CAPTURE_1_RISING_EDG   || 
             ccp2_obj->mode == CCP2_CAPTURE_4_RISING_EDG   || 
             ccp2_obj->mode == CCP2_CAPTURE_16_RISING_EDG         )
        {
            TRISCbits.RC1 = 1 ;
        }
        
#endif

#if CCP2_CFG_MODE_SELECT == CCP2_CFG_COMPARE_MODE
        if ( ccp2_obj->mode == CCP2_COMPARE_HIGH_ON_MATCH || 
             ccp2_obj->mode == CCP2_COMPARE_LOW_ON_MATCH   || 
             ccp2_obj->mode == CCP2_COMPARE_TOGGLE_ON_MATCH   || 
             ccp2_obj->mode == CCP2_COMPARE_SPECIAL_EVENT_ON_MATCH   || 
             ccp2_obj->mode == CCP2_COMPARE_SOFTWARE_INTERRUPT_ON_MATCH         )
        {
            TRISCbits.RC1 = 0 ;
        }
        
#endif
        
#if CCP2_CFG_MODE_SELECT == CCP2_CFG_PWM_MODE
        if ( ccp2_obj->mode == CCP2_PWM_MODE  )
        {
            TRISCbits.RC1 = 0 ;          
        }
        
#endif
    
        
    }
    
    return ret ;
}

static std_ReturnType CCP2_CONFIGURE_TIMERS(const ccp2_t *ccp2_obj)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp2_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {   
          
#if CCP2_CFG_MODE_SELECT == CCP2_CFG_CAPTURE_MODE 
        if (CCP1_CCP2_TMR1_CAPTURE == ccp2_obj->timer_capture)
        {       
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 0 ;
        }
        else if (CCP1_CCP2_TMR3_CAPTURE == ccp2_obj->timer_capture)
        {          
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 1 ;
        }
        else if (CCP1_TMR1_CCP2_TMR3_CAPTURE == ccp2_obj->timer_capture)
        {          
            T3CONbits.T3CCP1 = 1 ;
            T3CONbits.T3CCP2 = 0 ;
        }
        else { /* Nothing */ } 
        
#endif

#if CCP2_CFG_MODE_SELECT == CCP2_CFG_COMPARE_MODE

        
        if (CCP1_CCP2_TMR1_COMPARE == ccp2_obj->timer_compare)
        {
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 0 ;
                    
        }
        else if (CCP1_CCP2_TMR3_COMPARE == ccp2_obj->timer_compare)
        {           
            T3CONbits.T3CCP1 = 0 ;
            T3CONbits.T3CCP2 = 1 ;
        }
        else if (CCP1_TMR1_CCP2_TMR3_COMPARE == ccp2_obj->timer_compare)
        {           
            T3CONbits.T3CCP1 = 1 ;
            T3CONbits.T3CCP2 = 0 ;
        }
        else { /* Nothing */ } 
        
#endif
        
    }
    
    return ret ;
}

#if CCP2_CFG_MODE_SELECT == CCP2_CFG_PWM_MODE 
static std_ReturnType CCP2_CONFIGURE_PWM(const ccp2_t *ccp2_obj)
{
    std_ReturnType ret = E_OK ;
    if (NULL == ccp2_obj )
    {
        ret = E_NOT_OK ;
    }
    else 
    {   
         if ( ccp2_obj->mode == CCP2_PWM_MODE  )
        {
            
            PR2 = (uint8)( (_XTAL_FREQ)/((ccp2_obj->pwm_freq_KHZ)*1000*4.0*(ccp2_obj->tmr2_PSCA) * (ccp2_obj->tmr2_POSTSCA) ) -1 ) ;                /* Configure the period */
            ret = CCP2_pwm_set_duty_cycle(ccp2_obj , ccp2_obj->duty_cycle_percentage) ;
            
        }
       
         
    }
    
    return ret ;
}
#endif

///////////////////////////////////////////////
 void CCP2_ISR(void) 
 {
     
#if CCP2_INTERRUPT_CFG_ENABLE == 1
     CCP2_INTERRUPT_CLEAR_FLAG();
     if(_CCP2_INTERRUPT_HANDLER_)
         _CCP2_INTERRUPT_HANDLER_();
#endif
     
 }

 