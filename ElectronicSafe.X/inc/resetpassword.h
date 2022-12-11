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
#ifndef RESETPASSWORD_H
#define	RESETPASSWORD_H

#include "app.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPassword >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ResetPassword                                                           |
 | < @Description       : Read Events From User and set Into Reset Buffer                               |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appResetPassword(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordInit >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appResetPasswordInit                                                    |
 | < @Description       : initialization variables and I/O assignment with default (user not used)      |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appResetPasswordInit(void);

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
uint8_t appResetPasswordState();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appResetPasswordResetState >                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appResetPasswordResetState                                           |
 | < @Description       : go to default case                                                            |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void appResetPasswordResetState();

#endif	/* RESETPASSWORD_H */

