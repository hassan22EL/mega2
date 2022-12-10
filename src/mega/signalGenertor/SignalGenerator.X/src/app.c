/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */


#include "../inc/app.h"

/*memory test*/
uint8_t x;
SIGNALS(BUZ, LED, GPIO_A0, 0);
SIGNALS(LED, NullISignal, GPIO_A1, 1);

void appBoot(void) {
    FirstSignal(&BUZ);
}

void appInit(void) {
    x = 0;
}

void appSync(void) {

}

void appMain(void) {
    switch (x) {
        case 0:
            if (!SignalsState(&BUZ)) {
                SignalStart(&BUZ, 200, 80, 2, 5, SIGNAL_SLEEP_WITH_LOW, 2);
                SignalStart(&LED, 100, 80, 3, 10, SIGNAL_SLEEP_WITH_LOW, 3);
                x = 1;
            }
            break;
        case 1:
            break;
    }

}




/*test*/

