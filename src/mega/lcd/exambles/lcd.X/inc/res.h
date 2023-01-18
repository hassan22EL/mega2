/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   res.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   no-used
 * Program Space:   no-used
 * Version      :   Mega2v241022
 * Start Data   :   25-10-2022  20:15:00
 * End Data     :   25-10-2022  20:30:00
 * Work Time    :   15-min
 * Comments     :   no comment
 *  
 */

#ifndef RES_H
#define	RES_H

#include "appRes.h"






/*
----------------------------------------------------------------------------------------
|                                <TWI MODULE>                                          | 
----------------------------------------------------------------------------------------
| < TWI_MODULE              : 0 module is not active                                   | 
|                           : 1 module is active                                       |
| < TWI_TYPE                : @TWI_MASTER_SLAVE >  Work as two mode                    |
|                           : @TWI_SLAVE        >  work as slave                       |
|                           : @TWI_MASTER       >  work as master                      | 
| < TWI_INTERNAL_PULL_UP    : @TWI_PULL_ENABLE  >  enable internal pull up             |
|                           : @TWI_PULL_DIABLE  >  disable internal pull up            | 
| < TWI_SCL_PIN             : clock gpio pin if has enable interanl pull up            |
|                           : at disaple pull up don't care                            |
| < TWI_SDA_PIN             : data gpio pin if has enable interanl pull up             |
|                           : at disaple pull up don't care                            |
| < SRAM USAGE              : 8-Byte in Master Mode  && Slave mode 7 Byte              |  
| < PROGRAM USAGE           : 850 Byte (425 Instruction)   in Master mode              |
|                           : under test in slave mode                                 |   
----------------------------------------------------------------------------------------
 */
#define  TWI_MODULE                                              (0)
#if    TWI_MODULE
#define             TWI_TYPE                                      TWI_MASTER
#define            TWI_INTERNAL_PULL_UP                           TWI_PULL_ENABLE
#define            TWI_SCL_PIN                                    GPIO_D0
#define            TWI_SDA_PIN                                    GPIO_D1
#endif



/*
 ------------------------------------------------------------------------------------------------------------
 |                              USART_MODULE                                                                |                                       
 |-----------------------------------------------------------------------------------------------------------
 | @USART_MODULE               : 0 module is not active                                         |
 |                             : 1 module is active                                             |
 ------------------------------------------------------------------------------------------------------------
 | @USARTx_ENABLED             : to enable USART please define USART0_ENABLED                               |
 |                             : or defined USART0_ENABLED or defined both                                  |
 |                             : version supported a 4 USART (0,1,2,3)                                      |
 |-----------------------------------------------------------------------------------------------------------
 |  speed (Mbps)                                        |  Bit duration  |  byte rate      | byte duration  |
 |------------------------------------------------------|----------------|-----------------|----------------|  
 |  UARTx_BUADRATE            @StandBaudRate_1200       |    833.33 us   |  00120 byte/s   |  8333.33 us    |                
 |  x is 0 to 3               @StandBaudRate_2400       |    416.66 us   |  00240 byte/s   |  4166.66 us    |                                   
 |                            @StandBaudRate_4800       |    208.33 us   |  00480 byte/s   |  2083.33 us    |                     
 |                            @StandBaudRate_9600       |    104.16 us   |  00960 byte/s   |  1041.66 us    |                            
 |                            @StandBaudRate_19200      |    052.08 us   |  01920 byte/s   |  0520.83 us    |                                      
 |                            @StandBaudRate_38400      |    026.04 us   |  03840 byte/s   |  0260.41 us    |                        
 |                            @StandBaudRate_57600      |    017.36 us   |  05760 byte/s   |  0173.61 us    |
 |                            @StandBaudRate_76800      |    013.68 us   |  07680 byte/s   |  0130.20 us    |
 |                            @StandBaudRate_115200     |    008.68 us   |  11520 byte/s   |  0086.00 us    |                                                                  
 ------------------------------------------------------------------------------------------------------------
 | @note : @UARTx_BUADRATE      : x  0 to 3 if defined more UART please defined the baud rate every uart    |
 *       : @UART_XYZ            : not supported in current version the usart is work only 8nit data and     |
 *       :                      : and  no parity and 1-stop bit in new version can support this  and        | 
 *                              : @X is a number of bits and @Y type the parity and @Z is n-stop bits       |                                                 |
 ------------------------------------------------------------------------------------------------------------
 */
