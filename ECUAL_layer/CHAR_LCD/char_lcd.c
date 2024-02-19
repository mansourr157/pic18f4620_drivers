/* 
 * File:   char_lcd.c
 * Author: Mansour
 *
 * Created on October 31, 2023, 1:21 AM
 */

#include "char_lcd.h"

static std_ReturnType fire_enable_4b (const char_lcd_4b_t *lcd) ;
static std_ReturnType send_4b (const char_lcd_4b_t *lcd , uint8 _4b) ;
static std_ReturnType fire_enable_8b (const char_lcd_8b_t *lcd) ;
static std_ReturnType send_8b (const char_lcd_8b_t *lcd , uint8 _8b) ;

std_ReturnType lcd_4b_initialize ( const char_lcd_4b_t *lcd ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = gpio_pin_initialize(&lcd->E);
        ret |= gpio_pin_initialize(&lcd->RS);
        for (uint8 i=0 ; i<4 ; i++)
        {
            ret |= gpio_pin_initialize(&lcd->data[i]);
        }

        __delay_ms(20);
        ret |= lcd_4b_send_command( lcd , _LCD_8BIT ) ;
        __delay_ms(5);
        ret |= lcd_4b_send_command( lcd , _LCD_8BIT ) ;
        __delay_us(120);
        ret |= lcd_4b_send_command( lcd , _LCD_8BIT ) ;
        
        ret |= lcd_4b_send_command( lcd , _LCD_CLEAR ) ;
        ret |= lcd_4b_send_command( lcd , _LCD_RETURN_HOME ) ;
        ret |= lcd_4b_send_command( lcd , _LCD_CURSOR_INC ) ;
        ret |= lcd_4b_send_command( lcd , _LCD_DISPLAY_ON ) ;
        ret |= lcd_4b_send_command( lcd , _LCD_4BIT ) ;
        
    }
    return ret ;
}

std_ReturnType lcd_4b_send_command ( const char_lcd_4b_t *lcd , uint8 command) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {   
        //  CONNECT RW to gnd
        // SET RS to LOW
        ret = gpio_pin_write_logic( &lcd->RS , LOW) ;
        // SEND the command higher 4b
        ret |= send_4b ( lcd , command>>4 ) ;
        // FIRE ENABLE
        ret |= fire_enable_4b(lcd) ;
        // SEND the command lower 4b
        ret |= send_4b ( lcd , command ) ;
        // FIRE ENABLE
        ret |= fire_enable_4b(lcd) ;
    
    }
    return ret ;
}

std_ReturnType lcd_4b_send_char ( const char_lcd_4b_t *lcd , uint8 data ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {   
        //  CONNECT RW to gnd
        // SET RS to HIGH
        ret = gpio_pin_write_logic( &lcd->RS , HIGH) ;
        // SEND the command higher 4b
        ret |= send_4b ( lcd , data>>4 ) ;
        // FIRE ENABLE
        ret |= fire_enable_4b(lcd) ;
        // SEND the command lower 4b
        ret |= send_4b ( lcd , data ) ;
        // FIRE ENABLE
        ret |= fire_enable_4b(lcd) ;
    
    }
    return ret ;
}
 
std_ReturnType lcd_4b_set_cursor ( const char_lcd_4b_t *lcd , uint8 row , uint8 column  ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        column -- ;
        switch (row)    
        {
                case 1 :    ret   = lcd_4b_send_command( lcd , ( 0x80 + column )  ) ;       break;
                case 2 :    ret |= lcd_4b_send_command( lcd , ( 0xc0 + column )  ) ;       break;
                case 3 :    ret |= lcd_4b_send_command( lcd , ( 0x94 + column )  ) ;       break;
                case 4 :    ret |= lcd_4b_send_command( lcd , ( 0xd4 + column )  ) ;       break;
        }
    }
    return ret ;
}

std_ReturnType lcd_4b_send_char_pos ( const char_lcd_4b_t *lcd , uint8 row , uint8 column , uint8 data ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = lcd_4b_set_cursor( lcd , row , column) ;
        ret |= lcd_4b_send_char( lcd , data) ;
    }
    return ret ;
}
 
std_ReturnType lcd_4b_send_string ( const char_lcd_4b_t *lcd , uint8 *str ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        while (*str)
        {
            ret = lcd_4b_send_char(lcd , *str++) ;
        }
    }
    return ret ;
}
 
std_ReturnType lcd_4b_send_string_pos ( const char_lcd_4b_t *lcd , uint8 row , uint8 column , uint8 *str ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = lcd_4b_set_cursor( lcd , row , column ) ;
        ret |= lcd_4b_send_string( lcd , str) ;
    }
    return ret ;
}
 
