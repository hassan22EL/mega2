/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : resetpassword.h                                                         |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               :                                                                         |
| < PROGRAM USAGE            :                                                                         |                                      
| < Hardware Usage           : no used                                                                 |
| < File Created             : 07-12-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */

#include "../inc/app.h"

/*
--------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                     | 
--------------------------------------------------------------------------------------------------------
| < FILE                     : events.c                                                                |                                  
| < Author                   : Hassan Elsaied                                                          |
| < Version                  : Mega2v241022                                                            |
| < Refences                 : no refence                                                              |
| < SRAM USAGE               :                                                                         |
| < PROGRAM USAGE            :                                                                         |                                      
| < Hardware Usage           : no used                                                                 |
| < File Created             : 07-12-2022                                                              |
--------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Macro >                                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 * < @macro  RESTPASSWORD_WAITTING                       : Wait more event inputs
 */
#define      RESTPASSWORD_WAITTING                             (0)
/*
 * < @macro  RESTPASSWORD_IDLE_INICATOR                 : IDlE Case system Aaram
 */
#define      RESTPASSWORD_IDLE_INICATOR                        (1)
/*
 * < @macro  RESTPASSWORD_ERROR_INICATOR                 : ERROR Case system Aaram
 */
#define      RESTPASSWORD_ERROR_INICATOR                       (2)
/*
 * < @macro  RESTPASSWORD_SUCESS_INICATOR                 : IDlE Case system Aaram
 */
#define      RESTPASSWORD_SUCESS_INICATOR                      (3)
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Variable >                                                         |
 --------------------------------------------------------------------------------------------------------
 */
/*
 * @var  gu8ResetPasswordBuf  : temporary buffer store event number to new Password
 */
static uint8_t gu8ResetPasswordBuf[MAX_PASSWORD_LENGTH];

/*
 * @var gu8RestPasswordIndex : Write Event in current Index
 */
static uint8_t gu8RestPasswordIndex;
/*
 * @var gu8RestPasswordState : Indictor in Reset Mode or no
 */
static volatile byte_Flags2Bit_t gu8RestPasswordState;
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Definitions >                                   |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordValidtion >                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void appResetPasswordValidtion                                                |
 | < @Description       : Valid Password is min and max data input                                      |                   
 | < @return            : 0 is password is Invaild                                                      |
 |                      : 1 is password is valid                                                        |                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static inline uint8_t appResetPasswordValidtion(uint8_t Index);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordReadEvents>                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t appResetPasswordReadEvents                                            |
 | < @Description       : Read Event From Events System                                                 |                   
 | < @return            : RESTPASSWORD_WAITTING        : still reading events                           |
 |                      : RESTPASSWORD_IDLE_INICATOR   : cencel state action                            |
 |                      : RESTPASSWORD_SUCESS_INICATOR : Reset Password is success                      |    
 |                      : RESTPASSWORD_ERROR_INICATOR  : Reset Password have some errors                |
 --------------------------------------------------------------------------------------------------------
 */
