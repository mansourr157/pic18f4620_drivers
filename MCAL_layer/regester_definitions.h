/* 
 * File:   regester_definitions.h
 * Author: Mansour
 *
 * Created on October 8, 2023, 10:20 PM
 */

#ifndef REGESTER_DEFINITIONS_H
#define	REGESTER_DEFINITIONS_H


// PORT ADDRESSES
#define PORTA_ADD 0x05
#define PORTB_ADD 0x06
#define PORTC_ADD 0x07
#define PORTD_ADD 0x08
#define PORTE_ADD 0x09

// TRIS ADDRESSES
#define TRISA_ADD 0x85
#define TRISB_ADD 0x86
#define TRISC_ADD 0x87
#define TRISD_ADD 0x88
#define TRISE_ADD 0x89

// MACRO 
//#define HWREG8(_x)  (*(volatile uint8*)(_x))

// PORTS DEFINITIONS
#define myPORTA HWREG8(PORTA_ADD)
#define myPORTB HWREG8(PORTB_ADD)
#define myPORTC HWREG8(PORTC_ADD)
#define myPORTD HWREG8(PORTD_ADD)
#define myPORTE HWREG8(PORTE_ADD)

// TRIS DEFINITIONS
#define myTRISA HWREG8(TRISA_ADD)
#define myTRISB HWREG8(TRISB_ADD)
#define myTRISC HWREG8(TRISC_ADD)
#define myTRISD HWREG8(TRISD_ADD)
#define myTRISE HWREG8(TRISE_ADD)



//bitfield defintions 

typedef union
{

    struct
    {
        unsigned PORTA0 : 1;
        unsigned PORTA1 : 1;
        unsigned PORTA2 : 1;
        unsigned PORTA3 : 1;
        unsigned PORTA4 : 1;
        unsigned PORTA5 : 1;

    
    };
    
    uint8 All_PORTA;

}my_PORTA;

#define SELF_PORTA (*(volatile my_PORTA*)(0x05))
#define D_SELF_PORTA ((volatile my_PORTA*)(0x05))

// option_reg

typedef union {

    struct 
    {
        uint8 option_regx :3 ;
        uint8 option_reg3 :1 ;
        uint8 option_reg4 :1 ;
        uint8 option_reg5 :1 ;
        uint8 option_reg6 :1 ;
        uint8 option_reg7 :1 ;
    };
    
    uint8 all_option_reg ;

}self_option_reg;

#define SELF_OPTION_REG (*(self_option_reg*)(0x81))

#endif	/* REGESTER_DEFINITIONS_H */