std_ReturnType lcd_4b_send_custom_char ( const char_lcd_4b_t *lcd , uint8 row , uint8 column ,
                                                                 const uint8 *_char , uint8 mem_pos ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        
        // access the CGRAM position address    (we have 8 positions   64 bytes)
        ret = lcd_4b_send_command(lcd , _LCD_CGRAM_START + (mem_pos*8)  );  
        // fill the CGRAM with the pattern of custom char
        for(uint8 i=0 ; i<8 ; i++ )
        {
            ret |= lcd_4b_send_char ( lcd , _char[i] ) ;
        }
     
        // send this position to the lcd 
        ret |= lcd_4b_send_char_pos(  lcd , row , column , mem_pos  ) ;
        
    }
    
    return ret ;
}
 
/**
 * 
 * @param lcd                   // 4b
 * @param row   
 * @param column
 * @param str
 * @param str_length
 * @param steps                // it must be less than the  ( lcd coulums (20)  -  str_length )     if u enter 0 it will go till the end
 * @return  ret
 */
std_ReturnType lcd_4b_string_shift_right_and_left (const char_lcd_4b_t *lcd , uint8 row , uint8 column , uint8 *str , uint8 str_length , uint8 steps )
{
    
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    
    else
    {
        if ( (steps + str_length) > 20)
        {
            // do nothing
        }
        else if (steps == 0)
        {
                for (uint8 i=column ; i<=(20-str_length) ; i++ )
                {
                    ret |= lcd_4b_send_string_pos(lcd , row , i ,  str );
                    __delay_ms(250);
                    ret |= lcd_4b_send_char_pos(lcd , row , i , ' ' );

                }

            for (uint8 i=(column+(20-str_length)) ; i>=column ; i-- )
                {
                    ret |= lcd_4b_send_string_pos(lcd , row , i , str );
                    __delay_ms(250);
                    ret |= lcd_4b_send_char_pos(lcd , row , i+str_length-1  , ' ' );

                }
        }
        else
        {
                for (uint8 i=column ; i<=steps ; i++ )
                {
                    ret |= lcd_4b_send_string_pos(lcd , row , i ,  str );
                    __delay_ms(250);
                    ret |= lcd_4b_send_char_pos(lcd , row , i , ' ' );

                }

            for (uint8 i=(column+steps) ; i>=column ; i-- )
                {
                    ret |= lcd_4b_send_string_pos(lcd , row , i , str );
                    __delay_ms(250);
                    ret |= lcd_4b_send_char_pos(lcd , row , i+str_length-1  , ' ' );

                }
        }
         
    
    }
    return ret ;
    
}


///////////////////////////////////////////////////////////////////////////

std_ReturnType lcd_8b_initialize ( const char_lcd_8b_t *lcd ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = gpio_pin_initialize( &lcd->E );
        ret |= gpio_pin_initialize( &lcd->RS );
        
        for (uint8 i =0 ; i<8 ; i++)
        {
            ret |= gpio_pin_initialize( &lcd->data[i] );
        }
        
        __delay_ms(20);
        ret |= lcd_8b_send_command( lcd , _LCD_8BIT ) ;
        __delay_ms(5);
        ret |= lcd_8b_send_command( lcd , _LCD_8BIT ) ;
        __delay_us(120);
        ret |= lcd_8b_send_command( lcd , _LCD_8BIT ) ;
        
        ret |= lcd_8b_send_command( lcd , _LCD_DISPLAY_ON ) ;
        ret |= lcd_8b_send_command( lcd , _LCD_CLEAR ) ;
        ret |= lcd_8b_send_command( lcd , _LCD_RETURN_HOME ) ;
        ret |= lcd_8b_send_command( lcd , _LCD_CURSOR_INC ) ;

        
    }
    return ret ;
}
 
std_ReturnType lcd_8b_send_command ( const char_lcd_8b_t *lcd , uint8 command) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {   
        //  CONNECT RW to gnd
        // SET RS to LOW
        ret = gpio_pin_write_logic( &lcd->RS , LOW) ;
        // SEND the command
        ret |= send_8b( lcd , command ) ;
        // FIRE ENABLE
        ret |= fire_enable_8b (lcd) ;
    }
    return ret ;
}
 
std_ReturnType lcd_8b_send_char ( const char_lcd_8b_t *lcd , uint8 data ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {   
        //  CONNECT RW to gnd
        // SET RS to LOW
        ret = gpio_pin_write_logic( &lcd->RS , HIGH) ;
        // SEND the command
        ret |= send_8b( lcd , data ) ;
        // FIRE ENABLE
        ret |= fire_enable_8b (lcd) ;
    }
    return ret ;
}
 
