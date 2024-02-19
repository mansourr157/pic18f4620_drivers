/* 
 * File:   ecu_keypad.h
 * Author: Mansour
 *
 * Created on October 27, 2023, 8:32 PM
 */

#include "ecu_keypad.h"

static const uint8 btns[KEYPAD_ROWS][KEYPAD_COLUMNS] = {   { '7'  ,  '8'  ,  '9'  ,  '/' } ,
                                                                                                 { '4'  ,  '5'  ,  '6'  ,  '*' } ,
                                                                                                 { '1'  ,  '2'  ,  '3'  ,  '-' } ,
                                                                                                 { '#'  ,  '0'  ,  '='  ,  '+' }    } ;


/**
 * 
 * @param keypad
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType keypad_initialize ( keypad_t *keypad)
{
    std_ReturnType ret =E_OK ;
    if(NULL == keypad)
    {
        ret = E_NOT_OK ;
    }
    else
    {   
        for (uint8 i =0 ; i<KEYPAD_ROWS ; i++)
        {
            keypad->keypad_rows[i].direction = OUTPUT ;
            keypad->keypad_rows[i].logic = LOW ;
        }
        
        for (uint8 i =0 ; i<KEYPAD_COLUMNS ; i++)
        {
            keypad->keypad_columns[i].direction = INPUT ;
        }
        
        
        for(uint8 c =0 ; c<KEYPAD_ROWS ; c++)
        {
            ret   = gpio_pin_initialize( &keypad->keypad_rows[c] );
        }

        
        for(uint8 c =0 ; c<KEYPAD_COLUMNS ; c++)
        {
            ret |= gpio_pin_direction_initialize( &keypad->keypad_columns[c] );
        }

        
    } 
        return ret ;
}

/**
 * 
 * @param keypad
 * @param button
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType keypad_return_button ( keypad_t *keypad , uint8 *button)
{
    std_ReturnType ret =E_OK ;
    if(NULL == keypad || NULL == button )
    {
        ret = E_NOT_OK ;
    }
    else
    {   
        uint8 col_logic = LOW ;
        
        for (uint8 rows_counter = 0 ; rows_counter < KEYPAD_ROWS ; rows_counter++)                     // loop on rows
        {
            for(uint8 z = 0 ; z<KEYPAD_ROWS ; z++)            // make all rows logic = 0
            {
                ret |= gpio_pin_write_logic( &( keypad->keypad_rows[z] ) , LOW) ;
            }
             ret |= gpio_pin_write_logic( &keypad->keypad_rows[rows_counter] , HIGH) ; 
             
             for(uint8 columns_counter=0 ; columns_counter<KEYPAD_COLUMNS ; columns_counter++)        // loop on columns logic
             {
                  ret |= gpio_pin_read_logic( &keypad->keypad_columns[columns_counter] , &col_logic);
                  if (col_logic == HIGH)
                        {
                            *button = btns[rows_counter][columns_counter] ;
                        }
             }
             
        }
        
        
    } 
        return ret ;
}


        
