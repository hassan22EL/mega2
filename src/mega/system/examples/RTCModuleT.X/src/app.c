/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : app.h                                                                    |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 22-Byte                                                                  |
| < PROGRAM USAGE            : 388 Byte  (0 Instruction)                                                |                                    
| < Hardware Usage           : External eeprom Modeule                                                  |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */



#include <stdint-gcc.h>

#include "../inc/app.h"

tm_t DataTime;
uint8_t buf[PRINT_BUF_TIME_lENGTH];
uint8_t bufDate[PRINT_BUF_DATE_lENGTH];

void appBoot(void) {

}

void appInit(void) {

}

void appSync(void) {

}

void appMain(void) {
    if (systemSecondEvent()) {
        DateTimeFromTimeStamp(&DataTime, systemNow()); /*336*/
        PrintTime(&DataTime, buf);
        PrintDate(&DataTime, bufDate);
        lcdwritebuf(0, LCD_TEXT_CENTER, buf, PRINT_BUF_TIME_lENGTH);
        lcdwritebuf(1, LCD_TEXT_CENTER, bufDate, PRINT_BUF_DATE_lENGTH);
        lcdUpdateNow();
    }
}


/*test*/

