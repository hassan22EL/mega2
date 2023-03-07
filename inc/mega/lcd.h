/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : lcd.h                                                             |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : https://www.sparkfun.com/datasheets/LCD/HD44780.pdf               |
| < SRAM USAGE               : 36-Byte  (32 Byte buffer , 4 byte internal used                   |
| < PROGRAM USAGE            : 1010 Byte (950 byte (475 Instruction)) + 30 Byte custom char      |                                      
| < Hardware Usage           : GPIO                                                              |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#ifndef XC_LCD_H
#define	XC_LCD_H


#include "../mega.h"

#if defined LCD_MODULE
#if LCD_MODULE
/*
--------------------------------------------------------------------------------------------------
|                           <  LCD  Definition >                                                 | 
--------------------------------------------------------------------------------------------------
 */
#ifndef  LCD_NUMBER_OF_LINE
#define  LCD_NUMBER_OF_LINE      2
#endif 
#ifndef  LCD_NUMBER_OF_BYTE
#define  LCD_NUMBER_OF_BYTE      16
#endif
/*
 -------------------------------------------------------------------------------------------------------
 |                               <LCD  Text Alignment>                                                 |
 -------------------------------------------------------------------------------------------------------
 | < discuss :  this micro is call in pos write buffer the data centered in lcd                        |
 -------------------------------------------------------------------------------------------------------
 */
#define  LCD_TEXT_CENTER         (LCD_NUMBER_OF_BYTE >> 1)
/*
 --------------------------------------------------------------------------------------------------
 |                           < LCD Address of Lines  >                                            | 
 --------------------------------------------------------------------------------------------------
 | < macro LCD_LINE0_START  : start address of line one                                           |
 | < macro LCD_LINE1_START  : start address of line two                                           |
 | < macro LCD_LINE2_START  : start address of line thre                                          |
 | < macro LCD_LINE3_START  : start address of line four                                          |
---------------------------------------------------------------------------------------------------
 */


#define LCD_LINE0_START         (0x80) /* 0x00 as 7 bit data*/
#define LCD_LINE1_START         (0xC0)  
#define LCD_LINE2_START         (0x90)  
#define LCD_LINE3_START         (0xD0)  

/*
--------------------------------------------------------------------------------------------------
|                           <LCD I/O Pins>                                                       | 
--------------------------------------------------------------------------------------------------
 */

/*
--------------------------------------------------------------------------------------------------
|                           <LCD Read Pin>                                                       | 
--------------------------------------------------------------------------------------------------
 */

#ifndef   LCD_RW
#define   LCD_RW    NOT_A_PIN
#endif

/*
--------------------------------------------------------------------------------------------------
|                           <LCD Write Commands Pin >                                            | 
--------------------------------------------------------------------------------------------------
 */


#ifndef   LCD_RS
#define   LCD_RS    NOT_A_PIN
#endif

/*
--------------------------------------------------------------------------------------------------
|                           <LCD Pulse Enable Pin >                                              | 
--------------------------------------------------------------------------------------------------
 */
#ifndef   LCD_EN
#define   LCD_EN    NOT_A_PIN
#endif
/*
--------------------------------------------------------------------------------------------------
|                           < LCD Data 4 Pin >                                                   | 
--------------------------------------------------------------------------------------------------
 */

#ifndef   LCD_D4
#define   LCD_D4    NOT_A_PIN
#endif
/*
--------------------------------------------------------------------------------------------------
|                           < LCD Data BACK LIGTH Pin >                                                   | 
--------------------------------------------------------------------------------------------------
 */

#ifndef   LCD_BL
#define   LCD_BL    NOT_A_PIN
#endif
/*
--------------------------------------------------------------------------------------------------
|                           < LCD Data 5 Pin >                                                   | 
--------------------------------------------------------------------------------------------------
 */

#ifndef   LCD_D5
#define   LCD_D5    NOT_A_PIN
#endif
/*
--------------------------------------------------------------------------------------------------
|                           < LCD Data 6 Pin >                                                   | 
--------------------------------------------------------------------------------------------------
 */

#ifndef   LCD_D6
#define   LCD_D6    NOT_A_PIN
#endif
/*
--------------------------------------------------------------------------------------------------
|                           < LCD Data 7 Pin >                                                   | 
--------------------------------------------------------------------------------------------------
 */

#ifndef   LCD_D7
#define   LCD_D7    NOT_A_PIN
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdNoBlink  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdNoBlink                                                               |
 | < @Description       : lcd stop blink                                                                |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
extern void lcdNoBlink();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdBlink  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdBlink                                                                 |
 | < @Description       : lcd enable blink in position x ,y                                             |
 | < @Param u8line      : enable blink in specific line x and x from 0 to max line per lcd              |
 | < @Param u8pos       : enable blink in specific char (y) in line and                                 |
 |                      : y is 0 to max number of byte per line                                         |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

extern void lcdBlink(uint8_t u8line, uint8_t u8pos);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdNoCursor  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdNoCursor                                                              |
 | < @Description       : lcd stop cursor                                                               |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
extern void lcdNoCursor();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdCursor  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdCursor                                                                |
 | < @Description       : lcd enable blink in position x ,y                                             |
 | < @Param  u8line     : enable cursor in specific line x and x from 0 to max line per lcd             |
 | < @Param  u8Pos      : enable cursor in specific char (y) in line and                                |
 |                      : y is 0 to max number of byte per line                                         |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

extern void lcdCursor(uint8_t u8line, uint8_t u8pos);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdHwInit  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdHwInit                                                                |
 | < @Description       : lcd gpio pin init a mode input or out  or ... etc                             |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdHwInit();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdwrite >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdwrite                                                                 |
 | < @Description       : write data into buffer with select position                                   |
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |
 | < @Param  pos        : write in specific char (y) in line and                                        |
 |                      : y is 0 to max number of byte per line                                         |
 | < @Param string      : data put into lcd buffer                                                      |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

void lcdwrite(uint8_t line, uint8_t pos, const char *string);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdwritebuf >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdwritebuf                                                              |
 | < @Description       : write data into buffer with select position                                   |
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |
 | < @Param  pos        : write in specific char (y) in line and                                        |
 |                      : y is 0 to max number of byte per line                                         |
 | < @Param buf         : data put into lcd buffer                                                      |
 | < @Param Length      : Number of byte Load
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdwritebuf(uint8_t line, uint8_t pos, uint8_t *buf, uint8_t Length);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdCreateChar >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdCreateChar                                                            |
 | < @Description       : create custom char into lcd                                                   |
 | < @Param  u8location : write in specific location x in memory                                        |
 | < @Param  pu8Data    : pointer of the data created                                                   |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdCreateChar(uint8_t u8location, const uint8_t *pu8Data);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdwrite >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdwrite                                                                 |
 | < @Description       :  write address of the custom char  into buffer                                |
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |
 | < @Param  pos        : write in specific char (y) in line and                                        |
 |                      : y is 0 to max number of byte per line                                         |
 | < @param index       : address of char  to write into buffer                                         |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdwriteCGRAM(uint8_t line, uint8_t pos, uint8_t index);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdClearlines >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdClearlines                                                            |
 | < @Description       : lcd can be clear a line into lcd buffer by write 0x20 into the buffer         |
 |                      : from address of the start line 0 or 1 or ..etc to end address of the line     |
 |                      : address dependent of number of char into line                                 |                                |
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |
 |                      : y is 0 to max number of byte per line                                         |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdClearlines(bool from);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdClear >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdClear                                                                 |
 | < @Description       : lcd can be  for all lines into lcd by write 0x20 into the buffer              |
 |                      : from address of the start line 0  to end address of the line                  |         
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

void lcdClear();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdIsBusy >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdIsBusy                                                             |
 | < @Description       : check lcd is ready to write new data or not                                   |        
 | < @return            : 0 when  lcd is ready and other case lcd has not ready                         |                                                                       |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t lcdIsBusy();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdDriver >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void Driver                                                                   |
 | < @Description       : run in background to write data from buffer into lcd                          |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdDriver();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdUpdateNow >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdUpdateNow                                                             |
 | < @Description       : after write all into buffer from lcd call this function to start update       |                                    
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdUpdateNow();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdGetLineDate >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdGetLineDate                                                           |
 | < @Description       : assignment Line Date Into app Buffer                                          |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void lcdGetLineDate(uint8_t *u8Data, uint8_t Line);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < LcdWriteIndex >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void LcdWriteIndex                                                           |
 | < @Description       : assignment Index By this Function                                        |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void LcdWriteIndex(uint8_t Index, uint8_t byteDate);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdWriteromFlash >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdWriteromFlash                                                         |
 | < @Description       : write Data From Flash Memeory into LCD Buffer                                 |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void lcdWriteromFlash(uint8_t line, uint8_t pos, PGM_P const *date);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdWriteString >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdWriteString                                                           |
 | < @Description       : write string in cencer pos                                                    |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void lcdWriteString(uint8_t line, PGM_P date);
#endif
#endif

#endif	/* XC_LCD_H */

