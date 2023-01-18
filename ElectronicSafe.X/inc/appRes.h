/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : appRes.h                                                             |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : header file                                                       |
| < PROGRAM USAGE            : header file                                                       |                                      
| < Hardware Usage           : header file                                                       |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#ifndef XC_RES_H
#define	XC_RES_H
#include "../../mega2.X/inc/mega.h"

/*
 * < @macro SOL_TIME_WAIT         : door open time per second
 */
#define SOL_TIME_WAIT             (5)

/*
 * < @macro Button_RESET_PIN         : reset password button access from gpio
 */
#define BUTTON_RESET_PIN               GPIO_B5
/*
 *< @macro LED_GREEEN_PIN            : GPIO access open door indicator 
 */
#define  LED_GREEEN_PIN                GPIO_C2
/*
 * < @macro LED_RED_PIN              : GPIO access close door indicator 
 */
#define  LED_RED_PIN                   GPIO_B1
/*
 * < @macro SOLENOID_PIN             : GPIO access to control door 
 */
#define  SOLENOID_PIN                  GPIO_C0
/*
 * < @macro BUZ_PIN                 : GPIO access to generate SOUND 
 */
#define  BUZ_PIN                      GPIO_C1

/*
 * @macro  PASSWORD_LENGTH            : number of char per single password
 */
#define   MAX_PASSWORD_LENGTH               (10)
/*
 * @macro  PASSWORD_LENGTH            : number of char per single password
 */
#define   MIN_PASSWORD_LENGTH               (4)
/*
 * @macro USER_DEFAULT_PASSWORD_LENGTH   : default password length
 */
#define   USER_DEFAULT_PASSWORD_LENGTH            (5)

/*
 * @macro USER_MAX_PASSWORD_ADDRESS   : Last max password reset
 */
#define   USER_MAX_PASSWORD_ADDRESS         (0x0000)
/*
 * @macro USER_PASSWORD_ADDRESS   : Start address of the Max Byte */
#define   USER_PASSWORD_ADDRESS             (0x0001)



#endif	/* XC_HEADER_TEMPLATE_H */

