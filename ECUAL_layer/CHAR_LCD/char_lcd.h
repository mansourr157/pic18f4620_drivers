/* 
 * File:   char_lcd.h
 * Author: Mansour
 *
 * Created on October 31, 2023, 1:21 AM
 */

#ifndef CHAR_LCD_H
#define	CHAR_LCD_H


/*   section: Includes  */

#include "char_lcd_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*   section: Macros  */

// commands

#define _LCD_CLEAR                                   0x01         // clear lcd (DDRAM) and return cursor home
#define _LCD_RETURN_HOME                     0x02         // return cursor home without  clear lcd (DDRAM) 
#define _LCD_DISPLAY_OFF                        0x08         // hiding the all data of lcd without deleting or moving cursor
#define _LCD_DISPLAY_ON                          0x0c         // show the all data of lcd without deleting or moving cursor

#define _LCD_BLOCK_CURSOR_ON             0x0d
#define _LCD_UNDERLINED_CURSOR_ON   0x0e
#define _LCD_BOTH_CURSORS_ON             0x0f

#define _LCD_CURSOR_INC                    0x06          // increment cursor      (it increments after any character written)  @entry mode set
#define _LCD_CURSOR_DEC                   0x04        // decrement cursor       (it decrements after any character written)  @entry mode set

#define _LCD_CURSOR_SHIFT_RIGHT       0x14      // move the cursor to right (just one time) @cursor or display shift
#define _LCD_CURSOR_SHIFT_LEFT         0x10     // move the cursor to left   (just one time)  @cursor or display shift
#define _LCD_DISPLAY_SHIFT_RIGHT     0x1c        // move the whole display to right (including the cursor)  (just one time)  @cursor or display shift
#define _LCD_DISPLAY_SHIFT_LEFT        0x18       // move the whole display to left (including the cursor)      (just one time) @cursor or display shift

/*
#define _LCD_DISPLAY_SHIFT_LEFT_CURSOR_STAYS       0x07          // the display shifts left and the cursor stays in its position to write the new char  @entry mode set
#define _LCD_DISPLAY_SHIFT_RIGHT_CURSOR_STAYS     0x05         // the display shifts right and the cursor stays in its position to write the new char  @entry mode set
*/

#define _LCD_8BIT                                0x38            // 8bit mode 2lines lcd 5*8 dot matrix char @ref function set
#define _LCD_4BIT                                0x28            // 4bit mode 2lines lcd 5*8 dot matrix char @ref function set

#define _LCD_CGRAM_START                0x40            // the start address of CGRAM it is 0x00 but the last 2bits  bit6: 1 , bit7:1 @set CGRAM address
#define _LCD_DDRAM_START                0x80            // the start address of DDRAM it is 0x00 but the last bit bit7:1 @set DDRAM address


/*   section: Macro Functions declarations */


/*   section: Data Types declarations */

typedef struct {
    pin_config_t RS ;
    pin_config_t E ;
    pin_config_t data[4] ;
    
}char_lcd_4b_t;

typedef struct {
    pin_config_t RS ;
    pin_config_t E ;
    pin_config_t data[8] ;
    
}char_lcd_8b_t;

/*   section: Function declarations  */

std_ReturnType lcd_4b_initialize ( const char_lcd_4b_t *lcd ) ;
std_ReturnType lcd_4b_send_command ( const char_lcd_4b_t *lcd , uint8 command) ;
std_ReturnType lcd_4b_send_char ( const char_lcd_4b_t *lcd , uint8 data ) ;
std_ReturnType lcd_4b_set_cursor ( const char_lcd_4b_t *lcd , uint8 row , uint8 column  ) ;
std_ReturnType lcd_4b_send_char_pos ( const char_lcd_4b_t *lcd , uint8 row , uint8 column , uint8 data ) ;
std_ReturnType lcd_4b_send_string ( const char_lcd_4b_t *lcd , uint8 *str ) ;
std_ReturnType lcd_4b_send_string_pos ( const char_lcd_4b_t *lcd , uint8 row , uint8 column , uint8 *str ) ;
std_ReturnType lcd_4b_send_custom_char ( const char_lcd_4b_t *lcd , uint8 row , uint8 column ,
                                                              const uint8 *_char , uint8 mem_pos ) ;
std_ReturnType lcd_4b_string_shift_right_and_left (const char_lcd_4b_t *lcd , uint8 row , uint8 column , uint8 *str , uint8 str_length , uint8 steps ) ;

std_ReturnType lcd_8b_initialize ( const char_lcd_8b_t *lcd ) ;
std_ReturnType lcd_8b_send_command ( const char_lcd_8b_t *lcd , uint8 command) ;
std_ReturnType lcd_8b_send_char ( const char_lcd_8b_t *lcd , uint8 data ) ;
std_ReturnType lcd_8b_set_cursor ( const char_lcd_8b_t *lcd , uint8 row , uint8 column  ) ;
std_ReturnType lcd_8b_send_char_pos ( const char_lcd_8b_t *lcd , uint8 row , uint8 column , uint8 data ) ;
std_ReturnType lcd_8b_send_string ( const char_lcd_8b_t *lcd , uint8 *str ) ;
std_ReturnType lcd_8b_send_string_pos ( const char_lcd_8b_t *lcd , uint8 row , uint8 column , uint8 *str ) ;
std_ReturnType lcd_8b_send_custom_char ( const char_lcd_8b_t *lcd , uint8 row , uint8 column ,
                                                                  const uint8 *_char , uint8 mem_pos ) ;

std_ReturnType convert_byte_to_str (uint8 value , uint8 *str);
std_ReturnType convert_short_to_str (uint16 value , uint8 *str);
std_ReturnType convert_int_to_str (uint32 value , uint8 *str);

#endif	/* CHAR_LCD_H */




