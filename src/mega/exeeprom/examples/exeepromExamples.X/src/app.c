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
#if EX_EEPROM_MODULE
/*memory test*/
uint8_t memorytestBuffer[10];
uint8_t memoryReadBuffer[10];
volatile uint16_t address;
volatile uint8_t state;

void memTest();
#endif

void appBoot(void) {
#if EX_EEPROM_MODULE
    digitalpinMode(GPIO_E0, MODE_OUTPUT);
    digitalpinMode(GPIO_E1, MODE_OUTPUT);
#endif
}

void appInit(void) {
#if   EX_EEPROM_MODULE
    for (uint8_t i = 0; i < 10; i++) {
        memorytestBuffer[i] = i;
    }
    state = 0;
    address = 0;
#endif
}

void appSync(void) {

}

void appMain(void) {
#if EX_EEPROM_MODULE
    memTest();
#endif
}
#if EX_EEPROM_MODULE

void memTest() {
    switch (state) {
        case 0:
            if (exeepromReady()) {
                state = 1;
            }
            break;
        case 1:
            if (address < 50) {
                exeepromWriteBuffer(address, memorytestBuffer, 10);
                address += 10;
                state = 0;
            } else {
                state = 2;
            }
            break;
        case 2:/*request new data*/
            if (exeepromReady()) {
                exeepromRequestSteram(0x00, 10);
                state = 3;
            }
            break;
        case 3:
            if (exeepromReady()) {
                exEepromRead(memoryReadBuffer);
                state = 4;
            }
            break;
        case 4:
            for (uint8_t i = 0; i < 10; i++) {
                if (memoryReadBuffer[i] == memorytestBuffer[i]) {
                    digitalPinWrite(GPIO_E0, GPIO_TGL); /*success state*/
                } else {
                    digitalPinWrite(GPIO_E1, GPIO_TGL); /*error state*/
                }
            }
            state = 5;
            break;
        case 5:
            break;
        default:
            break;
    }
}

#endif


/*test*/

