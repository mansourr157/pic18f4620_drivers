/* 
 * File:   hal_usart.h
 * Author: Mansour
 *
 * Created on January 22, 2024, 7:21 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/*   section: Includes  */

#include "../mcal_std_types.h"
#include "hal_usart_cfg.h"
#include "../device_config.h"
#include "../interrupts/mcal_internal_interrupts.h"

/*   section: Macros  */
#define USART_SYNCHRONOUS_MODE      1
#define USART_ASYNCHRONOUS_MODE     0

#define USART_BAUD_RATE_HIGH_SPEED  1
#define USART_BAUD_RATE_LOW_SPEED   0

#define USART_BAUD_RATE_16_BIT  1
#define USART_BAUD_RATE_8_BIT   0

#define USART_FRAMMING_ERROR_DETECTED            1
#define USART_FRAMMING_ERROR_CLEARED              0  

#define USART_OVERRUN_ERROR_DETECTED            1
#define USART_OVERRUN_ERROR_CLEARED               0  

#define USART_TSR_EMPTY    1
#define USART_TSR_FULL      0 



/*   section: Macro Functions declarations */
#define _USART_ENABLE() (RCSTAbits.SPEN = 1)
#define _USART_DISABLE() (RCSTAbits.SPEN = 0)

#define _USART_SYNCHRONOUS_MODE() (TXSTAbits.SYNC = 1)
#define _USART_ASYNCHRONOUS_MODE() (TXSTAbits.SYNC = 0)

// TRANSMITION
#define _USART_TRANSMIT_ENABLE() (TXSTAbits.TXEN = 1)
#define _USART_TRANSMIT_DISABLE() (TXSTAbits.TXEN = 0)

#define _USART_9_BIT_TRANSMITION_ENABLE() (TXSTAbits.TX9 = 1)
#define _USART_9_BIT_TRANSMITION_DISABLE() (TXSTAbits.TX9 = 0)

#define _USART_TRANSMIT_9D_BIT(_X) (TXSTAbits.TX9D = _X)

#define _USART_TRANSMIT_SHIFT_REGISTER_STATUS() (TXSTA1bits.TRMT ) 

#define _USART_TRANSMIT_INTERRUPT_ENABLE() (PIE1bits.TXIE = 1)
#define _USART_TRANSMIT_INTERRUPT_DISABLE() (PIE1bits.TXIE = 0)

// RECEIVE
#define _USART_RECEIVE_ENABLE() (RCSTAbits.CREN = 1)
#define _USART_RECEIVE_DISABLE() (RCSTAbits.CREN = 0)

#define _USART_9_BIT_RECEIVE_ENABLE() (RCSTAbits.RX9 = 1)
#define _USART_9_BIT_RECEIVE_DISABLE() (RCSTAbits.RX9 = 0)

#define _USART_RECEIVE_9D_BIT() (RCSTAbits.RX9D)

#define _USART_RECEIVE_INTERRUPT_ENABLE() (PIE1bits.RCIE = 1)
#define _USART_RECEIVE_INTERRUPT_DISABLE() (PIE1bits.RCIE = 0)

// BAUD RATE
#define _USART_HIGH_BAUD_RATE_SELECT() (TXSTAbits.BRGH = 1)
#define _USART_LOW_BAUD_RATE_SELECT() (TXSTAbits.BRGH = 0)

#define _USART_16_BIT_BAUD_RATE_GENERATOR() (BAUDCONbits.BRG16 = 1)
#define _USART_8_BIT_BAUD_RATE_GENERATOR() (BAUDCONbits.BRG16 = 0)

// ERRORS
#define _USART_FRAMMING_ERROR_STATUS() (RCSTAbits.FERR)
#define _USART_OVERRUN_ERROR_STATUS() (RCSTAbits.OERR)


/*   section: Data Types declarations */
typedef enum{
    BAUDRATE_ASYN_8BIT_LOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baud_rate_t;

typedef struct {
    
    uint8 usart_tx_9bit_enable :1 ;
    uint8 bit_9 :1 ;                                    ////////////
    uint8 transmit_enable :1 ;

#if USART_TRANSMIT_INTERRUPT_CFG_ENABLE == 1 
    void (*USART_TRANSMIT_INTERRUPT_HANDLER)(void) ;
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
    uint8 trnsmit_priority :1 ;
#endif 
#endif
    
    
}tx_t;

typedef struct {
    
        uint8 usart_rx_9bit_enable :1 ;
        uint8 receive_enable :1 ;
    
#if USART_RECEIVE_INTERRUPT_CFG_ENABLE == 1 
    void (*USART_RECEIVE_INTERRUPT_HANDLER)(void) ;
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
    uint8 receive_priority :1 ;
#endif 
#endif
        
}rx_t;

typedef struct 
{

    uint8 FERR :1 ;
    uint8 OERR :1 ;
    
#if USART_RECEIVE_INTERRUPT_CFG_ENABLE == 1 
    void (*USART_FRAMING_ERROR_HANDLER)(void) ;
    void (*USART_OVERRUN_ERROR_HANDLER)(void) ;
#endif
    
}error_status_t;

typedef struct {
    
    tx_t transmit ;
    rx_t receive ;
    baud_rate_t baud_rate_config ;
    uint32 baud_rate_value ;
//    error_status_t errors ;
    
}usart_t;

/*   section: Function declarations  */

std_ReturnType USART_ASYNC_Init(const usart_t *usart_obj) ;
std_ReturnType USART_ASYNC_DeInit(const usart_t *usart_obj) ;

std_ReturnType USART_ASYNC_WriteByteBlocking(uint8 data);
std_ReturnType USART_ASYNC_WriteStringBlocking(uint8 *data ,uint16 data_length);


std_ReturnType USART_ASYNC_WriteByteNonBlocking(uint8 data);               
//std_ReturnType USART_ASYNC_WriteStringNonBlocking(uint8 *data, uint16 data_length);  

std_ReturnType USART_ASYNC_ReadByteBlocking(uint8 *data);
std_ReturnType USART_ASYNC_ReadByteNonBlocking(uint8 *data );

std_ReturnType USART_ASYNC_RX_Restart(void); 


#endif	/* HAL_USART_H */

