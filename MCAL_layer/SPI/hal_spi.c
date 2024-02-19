/* 
 * File:   hal_spi.c
 * Author: Mansour
 *
 * Created on January 27, 2024, 1:08 PM
 */

#include "hal_spi.h" 

static void ( *_SPI_INTERRUPT_HANDLER_) (void) = NULL ;

std_ReturnType SPI_Init(const spi_t *spi_obj)
{
    std_ReturnType ret = E_OK ;
    if(NULL == spi_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
       /* DISABLE THE MODULE */
        _SPI_DISABLE();
    
        /* SELECT THE MODE */
        _SPI_MODE_SELECT(spi_obj->spi_mode) ;
        
        /* CONFIGURE CLK POLARITY AND PHASE */
        switch (spi_obj->clk_polarity)
        {
                case SPI_CLK_POLARITY_IDLE_HIGH : 
                    _SPI_CLK_POLARITY_IDLE_HIGH() ;
                    break ;
                    
                case SPI_CLK_POLARITY_IDLE_LOW : 
                    _SPI_CLK_POLARITY_IDLE_LOW() ;
                    break ;
                    default : ;    
        }
        
        switch (spi_obj->clk_phase)
        {
                case SPI_CLK_PHASE_ACTIVE_TO_IDLE : 
                    _SPI_CLK_PHASE_TRANSMIT_FROM_ACTIVE_TO_IDLE() ;
                    break ;
                    
                case SPI_CLK_PHASE_IDLE_TO_ACTIVE : 
                    _SPI_CLK_PHASE_TRANSMIT_FROM_IDLE_TO_ACTIVE() ;
                    break ;
                default : ;    
        }           
                
        /* CONFIGURE PIN DIRECTIONS */
        TRISCbits.RC5 = 0 ;                 /* SDO output */     
        
        switch (spi_obj->spi_mode )
        {        
                case  SPI_MASTER_Fosc_DIV_4   : 
                case  SPI_MASTER_Fosc_DIV_16 : 
                case  SPI_MASTER_Fosc_DIV_64 :
                case  SPI_MASTER_TMR2_DIV_2 :
                    TRISCbits.RC3 = 0 ;                     //  Master SCK OUTPUT
                    break ;
                case  SPI_SLAVE_SS_ENABLE :
                    TRISAbits.RA5 = 1 ;                      /* SS input */
                    TRISCbits.RC3 = 1 ;                     //Slave SCK INPUT
                case  SPI_SLAVE_SS_DISABLE :
                    TRISCbits.RC3 = 1 ;                     //Slave SCK INPUT
                    break ;
        }
        
        /* configure sampling at middle of data output time*/
        switch (spi_obj->sampling)
        {
                case SPI_INPUT_SAMPLED_AT_END : 
                    _SPI_INPUT_SAMPLED_AT_END() ;
                    break ;
                    
                case SPI_INPUT_SAMPLED_AT_MIDDLE : 
                    _SPI_INPUT_SAMPLED_AT_MIDDLE() ;
                    break ;
                default : _SPI_INPUT_SAMPLED_AT_MIDDLE() ;   
        }       
                    
        /* CONFIGURE INTERRUPT */
        
#if SPI_INTERRUPT_CFG_ENABLE == 1
            
            SPI_INTERRUPT_ENABLE();
            _SPI_INTERRUPT_HANDLER_ = spi_obj->SPI_INTERRUPT_HANDLER ;
            SPI_INTERRUPT_CLEAR_FLAG();
            
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelsEnable() ;
            if(spi_obj->interrupt_priority == HIGH_PRIORITY)
            {
                INTERRUPT_GlobalInterruptHighEnable() ;
                SPI_INTERRUPT_HIGH_PRIORITY_ENABLE() ;
            }
            else if (spi_obj->interrupt_priority == LOW_PRIORITY) 
            {
                INTERRUPT_GlobalInterruptHighEnable();
                INTERRUPT_GlobalInterruptLowEnable();
                SPI_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
            else 
            {
                INTERRUPT_GlobalInterruptHighEnable() ;
                SPI_INTERRUPT_HIGH_PRIORITY_ENABLE() ;
            }
            
            
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
      
#endif 
       
        
        /* ENABLE THE MODULE */
        _SPI_ENABLE() ;
        
        
    }
    return ret ;
}

std_ReturnType SPI_DeInit(const spi_t *spi_obj)
{
    std_ReturnType ret = E_OK ;
    if(NULL == spi_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
       _SPI_DISABLE () ;
#if SPI_INTERRUPT_CFG_ENABLE ==1 
       SPI_INTERRUPT_DISABLE();
#endif
       
    }
    return ret ;
}

std_ReturnType SPI_Send_Byte_Blocking(const uint8 data)
{
    std_ReturnType ret = E_OK ;

        SSPBUF = data ;
        while(!(PIR1bits.SSPIF)); /* Waiting to transmit */
        PIR1bits.SSPIF = 0;
        
        uint8 temp = SSPBUF ;
    
    return ret ;

}

std_ReturnType SPI_Send_String_Blocking(const uint8 *data , uint16 data_length)
{
    std_ReturnType ret = E_OK ;
    if (NULL == data)
    {
        ret = E_NOT_OK ;
    }
    else 
    {
        for (uint16 i=0 ; i<data_length ; i++)
        {
            ret |= SPI_Send_Byte_Blocking(data[i]) ;
        }     
        
    }
    return ret ;

}


std_ReturnType SPI_Read_Byte_Blocking(uint8 *data)
{
    std_ReturnType ret = E_OK ;

    while(!SSPSTATbits.BF);
        *data = SSPBUF ;
       
    return ret ;
}

/*
std_ReturnType SPI_Send_Byte_NonBlocking(const spi_t *spi_obj, const uint8 data)
{
    std_ReturnType ret = E_OK ;
    if(NULL == spi_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {

       
       
    }
    return ret ;
}

std_ReturnType SPI_Read_Byte_NonBlocking(const spi_t *spi_obj, uint8 *data)
{
    std_ReturnType ret = E_OK ;
    if(NULL == spi_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {

     
       
    }
    return ret ;
}

 */
//////////////////////////////////
 void SPI_ISR (void)
 {
     
#if SPI_INTERRUPT_CFG_ENABLE == 1
     SPI_INTERRUPT_CLEAR_FLAG() ;
     if(_SPI_INTERRUPT_HANDLER_)
         _SPI_INTERRUPT_HANDLER_();
#endif
     
 }