/* 
 * File:   mcal_interrupt_manager.c
 * Author: Mansour
 *
 * Created on December 1, 2023, 2:20 PM
 */

#include "mcal_interrupt_manager.h"

#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void)
{
              
    /* TMR0 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCONbits.TMR0IE ) && ( INTERRUPT_OCCUR == INTCONbits.TMR0IF  ) && ( INTCON2bits.TMR0IP ==1  ) )
    {
        TMR0_ISR();
    }
    else { /*Nothing*/ }
              
    /* TMR1 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TMR1IE ) && ( INTERRUPT_OCCUR == PIR1bits.TMR1IF  ) && ( IPR1bits.TMR1IP ==1  ) )
    {
        TMR1_ISR();
    }
    else { /*Nothing*/ }

    /* TMR2 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TMR2IE ) && ( INTERRUPT_OCCUR == PIR1bits.TMR2IF  ) && ( IPR1bits.TMR2IP ==1  ) )
    {
        TMR2_ISR();
    }
    else { /*Nothing*/ }

    /* TMR3 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE2bits.TMR3IE ) && ( INTERRUPT_OCCUR == PIR2bits.TMR3IF  ) && ( IPR2bits.TMR3IP ==1  ) )
    {
        TMR3_ISR();
    }
    else { /*Nothing*/ }

    
    /* ADC INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.ADIE ) && ( INTERRUPT_OCCUR == PIR1bits.ADIF  ) && ( IPR1bits.ADIP == 1  ) )
    {
        ADC_ISR();
    }
    else { /*Nothing*/ }

    
    /* CCP1 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.CCP1IE ) && ( INTERRUPT_OCCUR == PIR1bits.CCP1IF  ) && ( IPR1bits.CCP1IP == 1  ) )
    {
        CCP1_ISR();
    }
    else { /*Nothing*/ }
    
    
    /* CCP2 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE2bits.CCP2IE ) && ( INTERRUPT_OCCUR == PIR2bits.CCP2IF  ) && ( IPR2bits.CCP2IP == 1  ) )
    {
        CCP2_ISR();
    }
    else { /*Nothing*/ }
    
    
    /* INT0 INTERRUPT */
    if ( ( INTERRUPT_ENABLE == INTCONbits.INT0E ) && ( INTERRUPT_OCCUR == INTCONbits.INT0IF ) )
    {
        INT0_ISR();
    }
    else { /*Nothing*/ }
    
    /* INT1 INTERRUPT */
    if ( ( INTERRUPT_ENABLE == INTCON3bits.INT1IE ) && ( INTERRUPT_OCCUR == INTCON3bits.INT1IF ) && ( 1 == INTCON3bits.INT1IP ) )
    {
        INT1_ISR();
    }
    else { /*Nothing*/ }

    /* INT2 INTERRUPT */
    if ( ( INTERRUPT_ENABLE == INTCON3bits.INT2IE ) && ( INTERRUPT_OCCUR == INTCON3bits.INT2IF ) && ( 1 == INTCON3bits.INT2IP ) )
    {
        INT2_ISR();
    }
    else { /*Nothing*/ }   
    
    /* RBx INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCONbits.RBIE ) && ( INTERRUPT_OCCUR == INTCONbits.RBIF )  )
    {
        RBx_ISR();
    }
    else { /*Nothing*/ }

    /* USART TRANSMITTER INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TXIE ) && ( INTERRUPT_OCCUR == PIR1bits.TXIF ) && ( 1 == IPR1bits.TXIP ) )
    {
        USART_TX_ISR();
    }
    else { /*Nothing*/ }   

    /* USART RECEIVER INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.RCIE ) && ( INTERRUPT_OCCUR == PIR1bits.RCIF ) && ( 1 == IPR1bits.RCIP ) )
    {
        USART_RX_ISR();
    }
    else { /*Nothing*/ }   

    /* SPI INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.SSPIE ) && ( INTERRUPT_OCCUR == PIR1bits.SSPIF ) && ( 1 == IPR1bits.SSPIP ) )
    {
        SPI_ISR();
    }
    else { /*Nothing*/ }   


}

