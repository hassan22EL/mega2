/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */


#include "../inc/app.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < constants >                                                         |
 --------------------------------------------------------------------------------------------------------
 */
Button(ResetButton, NullIButton, BUTTON_RESET_PIN, 0x01);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Functions >                                                         |
 --------------------------------------------------------------------------------------------------------
 */

void appBoot(void) {
    /*used 38 Byte (19 Instruction)*/
    digitalpinMode(SOLENOID_PIN, MODE_OUTPUT);
    FirstButton(&ResetButton);
    Inicator();
}

void appInit(void) {
    appEventsInit();
    appDefaultInit();
}

void appSync(void) {

}

void appMain(void) {
    appEvents();
    appDefault();
}




/*test*/

