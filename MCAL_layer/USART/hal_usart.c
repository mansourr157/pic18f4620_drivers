/* 
 * File:   hal_usart.c
 * Author: Mansour
 *
 * Created on January 22, 2024, 7:21 AM
 */

#include "hal_usart.h" 

/////////////////////////////////////////////////////

static std_ReturnType baud_rate_config(const usart_t *usart_obj) ;
static std_ReturnType tx_init(const usart_t *usart_obj) ;
static std_ReturnType rx_init(const usart_t *usart_obj) ;
/////////
static void (*_USART_TRANSMIT_INTERRUPT_HANDLER_)(void) = NULL ;
static void (*_USART_RECEIVE_INTERRUPT_HANDLER_)(void) = NULL ;
    
static void (*_USART_FRAMING_ERROR_HANDLER_)(void) = NULL ;
static void (*_USART_OVERRUN_ERROR_HANDLER_)(void) = NULL ;

/////////////////////////////////////////////////////
std_ReturnType USART_ASYNC_Init(const usart_t *usart_obj) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == usart_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        _USART_DISABLE() ;
        
        TRISCbits.RC6 = 1 ;
        TRISCbits.RC7 = 1 ;
        ret = baud_rate_config(usart_obj) ;
        ret |= tx_init(usart_obj) ;
        ret |= rx_init(usart_obj) ;
        
        _USART_ENABLE();
    }
    return ret ;
}
std_ReturnType USART_ASYNC_DeInit(const usart_t *usart_obj) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == usart_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = _USART_DISABLE();
        
#if USART_TRANSMIT_INTERRUPT_CFG_ENABLE ==1 
        USART_TRANSMIT_INTERRUPT_DISABLE();
#endif
        
#if USART_RECEIVE_INTERRUPT_CFG_ENABLE ==1 
        USART_RECEIVE_INTERRUPT_DISABLE();
#endif
        
    }
    return ret ;
}

std_ReturnType USART_ASYNC_WriteByteBlocking(uint8 data)
{   
    std_ReturnType ret = E_OK ;
    
    while (!TXSTAbits.TRMT) ;
    _USART_TRANSMIT_INTERRUPT_ENABLE();
    TXREG = data ;
    
    return ret ;
}

std_ReturnType USART_ASYNC_WriteStringBlocking(uint8 *data ,uint16 data_length)
{   
    std_ReturnType ret = E_OK ;
    
    for(uint16 i=0 ; i<data_length ; i++)
        ret = USART_ASYNC_WriteByteBlocking(data[i]);
    
    return ret ;
}

std_ReturnType USART_ASYNC_WriteByteNonBlocking(uint8 data)
{   
    std_ReturnType ret = E_OK ;
    
    if (TXSTAbits.TRMT)
    {
        _USART_TRANSMIT_INTERRUPT_ENABLE();
        TXREG = data ;
    }
    else { /* Nothing */ }
    
    return ret ;
}

//std_ReturnType USART_ASYNC_WriteStringNonBlocking(uint8 *data, uint16 data_length)
//{   
//    std_ReturnType ret = E_OK ;
//    
//    for(uint16 i=0 ; i<data_length ; i++)
//    {
//        if (TXSTAbits.TRMT)
//        {
//            ret = USART_ASYNC_WriteByteNonBlocking(data[i]);
//        }
//    }
//    
//    return ret ;
//}

std_ReturnType USART_ASYNC_ReadByteBlocking(uint8 *data )
{   
    std_ReturnType ret = E_OK ;
    
    while (!PIR1bits.RCIF) ;
    *data = RCREG ;
    
    return ret ;
}

std_ReturnType USART_ASYNC_ReadByteNonBlocking(uint8 *data )
{   
    std_ReturnType ret = E_NOT_OK ;
    
    if (1 == PIR1bits.RCIF) 
    {
    *data = RCREG ;
    ret = E_OK ;
    }
    else
    {
        ret = E_NOT_OK ;
    }
    
    return ret ;
}

