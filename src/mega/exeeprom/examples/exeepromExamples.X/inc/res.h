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
#define  TWI_MODULE                                              (1)
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
#define  EX_EEPROM_MODULE             (1)
#if  EX_EEPROM_MODULE 
#define  EXEEPROM_MEM_ADDR_LEN        TWI_SLAVE_TWO_BYTE_SIZE
#define  EXEEPROM_MEM_PAGE_SIZE       (32)
#define  EXEEPROM_MEM_ADDR            (0xA0)
#define  EXEEPROM_MEM_MAX_BUFFER      (16)
#define  EXEEPROM_BUS_SPEED           (TWI_400KHZ)
#endif


#endif	/* RES_H */