#define  USART_MODULE                                                           (0)
#if      USART_MODULE
#define  USART0_ENABLED
#define  UART0_BUADRATE                                                     StandBaudRate_19200
#endif
/* 
 -------------------------------------------------------------------------------------------------------------------------------------
 |                         <EX_EEPROM MODULE>                                                                                        |              
 -------------------------------------------------------------------------------------------------------------------------------------
 | < EX_EEPROM_MODULE         : 0 module is not active                                                                               |
 |                            : 1 module is active                                                                                   |
 | < EXEEPROM_MEM_ADDR_LEN    : internal address select one by four option >                                                         |              
 |                            : <@one   TWI_SLAVE_NO_INTERNAL_ADDRESS >  :  chip no have Internal address                            |         
 |                            : <@two   TWI_SLAVE_ONE_BYTE_SIZE    >     :  chip have one byte internal address 2^8 addresses        |        
 |                            : <@three TWI_SLAVE_TWO_BYTE_SIZE    >     :  chip have two byte internal address 2^16 addresses       |         
 |                            : <@Four  TWI_SLAVE_THREE_BYTE_SIZE  >     :  chip have a three byte internal address 2^24 addresses   |        
 | < EXEEPROM_MEM_PAGE_SIZE   : write page size in external memory >                                                                 |            
 | < EXEEPROM_MEM_ADDR        : chip address                                                                                         |             
 | < EXEEPROM_MEM_MAX_BUFFER  : max buffer read and write                                                                            |
 | < EXEEPROM_BUS_SPEED       : TWI_100KHZ   chip work speed 100Khz clock                                                            |
 |                            : TWI_400KHZ   chip work speed 10Khz  clock                                                            |
 | < SRAM_USAGE               : 40 Byte                                                                                              |
 |                            : @TWI  9 Byte Used                                                                                    |
 |                            : @Time Out  4 Byte                                                                                    |
 |                            : @eeprom description 11 Byte                                                                          |
 |                            : @Internal Read Buffer default used 16 Byte                                                           |
 | < PROGRAM_USAGE            : 1124 byte (562 Instruction)                                                                          |                                                                                                     |                   
 -------------------------------------------------------------------------------------------------------------------------------------
 */
#define  EX_EEPROM_MODULE             (0)
#if  EX_EEPROM_MODULE 
#define  EXEEPROM_MEM_ADDR_LEN        TWI_SLAVE_TWO_BYTE_SIZE
#define  EXEEPROM_MEM_PAGE_SIZE       (32)
#define  EXEEPROM_MEM_ADDR            (0xA0)
#define  EXEEPROM_MEM_MAX_BUFFER      (16)
#define  EXEEPROM_BUS_SPEED           (TWI_400KHZ)
#endif


/* 
 ------------------------------------------------------------------------------------------------
 |                          < LCD MODULE                                                         |                                              
 -------------------------------------------------------------------------------------------------
 | < LCD_MODULE              : 0 module is not active                                            |
 |                           : 1 module is active                                                |
 | < LCD_NUMBER_OF_LINE      : LCD has a number of line  shuc as 2 , 4 , , 3 ,..etc              |                                                       
 | < LCD_NUMBER_OF_BYTE      : LCD number of char per line   16 char , 20 char , ......etc       |                                                               
 | < LCD_RW                  : read pin in gpio pin such as GPIO_A0                              |                                                          
 | < LCD_RS                  : RS   pin in gpio pin such as GPIO_A1                              |
 | < LCD_EN                  : Enable pin in gpio pin such as GPIO_A2                            |
 | < LCD_D4                  : Data  bit 4 in gpio pin such as GPIO_A3                           |
 | < LCD_D5                  : Data  bit 4 in gpio pin such as GPIO_A4                           |
 | < LCD_D6                  : Data  bit 4 in gpio pin such as GPIO_A5                           |
 | < LCD_D7                  : Data  bit 4 in gpio pin such as GPIO_A6                           |
 | < SRAM USAGE              : 36-Byte in default 32 byte buffer   , 4 byte internal             |  
 | < PROGRAM USAGE           : 1082 Byte (1052 byte (526 Instruction)) + 30 Byte custom char     |                           
 -------------------------------------------------------------------------------------------------
 */
#define  LCD_MODULE                 (1)
#if  LCD_MODULE
#define  LCD_NUMBER_OF_LINE        (2)
#define  LCD_NUMBER_OF_BYTE        (16)
#define  LCD_RW                   (GPIO_A0)
#define  LCD_RS                   (GPIO_A1)
#define  LCD_EN                   (GPIO_A2)
#define  LCD_D4                   (GPIO_A3)
#define  LCD_D5                   (GPIO_A4)
#define  LCD_D6                   (GPIO_A5)
#define  LCD_D7                   (GPIO_A6)
#endif

/*
 --------------------------------------------------------------------------------------
 |                                CSMA_MODULE                                         |                                       
 |-------------------------------------------------------------------------------------
 | @CSMA_MODULE                : 0 module is not active                               |
 |                             : 1 module is active                                   |
 --------------------------------------------------------------------------------------
 | @CSMA_DEVICE_TYPE           : @CSMA_MASTER  : the device is work as a master       |
 |                             : @CSMA_SLAVE   : the device work as a  slave          |
 |                             : default value is  @CSMA_MASTER                       |                                                                                     
 --------------------------------------------------------------------------------------
 |@note : in this version is worked only USART 0  @upgrade can supported all UARTs    |
 ---------------------------------------------------------------------------------------
 */
#define    CSMA_MODULE                                     (0)
#if        CSMA_MODULE
#define    CSMA_DEVICE_TYPE                                (CSMA_MASTER)
#endif

#endif	/* RES_H */

