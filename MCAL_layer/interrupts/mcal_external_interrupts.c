/* 
 * File:   mcal_external_interrupts.c
 * Author: Mansour
 *
 * Created on December 1, 2023, 2:21 PM
 */

#include "mcal_external_interrupts.h"
///////////////////////////////////////////////////////////////////////  variables declaration

static interrupt_handler INT0_INTERRUPT_HANDLER = NULL ;  
static interrupt_handler INT1_INTERRUPT_HANDLER = NULL ;  
static interrupt_handler INT2_INTERRUPT_HANDLER = NULL ;  

static interrupt_handler RB4_INTERRUPT_HANDLER_HIGH = NULL ;  
static interrupt_handler RB4_INTERRUPT_HANDLER_LOW = NULL ;  
static interrupt_handler RB5_INTERRUPT_HANDLER_HIGH = NULL ;  
static interrupt_handler RB5_INTERRUPT_HANDLER_LOW = NULL ;  
static interrupt_handler RB6_INTERRUPT_HANDLER_HIGH = NULL ;  
static interrupt_handler RB6_INTERRUPT_HANDLER_LOW = NULL ;  
static interrupt_handler RB7_INTERRUPT_HANDLER_HIGH = NULL ; 
static interrupt_handler RB7_INTERRUPT_HANDLER_LOW = NULL ; 

static uint8 PORTB_CAPTURE  ; //   0x 7654 0000

/////////////////////////////////////////////////////////////////////// functions declaration

static std_ReturnType Interrupt_INTx_Enable( const interrupt_INTx_t *int_obj );
static std_ReturnType Interrupt_INTx_Disable( const interrupt_INTx_t *int_obj );
static std_ReturnType Interrupt_INTx_ClearFlag( const interrupt_INTx_t *int_obj );
static std_ReturnType Interrupt_INTx_PinInit( const interrupt_INTx_t *int_obj );
static std_ReturnType Interrupt_INTx_EdgeInit( const interrupt_INTx_t *int_obj );
static std_ReturnType Interrupt_INTx_PriorityInit( const interrupt_INTx_t *int_obj );
static std_ReturnType Interrupt_INTx_SetHandler( const interrupt_INTx_t *int_obj );

 void INT0_ISR(void) ;
 void INT1_ISR(void) ;
 void INT2_ISR(void) ;
 
 static std_ReturnType Interrupt_RBx_Enable ( const interrupt_RBx_t *int_obj ) ; 
 static std_ReturnType Interrupt_RBx_Disable ( const interrupt_RBx_t *int_obj ) ; 
 static std_ReturnType Interrupt_RBx_ClearFlag ( const interrupt_RBx_t *int_obj ) ; 
 static std_ReturnType Interrupt_RBx_PinInit ( const interrupt_RBx_t *int_obj ) ; 
 static std_ReturnType Interrupt_RBx_SetHandler ( const interrupt_RBx_t *int_obj ) ; 
 static std_ReturnType Interrupt_RBx_PriorityInit ( const interrupt_RBx_t *int_obj ) ; 

  void RB4_ISR(void);
  void RB5_ISR(void);
  void RB6_ISR(void);
  void RB7_ISR(void);
 
/////////////////////////////////////////////////////////////////////    functions definitions

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_INTx_Init( const interrupt_INTx_t *int_obj ) 
{
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = Interrupt_INTx_Disable( int_obj ) ;                          /* Disable the External interrupt INTx */
        ret |= Interrupt_INTx_ClearFlag( int_obj );                       /* Clear Interrupt INTx Flag  */ 
        ret |= Interrupt_INTx_PinInit( int_obj ) ;                         /* Configure External interrupt I/O pin */
        ret |= Interrupt_INTx_EdgeInit( int_obj );                      /* Configure External interrupt INTx edge */
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        ret |= Interrupt_INTx_PriorityInit( int_obj );                   /* Configure External Interrupt INTx priority */
#endif
        ret |= Interrupt_INTx_SetHandler( int_obj );                  /* Configure Default Interrupt CallBack */
        
        ret |= Interrupt_INTx_Enable( int_obj ) ;                      /* Enable the External interrupt INTx */  
    
    }
    return ret ;
    
}

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_INTx_DeInit( const interrupt_INTx_t *int_obj ) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = Interrupt_INTx_Disable( int_obj ) ;
    }
    return ret ;
    
}

