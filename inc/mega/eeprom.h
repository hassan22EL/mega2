/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : eeprom.h                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : datasheet                                                                |  
| < SRAM USAGE               : 21  Byte (10 Byte Buffer + 7 Byte eeprom Descriptor , 4 Byte Time Out)   |
| < PROGRAM USAGE            : 722 Byte  (386 Instruction)                                              |                                    
| < Hardware Usage           : Internal EEPROM                                                          |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#ifndef EEPROM_H
#define	EEPROM_H
#include "../mega.h"
#if defined (EEPROM_MODULE)
#if EEPROM_MODULE

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromInit >                                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromInit                                                              |
 | < @Description       : Initialization all variables and Initialization eeorpm                        |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromDriver >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromDriver                                                            |
 | < @Description       : read and update operaion active state run in background                       |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromDriver();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromWriteBuf >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromWriteBuf                                                          |
 | < @Description       : application write data into eeprom by this function to write muti row data    | 
 | < @Param address     : start address request to write data this address less than (EEPROM_END-10)    |
 | < @Param size        : number of byte write into eeprom and this size less than 10 byte in each time |
 | < @param data        : pointer to payload data into eeprom                                           |              
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromWriteBuf(uint16_t address, uint8_t size, uint8_t *data);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRequestSterm >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromRequestSterm                                                      |
 | < @Description       : application read data from eeprom by this function to read muti row data      | 
 | < @Param address     : start address request to read data this address+size less than (EEPROM_END)   |
 | < @Param size        : number of byte read from eeprom and this size less than 10 byte in each time  |            
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromRequestSterm(uint16_t address, uint8_t size);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRequestByte >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromRequestByte                                                       |
 | < @Description       : application read data from eeprom by this function to read single byte data   | 
 | < @Param address     : start address request to read data this address less than (EEPROM_END)        |           
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromRequestByte(uint16_t address);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromIsBusy >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  eepromIsBusy                                                         |
 | < @Description       : chack state of Internal eeprom is ready to access new operation or not        |        
 | < @return            : 0 eeprom is ready to new operation                                            |
 |                      : 1 eeprom Internal Write Operaion in Progress                                  |
 |                      : 2 eeprom Internal Read Operaion in Progress                                   |              
 --------------------------------------------------------------------------------------------------------
 */
uint8_t eepromIsBusy();
#endif
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRead >                                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  eepromRead                                                           |
 | < @Description       : Read data From Internal Buffer with Last Operation size                       |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void eepromRead(uint8_t *buf);

#endif	/* EEPROM_H */

