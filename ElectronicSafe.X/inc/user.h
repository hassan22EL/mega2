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
#ifndef USER_H
#define	USER_H
#include "app.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserInit >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  appUser                                                                 |
 | < @Description       : initialization variables                                                      |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void appUserInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUser >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appUser                                                              |
 | < @Description       : action of user stat                                                           |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void appUser();

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
uint8_t appUserState();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < appUserResetState >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  appUserResetState                                                    |
 | < @Description       : go to default case                                                            |                   
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void appUserResetState();

#endif	/* USER_H */

