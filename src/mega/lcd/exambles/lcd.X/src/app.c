/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on 25 ??????, 2021, 10:06 ?
 */


#include "../inc/app.h"
static uint8_t state;
static uint8_t index;
void updateProgressBar(uint8_t count, uint8_t totalCount, uint8_t lineToPrintOn);

void appBoot(void) {

}

void appInit(void) {

}

void appSync(void) {

}

void appMain(void) {
    if (!state) {

        state = 1;
    }
    if (index < 100) {
        lcdwrite(0, 0, "Test..");
        updateProgressBar(index, 100, 1);
        index++;
        _delay_ms(10);
    }
}

void updateProgressBar(uint8_t count, uint8_t totalCount, uint8_t lineToPrintOn) {
    float factor;
    uint8_t percent;
    uint8_t number;
    uint8_t remainder;
    factor = totalCount / (float) (LCD_NUMBER_OF_BYTE * 5); //See note above!
    percent = (count + 1) / factor;
    number = percent / 5;
    remainder = percent % 5;
    if (number > 0) {
        for (uint8_t j = 0; j < number; j++) {
            lcdwriteCGRAM(lineToPrintOn, j, 5);
        }
    }
    lcdwriteCGRAM(lineToPrintOn, number, remainder);
    if (number < LCD_NUMBER_OF_BYTE) {
        for (uint8_t j = number + 1; j <= LCD_NUMBER_OF_BYTE; j++) {
            lcdwriteCGRAM(lineToPrintOn, j, 0);
        }
    }
}

/*test*/

