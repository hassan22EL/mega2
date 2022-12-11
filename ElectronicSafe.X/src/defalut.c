/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : defalut.c                                                               |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               : 1-Byte                                                                  |
| < PROGRAM USAGE            :                                                                         |                                      
| < Hardware Usage           : no used                                                                 |
| < File Created             : 07-12-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */
#include "../inc/app.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < macro >                                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 * < @var APP_DEFAULT_MODE : System in Default Mode
 */
#define  APP_DEFAULT_MODE               0x00
/*
 * < @var APP_USER_MODE : System in set Password Mode
 */
#define  APP_USER_MODE                   0x01
/*
 * < @var APP_RESETPASSWORD_MODE : System in Reset  Password Mode
 */
#define  APP_RESETPASSWORD_MODE           0x02

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < variable >                                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 * < @var gu8DefaultState : selcect Mode of the System is Reset Mode Or User Mode Or Default Mode
 */
static volatile uint8_t gu8DefaultState;

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appDefault >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appDefault                                                              |
 | < @Description       : initialization variables                                                      |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appDefaultInit() {
    gu8DefaultState = APP_DEFAULT_MODE;
    appUserInit();
    appResetPasswordInit();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appDefault >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appDefault                                                              |
 | < @Description       : select mode of the system is reset password or user                           |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appDefault() {

    switch (gu8DefaultState) {
        case APP_DEFAULT_MODE:
            if (appEventsGetCode(0) == CENCEL_CODE) {
                gu8DefaultState = APP_USER_MODE;
                return;
            }
            if (buttonGetEvent() == BUTTON_PRESS(BUTTON01)) {
                gu8DefaultState = APP_RESETPASSWORD_MODE;
                return;
            }
            break;
        case APP_USER_MODE:
            appUser();
            if (appUserState()) {
                appUserResetState();
                gu8DefaultState = APP_DEFAULT_MODE;
            }
            break;
        case APP_RESETPASSWORD_MODE:
            appResetPassword();
            if (appResetPasswordState()) {
                appResetPasswordResetState();
                gu8DefaultState = APP_DEFAULT_MODE;
            }
            break;
        default:
            gu8DefaultState = APP_DEFAULT_MODE;
            break;

    }
}