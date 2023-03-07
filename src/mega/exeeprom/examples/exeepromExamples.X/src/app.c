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
uint8_t memoryReadBuffer[32];
volatile uint8_t gu8MemIndex;
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
    for (uint8_t i = 0; i < 32; i++) {
        memoryReadBuffer[i] = 0x00;
    }
#endif
}

void appSync(void) {

}

void appMain(void) {
#if EX_EEPROM_MODULE
    if (state == 0) {
        memTest();
    } else {
        return;
    }


#endif
}
#if EX_EEPROM_MODULE

void memTest() {
    memAddresst_t address;
    if (exeepromReady()) {
        if (gu8MemIndex == 255) {
            gu8MemIndex = 0;
            memoryReadBuffer[0] = 23;
            memoryReadBuffer[1] = 11;
            memoryReadBuffer[2] = 96;
            exeepromWriteBuffer(0, memoryReadBuffer, 3);
            state = 1;
            return;
        }
        address = gu8MemIndex << 5;
        exeepromWriteBuffer(address, memoryReadBuffer, 32);
        gu8MemIndex++;
    }
}

#endif


/*test*/

