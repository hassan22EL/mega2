/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   resource.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   no-used
 * Program Space:   no-used
 * Version      :   Mega2v241022
 * Start Data   :   25-10-2022  20:15:00
 * End Data     :   25-10-2022  20:30:00
 * Work Time    :   15-min
 * Comments     :   no comment
 *  
 */
#ifndef XC_RESOURCE_H
#define	XC_RESOURCE_H

#include "mega.h"
#include "resource.h"



/*
---------------------------------------------------------------------------------------
|                                System MODULE                                        | 
---------------------------------------------------------------------------------------
| < F_CPU                  : F_CPU CLOCK  >look clock.h                               |                                        |
| < N_OF_US_REQUIRED       : each F_CPU has base number of micro                      |
|                          : select one of number of micro seconds                    |
|                          : _number+us  > is defined and supported time              |  
| < SRAM_USAGE             : 14 Byte                                                  |
| < PROGRAM_USAGE          : 634 byte (317 Instruction)                               |
---------------------------------------------------------------------------------------
 */
#define     F_CPU                       XTAL_11059200
#define     N_OF_US_REQUIRED               (_1250us)


/*
 ****************************************************
 *                    Modules                       *
 * **************************************************
 */
//add  include the res.h in application 


#include "../../mega2.X/src/mega/exeeprom/examples/exeepromExamples.X/inc/res.h"

#endif


