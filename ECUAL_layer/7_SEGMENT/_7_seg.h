/* 
 * File:   _7_seg.h
 * Author: Mansour
 *
 * Created on October 23, 2023, 4:28 AM
 * 
 * the classic 7_seg common anode or cathode doesn't need any interface you just initialize the port direction: ( gpio_port_direction_initialize(PORT_INDEX); ) 
 * and then write the number u need with the help of @ seg_common_anode[0:9] ;
 * 
 * but if u use the seg with decoder 7447 / 7448 only or decoder with multiplixing u will use the interfaces
 */



#ifndef     _7_SEG_H
#define	_7_SEG_H

/*   section: Includes  */

#include "_7_seg_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*   section: Macros  */

#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

extern uint8 seg_common_anode[10] ;
extern uint8 seg_common_cathode[10];
/*   section: Macro Functions declarations */



/*   section: Data Types declarations */

typedef enum 
{
    SEGMENT_COMMON_CATHODE , 
    SEGMENT_COMMON_ANODE  
}segment_type_t;

typedef struct 
{
    pin_config_t segment_pins[4] ;
//    segment_type_t segment_type ;
}segment_t;

/*   section: Function declarations  */

std_ReturnType seven_segment_initialize ( segment_t *seg);
std_ReturnType seven_segment_write_number ( segment_t *seg , uint8 number );

#endif	/* _7_SEG_H */

