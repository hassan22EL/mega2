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
|                                <EEPROM MODULE>                                       | 
----------------------------------------------------------------------------------------
| < EEPROM_MODULE           : 0 module is not active                                   | 
|                           : 1 module is active                                       |
| < SRAM USAGE              : 21 Byte                                                  |  
| < PROGRAM USAGE           : 722 Byte ( Instruction)                                  |  
----------------------------------------------------------------------------------------
 */
#define       EEPROM_MODULE    (0)
/* 
 -------------------------------------------------------------------------------------------------
 |                          < KEYPAD MODULE  >                                                   |                                             
 -------------------------------------------------------------------------------------------------
 | < KEYPAD_MODULE                : 0 module is not active                                       |
 |                                : 1 module is active                                           |
 | < KEY_PREDIOC_TASK_TIME        : run evey x time                                              |
 | < KEYPAD_MAX_ROW               : max row in keypad and this value less than 8                 |
 | < KEYPAD_MAX_COL               : max column in keypad and this value less than 8              |
 | < KEYPAD_MAX_BUFFER            : max key stored                                               |
 | < KEYPAD_DEDEBOUND_TIME        : time required to press or released switch                    |
 | < KEYPAD_LONG_TIME             : time required to long press                                  |
 | < KEYPAD_REPEAT_TIME           : time required to repeat key                                  |
 | < KEYPAD_REPEAT_RATE           : time required between repeat key                             |
 | < note                         : keypad state is fixed active low                             |
 | < pin                          : replace NOT_A_PIN by digital pin with max rows and column    |                    
 | < SRAM USAGE                   : 28-Byte used  (4 buffer + 6buffer dis , 16 counter +2byte    |  
 | < PROGRAM USAGE                : 1056 Byte (528 Instruction)                                  |               
 -------------------------------------------------------------------------------------------------
 */
#define   KEYPAD_MODULE                  (0)
#if KEYPAD_MODULE
#define   KEYPAD_MAX_ROW                 (4)
#define   KEYPAD_MAX_COL                 (4)
#define   KEYPAD_DEDEBOUND_TIME          (20)   /* 20 ms*/
#define   KEYPAD_LONG_TIME               (2000) /* 2 second*/
#define   KEYPAD_REPEAT_TIME             (3000) /* 3 second*/
#define   KEYPAD_REPEAT_RATE             (5)    /* 5 ms*/
#define   KEY_PREDIOC_TASK_TIME          (10)
/***********************ROW Pins********************/
#define KEYPAD_C01_PIN          GPIO_B4
#define KEYPAD_C02_PIN          GPIO_B5
#define KEYPAD_C03_PIN          GPIO_B6
#define KEYPAD_C04_PIN          GPIO_B7
#define KEYPAD_C05_PIN          NOT_A_PIN
#define KEYPAD_C06_PIN          NOT_A_PIN
#define KEYPAD_C07_PIN          NOT_A_PIN
#define KEYPAD_C08_PIN          NOT_A_PIN
/***********************Clomuns Pins********************/
#define KEYPAD_SW01_PIN          GPIO_B0
#define KEYPAD_SW02_PIN          GPIO_B1
#define KEYPAD_SW03_PIN          GPIO_B2
#define KEYPAD_SW04_PIN          GPIO_B3
#define KEYPAD_SW05_PIN          NOT_A_PIN
#define KEYPAD_SW06_PIN          NOT_A_PIN
#define KEYPAD_SW07_PIN          NOT_A_PIN
#define KEYPAD_SW08_PIN          NOT_A_PIN
#endif

/* 
 -------------------------------------------------------------------------------------------------
 |                          < BUTTON_MODULE   >                                                  |                                             
 -------------------------------------------------------------------------------------------------
 | < BUTTON_MODULE                : 0 module is not active                                       |
 |                                : 1 module is active                                           |
 | < NUMBER_OF_BUTTON             : number  of Buttons  used                                     |  
 | < BUTTON_PREDIOC_TASK_TIME     : run evey x time                                              |
 | < BUTTON_MAX_BUFFER            : max key stored                                               |
 | < BUTTON_DEDEBOUND_TIME        : time required to press or released switch                    |
 | < BUTTON_LONG_TIME             : time required to long press                                  |
 | < BUTTON_REPEAT_TIME           : time required to repeat key                                  |
 | < BUTTON_REPEAT_RATE           : time required between repeat key                             |
 | < note                         : keypad state is fixed active low                             |          
 | < SRAM USAGE                   : 14 Byte + BUTTON_MAX_BUFFER                                  |  
 | < PROGRAM USAGE                : 624 Byte (312 Instruction)                                   |               
 -------------------------------------------------------------------------------------------------
 */
#define   BUTTON_MODULE                   1
#if BUTTON_MODULE
#define   NUMBER_OF_BUTTON               (1)
#define   BUTTON_DEDEBOUND_TIME          (20)   /* 20 ms*/
#define   BUTTON_LONG_TIME               (2000) /* 2 second*/
#define   BUTTON_REPEAT_TIME             (3000) /* 3 second*/
#define   BUTTON_REPEAT_RATE             (5)    /* 5 ms*/
#define   BUTTON_PREDIOC_TASK_TIME       (10)   
#define   BUTTON_MAX_BUFFER              (4)
#endif





#endif	/* RES_H */

