/* 
 * File:   hal_eeprom.c
 * Author: Mansour
 *
 * Created on December 6, 2023, 12:30 AM
 */

#include "hal_eeprom.h"


std_ReturnType EEPROM_WriteByte( uint16 dAdd , uint8 data ) 
{
   std_ReturnType ret = E_OK ; 
   
   /* write the address of data */
   EEADRH = (uint8)( (dAdd >> 8) & 0x03 )  ;      
   EEADR = (uint8)( dAdd & 0xff )  ;
   /* write the data */
   EEDATA = data ;
   /* Flash Program or Data EEPROM Memory Select bit */
   EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY ;
   /* Flash Program/Data EEPROM or Configuration Select bit */
   EECON1bits.CFGS = ACCESS_FLASH_OR_EEPROM_MEMORY ;
   /* Data EEPROM Write Enable  */
   EECON1bits.WREN = ALLOW_WRITE_CYCLES_TO_FLASH_OR_EEPROM ;
   /* save the status of interrupts */
   uint8 interrupt_status = INTCONbits.GIE ;
   uint8 low_interrupt_status = INTCONbits.GIEL ;
   /* Disable Interrupts */
   INTCONbits.GIE = 0 ;
   INTCONbits.GIEL = 0 ;
   /* write sequence in EECON2 0x55 THEN 0x0AA */
   EECON2 = 0x55 ;
   EECON2 = 0xAA ;
   /* initializing the erase/write cycle */
   EECON1bits.WR = INITIATE_THE_ERASE_WRITE_CYCLE ; 
   /* wait for write to complete */      ////////////////////////////////// using  interrupt ??
   while ( EECON1bits.WR );
   /* Data EEPROM Write Disable */
   EECON1bits.WREN = INHIBITS_WRITE_CYCLES_TO_FLASH_OR_EEPROM ;
   /* return the status of interrupts */
   INTCONbits.GIE = interrupt_status ;
   INTCONbits.GIEL = low_interrupt_status ;
   
   
   
   return ret ;
}


std_ReturnType EEPROM_ReadByte( uint16 dAdd , uint8 *data ) 
{
   std_ReturnType ret = E_NOT_OK ; 
   if ( NULL == data ) 
   {
       ret = E_NOT_OK ;
   }
   else 
   {
       
   /* write the address of data */
   EEADRH = (uint8)( (dAdd >> 8) & 0x03 )  ;      
   EEADR = (uint8)( dAdd & 0xff )  ;
   /* Flash Program or Data EEPROM Memory Select bit */
   EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY ;
   /* Flash Program/Data EEPROM or Configuration Select bit */
   EECON1bits.CFGS = ACCESS_FLASH_OR_EEPROM_MEMORY ;
   /* initializing the Read cycle */
   EECON1bits.RD = INITIATE_THE_READ_CYCLE ; 
   /* NOP is required for reading latency at high frequencies  */
   NOP();
   NOP();
   /* RETURN THE DATA */
   *data = EEDATA ;
   
   ret = E_OK ;
   
   }

   return ret ;
}

