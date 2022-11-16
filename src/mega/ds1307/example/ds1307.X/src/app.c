/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */




#include <stdint-gcc.h>

#include "../inc/app.h"

volatile uint8_t state;

void appBoot(void) {

}

void appInit(void) {
    state = 0;
    digitalpinMode(GPIO_E0 , MODE_OUTPUT);
}

void appSync(void) {

}

void appMain(void) {
    tm_t time;
    switch (state) {
        case 0:
            time.tm_hour = 12;
            time.tm_min = 5;
            time.tm_sec = 0;
            time.tm_wday = SUNDAY;
            time.tm_mday = 3;
            time.tm_mon = JANUARY;
            time.tm_year = 22;
            ds1307SetDate(&time);
            state = 1;
            break;
        case 1:
            if (!ds1307IsSetDone()) {
                state = 2;
            }
            break;
        case 2:
            digitalPinWrite(GPIO_E0, GPIO_TGL);
            break;
        default:
            break;

    }
}