///////////////////
/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBx_Init( const interrupt_RBx_t *int_obj ) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = Interrupt_RBx_Disable( int_obj ) ;                          /* Disable the External interrupt RBx */
        ret |= Interrupt_RBx_ClearFlag( int_obj );                       /* Clear Interrupt RBx Flag  */ 
        ret |= Interrupt_RBx_PinInit( int_obj ) ;                         /* Configure External interrupt I/O pin */
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
        ret |= Interrupt_RBx_PriorityInit( int_obj );                   /* Configure External Interrupt RBx priority */
#endif
        ret |= Interrupt_RBx_SetHandler( int_obj );                  /* Configure Default Interrupt CallBack */
        PORTB_CAPTURE = PORTB ;
        ret |= Interrupt_RBx_Enable( int_obj ) ;                      /* Enable the External interrupt RBx */  
    
    }
    return ret ;
    
}


/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBx_DeInit( const interrupt_RBx_t *int_obj ) 
{
    std_ReturnType ret = E_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = EXT_RBx_InterruptDisable() ;
    }
    return ret ;
    
}


/////////////////////////// Helper Functions /////////////////////////////
/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_Enable( const interrupt_INTx_t *int_obj )
{
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        switch (int_obj->src )
        {
                case EXT_INTERRUPT_INT0 : 
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable();     
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
//                INTERRUPT_PeripheralInterruptEnable();
#endif
                    EXT_INT0_InterruptEnable();
                    ret =E_OK ;
                    break ;
                    
                case EXT_INTERRUPT_INT1 : 
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable(); 
                if (HIGH_PRIORITY == int_obj->priority)
                    INTERRUPT_GlobalInterruptHighEnable();
                else if (LOW_PRIORITY == int_obj->priority)
                    INTERRUPT_GlobalInterruptLowEnable();
                else { /* Nothing */ }
                    
#else
                INTERRUPT_GlobalInterruptEnable();
//                INTERRUPT_PeripheralInterruptEnable();
#endif
                    EXT_INT1_InterruptEnable();
                    ret =E_OK ;
                    break ;
                    
                case EXT_INTERRUPT_INT2 : 
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable(); 
                if (HIGH_PRIORITY == int_obj->priority)
                    INTERRUPT_GlobalInterruptHighEnable();
                else if (LOW_PRIORITY == int_obj->priority)
                    INTERRUPT_GlobalInterruptLowEnable();
                else { /* Nothing */ }
                    
#else
                INTERRUPT_GlobalInterruptEnable();
//                INTERRUPT_PeripheralInterruptEnable();
#endif
                    EXT_INT2_InterruptEnable();
                    ret =E_OK ;
                    break ;
            default : ret = E_NOT_OK ;
        }
        
    }
    return ret ;
    
}

/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_Disable( const interrupt_INTx_t *int_obj )
{
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        switch (int_obj->src )
        {
                case EXT_INTERRUPT_INT0 : 
                    EXT_INT0_InterruptDisable();
                    ret =E_OK ;
                    break ;
                case EXT_INTERRUPT_INT1 : 
                    EXT_INT1_InterruptDisable();
                    ret =E_OK ;
                    break ;
                case EXT_INTERRUPT_INT2 : 
                    EXT_INT2_InterruptDisable();
                    ret =E_OK ;
                    break ;
            default : ret = E_NOT_OK ;
        }
        
    }
    return ret ;
    
}

/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_ClearFlag( const interrupt_INTx_t *int_obj )
{
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        switch (int_obj->src )
        {
                case EXT_INTERRUPT_INT0 : 
                   EXT_INT0_ClearFlag();
                   ret =E_OK ;
                    break ;
                case EXT_INTERRUPT_INT1 : 
                    EXT_INT1_ClearFlag();
                    ret =E_OK ;
                    break ;
                case EXT_INTERRUPT_INT2 : 
                    EXT_INT2_ClearFlag();
                    ret =E_OK ;
                    break ;
            default : ret = E_NOT_OK ;
        }
    }
    return ret ;
    
}

