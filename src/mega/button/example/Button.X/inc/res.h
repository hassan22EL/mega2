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
 | < PROGRAM USAGE                : (966) 624 Byte (312 Instruction)  + 342 when enable signal   |                                 |               
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
#define   SIGNAL_NUMBER_OF_PINS                       (1)
#endif





#endif	/* RES_H */

