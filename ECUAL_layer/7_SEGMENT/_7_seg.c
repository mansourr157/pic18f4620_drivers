/* 
 * File:   _7_seg.c
 * Author: Mansour
 *
 * Created on October 23, 2023, 4:28 AM
 */

#include "_7_seg.h"

extern uint8 seg_common_anode[10]   = { 0xc0 , 0xf9 , 0xa4 , 0xb0 , 0x99 , 0x92 , 0x82 , 0xf8 , 0x80 , 0x90  } ;
extern uint8 seg_common_cathode[10] = { 0x3f , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x07 , 0x7f , 0x6f  } ;

/**
 * 
 * @param seg
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType seven_segment_initialize ( segment_t *seg)
{
    
    std_ReturnType ret = E_OK ;
    if( NULL == seg )
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
        seg->segment_pins[0].direction = OUTPUT ;
        seg->segment_pins[1].direction = OUTPUT ;
        seg->segment_pins[2].direction = OUTPUT ;
        seg->segment_pins[3].direction = OUTPUT ;
        seg->segment_pins[0].logic = LOW ;
        seg->segment_pins[1].logic = LOW ;
        seg->segment_pins[2].logic = LOW ;
        seg->segment_pins[3].logic = LOW ;
        
        ret   = gpio_pin_initialize( &(seg ->segment_pins[SEGMENT_PIN0]) );
        ret |= gpio_pin_initialize( &(seg ->segment_pins[SEGMENT_PIN1]) );
        ret |= gpio_pin_initialize( &(seg ->segment_pins[SEGMENT_PIN2]) );
        ret |= gpio_pin_initialize( &(seg ->segment_pins[SEGMENT_PIN3]) );
    }
    return ret ;
}


/**
 * 
 * @param seg
 * @param number
 * @return status of function
 *                  (E_OK) : function done successfully
 *                  (E_NOT_OK) : function has an issue
 */
std_ReturnType seven_segment_write_number ( segment_t *seg , uint8 number )
{
    
    std_ReturnType ret = E_OK ;
    if( NULL == seg || number > 9)
    {
        ret = E_NOT_OK ;
    }
    
    else 
    {
       ret   = gpio_pin_write_logic(&seg->segment_pins[0] , (number&0b0001));
       ret |= gpio_pin_write_logic(&seg->segment_pins[1] , (number&0b0010) >>1);
       ret |= gpio_pin_write_logic(&seg->segment_pins[2] , (number&0b0100) >>2);
       ret |= gpio_pin_write_logic(&seg->segment_pins[3] , (number&0b1000) >>3);

       
    }
    return ret ;
}