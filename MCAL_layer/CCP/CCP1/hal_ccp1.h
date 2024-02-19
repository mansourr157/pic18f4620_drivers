/* 
 * File:   hal_ccp1.h
 * Author: Mansour
 *
 * Created on January 11, 2024, 1:10 AM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H


/*   section: Includes  */
#include "hal_ccp1_cfg.h"
#include "pic18f4620.h"
#include "../../mcal_std_types.h"
#include "../../interrupts/mcal_internal_interrupts.h"

/*   section: Macros  */

#define CCP1_MODULE_DISABLE 0

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE
#define CCP1_CAPTURE_1_FALLING_EDG  4
#define CCP1_CAPTURE_1_RISING_EDG     5   
#define CCP1_CAPTURE_4_RISING_EDG    6      
#define CCP1_CAPTURE_16_RISING_EDG  7

#define CCP1_CCP2_TMR1_CAPTURE  0
#define CCP1_CCP2_TMR3_CAPTURE  2
#define CCP1_TMR1_CCP2_TMR3_CAPTURE 1

#endif 


#if CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE 
#define CCP1_COMPARE_HIGH_ON_MATCH  8
#define CCP1_COMPARE_LOW_ON_MATCH   9
#define CCP1_COMPARE_TOGGLE_ON_MATCH    2
#define CCP1_COMPARE_SOFTWARE_INTERRUPT_ON_MATCH 10   // NO ACTION ON PIN CCP1
#define CCP1_COMPARE_SPECIAL_EVENT_ON_MATCH             11   

#define CCP1_CCP2_TMR1_COMPARE  0
#define CCP1_CCP2_TMR3_COMPARE  2
#define CCP1_TMR1_CCP2_TMR3_COMPARE 1

#endif 


#if CCP1_CFG_MODE_SELECT == CCP1_CFG_PWM_MODE 
#define CCP1_PWM_MODE   12

#define CCP1_TMR2_POSTSCALER1_1  1
#define CCP1_TMR2_POSTSCALER1_2  2
#define CCP1_TMR2_POSTSCALER1_3  3
#define CCP1_TMR2_POSTSCALER1_4  4
#define CCP1_TMR2_POSTSCALER1_5  5
#define CCP1_TMR2_POSTSCALER1_6  6
#define CCP1_TMR2_POSTSCALER1_7  7
#define CCP1_TMR2_POSTSCALER1_8  8
#define CCP1_TMR2_POSTSCALER1_9  9
#define CCP1_TMR2_POSTSCALER1_10  10
#define CCP1_TMR2_POSTSCALER1_11  11
#define CCP1_TMR2_POSTSCALER1_12  12
#define CCP1_TMR2_POSTSCALER1_13  13
#define CCP1_TMR2_POSTSCALER1_14  14
#define CCP1_TMR2_POSTSCALER1_15  15
#define CCP1_TMR2_POSTSCALER1_16  16


#define CCP1_TMR2_PRESCALER1_1  1
#define CCP1_TMR2_PRESCALER1_4  4
#define CCP1_TMR2_PRESCALER1_16  16
#endif 


/*   section: Macro Functions declarations */
#define CCP1_MODE_SELECT(_X) (CCP1CONbits.CCP1M = _X)

/*   section: Data Types declarations */

typedef union 
{
    struct 
    {
        uint8 CCP1L ;
        uint8 CCP1H ;
    };
    
    struct 
    {
        uint16 CCP1_16B ;
    };
    
}ccp1_register_t;


typedef struct 
{
    uint8 mode :4;
    
#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE
    
#if CCP1_INTERRUPT_CFG_ENABLE == 1
    void ( *CCP1_INTERRUPT_HANDLER ) (void) ;
    uint8 priority :1 ;
#endif
    
    uint8 timer_capture :1 ;
#endif 

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE  
    
#if CCP1_INTERRUPT_CFG_ENABLE == 1
    void ( *CCP1_INTERRUPT_HANDLER ) (void) ;
    uint8 priority :1 ;
#endif
    
    uint8 timer_compare :1 ;
#endif 

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_PWM_MODE 
    uint16 pwm_freq_KHZ ;
    uint8 duty_cycle_percentage ;
    uint8 tmr2_PSCA ; 
    uint8 tmr2_POSTSCA ; 
#endif 
    
}ccp1_t;


/*   section: Function declarations  */

std_ReturnType CCP1_Init(const ccp1_t *ccp1_obj) ;
std_ReturnType CCP1_DeInit(const ccp1_t *ccp1_obj) ;

////////////////////////////////////////////////////////////////////////////////////

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_CAPTURE_MODE
std_ReturnType CCP1_capture_get_value(uint16 *capture_value);
#endif 

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_COMPARE_MODE  
std_ReturnType CCP1_compare_set_value( uint16 *compare_value);
#endif 

#if CCP1_CFG_MODE_SELECT == CCP1_CFG_PWM_MODE 
std_ReturnType CCP1_pwm_set_duty_cycle(const ccp1_t *ccp1_obj , uint8 duty_cycle_percentage);
#endif 


#endif	/* HAL_CCP1_H */

