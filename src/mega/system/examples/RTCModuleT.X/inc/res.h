/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : res.h                                                             |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : header file                                                       |
| < PROGRAM USAGE            : header file                                                       |                                      
| < Hardware Usage           : header file                                                       |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */

#ifndef RES_H
#define	RES_H

#include "appRes.h"
#define  COMPILER_TYPE                       GCC

/*
 ---------------------------------------------------------------------------------------
 |                                <System MODULE>                                      | 
 ---------------------------------------------------------------------------------------
 | <macro F_CPU                  : F_CPU CLOCK  >look clock.h                          |                                        |
 | <macro @N_OF_US_REQUIRED      : each F_CPU has base number of micro                 |
 |                               : select one of number of micro seconds               |
 |                               : _number+us  > is defined and supported time         |  
 | <macro SRAM_USAGE             : 14 Byte                                             |
 | <macro PROGRAM_USAGE          : 694 byte (347 Instruction)                          |
 ---------------------------------------------------------------------------------------
 */
#define     F_CPU                          XTAL_11059200
#define     N_OF_US_REQUIRED               (_1250us)
/*
 ---------------------------------------------------------------------------------------
 |                                <GPIO MODULE>                                        | 
 ---------------------------------------------------------------------------------------
 | < macro GPIO2_PREFER_SPEED     : gpio speed acess                                   |
 |                                : 0 the  function called used                        |
 |                                : 1 the  function not called and used inline         |
 | < macro GPIO2_IOREGS_ABOVEFF   : enable or disable access gpio with in atomic block |
 |                                : 0 gpio acess without atomic                        |
 |                                : 1 gpio acess with in atomic                        |
 |                                : @note : atomic means disable any extrnal interrupt |
 |                                :       : to not effect in gpio pins at write or...  |
 ---------------------------------------------------------------------------------------
 */
#define     GPIO2_PREFER_SPEED               (1)
#define     GPIO2_IOREGS_ABOVEFF             (0)





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
| < PROGRAM USAGE           : 658 Byte (329 Instruction)   in Master mode              |
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
 | < PROGRAM_USAGE            : 1002 byte (501 Instruction)                                                                          |                                                                                                     |                   
 -------------------------------------------------------------------------------------------------------------------------------------
 */
#define  EX_EEPROM_MODULE             (0)
#if  EX_EEPROM_MODULE 
#define  EXEEPROM_MEM_ADDR_LEN        TWI_SLAVE_TWO_BYTE_SIZE
#define  EXEEPROM_MEM_PAGE_SIZE       (32)
#define  EXEEPROM_MEM_ADDR            (0xA0)
#define  EXEEPROM_MEM_MAX_BUFFER      (32)
#define  EXEEPROM_BUS_SPEED           (TWI_400KHZ)
#endif

/* 
 -------------------------------------------------------------------------------------------------
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
 | < SRAM USAGE              : 36-Byte in default ==> 32 buffer , 4 byte data                    |  
 | < PROGRAM USAGE           : 1010 Byte (1030 byte (515 Instruction)) + 30 Byte custom char     |                             
 -------------------------------------------------------------------------------------------------
 */
#define  LCD_MODULE                 (1)
#if  LCD_MODULE
#define  LCD_NUMBER_OF_LINE         (2)
#define  LCD_NUMBER_OF_BYTE        (16)
#define  LCD_CUSTOM_CHAR_EN        (0)
#define  LCD_RW                   (GPIO_B4)
#define  LCD_RS                   (GPIO_A4)
#define  LCD_EN                   (GPIO_A3)
#define  LCD_D4                   (GPIO_A6)
#define  LCD_D5                   (GPIO_A2)
#define  LCD_D6                   (GPIO_A5)
#define  LCD_D7                   (GPIO_A1)
#define  LCD_BL                   (GPIO_A0) 
#endif

#endif	/* RES_H */