std_ReturnType lcd_8b_set_cursor ( const char_lcd_8b_t *lcd , uint8 row , uint8 column  ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        column -- ;
        switch (row)    
        {
                case 1 :    ret   = lcd_8b_send_command( lcd , ( 0x80 + column )  ) ;       break;
                case 2 :    ret |= lcd_8b_send_command( lcd , ( 0xc0 + column )  ) ;       break;
                case 3 :    ret |= lcd_8b_send_command( lcd , ( 0x94 + column )  ) ;       break;
                case 4 :    ret |= lcd_8b_send_command( lcd , ( 0xd4 + column )  ) ;       break;
        }
    }
    return ret ;
}

std_ReturnType lcd_8b_send_char_pos ( const char_lcd_8b_t *lcd , uint8 row , uint8 column , uint8 data ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = lcd_8b_set_cursor(lcd , row , column );
        ret |= lcd_8b_send_char(lcd , data);
    }
    return ret ;
}
 
std_ReturnType lcd_8b_send_string ( const char_lcd_8b_t *lcd , uint8 *str ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        while (*str) 
        {
            ret = lcd_8b_send_char(lcd , *str++);
        }
    }
    return ret ;
}
 
std_ReturnType lcd_8b_send_string_pos ( const char_lcd_8b_t *lcd , uint8 row , uint8 column , uint8 *str ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret   = lcd_8b_set_cursor(lcd , row ,column) ;
        ret |= lcd_8b_send_string(lcd , str) ;
    }
    return ret ;
}
 
std_ReturnType lcd_8b_send_custom_char ( const char_lcd_8b_t *lcd , uint8 row , uint8 column ,
                                                                  const uint8 *_char , uint8 mem_pos ) 
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        
        // access the CGRAM position address    (we have 8 positions   64 bytes)
        ret = lcd_8b_send_command(lcd , _LCD_CGRAM_START + (mem_pos*8)  );  
        // fill the CGRAM with the pattern of custom char
        for(uint8 i=0 ; i<8 ; i++ )
        {
            ret |= lcd_8b_send_char ( lcd , _char[i] ) ;
        }
     
        // send this position to the lcd 
        ret |= lcd_8b_send_char_pos(  lcd , row , column , mem_pos  ) ;
        
    }
    return ret ;
}
 
////////////////////////////////////////////


std_ReturnType convert_byte_to_str (uint8 value , uint8 *str )
{
    std_ReturnType ret =E_OK ;
    if(NULL == str)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        memset ( str , '\0' , 4 ) ;
        sprintf( str , "%i" , value  ) ;
    }
    return ret ;
}

std_ReturnType convert_short_to_str (uint16 value , uint8 *str)
{
    std_ReturnType ret =E_OK ;
    if(NULL == str)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        uint8 counter = 0 ;
        uint8 temp_str[6] ; 
        memset ( str , ' ' , 5  ) ;
        str[5] = '\0' ;
        sprintf( temp_str , "%i" , value  ) ;       // converts the number into string and then complete the array with null terminations
        while (temp_str[counter] )
        {
            str[counter] = temp_str[counter] ;   //       365\0\0\0   ->   365__\0   
            counter ++ ;
        }
    }
    return ret ;
}

std_ReturnType convert_int_to_str (uint32 value , uint8 *str)
{
    std_ReturnType ret =E_OK ;
    if(NULL == str)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        memset ( str , '\0' , 11 ) ;
        sprintf( str , "%i" , value  ) ;
    }
    return ret ;
}
 


    //////////////////////////  STATIC FUNCTIONS   ////////////////////

static std_ReturnType fire_enable_4b (const char_lcd_4b_t *lcd)
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = gpio_pin_write_logic( &lcd->E , HIGH) ;
        __delay_us(5) ;
        ret |= gpio_pin_write_logic( &lcd->E , LOW) ;
    }
    return ret ;
}

static std_ReturnType send_4b (const char_lcd_4b_t *lcd , uint8 _4b)
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        for(uint8 i=0 ;i<4 ; i++)
        {
            ret = gpio_pin_write_logic( &lcd->data[i] , (_4b >> i) & 0x01 ) ;
        }
    }
    return ret ;
}

static std_ReturnType fire_enable_8b (const char_lcd_8b_t *lcd)
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        ret = gpio_pin_write_logic( &lcd->E , HIGH) ;
        __delay_us(5) ;
        ret |= gpio_pin_write_logic( &lcd->E , LOW) ;
    }
    return ret ;
}

static std_ReturnType send_8b (const char_lcd_8b_t *lcd , uint8 _8b)
{
    std_ReturnType ret =E_OK ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK ;
    }
    else
    {
        for(uint8 i=0 ;i<8 ; i++)
        {
            ret = gpio_pin_write_logic( &lcd->data[i] , (_8b >> i) & 0x01 ) ;
        }
    }
    return ret ;
}