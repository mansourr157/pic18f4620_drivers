/* 
 * File:   hal_ADC.c
 * Author: Mansour
 *
 * Created on December 20, 2023, 1:14 PM
 */
#include "hal_ADC.h"

/////////
static adc_interrupt_handler_t adc_interrupt_handler = NULL ;

/* Static functions declarations */
static std_ReturnType result_format(const adc_obj_t *adc_obj) ;
static std_ReturnType voltage_reference(const adc_obj_t *adc_obj);
static std_ReturnType interrupt_config(const adc_obj_t *adc_obj);


////////////////////////////////////////////////////////


std_ReturnType ADC_Init( const adc_obj_t *adc_obj ) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == adc_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        /* disable the module */
        ADC_DISABLE() ;
        
        /* Set the acquisition_time */
        ADC_ACQUISITION_TIME_SELECT (adc_obj->acquisition_time) ;
        
        /* Set the conversion_clock */
        ADC_CONVERSION_CLOCK_SELECT (adc_obj->conversion_clock) ;
        
        /* Select The voltage reference  */
        ret |= voltage_reference(adc_obj);
        
        /* Select the result format */
        ret |= result_format(adc_obj);
        
        /* Select the channels , Analog pins and initializing them as input */
        adc_select_channel(adc_obj->channel);
        
        /* configure ADC_interrupt */
        ret |= interrupt_config(adc_obj);
        
        /* Enable the module */
        ADC_ENABLE() ;
        
    }
    return ret ; 
    
}


std_ReturnType ADC_DeInit( const adc_obj_t *adc_obj ) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == adc_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        /* disable the module */
        ADC_DISABLE () ;
        ADC_INTERRUPT_DISABLE();
        
    }
    return ret ; 
    
}

std_ReturnType ADC_start_conversion( const adc_obj_t *adc_obj ) 
{
    
    std_ReturnType ret = E_OK ;
    if( NULL == adc_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        ADC_START_CONVERSION();
    }
    
    return ret ;
}

std_ReturnType ADC_get_conversion_result( const adc_obj_t *adc_obj , conversion_result_t *result) 
{
    
    std_ReturnType ret = E_OK ;
    if( (NULL == adc_obj) || (NULL == result ) )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
       
        if (ADC_RIGHT_JUSTIFIED_FORMAT == adc_obj->format)
        {
            *result = (conversion_result_t)( (ADRESH << 8 ) | (ADRESL) ) ; 
        }
        else if (ADC_LEFT_JUSTIFIED_FORMAT == adc_obj->format)
        {
            *result = (conversion_result_t)( ( (ADRESH << 8 ) | (ADRESL) )  << 6 ) ; 
        }
        else
        {
            *result = (conversion_result_t)( (ADRESH << 8 ) | (ADRESL) ) ; 
        }
    
    }
    
    return ret ;
}

std_ReturnType ADC_get_conversion_blocking (const adc_obj_t *adc_obj , conversion_result_t *result 
                                                                       , adc_select_channel_t channel )
{
    
    std_ReturnType ret = E_OK ;
    if( (NULL == adc_obj) || (NULL == result ) )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        adc_select_channel(channel) ;
        ret |= ADC_start_conversion(adc_obj);
        while ( ADC_STATUS() ) ;
        ret |= ADC_get_conversion_result( adc_obj , result ) ;
    }
    
    return ret ;
}

std_ReturnType ADC_SelectChannel_StartConversion (const adc_obj_t *adc_obj , adc_select_channel_t channel )
{
    
    std_ReturnType ret = E_OK ;
    if( NULL == adc_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        adc_select_channel(channel) ;
        ret = ADC_start_conversion(adc_obj);
    }
    
    return ret ;
}