static inline uint8_t appResetPasswordReadEvents(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordSave >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void appResetPasswordSave                                                     |
 | < @Description       : save current Index and current buffer In EEPROM                               |                   
 | < @return            : 1 is password is saved                                                        |
 |                      : 0 is password is running                                                       |                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static inline uint8_t appResetPasswordSave();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions Implementions >                                  |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordValidtion >                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void appResetPasswordValidtion                                                |
 | < @Description       : Valid Password is min and max data input                                      |                   
 | < @return            : 0 is password is Invaild                                                      |
 |                      : 1 is password is valid                                                        |                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */

static inline uint8_t appResetPasswordValidtion(uint8_t Index) {
    if (Index > MAX_PASSWORD_LENGTH || Index < MIN_PASSWORD_LENGTH) {
        return (0);
    }
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordReadEvents>                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t appResetPasswordReadEvents                                            |
 | < @Description       : Read Event From Events System                                                 |                   
 | < @return            : RESTPASSWORD_WAITTING        : still reading events                           |
 |                      : RESTPASSWORD_IDLE_INICATOR   : cencel state action                            |
 |                      : RESTPASSWORD_SUCESS_INICATOR : Reset Password is success                      |    
 |                      : RESTPASSWORD_ERROR_INICATOR  : Reset Password have some errors                |
 --------------------------------------------------------------------------------------------------------
 */
static inline uint8_t appResetPasswordReadEvents(void) {
    uint8_t EventCode;
    EventCode = appEventsGetCode(0);
    if (EventCode == 0xFF) {
        return (RESTPASSWORD_WAITTING);
    }
    if (EventCode == CENCEL_CODE) {
        /*Cancel*/
        gu8RestPasswordIndex = 0;
        /*Indicator Go To Idle Case*/
        return (RESTPASSWORD_IDLE_INICATOR);
    }
    if (EventCode == ENTER_CODE) {
        /*save In EEPROM*/
        if (appResetPasswordValidtion(gu8RestPasswordIndex))
            return (RESTPASSWORD_SUCESS_INICATOR);

        /*Indicator Go To error Case*/
        gu8RestPasswordIndex = 0;
        return (RESTPASSWORD_ERROR_INICATOR);
    }
    if (EventCode < CENCEL_CODE) { /*number 0 to 9 */
        /*Store Value*/
        if (gu8RestPasswordIndex < MAX_PASSWORD_LENGTH) {
            gu8ResetPasswordBuf[gu8RestPasswordIndex] = EventCode;
            /*Indicator write data*/
            InicatorWhenWriteData();
        }
        if (gu8RestPasswordIndex < 255) {
            gu8RestPasswordIndex++;
        }
        return (RESTPASSWORD_WAITTING);
    }
    return (RESTPASSWORD_WAITTING);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordSave >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void appResetPasswordSave                                                     |
 | < @Description       : save current Index and current buffer In EEPROM                               |                   
 | < @return            : 1 is password is saved                                                        |
 |                      : 0 is password is running                                                       |                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static inline uint8_t appResetPasswordSave() {

    switch (gu8RestPasswordState.b4_5) {
        case 0: /*check busy*/
            if (!eepromIsBusy()) {
                eepromWriteBuf(USER_PASSWORD_ADDRESS, gu8RestPasswordIndex, gu8ResetPasswordBuf);
                gu8RestPasswordState.b4_5 = 1;
            }
            break;
        case 1: /*save Max Index*/
            if (!eepromIsBusy()) {
                eepromWriteBuf(USER_MAX_PASSWORD_ADDRESS, 1, &gu8RestPasswordIndex);
                gu8RestPasswordState.b4_5 = 2;
            }
            break;
        case 2: /*password saving*/
            if (!eepromIsBusy()) {
                gu8RestPasswordIndex = 0;
                for (uint8_t i = 0; i < MAX_PASSWORD_LENGTH; i++) {
                    gu8ResetPasswordBuf[i] = 0x00;
                }
                gu8RestPasswordState.b4_5 = 0;
                return (1);
            }
            break;
        default:
            break;

    }
    return (0);
}
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < User Functions Implementions >                                  |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPassword >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ResetPassword                                                           |
 | < @Description       : Read Events From User and set Into Reset Buffer and store new password        |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appResetPassword(void) {
    uint8_t Indicate;
    /*
     * read reset switch 
     * if reset switch is press go to read keypad event from event
     */
    if (!gu8RestPasswordState.B0) { /*read keypad events*/
        Indicate = appResetPasswordReadEvents();
        if (Indicate == RESTPASSWORD_IDLE_INICATOR) {
            /*Indictor with IDLE*/
            InicatorIDLE();
            gu8RestPasswordState.B1 = 1;

        } else if (Indicate == RESTPASSWORD_SUCESS_INICATOR) {
            gu8RestPasswordState.B0 = 1;
        } else if (Indicate == RESTPASSWORD_ERROR_INICATOR) {
            /*Indictor with error*/
            InicatorError();
            gu8RestPasswordIndex = 0;
            for (uint8_t i = 0; i < MAX_PASSWORD_LENGTH; i++) {
                gu8ResetPasswordBuf[i] = 0x00;
            }
        }
    } else {/*save data in EEPROM*/
        if (appResetPasswordSave()) {
            /*Indictor with success*/
            gu8RestPasswordState.B1 = 1;
            gu8RestPasswordState.B0 = 0;
            InicatorSuccess();
            return;
        }
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordInit >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appResetPasswordInit                                                    |
 | < @Description       : initialization variables and I/O assignment with default (user not used)      |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appResetPasswordInit(void) {
    for (uint8_t i = 0; i < MAX_PASSWORD_LENGTH; i++) {
        gu8ResetPasswordBuf[i] = 0x00; /*clear password*/
    }
    gu8RestPasswordState.byte = 0; /*Read Switch*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordState >                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appResetPasswordStart                                                |
 | < @Description       : Reset Password Mode is active                                                 |                   
 | < @return            : 0 the Reset password still worked                                             |  
 |                      : 1 the reset password is done                                                  |                                                             
 --------------------------------------------------------------------------------------------------------
 */
uint8_t appResetPasswordState() {
    return gu8RestPasswordState.B1;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordResetState >                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appResetPasswordResetState                                           |
 | < @Description       : go to default case                                                            |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
inline void appResetPasswordResetState() {
    gu8RestPasswordState.B1 = 0;
}