void __interrupt( low_priority ) InterruptManagerLow(void)
{   
         /* TMR0 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCONbits.TMR0IE ) && ( INTERRUPT_OCCUR == INTCONbits.TMR0IF  ) && ( INTCON2bits.TMR0IP ==0  ) )
    {
        TMR0_ISR();
    }
    else { /*Nothing*/ }
    
        /* TMR1 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TMR1IE ) && ( INTERRUPT_OCCUR == PIR1bits.TMR1IF  ) && ( IPR1bits.TMR1IP ==0  ) )
    {
        TMR1_ISR();
    }
    else { /*Nothing*/ }    
    
        /* TMR2 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TMR2IE ) && ( INTERRUPT_OCCUR == PIR1bits.TMR2IF  ) && ( IPR1bits.TMR2IP ==0  ) )
    {
        TMR2_ISR();
    }
    else { /*Nothing*/ }
    
    /* TMR3 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE2bits.TMR3IE ) && ( INTERRUPT_OCCUR == PIR2bits.TMR3IF  ) && ( IPR2bits.TMR3IP ==0  ) )
    {
        TMR3_ISR();
    }
    else { /*Nothing*/ }

    
    /* ADC INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.ADIE ) && ( INTERRUPT_OCCUR == PIR1bits.ADIF  ) && ( IPR1bits.ADIP == 0  ) )
    {
        ADC_ISR();
    }
    else { /*Nothing*/ }

    
    /* CCP1 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.CCP1IE ) && ( INTERRUPT_OCCUR == PIR1bits.CCP1IF  ) && ( IPR1bits.CCP1IP == 0  ) )
    {
        CCP1_ISR();
    }
    else { /*Nothing*/ }
    
    /* CCP2 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE2bits.CCP2IE ) && ( INTERRUPT_OCCUR == PIR2bits.CCP2IF  ) && ( IPR2bits.CCP2IP == 0  ) )
    {
        CCP2_ISR();
    }
    else { /*Nothing*/ }
      
    
    /* INT1 INTERRUPT */
    if ( ( INTERRUPT_ENABLE == INTCON3bits.INT1IE ) && ( INTERRUPT_OCCUR == INTCON3bits.INT1IF )  && ( 0 == INTCON3bits.INT1IP ))
    {
        INT1_ISR();
    }
    else { /*Nothing*/ }  
    
    /* INT2 INTERRUPT */
    if ( ( INTERRUPT_ENABLE == INTCON3bits.INT2IE ) && ( INTERRUPT_OCCUR == INTCON3bits.INT2IF )  && ( 0 == INTCON3bits.INT2IP ) )
    {
        INT2_ISR();
    }
    else { /*Nothing*/ }
    
    /* RBx INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCONbits.RBIE ) && ( INTERRUPT_OCCUR == INTCONbits.RBIF )  )
    {
        RBx_ISR();
    }
    else { /*Nothing*/ }
      
    /* USART TRANSMITTER INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TXIE ) && ( INTERRUPT_OCCUR == PIR1bits.TXIF ) && ( 0 == IPR1bits.TXIP ) )
    {
        USART_TX_ISR();
    }
    else { /*Nothing*/ }   
  
    
    /* USART RECEIVER INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.RCIE ) && ( INTERRUPT_OCCUR == PIR1bits.RCIF ) && ( 0 == IPR1bits.RCIP ) )
    {
        USART_RX_ISR();
    }
    else { /*Nothing*/ }   
    
    
    /* SPI INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.SSPIE ) && ( INTERRUPT_OCCUR == PIR1bits.SSPIF ) && ( 0 == IPR1bits.SSPIP ) )
    {
        SPI_ISR();
    }
    else { /*Nothing*/ }   
    
}

#else

void __interrupt() InterruptManager(void)
{
         /* TMR0 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCONbits.TMR0IE ) && ( INTERRUPT_OCCUR == INTCONbits.TMR0IF  ) )
    {
        TMR0_ISR();
    }
    else { /*Nothing*/ }
    
        /* TMR1 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TMR1IE ) && ( INTERRUPT_OCCUR == PIR1bits.TMR1IF  )   )
    {
        TMR1_ISR();
    }
    else { /*Nothing*/ }
    
    
        /* TMR2 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TMR2IE ) && ( INTERRUPT_OCCUR == PIR1bits.TMR2IF  )   )
    {
        TMR2_ISR();
    }
    else { /*Nothing*/ }
    
    /* TMR3 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE2bits.TMR3IE ) && ( INTERRUPT_OCCUR == PIR2bits.TMR3IF  )  )
    {
        TMR3_ISR();
    }
    else { /*Nothing*/ }

     /* ADC INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.ADIE ) && ( INTERRUPT_OCCUR == PIR1bits.ADIF  ) )
    {
        ADC_ISR();
    }
    else { /*Nothing*/ }
    
     /* CCP1 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE1bits.CCP1IE ) && ( INTERRUPT_OCCUR == PIR1bits.CCP1IF  ) )
    {
        CCP1_ISR();
    }
    else { /*Nothing*/ }
    
     /* CCP2 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == PIE2bits.CCP2IE ) && ( INTERRUPT_OCCUR == PIR2bits.CCP2IF  ) )
    {
        CCP2_ISR();
    }
    else { /*Nothing*/ }
    
     /* INT0 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCONbits.INT0E ) && ( INTERRUPT_OCCUR == INTCONbits.INT0IF ) )
    {
        INT0_ISR();
    }
    else { /*Nothing*/ }
    
     /* INT1 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCON3bits.INT1IE ) && ( INTERRUPT_OCCUR == INTCON3bits.INT1IF ) )
    {
        INT1_ISR();
    }
    else { /*Nothing*/ }
    
     /* INT2 INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCON3bits.INT2IE ) && ( INTERRUPT_OCCUR == INTCON3bits.INT2IF ) )
    {
        INT2_ISR();
    }
    else { /*Nothing*/ }
    
     /* RBx INTERRUPT  */
    if ( ( INTERRUPT_ENABLE == INTCONbits.RBIE ) && ( INTERRUPT_OCCUR == INTCONbits.RBIF ) )
    {
        RBx_ISR();
    }
    else { /*Nothing*/ }
    
    /* USART TRANSMITTER INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.TXIE ) && ( INTERRUPT_OCCUR == PIR1bits.TXIF ) )
    {
        USART_TX_ISR();
    }
    else { /*Nothing*/ }   
  
    
    /* USART RECEIVER INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.RCIE ) && ( INTERRUPT_OCCUR == PIR1bits.RCIF )  )
    {
        USART_RX_ISR();
    }
    else { /*Nothing*/ }   
       
    /* SPI INTERRUPT */
    if ( ( INTERRUPT_ENABLE == PIE1bits.SSPIE ) && ( INTERRUPT_OCCUR == PIR1bits.SSPIF )  )
    {
        SPI_ISR();
    }
    else { /*Nothing*/ }   
    
    
}

#endif