//////
void adc_select_channel(adc_select_channel_t channel)
{
            ADC_SELECT_CHANNEL(channel) ;
                
        switch (channel)
        {
            case AN_0 :
                SET_BIT( PORTA , PIN0 );
                ADC_ANALOG_SELECT_AN0() ;
                break ;
            case AN_1 :
                SET_BIT( PORTA , PIN1 );
                ADC_ANALOG_SELECT_AN1();
                break ;
            case AN_2 :
                ADC_ANALOG_SELECT_AN2();
                SET_BIT( PORTA , PIN2 );
                break ;
            case AN_3 :
                SET_BIT( PORTA , PIN3 );
                ADC_ANALOG_SELECT_AN3() ;
                break ;
            case AN_4 :
                SET_BIT( PORTA , PIN5 );
                ADC_ANALOG_SELECT_AN4();
                break ;
            case AN_5 :
                SET_BIT( PORTE , PIN0 );
                ADC_ANALOG_SELECT_AN5();
                break ;
            case AN_6 :
                SET_BIT( PORTE , PIN1 );
                ADC_ANALOG_SELECT_AN6();
                break ;
            case AN_7 :
                SET_BIT( PORTE , PIN2 );
                ADC_ANALOG_SELECT_AN7();
                break ;
            case AN_8 :
                SET_BIT( PORTB , PIN2 );
                ADC_ANALOG_SELECT_AN8();
                break ;
            case AN_9 :
                SET_BIT( PORTB , PIN3 );
                ADC_ANALOG_SELECT_AN9();
                break ;
            case AN_10 :
                SET_BIT( PORTB , PIN1 );
                ADC_ANALOG_SELECT_AN10();
                break ;
            case AN_11 :
                SET_BIT( PORTB , PIN4 );
                ADC_ANALOG_SELECT_AN11();
                break ;
            case AN_12 :
                SET_BIT( PORTB , PIN0 );
                ADC_ANALOG_SELECT_AN12();
                break ;    
            
            default :
                SET_BIT( PORTA , PIN0 );
                ADC_ANALOG_SELECT_AN0() ;
                ADC_SELECT_CHANNEL( AN_0 ) ;
                break ;
                
        }

}

/**
 * 
 * @param adc_obj
 * @param status      True: if it is done   False: if it is in progress  
 * @return 
 */
std_ReturnType ADC_is_conversion_done( const adc_obj_t *adc_obj , uint8 *status) 
{
    
    std_ReturnType ret = E_OK ;
    if( (NULL == adc_obj) || (NULL == status ) )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        *status = !ADC_STATUS()  ;
    }
    
    return ret ;
}



///////////// Static Functions definition ////////////////

static std_ReturnType result_format(const adc_obj_t *adc_obj)
{
    
    std_ReturnType ret = E_OK ;
    
    if(NULL == adc_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        if (ADC_RIGHT_JUSTIFIED_FORMAT == adc_obj->format)
        {
            ADC_RESULT_RIGHT_FORMAT();
        }
        else if (ADC_LEFT_JUSTIFIED_FORMAT == adc_obj->format)
        {
            ADC_RESULT_LEFT_FORMAT();
        }
        else
        {
             ADC_RESULT_RIGHT_FORMAT();
        }
        
    }
     return ret;

}

static std_ReturnType voltage_reference(const adc_obj_t *adc_obj)
{
    
     std_ReturnType ret = E_OK ;
    
    if(NULL == adc_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        if (ADC_VOLTAGE_REFERENCE_ENABLED == adc_obj->voltage_reference)
        {
            ADC_ENABLE_VOLTAGE_REFERENCE();
        }
        else if (ADC_VOLTAGE_REFERENCE_DISABLED == adc_obj->voltage_reference)
        {
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        else
        {
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        
    }
     return ret;

}

static std_ReturnType interrupt_config(const adc_obj_t *adc_obj)
{
    
     std_ReturnType ret = E_OK ;
    
    if(NULL == adc_obj )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        
#if ADC_INTERRUPT_CFG_ENABLE == 1
        
        ADC_INTERRUPT_CLEAR_FLAG();
        adc_interrupt_handler = adc_obj->ADC_INTERRUPT_HANDLER ;

#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (HIGH_PRIORITY == adc_obj->interrupt_priority)
        {
        INTERRUPT_GlobalInterruptHighEnable();
        ADC_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        else if (LOW_PRIORITY == adc_obj->interrupt_priority)
        {
        INTERRUPT_GlobalInterruptLowEnable();
        ADC_INTERRUPT_LOW_PRIORITY_ENABLE();
        }
        else
        {
        INTERRUPT_GlobalInterruptHighEnable();
        ADC_INTERRUPT_HIGH_PRIORITY_ENABLE();
        }
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        ADC_INTERRUPT_ENABLE() ;
#endif

#endif  
        
    }
     return ret;

}

void ADC_ISR (void)
{
#if ADC_INTERRUPT_CFG_ENABLE == 1
    ADC_INTERRUPT_CLEAR_FLAG();
    if(adc_interrupt_handler)
        adc_interrupt_handler();
#endif
    
}