std_ReturnType USART_ASYNC_RX_Restart(void)
{
    std_ReturnType ret = E_OK;
    RCSTAbits.CREN = 0;     /* Disables receiver */
    RCSTAbits.CREN = 1;     /* Enables receiver */
    return ret;
}

/////////////////////////////////////////////////////////////
static std_ReturnType baud_rate_config(const usart_t *usart_obj) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == usart_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        uint16 baud_rate_temp = 0 ;
        switch(usart_obj->baud_rate_config)
        {
            case (BAUDRATE_ASYN_8BIT_LOW_SPEED) : 
                _USART_ASYNCHRONOUS_MODE();
                _USART_8_BIT_BAUD_RATE_GENERATOR();
                _USART_LOW_BAUD_RATE_SELECT();
                baud_rate_temp = ( ( _XTAL_FREQ/(float)usart_obj->baud_rate_value ) / 64 ) - 1 ;
                break ;
                
            case (BAUDRATE_ASYN_8BIT_HIGH_SPEED) : 
                _USART_ASYNCHRONOUS_MODE();
                _USART_8_BIT_BAUD_RATE_GENERATOR();
                _USART_HIGH_BAUD_RATE_SELECT();
                baud_rate_temp = ( ( _XTAL_FREQ/(float)usart_obj->baud_rate_value ) / 16 ) - 1 ;
                break ;
                
            case (BAUDRATE_ASYN_16BIT_LOW_SPEED) : 
                _USART_ASYNCHRONOUS_MODE();
                _USART_16_BIT_BAUD_RATE_GENERATOR();
                _USART_LOW_BAUD_RATE_SELECT();
                baud_rate_temp = ( ( _XTAL_FREQ/(float)usart_obj->baud_rate_value ) / 16 ) - 1 ;
                break ;
                
            case (BAUDRATE_ASYN_16BIT_HIGH_SPEED) :
                _USART_ASYNCHRONOUS_MODE();
                _USART_16_BIT_BAUD_RATE_GENERATOR();
                _USART_HIGH_BAUD_RATE_SELECT();
                baud_rate_temp = ( ( _XTAL_FREQ/(float)usart_obj->baud_rate_value ) / 4 ) - 1 ;
                break ;
                
            case (BAUDRATE_SYN_8BIT) : 
                _USART_SYNCHRONOUS_MODE();
                _USART_8_BIT_BAUD_RATE_GENERATOR();
                baud_rate_temp = ( ( _XTAL_FREQ/(float)usart_obj->baud_rate_value ) / 4 ) - 1 ;
                break ;
                
            case (BAUDRATE_SYN_16BIT) : 
                _USART_SYNCHRONOUS_MODE();
                _USART_16_BIT_BAUD_RATE_GENERATOR();
                baud_rate_temp = ( ( _XTAL_FREQ/(float)usart_obj->baud_rate_value ) / 4 ) - 1 ;
                break ;
                
            default : ;

        }
        
        SPBRG = (uint8) (baud_rate_temp) ;
        SPBRGH = (uint8) (baud_rate_temp >> 8) ;
        
    }
    return ret ;
}

static std_ReturnType tx_init(const usart_t *usart_obj) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == usart_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        /* Enable the module */
        if(usart_obj->transmit.transmit_enable)
        {
            
            _USART_TRANSMIT_ENABLE() ;
            
            /* Enable the interrupt */
#if USART_TRANSMIT_INTERRUPT_CFG_ENABLE == 1
            
            _USART_TRANSMIT_INTERRUPT_HANDLER_ = usart_obj->transmit.USART_TRANSMIT_INTERRUPT_HANDLER ;
            USART_TRANSMIT_INTERRUPT_ENABLE();
            
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelsEnable() ;
            if(usart_obj->transmit.trnsmit_priority == HIGH_PRIORITY)
            {
                INTERRUPT_GlobalInterruptHighEnable() ;
                USART_TRANSMIT_INTERRUPT_HIGH_PRIORITY_ENABLE() ;
            }
            else if (usart_obj->transmit.trnsmit_priority == LOW_PRIORITY) 
            {
                INTERRUPT_GlobalInterruptHighEnable();
                INTERRUPT_GlobalInterruptLowEnable();
                USART_TRANSMIT_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
            else 
            {
                INTERRUPT_GlobalInterruptHighEnable() ;
                USART_TRANSMIT_INTERRUPT_HIGH_PRIORITY_ENABLE() ;
            }
            
            
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
      
#endif 
            
         /* Enable TX9 */
        if (usart_obj->transmit.usart_tx_9bit_enable)
        {
            _USART_9_BIT_TRANSMITION_ENABLE() ;
        }
        else if (usart_obj->transmit.usart_tx_9bit_enable == 0) 
        {
            _USART_9_BIT_TRANSMITION_DISABLE() ;
        }
        else { /*Nothing */ } 
                    
        }
        
        else if (usart_obj->transmit.transmit_enable == 0)
        {
            _USART_TRANSMIT_DISABLE() ;            
        }
        else { /* Nothing */ } 
        
        
        
    }
    return ret ;
}