/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_PinInit( const interrupt_INTx_t *int_obj )
{
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = gpio_pin_initialize( &int_obj->pin ) ;
    }
    return ret ;
    
}

/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_EdgeInit( const interrupt_INTx_t *int_obj )
{
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        switch (int_obj->src )
        {
                case EXT_INTERRUPT_INT0 : 
                {
                    if (FALLING_EDG == int_obj->edge )
                        EXT_INT0_FallingEdgeSet();
                    else if (RISING_EDG == int_obj->edge )
                        EXT_INT0_RisingEdgeSet() ;
                    else { /* Nothing */ } 
                   ret =E_OK ;
                    break ;
                }   
                case EXT_INTERRUPT_INT1 : 
                {
                    if (FALLING_EDG == int_obj->edge )
                        EXT_INT1_FallingEdgeSet();
                    else if (RISING_EDG == int_obj->edge )
                        EXT_INT1_RisingEdgeSet() ;
                    else { /* Nothing */ } 
                    ret =E_OK ;
                    break ;
                 }   
                case EXT_INTERRUPT_INT2 : 
                {
                    if (FALLING_EDG == int_obj->edge )
                        EXT_INT2_FallingEdgeSet();
                    else if (RISING_EDG == int_obj->edge )
                        EXT_INT2_RisingEdgeSet() ;
                    else { /* Nothing */ } 
                    ret =E_OK ;
                    break ;
                }   
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
    
}

/**
 * 
 * @param int_obj
 * @return 
 */
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
static std_ReturnType Interrupt_INTx_PriorityInit( const interrupt_INTx_t *int_obj )
{
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
         switch (int_obj->src )
        {
              
                case EXT_INTERRUPT_INT1 : 
                {
                    if (LOW_PRIORITY == int_obj->priority )
                        EXT_INT1_LowPrioritySet();
                    else if (HIGH_PRIORITY == int_obj->priority )
                        EXT_INT1_HighPrioritySet() ;
                    else { /* Nothing */ } 
                    ret =E_OK ;
                    break ;
                 }   
                case EXT_INTERRUPT_INT2 : 
                {
                    if (LOW_PRIORITY == int_obj->priority )
                        EXT_INT2_LowPrioritySet();
                    else if (HIGH_PRIORITY == int_obj->priority )
                        EXT_INT2_HighPrioritySet() ;
                    else { /* Nothing */ } 
                    ret =E_OK ;
                    break ;
                }   
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
    
}
#endif

/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_SetHandler( const interrupt_INTx_t *int_obj )
{
    std_ReturnType ret = E_NOT_OK ;
    if( NULL == int_obj  || NULL == int_obj->EXT_INTERRUPT_HANDLER )
    {
        ret = E_NOT_OK ;
    }
    else
    {
         switch (int_obj->src )
        {
                case EXT_INTERRUPT_INT0 : 
                {
                   INT0_INTERRUPT_HANDLER = int_obj->EXT_INTERRUPT_HANDLER ;
                   ret =E_OK ;
                    break ;
                }   
                case EXT_INTERRUPT_INT1 : 
                {
                   INT1_INTERRUPT_HANDLER = int_obj->EXT_INTERRUPT_HANDLER ;
                    ret =E_OK ;
                    break ;
                 }   
                case EXT_INTERRUPT_INT2 : 
                {
                   INT2_INTERRUPT_HANDLER = int_obj->EXT_INTERRUPT_HANDLER ;
                    ret =E_OK ;
                    break ;
                }   
                default : ret = E_NOT_OK ;
         }
   
    
    }
    return ret ;
    
}

///////////////////

 static std_ReturnType Interrupt_RBx_Enable ( const interrupt_RBx_t *int_obj ) 
 {
      std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {  
                
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable(); 
                if (HIGH_PRIORITY == int_obj->priority)
                    INTERRUPT_GlobalInterruptHighEnable();
                else if (LOW_PRIORITY == int_obj->priority)
                    INTERRUPT_GlobalInterruptLowEnable();
                else { /* Nothing */  }
#else
                INTERRUPT_GlobalInterruptEnable();
//                INTERRUPT_PeripheralInterruptEnable();
#endif
                    EXT_RBx_InterruptEnable();
                    ret =E_OK ;
                
    }
    return ret ;
   
 }
 static std_ReturnType Interrupt_RBx_Disable ( const interrupt_RBx_t *int_obj ) 
  {
      std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {  
        ret = EXT_RBx_InterruptDisable() ;
    }
    return ret ;
   
 }
 
 static std_ReturnType Interrupt_RBx_ClearFlag ( const interrupt_RBx_t *int_obj ) 
 {
      std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {  
        ret = EXT_RBx_ClearFlag() ;
    }
    return ret ;
   
 }
 
 
 static std_ReturnType Interrupt_RBx_PinInit ( const interrupt_RBx_t *int_obj ) 
  {
      std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {  
        ret = gpio_pin_direction_initialize(& int_obj->pin) ;
    }
    return ret ;
   
 }
 static std_ReturnType Interrupt_RBx_SetHandler ( const interrupt_RBx_t *int_obj ) 
{
    std_ReturnType ret = E_NOT_OK ;
    if( NULL == int_obj  || NULL == int_obj->EXT_INTERRUPT_HANDLER_HIGH || NULL == int_obj->EXT_INTERRUPT_HANDLER_LOW )
    {
        ret = E_NOT_OK ;
    }
    else
    {
         switch (int_obj->pin.pin )
        {
                case PIN4 : 
                {
                   RB4_INTERRUPT_HANDLER_HIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH ;
                   RB4_INTERRUPT_HANDLER_LOW = int_obj->EXT_INTERRUPT_HANDLER_LOW ;
                   ret =E_OK ;
                    break ;
                }   
                case PIN5 : 
                {
                   RB5_INTERRUPT_HANDLER_HIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH ;
                   RB5_INTERRUPT_HANDLER_LOW = int_obj->EXT_INTERRUPT_HANDLER_LOW ;
                    ret =E_OK ;
                    break ;
                 }   
                case PIN6 : 
                {
                   RB6_INTERRUPT_HANDLER_HIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH ;
                   RB6_INTERRUPT_HANDLER_LOW = int_obj->EXT_INTERRUPT_HANDLER_LOW ;
                    ret =E_OK ;
                    break ;
                }   
                case PIN7 : 
                {
                   RB7_INTERRUPT_HANDLER_HIGH = int_obj->EXT_INTERRUPT_HANDLER_HIGH ;
                   RB7_INTERRUPT_HANDLER_LOW = int_obj->EXT_INTERRUPT_HANDLER_LOW ;
                    ret =E_OK ;
                    break ;
                }   
                default : ret = E_NOT_OK ;
         }
   
    
    }
    return ret ;
    
}
 
#ifdef INTERRUPT_PRIORITY_LEVELS_FEATURE_ENABLE
 static std_ReturnType Interrupt_RBx_PriorityInit ( const interrupt_RBx_t *int_obj )  
 {
    std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        if (HIGH_PRIORITY == int_obj ->priority )
        { EXT_RBx_HighPrioritySet();  }
       
        else if (HIGH_PRIORITY == int_obj ->priority )
        { EXT_RBx_LowPrioritySet();  }
        
        else { /* Nothing */  }
    }
    return ret ;
    
}
#endif

 
////////////////////////////////////////////////////////////////////  called from manager
 void INT0_ISR(void)
{
     
#ifdef INTERRUPT_EXTERNAL_INTx_FEATURE_ENABLE    
     EXT_INT0_ClearFlag();
    /* Code : To be executed from MCAL Interrupt Context */
    if (INT0_INTERRUPT_HANDLER)
        INT0_INTERRUPT_HANDLER();
    
    else { /* Nothing */  }
#endif
 
 }

 void INT1_ISR(void)
{
#ifdef INTERRUPT_EXTERNAL_INTx_FEATURE_ENABLE     
    EXT_INT1_ClearFlag();
    /* Code : To be executed from MCAL Interrupt Context */
    if (INT1_INTERRUPT_HANDLER) 
        INT1_INTERRUPT_HANDLER();
    
    else { /* Nothing */  }
#endif
    
}

 void INT2_ISR(void)
{
#ifdef INTERRUPT_EXTERNAL_INTx_FEATURE_ENABLE    
     EXT_INT2_ClearFlag();
    /* Code : To be executed from MCAL Interrupt Context */
    if (INT2_INTERRUPT_HANDLER) 
        INT2_INTERRUPT_HANDLER();
    
    else { /* Nothing */  }
#endif
     
}

 /////////////////////////
 

 void RBx_ISR(void)
{

#ifdef INTERRUPT_EXTERNAL_IOC_FEATURE_ENABLE

     if ( ( (PORTB_CAPTURE>>4) & 0x01) != ( (PORTB>>4) & 0x01)  )
     {
         RB4_ISR();
     }
     else if ( ( (PORTB_CAPTURE>>5) & 0x01) != ( (PORTB>>5) & 0x01)  )
     {
         RB5_ISR();
     }
     else if ( ( (PORTB_CAPTURE>>6) & 0x01) != ( (PORTB>>6) & 0x01)  )
     {
         RB6_ISR();
     }
     else if ( ( (PORTB_CAPTURE>>7) & 0x01) != ( (PORTB>>7) & 0x01)  )
     {
         RB7_ISR();
     }
     else { /* Nothing */ }
     
#endif
     
}
 
#ifdef INTERRUPT_EXTERNAL_IOC_FEATURE_ENABLE

 void RB4_ISR(void)
{
    EXT_RBx_ClearFlag();
    PORTB_CAPTURE = PORTB ;
    /* Code : To be executed from MCAL Interrupt Context */
    if (PORTBbits.RB4 == 1)
    {
            if (RB4_INTERRUPT_HANDLER_HIGH) 
            RB4_INTERRUPT_HANDLER_HIGH();
            else { /* Nothing */  }
    }
    else if (PORTBbits.RB4 == 0)
    {
            if (RB4_INTERRUPT_HANDLER_LOW) 
            RB4_INTERRUPT_HANDLER_LOW();
            else { /* Nothing */  }
    }
    else { /*Nothing */ }
    
}

 void RB5_ISR(void)
{
    EXT_RBx_ClearFlag();
    PORTB_CAPTURE = PORTB ;
    /* Code : To be executed from MCAL Interrupt Context */
    if (PORTBbits.RB5 == 1)
    {
            if (RB5_INTERRUPT_HANDLER_HIGH) 
            RB5_INTERRUPT_HANDLER_HIGH();
            else { /* Nothing */  }
    }
    else if (PORTBbits.RB5 == 0)
    {
            if (RB5_INTERRUPT_HANDLER_LOW) 
            RB5_INTERRUPT_HANDLER_LOW();
            else { /* Nothing */  }
    }
    else { /*Nothing */ }
    
}

 void RB6_ISR(void)
{
    EXT_RBx_ClearFlag();
    PORTB_CAPTURE = PORTB ;
    /* Code : To be executed from MCAL Interrupt Context */
    if (PORTBbits.RB6 == 1)
    {
            if (RB6_INTERRUPT_HANDLER_HIGH) 
            RB6_INTERRUPT_HANDLER_HIGH();
            else { /* Nothing */  }
    }
    else if (PORTBbits.RB6 == 0)
    {
            if (RB6_INTERRUPT_HANDLER_LOW) 
            RB6_INTERRUPT_HANDLER_LOW();
            else { /* Nothing */  }
    }
    else { /*Nothing */ }
    
}

 void RB7_ISR(void)
{
    EXT_RBx_ClearFlag();
    PORTB_CAPTURE = PORTB ;
    /* Code : To be executed from MCAL Interrupt Context */
    if (PORTBbits.RB7 == 1)
    {
            if (RB7_INTERRUPT_HANDLER_HIGH) 
            RB7_INTERRUPT_HANDLER_HIGH();
            else { /* Nothing */  }
    }
    else if (PORTBbits.RB7 == 0)
    {
            if (RB7_INTERRUPT_HANDLER_LOW) 
            RB7_INTERRUPT_HANDLER_LOW();
            else { /* Nothing */  }
    }
    else { /*Nothing */ }
    
}
 
#endif