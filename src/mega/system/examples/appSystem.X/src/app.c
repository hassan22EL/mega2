/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */


#include "../inc/app.h"
stTimer_t gsTimerTest;
static volatile uint8_t state;

void testPeriodicTimerUS() {
    switch (state) {
        case 0:
            sysTimerInitUs(&gsTimerTest, 0, 500);
            state = 1;
            break;
        case 1:
            if (sysTimerCheckUs(&gsTimerTest) == 0) {
                digitalPinWrite(GPIO_B0, GPIO_TGL);
            }
            break;
        default:
            break;

    }
}

void testPeriodicTimerMS() {
    switch (state) {
        case 0:
            sysTimerInitMS(&gsTimerTest, 0, 5);
            state = 1;
            break;
        case 1:
            if (sysTimerCheckMs(&gsTimerTest) == 0) {
                digitalPinWrite(GPIO_B0, GPIO_TGL);
            }
            break;
        default:
            break;

    }
}

void appBoot(void) {

}

void appInit(void) {
    digitalpinMode(GPIO_B0, MODE_OUTPUT);
}

void appSync(void) {

}

void appMain(void) {
    switch (state) {
        case 0:
            sysTimerInitS(&gsTimerTest, 0, 1);
            state = 1;
            break;
        case 1:
            if (sysTimerCheckS(&gsTimerTest) == 0) {
                digitalPinWrite(GPIO_B0, GPIO_TGL);
            }
            break;
        default:
            break;

    }
}




/*test*/

