
/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : user.c                                                                  |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               : 38 Byte                                                                       |
| < PROGRAM USAGE            :                                                                         |                                      
| < Hardware Usage           : no used                                                                 |
| < File Created             : 07-12-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */
#include "../inc/app.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Macro >                                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 * < @macro   USERPASSWORD_WAITTING                       : Wait more event inputs
 */
#define      USERPASSWORD_WAITTING                             (0)
/*
 * < @macro  USERPASSWORD_IDLE_INICATOR                 : IDlE Case system Aaram
 */
#define      USERPASSWORD_IDLE_INICATOR                        (1)
/*
 * < @macro  USERPASSWORD_ERROR_INICATOR                 : ERROR Case system Aaram
 */
#define      USERPASSWORD_ERROR_INICATOR                       (2)
/*
 * < @macro  USERPASSWORD_SUCESS_INICATOR                 : IDlE Case system Aaram
 */
#define      USERPASSWORD_SUCESS_INICATOR                      (3)
/*
 * < @macro  USER_MATCH_WAIT_OPERATION                 : wait for match function is done
 */
#define      USER_MATCH_WAIT_OPERATION                         (4)

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Variable >                                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 * @var  gu8UserBuf  : temporary buffer store event number to  Password
 */
static uint8_t gu8UserBuf[MAX_PASSWORD_LENGTH];
/*
 * @var  gu8DefaultPassword  : default password when error or forgot password
 */
static uint8_t gu8DefaultPassword[USER_DEFAULT_PASSWORD_LENGTH];
/*
 * @var  eeprom Password  : Read Last password value in eeprom
 */
static uint8_t gu8UserBufRead[MAX_PASSWORD_LENGTH];
/*
 * @var gu8RestPasswordIndex : Write Event in current Index
 */
static volatile uint8_t gu8UserPasswordIndex;
/*
 * @var gu8RestPasswordState : Indictor in Reset Mode or no
 */
static volatile uint8_t gu8UserState;
/*
 * @avr gu8MaxPasswordLength : max value stored from last reset password
 */
static uint8_t gu8MaxPasswordLength;
/*
 * @avr gu8EventState : Indicator the current event set;
 */
static volatile byte_Flags2Bit_t gu8EventState;
/*
 * @var  gsSolSignalTimeOut  : Time out of signal of the solined is done
 */
