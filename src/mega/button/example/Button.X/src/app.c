/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */


#include "../inc/app.h"
#if defined  BUTTON_MODULE
#if BUTTON_MODULE
/*memory test*/
Button(SW1, NullIButton, GPIO_A0, 0x01); /*ena*/
#endif
#endif

void appBoot(void) {
#if defined  BUTTON_MODULE
#if BUTTON_MODULE
    FirstButton(&SW1);
#endif
#endif
}

void appInit(void) {
#if defined  BUTTON_MODULE
#if BUTTON_MODULE
    digitalpinMode(GPIO_A1, MODE_OUTPUT);
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
        digitalPinWrite(GPIO_A1, GPIO_TGL);
        return;
    }
    if (event == BUTTON_LONGPRESS(BUTTON01)) {
        digitalPinWrite(GPIO_A1, GPIO_LOW);
        return;
    }

#endif
#endif

}




/*test*/

