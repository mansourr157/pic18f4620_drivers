/* 
 * File:   mcal_external_interrupts.h
 * Author: Mansour
 *
 * Created on December 1, 2023, 2:21 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPTS_H
#define	MCAL_EXTERNAL_INTERRUPTS_H

/*   section: Includes  */
#include "mcal_interrupt_cfg.h"

/*   section: Macros  */

/////////////////////////////////////////////////////////////////////////

#ifdef INTERRUPT_EXTERNAL_INTx_FEATURE_ENABLE

#define EXT_INT0_InterruptEnable()          ( INTCONbits.INT0E = 1 )
#define EXT_INT0_InterruptDisable()          ( INTCONbits.INT0E = 0 )
#define EXT_INT0_ClearFlag()                    ( INTCONbits.INT0F = 0 )
#define EXT_INT0_RisingEdgeSet()            ( INTCON2bits.INTEDG0 = 1 )
#define EXT_INT0_FallingEdgeSet()           ( INTCON2bits.INTEDG0 = 0 )

#define EXT_INT1_InterruptEnable()          ( INTCON3bits.INT1E = 1 )
#define EXT_INT1_InterruptDisable()          ( INTCON3bits.INT1E = 0 )
#define EXT_INT1_ClearFlag()                    ( INTCON3bits.INT1F = 0 )
#define EXT_INT1_RisingEdgeSet()            ( INTCON2bits.INTEDG1 = 1 )
#define EXT_INT1_FallingEdgeSet()           ( INTCON2bits.INTEDG1 = 0 )

#define EXT_INT2_InterruptEnable()          ( INTCON3bits.INT2E = 1 )
#define EXT_INT2_InterruptDisable()          ( INTCON3bits.INT2E = 0 )
#define EXT_INT2_ClearFlag()                    ( INTCON3bits.INT2F = 0 )
#define EXT_INT2_RisingEdgeSet()            ( INTCON2bits.INTEDG2 = 1 )
#define EXT_INT2_FallingEdgeSet()           ( INTCON2bits.INTEDG2 = 0 )

/* setting the priority of int1,2 ( RB1,RB2 ) */
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE      

#define EXT_INT1_HighPrioritySet()            ( INTCON3bits.INT1P = 1 )
#define EXT_INT1_LowPrioritySet()            ( INTCON3bits.INT1P = 0 )

#define EXT_INT2_HighPrioritySet()            ( INTCON3bits.INT2P = 1 )
#define EXT_INT2_LowPrioritySet()            ( INTCON3bits.INT2P = 0 )

#endif

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef INTERRUPT_EXTERNAL_IOC_FEATURE_ENABLE

#define EXT_RBx_InterruptEnable()          ( INTCONbits.RBIE = 1 )
#define EXT_RBx_InterruptDisable()          ( INTCONbits.RBIE = 0 )
#define EXT_RBx_ClearFlag()                    ( INTCONbits.RBIF = 0 )

/* setting the priority of RBx ( RB4:RB7 ) */
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE      

#define EXT_RBx_HighPrioritySet()            ( INTCON2bits.RBIP = 1 )
#define EXT_RBx_LowPrioritySet()            ( INTCON2bits.RBIP = 0 )

#endif

#endif
//////////////////////////////////////////////////////////////////////////////

/*   section: Macro Functions declarations */

/////////////////////////////////////////////////////////////////////////////
/*   section: Data Types declarations */

typedef void ( *interrupt_handler) (void) ;

typedef enum {
    
    EXT_INTERRUPT_INT0 ,
    EXT_INTERRUPT_INT1 ,
    EXT_INTERRUPT_INT2 
    
}interrupt_INTx_src;

typedef enum {
    
    FALLING_EDG, 
    RISING_EDG 
    
}interrupt_INTx_edge;

typedef struct {
    
    void ( *EXT_INTERRUPT_HANDLER ) (void) ;
    pin_config_t pin ;
    interrupt_INTx_src      src;
    interrupt_INTx_edge   edge ;
    interrupt_priority_cfg  priority ;
    
}interrupt_INTx_t;

typedef struct {
    
    void ( *EXT_INTERRUPT_HANDLER_HIGH ) (void) ;
    void ( *EXT_INTERRUPT_HANDLER_LOW ) (void) ;
    pin_config_t pin ;
    interrupt_priority_cfg  priority ;
    
}interrupt_RBx_t;

///////////////////////////////////////////////////////////////////////
/*   section: Function declarations  */

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_INTx_Init( const interrupt_INTx_t *int_obj ) ;

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_INTx_DeInit( const interrupt_INTx_t *int_obj ) ;

//////////////////////
/*   section: Function declarations  */

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBx_Init( const interrupt_RBx_t *int_obj ) ;

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBx_DeInit( const interrupt_RBx_t *int_obj ) ;

#endif	/* MCAL_EXTERNAL_INTERRUPTS_H */