static stTimer_TimeOut_t gsSolSignalTimeOut;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Definitions >                                   |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserPasswordMatchBuff >                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t appUserPasswordMatchBuff                                              |
 | < @Description       : compare the all values in buffer is equlas or not                             |
 | < @Param readBuf     : first buffer                                                                  |
 | < @Param userbuf     : Data Input From User                                                          |
 | < @return            : 0 data Not matched                                                            |
 |                      : 1 data match                                                                  |                                                                                
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Definition >                                    |
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t appUserPasswordMatchBuff(uint8_t length, uint8_t *buf_one, uint8_t *buf_two);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserReadEvents>                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t appUserReadEvents                                                     |
 | < @Description       : Read Event From Events System                                                 |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void appUserReadEvents(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < apppUserPasswordMatch >                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void appResetPasswordValidtion                                                |
 | < @Description       : Valid Password is min and max data input                                      |  
 | < @Param length      : User Lengh Data                                                               |
 | < @Param readBuf     : password stored in eeprom                                                     |
 | < @Param userbuf     : Data Input From User                                                          |
 | < @Param defaultbuf  : system default password match                                                 | 
 | < @return            : 0 is password is Invaild                                                      |
 |                      : 1 is password is valid                                                        |                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t appUserPasswordMatch(uint8_t length);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserPasswordMatchBuff >                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t appUserPasswordMatchBuff                                              |
 | < @Description       : compare the all values in buffer is equlas or not                             |
 | < @Param readBuf     : first buffer                                                                  |
 | < @Param userbuf     : Data Input From User                                                          |
 | < @return            : 0 data Not matched                                                            |
 |                      : 1 data match                                                                  |                                                                                
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t appUserPasswordMatchBuff(uint8_t length, uint8_t *buf_one, uint8_t *buf_two) {
    for (uint8_t i = 0; i < length; i++) {
        if (buf_one[i] != buf_two[i]) {
            return (0);
        }
    }
    return (1);
}
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Implementions >                                  |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < apppUserPasswordMatch >                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void appResetPasswordValidtion                                                |
 | < @Description       : Valid Password is min and max data input                                      |  
 | < @Param length      : User Lengh Data                                                               |
 | < @return            : 0 is password is Invaild                                                      |
 |                      : 1 is password is valid                                                        |                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t appUserPasswordMatch(uint8_t length) {
    switch (gu8UserState) {
        case 0: /*Read length From EEPROM*/
            if (!eepromIsBusy()) {
                eepromRequestSterm(USER_MAX_PASSWORD_ADDRESS, 1);
                gu8UserState = 1;
            }

            break;
        case 1:/*Match*/
            if (!eepromIsBusy()) {
                eepromRead(&gu8MaxPasswordLength);
                if (length == gu8MaxPasswordLength) {
                    /*go to case 3*/
                    gu8UserState = 3;
                } else if (length == USER_DEFAULT_PASSWORD_LENGTH) {
                    /*go to case 2*/
                    gu8UserState = 2;
                } else {
                    /*error*/
                    gu8UserState = 0;
                    return (USERPASSWORD_ERROR_INICATOR);
                }
            }

            break;
        case 2:
            /*match with default password*/
            gu8UserState = 0;
            if (appUserPasswordMatchBuff(USER_DEFAULT_PASSWORD_LENGTH, gu8UserBuf, gu8DefaultPassword)) {
                gu8UserState = 5;
                InicatorSuccess();
                digitalPinWrite(SOLENOID_PIN, GPIO_HIGH);
                sysSetPeriodS(&gsSolSignalTimeOut, SOL_TIME_WAIT);
            } else {
                return (USERPASSWORD_ERROR_INICATOR);
            }
            break;
        case 3: /*read from last password used*/
            if (!eepromIsBusy()) {
                eepromRequestSterm(USER_PASSWORD_ADDRESS, gu8MaxPasswordLength);
                gu8UserState = 4;
            }
            break;
        case 4: /*Match with last password set*/
            if (!eepromIsBusy()) {
                eepromRead(gu8UserBufRead);
                /*match*/

                if (appUserPasswordMatchBuff(gu8MaxPasswordLength, gu8UserBuf, gu8UserBufRead)) {
                    gu8UserState = 5;
                    InicatorSuccess();
                    digitalPinWrite(SOLENOID_PIN, GPIO_HIGH);
                    sysSetPeriodS(&gsSolSignalTimeOut, SOL_TIME_WAIT);
                } else {
                    return (USERPASSWORD_ERROR_INICATOR);
                }

            }
            break;
        case 5:
            if (sysIsTimeoutS(&gsSolSignalTimeOut) == 0) {
                gu8UserState = 0;
                digitalPinWrite(SOLENOID_PIN, GPIO_LOW);
                return (USERPASSWORD_SUCESS_INICATOR);
            }
        default:
            break;
    }
    return USER_MATCH_WAIT_OPERATION;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserReadEvents>                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t appUserReadEvents                                                     |
 | < @Description       : Read Event From Events System                                                 |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void appUserReadEvents(void) {
    uint8_t EventCode;
    EventCode = appEventsGetCode(0);
    if (EventCode == 0xFF) {
        gu8EventState.b2_3 = 0;
        return;
    }

    if (EventCode == CENCEL_CODE) {
        /*Cancel*/
        gu8UserPasswordIndex = 0;
        /*Indicator Go To Idle Case*/
        /*active Idle state*/
        gu8EventState.b2_3 = 1; /*Idle Case*/
        return;
    }
    if (EventCode == ENTER_CODE) {
        /*active Match state*/
        gu8EventState.b2_3 = 2; /*Enter case*/
        return;
    }
    if (EventCode < CENCEL_CODE) { /*number 0 to 9 */
        /*Store Value*/
        if (gu8UserPasswordIndex < MAX_PASSWORD_LENGTH) {
            gu8UserBuf[gu8UserPasswordIndex] = EventCode;
            /*Indicator write data*/
            InicatorWhenWriteData();
        }
        if (gu8UserPasswordIndex < 255) {
            gu8UserPasswordIndex++;
        }
        /*active wait state*/
        gu8EventState.b2_3 = 3; /*write case*/
        return;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < User Functions Implementions >                                  |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUser >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appUser                                                              |
 | < @Description       : action of user stat                                                           |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void appUser() {
    uint8_t erroraction;
    if (!gu8EventState.B1) {
        appUserReadEvents();
        if (gu8EventState.b2_3 == 1) { /*Cencel*/
            InicatorIDLE();
            gu8EventState.b2_3 = 0;
            gu8EventState.B0 = 1; /*cencel event*/
            return;
        }
        if (gu8EventState.b2_3 == 2) {
            gu8EventState.b2_3 = 0;
            gu8EventState.B1 = 1; /*match*/
        }
    } else {
        erroraction = appUserPasswordMatch(gu8UserPasswordIndex);
        if (erroraction == USERPASSWORD_ERROR_INICATOR) {
            gu8EventState.B1 = 0; /*match*/
            InicatorError();
        } else if (erroraction == USERPASSWORD_SUCESS_INICATOR) {
            gu8EventState.B1 = 0; /*match*/
            gu8EventState.B0 = 1; /*cencel event*/

        }
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserState >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appUserState                                                         |
 | < @Description       : User Mode is active                                                           |                   
 | < @return            : 0 the User mode still worked                                                  |  
 |                      : 1 the User Mode  is done                                                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */
uint8_t appUserState() {
    return gu8EventState.B0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserResetState >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appUserResetState                                                    |
 | < @Description       : go to default case                                                            |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void appUserResetState() {
    gu8EventState.B0 = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserInit >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appUser                                                                 |
 | < @Description       : initialization variables                                                      |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appUserInit() {
    gu8DefaultPassword[0] = 2;
    gu8DefaultPassword[1] = 3;
    gu8DefaultPassword[2] = 1;
    gu8DefaultPassword[3] = 1;
    gu8DefaultPassword[4] = 9;
    gu8MaxPasswordLength = 0;
    gu8UserPasswordIndex = 0;
    gu8EventState.byte = 0;
    gu8UserState = 0;
}