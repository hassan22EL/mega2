/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : keypad.h                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : (4 Byte buffer , 6 buffer dis , r*c byte internal conter , 2byte         |
| < PROGRAM USAGE            : (764)((548 Byte  (274 Instruction))+(216Byte when enable signal))        |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */



#ifndef KEYPAD_H
#define	KEYPAD_H

#include "../mega.h"
#if defined  KEYPAD_MODULE
#if KEYPAD_MODULE
/* 
 ---------------------------------------------------------------------------------------------------------
 |                     <   Events Encoded   >                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define   KEYPAD_PRESS_EVENT            (0x00)
#define   KEYPAD_LONGPRESS_EVENT        (0x40)
#define   KEYPAD_REPEAT_EVENT           (0x80)
#define   KEYPAD_RELEASE_EVENT          (0xC0)


/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KEYPAD_PRESS >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KEYPAD_PRESS                                                              |  
 | < @Description       : set or get press key event code of from switch id                              | 
 | < @Param x           : switch id look enum table in keypad.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define KEYPAD_PRESS(x)                 (((x)&(0x3F))|KEYPAD_PRESS_EVENT)
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KEYPAD_LONGPRESS                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KEYPAD_PRESS                                                              |  
 | < @Description       : set or get long press key event code of from switch id                         | 
 | < @Param x           : switch id look enum table in keypad.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define KEYPAD_LONGPRESS(x)             (((x)&(0x3F))|KEYPAD_LONGPRESS_EVENT)
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KEYPAD_REPEAT >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KEYPAD_PRESS                                                              |  
 | < @Description       : set or get repeat key event code of from switch id                             | 
 | < @Param x           : switch id look enum table in keypad.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define KEYPAD_REPEAT(x)                (((x)&(0x3F))|KEYPAD_REPEAT_EVENT)
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KEYPAD_RELEASE >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KEYPAD_RELEASE                                                            |  
 | < @Description       : set or get release key event code of from switch id                            | 
 | < @Param x           : switch id look enum table in keypad.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define KEYPAD_RELEASE(x)               (((x)&(0x3F))|KEYPAD_RELEASE_EVENT)

#define   KEYPAD_NOT_AN_EVENT               (0)

typedef enum {
    /*
     ---------------------------------------------------------------------------------------------------------
     |                    <SWITCH ID  >                                                                      |
     ---------------------------------------------------------------------------------------------------------
     */

    KEYPAD_INVALID_KEY,
    KEYPAD_SW01, KEYPAD_SW02, KEYPAD_SW03, KEYPAD_SW04, KEYPAD_SW05, KEYPAD_SW06, KEYPAD_SW07, KEYPAD_SW08, KEYPAD_SW09,
    KEYPAD_SW10, KEYPAD_SW11, KEYPAD_SW12, KEYPAD_SW13, KEYPAD_SW14, KEYPAD_SW15, KEYPAD_SW16, KEYPAD_SW17, KEYPAD_SW18,
    KEYPAD_SW19, KEYPAD_SW20, KEYPAD_SW21, KEYPAD_SW22, KEYPAD_SW23, KEYPAD_SW24, KEYPAD_SW25, KEYPAD_SW26, KEYPAD_SW27,
    KEYPAD_SW28, KEYPAD_SW29, KEYPAD_SW30, KEYPAD_SW31, KEYPAD_SW32, KEYPAD_SW33, KEYPAD_SW34, KEYPAD_SW35, KEYPAD_SW36,
    KEYPAD_SW37, KEYPAD_SW38, KEYPAD_SW39, KEYPAD_SW40, KEYPAD_SW41, KEYPAD_SW42, KEYPAD_SW43, KEYPAD_SW44, KEYPAD_SW45,
    KEYPAD_SW46, KEYPAD_SW47, KEYPAD_SW48, KEYPAD_SW49, KEYPAD_SW50, KEYPAD_SW51, KEYPAD_SW52, KEYPAD_SW53, KEYPAD_SW54,
    KEYPAD_SW55, KEYPAD_SW56, KEYPAD_SW57, KEYPAD_SW58, KEYPAD_SW59, KEYPAD_SW60, KEYPAD_SW61, KEYPAD_SW62, KEYPAD_SW63,

} KEYPADIDs_t;
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyscan >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyscan                                                                   |  
 | < @Description       : primitive function run every time (ex. 10ms) (user not used)                   | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyscan();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyInit >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyInit                                                                   |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)       | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadGetEvent >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t keypadGetEvent                                                         |  
 | < @Description       : read key event from buffer  (user  used)                                       | 
 | < @return            : key event code                                                                 |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t keypadGetEvent();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadResetEvents >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keypadResetEvents                                                         |  
 | < @Description       : reset keypad with removed all events and remove counters                       |                                                                |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keypadResetEvents();
#if defined (SIGNALGENERATED_MODULE) 
#if (SIGNALGENERATED_MODULE)

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadSignal >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void button buttonSignal                                                       |  
 | < @Description       : Assignment signal to generate fixed signal at press any  switch in keypad      | 
 | < @Param signal      : pointer to signal to generate event with time at buffer is full and            |
 |                      : switch keypad press                                                            |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keypadSignal(const Signal_t *signal);

#endif
#endif



#endif
#endif


#endif	/* KEYPAD_H */

