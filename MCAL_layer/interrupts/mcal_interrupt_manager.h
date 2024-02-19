/* 
 * File:   mcal_interrupt_manager.h
 * Author: Mansour
 *
 * Created on December 1, 2023, 2:20 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/*   section: Includes  */
#include "mcal_interrupt_cfg.h"

/*   section: Macros  */


/*   section: Macro Functions declarations */


/*   section: Data Types declarations */


/*   section: Function declarations  */

 void ADC_ISR(void) ;
 void CCP1_ISR(void) ;
 void CCP2_ISR(void) ;
 
 void USART_TX_ISR (void);
 void USART_RX_ISR (void);
 
 void SPI_ISR (void);
 
 void TMR0_ISR(void);
 void TMR1_ISR(void);
 void TMR2_ISR(void);
 void TMR3_ISR(void);
 
 void INT0_ISR(void) ;
 void INT1_ISR(void) ;
 void INT2_ISR(void) ;
 void RBx_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

