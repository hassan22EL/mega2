/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : resource.h                                                       |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : header file                                                       |
| < PROGRAM USAGE            : header file                                                       |                                      
| < Hardware Usage           : header file                                                       |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#ifndef XC_RESOURCE_H
#define	XC_RESOURCE_H

#include "mega.h"
#include "resource.h"



/*
---------------------------------------------------------------------------------------
|                                <System MODULE>                                      | 
---------------------------------------------------------------------------------------
| <macro F_CPU                  : F_CPU CLOCK  >look clock.h                          |                                        |
| <macro @N_OF_US_REQUIRED      : each F_CPU has base number of micro                 |
|                               : select one of number of micro seconds               |
|                               : _number+us  > is defined and supported time         |  
| <macro SRAM_USAGE             : 13 Byte                                             |
| <macro PROGRAM_USAGE          : 678 byte (339 Instruction)                          |
---------------------------------------------------------------------------------------
 */
#define     F_CPU                       XTAL_11059200
#define     N_OF_US_REQUIRED               (_1250us)


/*
 ---------------------------------------------------------------------------------------
 |                    Modules                                                          |
 ---------------------------------------------------------------------------------------
 | < @ note  :include the res.h from  application                                      |
 ---------------------------------------------------------------------------------------
 */
 
#include "../../NurseMaster.X/inc/res.h"

#endif


