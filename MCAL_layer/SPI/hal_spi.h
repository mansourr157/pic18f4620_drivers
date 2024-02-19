/* 
 * File:   hal_spi.h
 * Author: Mansour
 *
 * Created on January 27, 2024, 1:08 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/*   section: Includes  */
#include "../mcal_std_types.h"
#include "../interrupts/mcal_internal_interrupts.h"

/*   section: Macros  */

#define SPI_CLK_POLARITY_IDLE_HIGH 1
#define SPI_CLK_POLARITY_IDLE_LOW 0

#define SPI_CLK_PHASE_ACTIVE_TO_IDLE  1
#define SPI_CLK_PHASE_IDLE_TO_ACTIVE  0

#define SPI_INPUT_SAMPLED_AT_END           1
#define SPI_INPUT_SAMPLED_AT_MIDDLE     0

#define SPI_RECEIVE_COMPLETED           1
#define SPI_RECEIVE_NOT_COMPLETED   0

#define SPI_COLLISION_DETECTED      1
#define SPI_NO_COLLISION                   0

#define SPI_OVERFLOW_DETECTED      1
#define SPI_NO_OVERFLOW                   0



/*   section: Macro Functions declarations */

#define _SPI_ENABLE() (SSPCON1bits.SSPEN = 1)
#define _SPI_DISABLE() (SSPCON1bits.SSPEN = 0)

#define _SPI_MODE_SELECT(_X) (SSPCON1bits.SSPM = _X)

#define _SPI_CLK_POLARITY_IDLE_HIGH() (SSPCON1bits.CKP = 1)    
#define _SPI_CLK_POLARITY_IDLE_LOW() (SSPCON1bits.CKP = 0) 

#define _SPI_CLK_PHASE_TRANSMIT_FROM_ACTIVE_TO_IDLE() (SSPSTATbits.CKE = 1)
#define _SPI_CLK_PHASE_TRANSMIT_FROM_IDLE_TO_ACTIVE() (SSPSTATbits.CKE = 0)


#define _SPI_INPUT_SAMPLED_AT_END()  (SSPSTATbits.SMP = 1)
#define _SPI_INPUT_SAMPLED_AT_MIDDLE() (SSPSTATbits.SMP = 0)

#define _SPI_RECEIVE_STATUS() (SSPSTATbits.BF)

#define _SPI_WRITE_COLLISION_STATUS() (SSPCON1bits.WCOL)
#define _SPI_WRITE_COLLISION_RESET() (SSPCON1bits.WCOL = 0)

#define _SPI_OVERFLOW_STATUS() (SSPCON1bits.SSPOV)
#define _SPI_OVERFLOW_RESET() (SSPCON1bits.SSPOV = 0)

/*   section: Data Types declarations */

typedef enum {
    
    SPI_MASTER_Fosc_DIV_4 ,
    SPI_MASTER_Fosc_DIV_16 ,
    SPI_MASTER_Fosc_DIV_64 ,
    SPI_MASTER_TMR2_DIV_2 ,
    SPI_SLAVE_SS_ENABLE ,
    SPI_SLAVE_SS_DISABLE ,
            
}spi_mode_t;

typedef struct {
    
    spi_mode_t spi_mode ;
    uint8 clk_polarity :1 ;
    uint8 clk_phase :1 ;
    uint8 sampling :1 ;
    
#if SPI_INTERRUPT_CFG_ENABLE == 1
    void ( *SPI_INTERRUPT_HANDLER) (void) ;
    uint8 interrupt_priority :1 ;
#endif
    
}spi_t;

/*   section: Function declarations  */

std_ReturnType SPI_Init(const spi_t *spi_obj);
std_ReturnType SPI_DeInit(const spi_t *spi_obj);

std_ReturnType SPI_Send_Byte_Blocking(const uint8 data);
std_ReturnType SPI_Send_String_Blocking(const uint8 *data , uint16 data_length);
std_ReturnType SPI_Read_Byte_Blocking(uint8 *data);

//std_ReturnType SPI_Send_Byte_NonBlocking(const spi_t *spi_obj, const uint8 data);
//std_ReturnType SPI_Send_String_NonBlocking(const spi_t *spi_obj, const uint8 data);
//std_ReturnType SPI_Read_Byte_NonBlocking(const spi_t *spi_obj, uint8 *data);



//std_ReturnType SPI_Send_String(const spi_t *spi_obj, const uint8 data);

#endif	/* HAL_SPI_H */

