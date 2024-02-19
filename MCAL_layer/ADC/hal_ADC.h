/* 
 * File:   hal_ADC.h
 * Author: Mansour
 *
 * Created on December 20, 2023, 1:14 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H


/*   section: Includes  */

#include "hal_ADC_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupts/mcal_internal_interrupts.h"
//#include "pic18f4620.h"

/*   section: Macros  */

#define ADC_RIGHT_JUSTIFIED_FORMAT  1
#define ADC_LEFT_JUSTIFIED_FORMAT  0

#define ADC_CONVERSION_COMPLETED  1
#define ADC_CONVERSION_INPROGRESS 0

#define ADC_VOLTAGE_REFERENCE_ENABLED 1
#define ADC_VOLTAGE_REFERENCE_DISABLED  0

/*   section: Macro Functions declarations */

#define ADC_ENABLE() (ADCON0bits.ADON = 1)
#define ADC_DISABLE() (ADCON0bits.ADON = 0)

#define ADC_START_CONVERSION() (ADCON0bits.GO = 1)

#define ADC_STATUS() (ADCON0bits.GODONE)

#define ADC_SELECT_CHANNEL(_X) (ADCON0bits.CHS = _X )

#define conversion_result_t uint16

/*  if u choosed AN4 for examble... All the pins before it (AN0,AN1,AN2,AN3) will also configured as analog */
#define ADC_ANALOG_SELECT_NONE() (ADCON1bits.PCFG = 15) 
#define ADC_ANALOG_SELECT_AN0() (ADCON1bits.PCFG = 14) 
#define ADC_ANALOG_SELECT_AN1() (ADCON1bits.PCFG = 13) 
#define ADC_ANALOG_SELECT_AN2() (ADCON1bits.PCFG = 12) 
#define ADC_ANALOG_SELECT_AN3() (ADCON1bits.PCFG = 11) 
#define ADC_ANALOG_SELECT_AN4() (ADCON1bits.PCFG = 10) 
#define ADC_ANALOG_SELECT_AN5() (ADCON1bits.PCFG = 9) 
#define ADC_ANALOG_SELECT_AN6() (ADCON1bits.PCFG = 8) 
#define ADC_ANALOG_SELECT_AN7() (ADCON1bits.PCFG = 7) 
#define ADC_ANALOG_SELECT_AN8() (ADCON1bits.PCFG = 6) 
#define ADC_ANALOG_SELECT_AN9() (ADCON1bits.PCFG = 5) 
#define ADC_ANALOG_SELECT_AN10() (ADCON1bits.PCFG = 4) 
#define ADC_ANALOG_SELECT_AN11() (ADCON1bits.PCFG = 3) 
#define ADC_ANALOG_SELECT_AN12() (ADCON1bits.PCFG = 2) 

#define ADC_ENABLE_VOLTAGE_REFERENCE() (ADCON1bits.VCFG = 3 )
#define ADC_DISABLE_VOLTAGE_REFERENCE() (ADCON1bits.VCFG = 0)

#define ADC_RESULT_RIGHT_FORMAT() (ADCON2bits.ADFM = ADC_RIGHT_JUSTIFIED_FORMAT)
#define ADC_RESULT_LEFT_FORMAT()   (ADCON2bits.ADFM = ADC_LEFT_JUSTIFIED_FORMAT)

#define ADC_ACQUISITION_TIME_SELECT(_X) (ADCON2bits.ACQT = _X)
#define ADC_CONVERSION_CLOCK_SELECT(_X) (ADCON2bits.ADCS = _X)



/*   section: Data Types declarations */

typedef void ( *adc_interrupt_handler_t) (void) ;


typedef enum {
    
    AN_0 ,
    AN_1 ,
    AN_2 ,
    AN_3 ,
    AN_4 ,
    AN_5 ,
    AN_6 ,
    AN_7 ,
    AN_8 ,
    AN_9 ,
    AN_10 ,
    AN_11 ,
    AN_12 
    
}adc_select_channel_t;

typedef enum {
    
    TAD0 ,
    TAD2 ,
    TAD4 ,
    TAD6 ,
    TAD8 ,
    TAD12 ,
    TAD16 ,
    TAD20 ,
    
}adc_acquisition_time_select_bits_t;

typedef enum {
    
    FOSC_2 ,
    FOSC_8 ,
    FOSC_32 ,
    FRc ,
    FOSC_4 ,
    FOSC_16 ,
    FOSC_64 
    
}adc_conversion_clock_bits_t;


typedef struct {
    
//    pin_config_t pin ;
    uint8 channel :4 ;
    uint8 format   :1 ;
    uint8 voltage_reference   :1 ;
    
    adc_acquisition_time_select_bits_t  acquisition_time ;
    adc_conversion_clock_bits_t conversion_clock ;
    
#if ADC_INTERRUPT_CFG_ENABLE == 1
    void ( *ADC_INTERRUPT_HANDLER ) (void) ;
    interrupt_priority_cfg interrupt_priority   ;

#endif
    
}adc_obj_t;


/*   section: Function declarations  */

std_ReturnType ADC_Init( const adc_obj_t *adc_obj ) ;
std_ReturnType ADC_deInit( const adc_obj_t *adc_obj ) ;
std_ReturnType ADC_start_conversion( const adc_obj_t *adc_obj ) ;
void adc_select_channel(adc_select_channel_t channel) ;
/**
 * 
 * @param adc_obj
 * @param status      True: if it is done   False: if it is in progress  
 * @return 
 */
std_ReturnType ADC_is_conversion_done( const adc_obj_t *adc_obj , uint8 *status) ;
std_ReturnType ADC_get_conversion_result( const adc_obj_t *adc_obj , conversion_result_t *result) ;  //conversion_result_t uint16

std_ReturnType ADC_get_conversion_blocking (const adc_obj_t *adc_obj , conversion_result_t *result  , 
                                                                        adc_select_channel_t channel );
std_ReturnType ADC_SelectChannel_StartConversion (const adc_obj_t *adc_obj , adc_select_channel_t channel );


#endif	/* HAL_ADC_H */

