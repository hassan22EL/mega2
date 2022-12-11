/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : Indictor.c                                                              |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               : no used any data                                                        |
| < PROGRAM USAGE            :depent in other   calling                                                |                                      
| < Hardware Usage           : no used                                                                 |
| < File Created             : 07-12-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */

#include "../inc/app.h"

SIGNALS(BUZ, LED_R, BUZ_PIN, 0);
SIGNALS(LED_R, LED_G, LED_RED_PIN, 1);
SIGNALS(LED_G, NullISignal, LED_GREEEN_PIN, 2);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Inicator >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void Inicator                                                                 |
 | < @Description       : Start Driver and signals to indicator any action run in boot function         |                   
 | < @return            : void                  |                                                       |      
 --------------------------------------------------------------------------------------------------------
 */
void Inicator() {
    FirstSignal(&BUZ);
    buttonSignal(&BUZ);
    keypadSignal(&BUZ);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < InicatorSucess >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InicatorSucess                                                           |
 | < @Description       : when the reset password is sucess and user set true password the inicate      |                   
 | < @return            : void                                                                          |      
 --------------------------------------------------------------------------------------------------------
 */
void InicatorSuccess() {
    SignalStart(&BUZ, 200, 100, 1, 1, SIGNAL_SLEEP_WITH_LOW, 1);
    SignalStart(&LED_G, 1000, 80, 3, 1, SIGNAL_SLEEP_WITH_LOW, 1);
    SignalStop(&LED_R);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < InicatorError >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InicatorError                                                            |
 | < @Description       : when the reset password is flase and user set flase password the inicate      |                   
 | < @return            : void                                                                          |      
 --------------------------------------------------------------------------------------------------------
 */
void InicatorError() {
    SignalStart(&BUZ, 200, 80, 2, 10, SIGNAL_SLEEP_WITH_LOW, 10);
    SignalStart(&LED_R, 100, 80, 3, 10, SIGNAL_SLEEP_WITH_LOW, SIGNAL_NOT_STOP);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < InicatorIDLE>                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InicatorIDLE                                                             |
 | < @Description       : safe electroin is looked and not any action used                              |                   
 | < @return            : void                                                                          |      
 --------------------------------------------------------------------------------------------------------
 */
void InicatorIDLE() {
    SignalStop(&LED_R);
    SignalStop(&LED_G);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < InicatorWhenWriteData>                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InicatorIDLE                                                             |
 | < @Description       : when write any action the Read Red Indictor is Run                            |                   
 | < @return            : void                                                                          |      
 --------------------------------------------------------------------------------------------------------
 */
void InicatorWhenWriteData() {
    SignalStart(&LED_R, 200, 0, 1, 1, SIGNAL_SLEEP_WITH_HIGH, SIGNAL_NOT_STOP);
}