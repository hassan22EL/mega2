/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : app.h                                                                    |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 21-Byte                                                                  |
| < PROGRAM USAGE            : 428 Byte  (0 Instruction)                                                  |                                    
| < Hardware Usage           : Internal eeprom Modeule                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */
#include "../inc/app.h"
#if EEPROM_MODULE
uint8_t eepromWritedata[10];
uint8_t eepromReaddata[10];
volatile uint8_t state;
#endif

void appBoot(void) {
#if EEPROM_MODULE
    digitalpinMode(GPIO_D0, MODE_OUTPUT);
    digitalpinMode(GPIO_D1, MODE_OUTPUT);
#endif
}

void appInit(void) {
#if EEPROM_MODULE
    for (uint8_t i = 0; i < 10; i++)
        eepromWritedata[i] = i + 2;
#endif
}

void appSync(void) {

}

void appMain(void) {
#if EEPROM_MODULE
    switch (state) {
        case 0:/*write state*/
            if (!eepromIsBusy()) {
                eepromWriteBuf(0x01, 10, eepromWritedata);
                state = 1;
            }
            break;
        case 1:/*assignment read state*/
            if (!eepromIsBusy()) {
                eepromRequestSterm(0x01, 10);
                state = 2;
            }
            break;
        case 2:
            if (!eepromIsBusy()) {
                /*read operation is Ready*/
                eepromRead(eepromReaddata);
                /*compare to buffer*/
                state = 3;
            }
            break;
        case 3:
            /*compare two buffer */
            for (uint8_t i = 0; i < 10; i++) {
                if (eepromReaddata[i] == eepromWritedata[i]) {
                    digitalPinWrite(GPIO_D0, GPIO_TGL); /*success case */
                } else {
                    digitalPinWrite(GPIO_D1, GPIO_TGL); /*error case*/
                }
            }
            state = 4;
            break;
        case 4:/*wait state*/
            break;
        default:
            break;
    }
#endif
}




/*test*/

