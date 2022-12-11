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



/*
 ---------------------------------------------------------------------------------------
 |                                <System MODULE>                                      | 
 ---------------------------------------------------------------------------------------
 | <macro F_CPU                  : F_CPU CLOCK  >look clock.h                          |                                        |
 | <macro @N_OF_US_REQUIRED      : each F_CPU has base number of micro                 |
 |                               : select one of number of micro seconds               |
 |                               : _number+us  > is defined and supported time         |  
 | <macro SRAM_USAGE             : 14 Byte                                             |
 | <macro PROGRAM_USAGE          : 694 byte (347 Instruction)                          |
 ---------------------------------------------------------------------------------------
 */
#define     F_CPU                          XTAL_11059200
#define     N_OF_US_REQUIRED               (_1250us)
/*
 ---------------------------------------------------------------------------------------
 |                                <GPIO MODULE>                                        | 
 ---------------------------------------------------------------------------------------
 | < macro GPIO2_PREFER_SPEED     : gpio speed acess                                   |
 |                                : 0 the  function called used                        |
 |                                : 1 the  function not called and used inline         |
 | < macro GPIO2_IOREGS_ABOVEFF   : enable or disable access gpio with in atomic block |
 |                                : 0 gpio acess without atomic                        |
 |                                : 1 gpio acess with in atomic                        |
 |                                : @note : atomic means disable any extrnal interrupt |
 |                                :       : to not effect in gpio pins at write or...  |
 ---------------------------------------------------------------------------------------
 */
#define     GPIO2_PREFER_SPEED               (1)
#define     GPIO2_IOREGS_ABOVEFF             (0)


/*
 ---------------------------------------------------------------------------------------
 |                     < Modules >                                                     |
 ---------------------------------------------------------------------------------------
 | < @ note  :include the res.h from  application                                      |
 ---------------------------------------------------------------------------------------
 */
#include "../../ElectronicSafe.X/inc/res.h"


/*
 ---------------------------------------------------------------------------------------
 |                     < Periodically tasks >                                          |
 ---------------------------------------------------------------------------------------
 | < @PERIODICALLY_TASKS_MAX_TIME: @assume1 task 1 = 5ms , task 2 = 20 ms              |
 |                               : the max time is 20ms becouse 20/5 = Interger value  |
 |                               : and 20ms is Lagrest number                          |
 |                               : @assume2 task 1 = 5ms , task 2 = 7ms the max time   |
 |                               : is 7ms *5ms = 35ms becouse the 35ms can divid by 5,7|
 ---------------------------------------------------------------------------------------
 */
#define      PERIODICALLY_TASKS_MAX_TIME        (10)


#endif


