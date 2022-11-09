/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */


#include "../inc/app.h"

/*memory test*/
uint8_t memorytestBuffer[10];
volatile uint16_t address;
volatile uint8_t state;

void memTest();
void appBoot(void) {
 
}

void appInit(void) {
    for (uint8_t i = 0; i < 10; i++) {
        memorytestBuffer[i] = i;
    }
    state = 0;
    address = 0;

}

void appSync(void) {

}

void appMain(void) {
 memTest();
}


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
        case 2:
            break;
        default:
            break;
    }
}




/*test*/

