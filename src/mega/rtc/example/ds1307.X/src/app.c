/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */


#include <stdint-gcc.h>

#include "../inc/app.h"
stm_t date;
uint8_t state;
void appBoot(void) {

}

void appInit(void) {
    date.sec = 0;
    date.min = 0;
    date.hour = 12;
    date.dayw = 1;
    date.daym = 11;
    date.month = 11;
    date.year = 22;
}

void appSync(void) {

}

void appMain(void) {
    if(!state && !ds1307IsSetDone()) {
        ds1307SetDate(&date);
        state = 1;
    }
}




/*test*/

