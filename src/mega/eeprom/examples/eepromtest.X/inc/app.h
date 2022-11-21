/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : app.c                                                                    |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 1-Byte                                                                   |
| < PROGRAM USAGE            : 464 Byte  (232 Instruction)                                              |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#ifndef XC_APP_H
#define	XC_APP_H

#include "appRes.h"

/*memory address*/









extern void appMain(void);
extern void appBoot(void);
extern void appInit(void);
extern void appSync(void);



#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_APP_H */

