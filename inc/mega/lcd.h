/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   lcd.c
 * Author       :   Hassan Elsaied
 * Data Memory  :   number of line * number of char per line  +  4byte is default 2*16 +4 = 36Byte
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   5-hour
 * Comments     :   no comment
 */
#ifndef XC_LCD_H
#define	XC_LCD_H


#include "../mega.h"

#if defined LCD_MODULE
#if LCD_MODULE

/* 
 * ******************************************************************************
 *                        LCD  Definition                                     *
 * ******************************************************************************
 */
#ifndef  LCD_NUMBER_OF_LINE
#define  LCD_NUMBER_OF_LINE      2
#endif 
#ifndef  LCD_NUMBER_OF_BYTE
#define  LCD_NUMBER_OF_BYTE      16
#endif

/* 
 * ******************************************************************************
 *                        LCD Address of Lines                                    *
 * ******************************************************************************
 */



#define LCD_LINE0_START         (0x80) /* 0x00 as 7 bit data*/
#define LCD_LINE1_START         (0xC0)  
#define LCD_LINE2_START         (0x90)  
#define LCD_LINE3_START         (0xD0)  

/* 
 * ******************************************************************************
 *                        LCD I/O Pins                                          *
 * ******************************************************************************
 */


/* 
 * ******************************************************************************
 *                        LCD Read Pin                                         *
 * ******************************************************************************
 */

#ifndef   LCD_RW
#define   LCD_RW    NOT_A_PIN
#endif

/* 
 * ******************************************************************************
 *                        LCD Write Commands Pin                                *
 * ******************************************************************************
 */


#ifndef   LCD_RS
#define   LCD_RS    NOT_A_PIN
#endif

/* 
 * ******************************************************************************
 *                        LCD Pulse Enable Pin                                  *
 * ******************************************************************************
 */


#ifndef   LCD_EN
#define   LCD_EN    NOT_A_PIN
#endif
/* 
 * ******************************************************************************
 *                        LCD Data 4 Pin                                        *
 * ******************************************************************************
 */


#ifndef   LCD_D4
#define   LCD_D4    NOT_A_PIN
#endif
/* 
 * ******************************************************************************
 *                        LCD Data 5 Pin                                        *
 * ******************************************************************************
 */

#ifndef   LCD_D5
#define   LCD_D5    NOT_A_PIN
#endif
/* 
 * ******************************************************************************
 *                        LCD Data 6 Pin                                        *
 * ******************************************************************************
 */

#ifndef   LCD_D6
#define   LCD_D6    NOT_A_PIN
#endif
/* 
 * ******************************************************************************
 *                        LCD Data 7 Pin                                        *
 * ******************************************************************************
 */

#ifndef   LCD_D7
#define   LCD_D7    NOT_A_PIN
#endif

/*
 * *******************************************************************
 *                               Pulse_En                            *
 * *******************************************************************
 * @benfit                : pulse to write any data in lcd 
 * @return                : void
 */

static inline void Pulse_En();
/*
 * *******************************************************************
 *                               lcdPosToAddress                      *
 * *******************************************************************
 * @benfit                 : convert line number and pos to lcd ram address to read or write
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param u8pos            : pos char of in the line char 0 or 1 or .........rtc
 * @return                 : address of data into lcd
 */
static inline uint8_t lcdPosToAddress(uint8_t u8line, uint8_t u8pos);
static inline void Pulse_En() __attribute__((always_inline, unused));

/*
 * *******************************************************************
 *                               Pulse_En                            *
 * *******************************************************************
 * @benfit                : pulse to write any data in lcd 
 * @return                : void
 */
static inline void Pulse_En() {
    digitalPinWrite(LCD_EN, GPIO_HIGH);
    digitalPinWrite(LCD_EN, GPIO_LOW);

}

/*
 * *******************************************************************
 *                               lcdPosToAddress                      *
 * *******************************************************************
 * @benfit                 : convert line number and position to lcd ram address to read or write
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param u8pos            : position char of in the line char 0 or 1 or .........etc
 * @return                 : address of data into lcd
 */
static inline uint8_t lcdPosToAddress(uint8_t u8line, uint8_t u8pos) __attribute__((always_inline, unused));

static inline uint8_t lcdPosToAddress(uint8_t u8line, uint8_t u8pos) {
    uint8_t u8Address;
    u8pos &= 0x3F;
    u8line &= 0x03;
    if (u8line == 3) {
        u8Address = ((LCD_LINE1_START + (LCD_NUMBER_OF_BYTE)) + u8pos);
    } else if (u8line == 2) {
        u8Address = ((LCD_LINE0_START + (LCD_NUMBER_OF_BYTE)) + u8pos);
    } else if (u8line == 1) {
        u8Address = ((LCD_LINE1_START) + u8pos);
    } else {
        u8Address = ((LCD_LINE0_START) + u8pos);
    }
    return (u8Address);
}

