/* 
 * File:   mcal_interrupt_cfg.h
 * Author: Mansour
 *
 * Created on December 1, 2023, 2:19 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H


/*   section: Includes  */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"

/*   section: Macros  */

#define INTERRUPT_ENABLE                         1
#define INTERRUPT_DISABLE                        0
#define INTERRUPT_OCCUR                          1
#define INTERRUPT_NOT_OCCUR                  0
#define INTERRUPT_PRIORITY_ENABLE         1
#define INTERRUPT_PRIORITY_DISABLE        0

/*   section: Macro Functions declarations */

#ifdef  INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE

#define INTERRUPT_PriorityLevelsEnable()             ( RCONbits.IPEN = 1 )
#define INTERRUPT_PriorityLevelsDisable()            ( RCONbits.IPEN = 0 )

#define INTERRUPT_GlobalInterruptHighEnable()        ( INTCONbits.GIEH = 1 )
#define INTERRUPT_GlobalInterruptHighDisable()    ( INTCONbits.GIEH = 0 )

#define INTERRUPT_GlobalInterruptLowEnable()        ( INTCONbits.GIEL = 1 )
#define INTERRUPT_GlobalInterruptLowDisable()    ( INTCONbits.GIEL = 0 )


#else

#define INTERRUPT_GlobalInterruptEnable()          ( INTCONbits.GIE = 1 )
#define INTERRUPT_GlobalInterruptDisable()          ( INTCONbits.GIE = 0 )

#define INTERRUPT_PeripheralInterruptEnable()    ( INTCONbits.PEIE = 1 )
#define INTERRUPT_PeripheralInterruptDisable()    ( INTCONbits.PEIE = 0 )


#endif

/*   section: Data Types declarations */

typedef enum {
    
    LOW_PRIORITY, 
    HIGH_PRIORITY 
    
}interrupt_priority_cfg;

/*   section: Function declarations  */


#endif	/* MCAL_INTERRUPT_CFG_H */

