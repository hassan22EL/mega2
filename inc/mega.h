/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : mega.h                                                            |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : header file                                                       |
| < PROGRAM USAGE            : header file                                                       |                                      
| < Hardware Usage           : header file                                                       |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#ifndef XC_MEGA_H
#define	XC_MEGA_H
//#include <xc.h> /*xc compiler*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "mega/clock.h"
#include "mega/buffers.h"
#include "resource.h"
#include "mega/macros.h"
#include "mega/bootloadercmd.h"
#include "mega/types.h"


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

/*Modules*/
#include "mega/gpio.h"
#include "mega/system.h"
#include "mega/time.h"
#include "mega/usart.h"
#include "mega/lcd.h"
#include "mega/twi.h"
#include "mega/exEprom.h"
#include "mega/ds1307.h"
#include "mega/csma.h"
#include "mega/lcdmenu.h"
#include "mega/eeprom.h"
#include "mega/signalGenerator.h"
#include "mega/keypad.h"
#include "mega/button.h"
extern int main(void);
// Application Functions
extern void appMain(void);
extern void appBoot(void);
extern void appInit(void);
extern void appSync(void);

#endif	/* XC_MEGA_H */