/*
 * *******************************************************************
 *                               lcdNoBlink                           *
 * *******************************************************************
 * @benfit                 : lcd stop blink
 * @return                 : void
 */

void lcdNoBlink();
/*
 * *******************************************************************
 *                               lcdNoBlink                           *
 * *******************************************************************
 * @benfit                 : lcd enable blink in position x,y 
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param u8pos            : pos char of in the line char 0 or 1 or .........etc
 * @return                 : void
 */
void lcdBlink(uint8_t u8line, uint8_t u8pos);
/*
 * *******************************************************************
 *                               lcdNoCursor                           *
 * *******************************************************************
 * @benfit                 : lcd stop cursor
 * @return                 : void
 */


void lcdNoCursor();
/*
 * *******************************************************************
 *                               lcdCursor                           *
 * *******************************************************************
 * @benfit                 : lcd enable cursor in position x,y 
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param u8pos            : pos char of in the line char 0 or 1 or .........etc
 * @return                 : void
 */
void lcdCursor(uint8_t u8line, uint8_t u8pos);
/*
 * *******************************************************************
 *                               lcdNoCursor                           *
 * *******************************************************************
 * @benfit                 : lcd  hardware init such gpio pins a
 * @return                 : void
 */

void lcdHwInit();

/*
 * *******************************************************************
 *                               lcdwrite                           *
 * *******************************************************************
 * @benfit                 : write data into buffer with select position
 * param line              : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  of  the string in the line char 0 or 1 or .........etc
 * string                  : pointer to string to write into buffer
 * @return                 : void
 */

void lcdwrite(uint8_t line, uint8_t pos, const char *string);
/*
 * *******************************************************************
 *                               lcdIsCurrentNumber                  *
 * *******************************************************************
 * @benfit                 : check is specific position is a number or not into buffer
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  of  the char in the line char 0 or 1 or .........etc
 * @return                 : 0 is buffer not contains a number in position and  1 if the position is a number
 */
uint8_t lcdIsCurrentNumber(uint8_t line, uint8_t pos);
/*
 * *******************************************************************
 *                              lcdCreateChar                        *
 * *******************************************************************
 * @benfit                 : create custom char into lcd 
 * @param u8location       : the address of the custome char to be create
 * @pu8Data                 : pointer to data of the char 
 * @return                 : void
 */
void lcdCreateChar(uint8_t u8location, const uint8_t *pu8Data);
/*
 * *******************************************************************
 *                               lcdwrite                           *
 * *******************************************************************
 * @benfit                 : write address of the custom char  into buffer with select position
 * @param line              : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  of  the custome char  in the line char 0 or 1 or .........etc
 * index                   : address of char  to write into buffer
 * @return                 : void
 */

void lcdwriteCGRAM(uint8_t line, uint8_t pos, uint8_t index);
/*
 * *******************************************************************
 *                               getlcdData                          *
 * *******************************************************************
 * @benfit                 : get data frome lcd buffer start form pos as assignment into pointer of the string read 
 *                         : and max length data to be get is max size of the data pointer can to be read
 * @param str               : pointer to assignment data read from buffer
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  into buffer to be read  in the line char 0 or 1 or .........etc
 * @return                 : void
 */
void getlcdData(char *str, uint8_t line, uint8_t pos);
/*
 * *******************************************************************
 *                               lcdClearlines                           *
 * *******************************************************************
 * @benfit                 : lcd can be clear a line into lcd buffer by write 0x20 into the buffer from address of the start line
 *                         :  0 or 1 or ..etc to end address of the line address dependent of number of char into line 
 * @param from             : start address of line  0 or 1 or ...........etc
 * @return                 : void
 */

void lcdClearlines(uint8_t from);
/*
 * *******************************************************************
 *                               lcdClearlines                           *
 * *******************************************************************
 * @benfit                 : lcd can be clear a buffer for all lines into lcd by write 0x20 into the buffer
 *                         :  from address of the  line 0 to line n  
 * @return                 : void
 */
void lcdClear();
/* ***************************************************************************************************************
 *                                 lcdIsBusy                                                                  *
 * ***************************************************************************************************************
 * @benfit                 : check lcd  is ready to write new data or not
 * @return                 : LCD_SUCCESS when  lcd is ready and other case lcd has not ready
 */

uint8_t lcdIsBusy();

/* ***************************************************************************************************************
 *                                Lcd Driver                                                                  *
 * ***************************************************************************************************************
 * @benfit                 : run at back ground of the system if is error or success run user 
 * @return                 : void
 */

void lcdDriver();
#endif
#endif

#endif	/* XC_LCD_H */

