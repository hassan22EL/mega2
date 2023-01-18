/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : events.c                                                                |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               : 2-Byte                                                                  |
| < PROGRAM USAGE            : 334 Byte   (167 Instruction)                                            |                                      
| < Hardware Usage           : no used                                                                 |
| < File Created             : 07-12-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */
#include "../inc/app.h"

/*
--------------------------------------------------------------------------------------------------------
|                           <Macro>                                                     | 
--------------------------------------------------------------------------------------------------------
 */

/*
 * <macro     KEY_00_CODE                      : get event code and encode with number 0 (0x00)
 */
#define       KEY_00_CODE                        KEYPAD_SW11                     
/*
 * <macro     KEY_01_CODE                      : get event code and encode with number 1 (0x01)
 */
#define       KEY_01_CODE                        KEYPAD_SW01
/*
 * <macro     KEY_02_CODE                      : get event code and encode with number 2 (0x02)
 */
#define       KEY_02_CODE                        KEYPAD_SW02                   
/*
 * <macro     KEY_03_CODE                      : get event code and encode with number 3 (0x03)
 */
#define       KEY_03_CODE                        KEYPAD_SW03
/*
 * <macro     KEY_04_CODE                      : get event code and encode with number 4 (0x04)
 */
#define       KEY_04_CODE                        KEYPAD_SW04                     
/*
 * <macro     KEY_05_CODE                      : get event code and encode with number 5 (0x05)
 */
#define       KEY_05_CODE                        KEYPAD_SW05
/*
 * <macro     KEY_06_CODE                      : get event code and encode with number 6 (0x06)
 */
#define       KEY_06_CODE                        KEYPAD_SW06                  
/*
 * <macro     KEY_07_CODE                      : get event code and encode with number 7 (0x07)
 */
#define       KEY_07_CODE                        KEYPAD_SW07
/*
 * <macro     KEY_08_CODE                      : get event code and encode with number 8 (0x08)
 */
#define       KEY_08_CODE                        KEYPAD_SW08
/*
 * <macro     KEY_09_CODE                      : get event code and encode with number 8 (0x09)
 */
#define       KEY_09_CODE                        KEYPAD_SW09
/*
 * <macro     KEY_CANCEL_CODE                  : get event code and encode with char * (CENCEL) (0x0A)
 */
#define       KEY_CANCEL_CODE                     KEYPAD_SW10
/*
 * <macro     KEY_ENTER_CODE                  : get event code and encode with char # (ENTER) (0x0B)
 */
#define       KEY_ENTER_CODE                     KEYPAD_SW12

/*
--------------------------------------------------------------------------------------------------------
|                           <Variable>                                                                 | 
--------------------------------------------------------------------------------------------------------
 */
/*
 * < @var : gu8EventCode    : number to store into buffer or action
 */
static volatile uint8_t gu8EventCode;
/*
 * < @var : gu8EventListeners : each listener assign one bit in byte 0 to 7 listener 
 *                            : when new event generated the Inform Listeners to set 1's into 
 *                            : listeners byte and this value chack have a new event when lisener is read
 *                            : event clear the bit by lisener number 
 */
static volatile uint8_t gu8EventListeners;
/*
--------------------------------------------------------------------------------------------------------
|                           <Functions>                                                                | 
--------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appEventsInit >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appEventsInit                                                           |
 | < @Description       : initialization Event Code with no Code (0xFF) and initialization other        |
 |                      : Variable with default values                                                  |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appEventsInit(void) {
    gu8EventCode = 0xFF;
    gu8EventListeners = 0x00; /*default case all listeners is listen event */
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appEvents >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appEvents                                                               |
 | < @Description       : Read Event and assignment Code                                                |                                              |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appEvents(void) {
    uint8_t u8Event;
    u8Event = keypadGetEvent(); /*read current event*/
    if (u8Event == KEYPAD_NOT_AN_EVENT)/*check no event assignment*/
        return;
    if (u8Event == KEYPAD_PRESS(KEY_00_CODE)) {/*number 0 is Pressed*/
        gu8EventCode = 0x00;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_01_CODE)) {/*number 1 is Pressed*/
        gu8EventCode = 0x01;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_02_CODE)) {/*number 2 is Pressed*/
        gu8EventCode = 0x02;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_03_CODE)) {/*number 3 is Pressed*/
        gu8EventCode = 0x03;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_04_CODE)) {/*number 4 is Pressed*/
        gu8EventCode = 0x04;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_05_CODE)) {/*number 5 is Pressed*/
        gu8EventCode = 0x05;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_06_CODE)) {/*number 6 is Pressed*/
        gu8EventCode = 0x06;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_07_CODE)) {/*number 7 is Pressed*/
        gu8EventCode = 0x07;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_08_CODE)) {/*number 8 is Pressed*/
        gu8EventCode = 0x08;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

    if (u8Event == KEYPAD_PRESS(KEY_09_CODE)) {/*number 9 is Pressed*/
        gu8EventCode = 0x09;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }
    if (u8Event == KEYPAD_PRESS(KEY_CANCEL_CODE)) {/*char * is Pressed*/
        gu8EventCode = 0x0A;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }
    if (u8Event == KEYPAD_PRESS(KEY_ENTER_CODE)) {/*char # is Pressed*/
        gu8EventCode = 0x0B;
        gu8EventListeners = 0xFF; /*inform all listeners have new Event Generated*/
        return;
    }

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appEventsGetCode >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function               : uint8_t  appEventsGetCode                                                |
 | < @Description            :  get new code                                                            |   
 | < @ Param Listener_Number : 0 to 8 supported in this current                                         |                   
 | < @return                 : 0xFF when the current read is lisen data befor                           |
 |                           : event code when the first read event                                     |                                                                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */
uint8_t appEventsGetCode(uint8_t Listener_Number) {
    if (BitCheck(gu8EventListeners, Listener_Number)) {
        bitClear(gu8EventListeners, Listener_Number);
        return (gu8EventCode);
    }
    return (0xFF);
}