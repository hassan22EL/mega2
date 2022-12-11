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
| < PROGRAM USAGE           : 766 Byte ( Instruction)                                  |  
----------------------------------------------------------------------------------------
 */
#define       EEPROM_MODULE    (1)
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
 | < SRAM USAGE                   : (4 Byte buffer , 6 buffer dis , r*c byte  , 2byte            |
 | < PROGRAM USAGE                : ()((678 Byte)+(216Byte when enable signal))               |              
 -------------------------------------------------------------------------------------------------
 */
#define   KEYPAD_MODULE                  (1)
#if KEYPAD_MODULE
#define   KEYPAD_MAX_ROW                 (4)
#define   KEYPAD_MAX_COL                 (3)
#define   KEYPAD_DEDEBOUND_TIME          (20)   /* 20 ms*/
#define   KEYPAD_LONG_TIME               (2000) /* 2 second*/
#define   KEYPAD_REPEAT_TIME             (3000) /* 3 second*/
#define   KEYPAD_REPEAT_RATE             (5)    /* 5 ms*/
#define   KEY_PREDIOC_TASK_TIME          (10)
/***********************ROW Pins********************/
#define KEYPAD_C01_PIN          GPIO_C3
#define KEYPAD_C02_PIN          GPIO_C4
#define KEYPAD_C03_PIN          GPIO_C5
#define KEYPAD_C04_PIN          GPIO_D5
#define KEYPAD_C05_PIN          NOT_A_PIN
#define KEYPAD_C06_PIN          NOT_A_PIN
#define KEYPAD_C07_PIN          NOT_A_PIN
#define KEYPAD_C08_PIN          NOT_A_PIN
/***********************Clomuns Pins********************/
#define KEYPAD_SW01_PIN          GPIO_D6
#define KEYPAD_SW02_PIN          GPIO_D7
#define KEYPAD_SW03_PIN          GPIO_B0
#define KEYPAD_SW04_PIN          NOT_A_PIN
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
#define   BUTTON_MODULE                   (1)
#if BUTTON_MODULE
#define   NUMBER_OF_BUTTON               (1)
#define   BUTTON_DEDEBOUND_TIME          (20)   /* 20 ms*/
#define   BUTTON_LONG_TIME               (2000) /* 2 second*/
#define   BUTTON_REPEAT_TIME             (3000) /* 3 second*/
#define   BUTTON_REPEAT_RATE             (5)    /* 5 ms*/
#define   BUTTON_PREDIOC_TASK_TIME       (10)   
#define   BUTTON_MAX_BUFFER              (4)
#endif

/*
 ----------------------------------------------------------------------------------------
 |                                <SIGNALGENERATED_MODULE>                              | 
 ----------------------------------------------------------------------------------------
 | < BUZ_MODULE              : 0 module is not active                                   | 
 |                           : 1 module is active                                       |
 | < SIGNAL_NUMBER_OF_PINS   : number of Pins to Generated different signal             |
 | < SRAM USAGE              : 10 Byte Per Pin  +2 Byte Pinter to first signal          |      
 | < PROGRAM USAGE           : (918 Byte ) 459 Instruction                              |  
 ----------------------------------------------------------------------------------------
 */
#define       SIGNALGENERATED_MODULE                  (1)
#if SIGNALGENERATED_MODULE
#define   SIGNAL_NUMBER_OF_PINS                       (3)
#endif




#endif	/* RES_H */

