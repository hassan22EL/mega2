/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : app.c                                                                    |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no refence                                                               |
| < SRAM USAGE               : 0 in app and 43 byte in lib                                              |
| < PROGRAM USAGE            :206 Byte in app and lib 2578 Byte (system , signal ,button)               |                                      
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */


#include "../inc/app.h"
#if defined  BUTTON_MODULE
#if BUTTON_MODULE
/*memory test*/
Button(SW1, NullIButton, GPIO_A0, 0x01); /*ena*/
SIGNALS(BUZ, NullISignal, GPIO_A1, 0);


#endif
#endif

void appBoot(void) {
#if defined  BUTTON_MODULE
#if BUTTON_MODULE
    FirstButton(&SW1);
    FirstSignal(&BUZ);
    buttonSignal(&BUZ);
#endif
#endif
}

void appInit(void) {
#if defined  BUTTON_MODULE
#if BUTTON_MODULE
    digitalpinMode(GPIO_A2, MODE_OUTPUT);
#endif
#endif
}

void appSync(void) {

}

void appMain(void) {
#if defined  BUTTON_MODULE
#if BUTTON_MODULE
    uint8_t event;
    event = buttonGetEvent();
    if (event == BUTTON_NOT_AN_EVENT) {
        return;
    }
    if (event == BUTTON_PRESS(BUTTON01)) {
        digitalPinWrite(GPIO_A2, GPIO_TGL);
        return;
    }
    if (event == BUTTON_LONGPRESS(BUTTON01)) {
        digitalPinWrite(GPIO_A2, GPIO_LOW);
        return;
    }

#endif
#endif

}




/*test*/