static std_ReturnType rx_init(const usart_t *usart_obj) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == usart_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        /* Enable the module */
        if(usart_obj->receive.receive_enable)
        {
            
            _USART_RECEIVE_ENABLE() ;
            
            /* Enable the interrupt */
#if USART_RECEIVE_INTERRUPT_CFG_ENABLE == 1
            
            _USART_RECEIVE_INTERRUPT_HANDLER_ = usart_obj->receive.USART_RECEIVE_INTERRUPT_HANDLER ;
//            _USART_FRAMING_ERROR_HANDLER_ = usart_obj->errors.USART_FRAMING_ERROR_HANDLER ;
//            _USART_OVERRUN_ERROR_HANDLER_ = usart_obj->errors.USART_OVERRUN_ERROR_HANDLER ;
            
            USART_RECEIVE_INTERRUPT_ENABLE();
            
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelsEnable() ;
            if(usart_obj->receive.receive_priority == HIGH_PRIORITY)
            {
                INTERRUPT_GlobalInterruptHighEnable() ;
                USART_RECEIVE_INTERRUPT_HIGH_PRIORITY_ENABLE() ;
            }
            else if (usart_obj->receive.receive_priority == LOW_PRIORITY) 
            {
                INTERRUPT_GlobalInterruptHighEnable();
                INTERRUPT_GlobalInterruptLowEnable();
                USART_RECEIVE_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
            else 
            {
                INTERRUPT_GlobalInterruptHighEnable() ;
                USART_RECEIVE_INTERRUPT_HIGH_PRIORITY_ENABLE() ;
            }
            
            
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
      

#endif 
            
         /* Enable RX9 */
        if (usart_obj->receive.usart_rx_9bit_enable)
        {
            _USART_9_BIT_RECEIVE_ENABLE() ;
        }
        else if (usart_obj->receive.usart_rx_9bit_enable == 0) 
        {
            _USART_9_BIT_RECEIVE_DISABLE() ;
        }
        else { /*Nothing */ } 
                    
        }
        
        else if (usart_obj->receive.receive_enable == 0)
        {
            _USART_RECEIVE_DISABLE() ;            
        }
        else { /* Nothing */ } 
        
        
        
    }
    return ret ;
}

///////

void USART_TX_ISR (void)
{
    _USART_TRANSMIT_INTERRUPT_DISABLE();
    if (_USART_TRANSMIT_INTERRUPT_HANDLER_)
        _USART_TRANSMIT_INTERRUPT_HANDLER_();
}

void USART_RX_ISR (void)
{   
    if (_USART_RECEIVE_INTERRUPT_HANDLER_)
        _USART_RECEIVE_INTERRUPT_HANDLER_();
    else { /* Nothing */ }
    
//    if (_USART_FRAMING_ERROR_HANDLER_)
//        _USART_FRAMING_ERROR_HANDLER_();
//    else { /* Nothing */ }
//    
//    if (_USART_OVERRUN_ERROR_HANDLER_)
//        _USART_OVERRUN_ERROR_HANDLER_();
//    else { /* Nothing */ }
    
    uint8 temp = RCREG ;
    
}