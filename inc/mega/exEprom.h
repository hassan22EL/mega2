/*
------------------------------------------------------------------------------------------
|                          < Module  Definition >                                        | 
------------------------------------------------------------------------------------------
| < FILE                   : exeeprom.h                                                  |                                  
| < Author                 : Hassan Elsaied                                              | 
| < Version                : Mega2v241022                                                |
| < References             : no-used references in this documents                        |
| < SRAM_USAGE             : 40 Byte                                                     |
|                          : @TWI  9 Byte Used                                           |
|                          : @Time Out  4 Byte                                           |
|                          : @eeprom description 11 Byte                                 |
|                          : @Internal Read Buffer default used 16 Byte                  |
| < PROGRAM_USAGE          : 1002 byte (501 Instruction)                                 |
| < Hardware Usage         : I2C  as a master                                            |
| < File Created           : 24-10-2022                                                  |
-------------------------------------------------------------------------------------------
 */

#ifndef XC_EXEEPROM_H
#define	XC_EXEEPROM_H

#include "../mega.h"


#if defined  EX_EEPROM_MODULE
#if EX_EEPROM_MODULE
/*
 --------------------------------------------------------------------------------------------------------
 |                                   <  user operations  >                                               |
 --------------------------------------------------------------------------------------------------------
 */


/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReset  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromReset                                              |
 | < @Description       : in at24cxx is reset eeprom after power unstable to remove last operation      |                                                          |                                                          |
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */



void exeepromReset();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromWriteBuffer  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void exeepromWriteBuffer                                            |
 | < @Description       : this function assignent data into ex-eeprom description                       |
 *                      : and enable update  fuction                                                    |
 | < @param  address    : specefic address to write data witj specific size                             |
 | < @param  buf        : pointer of the data from application                                          |
 | < @param  length     : total number of bytes to  write into ex-eeprom                                |
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */

void exeepromWriteBuffer(uint32_t address, uint8_t *buf, uint8_t length);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromWriteByte  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromWriteByte                                                       |
 | < @Description       : this function assignent data into ex-eeprom description                       |
 *                      : and enable update  function with update one byte                              |
 | < @param  address    : specefic address to write data with write one byte                            |
 | < @param  byte       : data write into ex-eeprom                                                     |                               |
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */

void exeepromWriteByte(uint32_t address, uint8_t byte);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromRequestSteram  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromRequestSteram                                                   |
 | < @Description       : this function assignent data into ex-eeprom description                       |
 |                      : and enable read  fuction and after compelete the data found                   |
 |                      : in internal buffer with specefic length                                       |
 | < @param  address    : specefic address to write data witj specific size                             |                                         |
 | < @param  length     : total number of bytes to read from ex-eeprom                                  |
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void exeepromRequestSteram(uint32_t address, uint8_t length);

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromRequestByte  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromRequestByte                                                     |
 | < @Description       : this function assignment data into ex-eeprom description                      |
 *                      : and enable read  fuction and after compelete the data found                   |
 *                      : in internal buffer with specefic one byte                                     |
 | < @param  address    : specefic address to write data with specific one byte                         |                     
 | < @return            : void                                                                          |                    
 --------------------------------------------------------------------------------------------------------
 */

void exeepromRequestByte(uint32_t address);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromDriver  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromDriver                                                          |
 | < @Description       : mangment data between user and driver if enable read operation                |
 |                      : switch state from wait state to read operation id done switch state           |
 |                      : form read to wait and same operation with update operation                    |
 |                      : and enable read  fuction and after compelete the data found                   |
 |                      : in internal buffer with specefic one byte                                     |                      |                     
 | < @return            : void                                                                          |                    
 --------------------------------------------------------------------------------------------------------
 */

void exeepromDriver();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < exEepromInit  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exEepromInit                                                            |
 | < @Description       : assignment default values of the ex-eeprom after powr on and start            |
 |                      : application the data into Read buffer is start application is 0xFF            |                                   |                      |                     
 | < @return            : void                                                                          |                    
 --------------------------------------------------------------------------------------------------------
 */

void exEepromInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReady  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char   exeepromReady                                                 |
 | < @Description       : before any write or call this function and check the driver in wait state     |
 *                      : or not if driver in wait state can be write or read and chcek after to        |
 *                      : write operation is done to be write or read other operation                   |
 *                      : and check after read to write or read or data into internal buffer is ready   |                                                         
 | < @return            : 0  driver is busy state                                                       |
 *                      : 1 driver is ready state  (wait state)                                         |                    
 --------------------------------------------------------------------------------------------------------
 */
uint8_t exeepromReady();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < exEepromRead >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  exEepromRead                                                         |
 | < @Description       : Read data From Internal Buffer with Last Operation size                       |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void exEepromRead(uint8_t *buf);
#endif
#endif

#endif