

#include "../inc/appRes.h"

static uint8_t gbufLCDIndexed[7] = {10, 7, 4, 17, 21, 24, 30};
static uint8_t DateTimeIndexValid[7] = {59, 59, 23, 6, 31, 11, 99};
/*
 * @var  gstDataTime : edit the data into this buffer
 */
static tm_t gstDataTime;
/*
 * < @var time Index Value
 */
static int8_t gu8TimeIndexValue;
/*
 * <@var Callback State have a three state 0 is assignment callbacks , 1 show current time  , 1 stop update tiem
 */
static uint8_t gu8SystemTimeState;
/*
 * <@var LCD Blinking Index
 */
static uint8_t gu8LCDBlink;
/*
 --------------------------------------------------------------------------------------------------------
 |                            < ShowEditTime  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  ShowEditTime                                                   |
 | < @Description       : show Time In System Menu                                                      |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ShowEditTime(uint8_t T);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyNumbersEvents  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyNumbersEvents                                                  |
 | < @Description       : key Numbers Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyNumbersEvents(uint8_t s);

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyCencelEvents  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyCencelEvents                                                               |
 | < @Description       : key Cencel Events   Handler                                                   |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyCencelEvents();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyEnterEvents  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyEnterEvents                                                               |
 | < @Description       : key Enter Events   Handler                                                   |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyEnterEvents();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF1Events  >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF1Events                                                                   |
 | < @Description       : key F1 Events   Handler                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyF1Events();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF2Events  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF2Events                                                  |
 | < @Description       : key F2 Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyF2Events();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF3Events  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF3Events                                                                   |
 | < @Description       : key F2 Events   Handler                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyF3Events();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ShowEditTime(uint8_t T) {

    uint8_t SystemTimeBuf[PRINT_BUF_TIME_lENGTH];
    uint8_t SystemDateBuf[PRINT_BUF_DATE_lENGTH];
    uint8_t Index;
    PrintTime(&gstDataTime, SystemTimeBuf);
    PrintDate(&gstDataTime, SystemDateBuf);
    lcdClear();
    lcdwritebuf(0, 4, SystemTimeBuf, PRINT_BUF_TIME_lENGTH);
    lcdwritebuf(1, 1, SystemDateBuf, PRINT_BUF_DATE_lENGTH);
    if (T) {
        gu8LCDBlink ^= 1;
        Index = gbufLCDIndexed[gu8TimeIndexValue];
        lcdBlink(Index / LCD_NUMBER_OF_BYTE, (Index % LCD_NUMBER_OF_BYTE) + gu8LCDBlink);
    } else {
        lcdNoBlink();
    }
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < TimeCallBack  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  TimeCallBack                                                   |
 | < @Description       : run in menu system driver                                                      |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemTimeCallBack() {
    /*Register Callback Function and go to to wait state*/
    if (gu8SystemTimeState == 0) {
        CommanEventHandles(keyNumbersEvents);
        CommanEventFunctions(keyF1Events, keyF2Events, keyF3Events, keyEnterEvents, keyCencelEvents);
        gu8SystemTimeState = 1;
    }

    if (gu8SystemTimeState == 1) {
        if (!systemSecondEvent())
            return (0);
        DateTimeFromTimeStamp(&gstDataTime, systemNow());
        ShowEditTime(0);
        return (0);
    }

    if (gu8SystemTimeState == 2) {
        return (0); /*wait state*/
    }

    if (gu8SystemTimeState == 3) {
        ReturnMenuCallBack();
        gu8SystemTimeState = 0;
        gu8TimeIndexValue = -1;

        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < SystemTimeInit  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemTimeInit                                                           |
 | < @Description       : system time is reset values to default values                                 |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void SystemTimeInit() {
    gu8TimeIndexValue = -1;
    gu8SystemTimeState = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyNumbersEvents  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyNumbersEvents                                                  |
 | < @Description       : key Numbers Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t s3[2];

static void keyNumbersEvents(uint8_t s) {
    if ((gu8TimeIndexValue == -1) || (gu8TimeIndexValue == 3) || (gu8TimeIndexValue == 5))
        return;
    uint8_t *Date; /*0 hour , min*/
    uint8_t Byte;
    uint8_t Valid;
    uint8_t s2[3];
    Date = (uint8_t *) &(gstDataTime.tm_sec);
    Byte = *(Date + gu8TimeIndexValue);
    print2d(Byte, s2, 0);
    s2[gu8LCDBlink] = s;
    Byte = conv2d(s2);
    Valid = (DateTimeIndexValid[gu8TimeIndexValue]);
    if (Byte <= Valid) {
        *(Date + gu8TimeIndexValue) = Byte;
        ShowEditTime(1);
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyCencelEvents  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyCencelEvents                                                  |
 | < @Description       : key Cencel Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyCencelEvents() {
    gu8SystemTimeState = 3;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF1Events  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF1Events                                                  |
 | < @Description       : key F1 Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyF1Events() {
    /*lcd blink in current Pos*/
    if (gu8TimeIndexValue < 6) {
        gu8TimeIndexValue++;
    } else {

        gu8TimeIndexValue = 0;
    }
    /*show Time with blink*/
    gu8LCDBlink = 1;
    ShowEditTime(1);
    gu8SystemTimeState = 2;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF2Events  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF2Events                                                  |
 | < @Description       : key F2 Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyF2Events() {
    if (gu8TimeIndexValue == -1) {
        gu8TimeIndexValue = 0;
    }

    if (gu8TimeIndexValue == 0) {
        gu8TimeIndexValue = 6;
    } else {

        gu8TimeIndexValue--;
    }
    gu8LCDBlink = 1;
    ShowEditTime(1);
    /*show Time with blink*/
    gu8SystemTimeState = 2;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF3Events  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF3Events                                                                   |
 | < @Description       : key F2 Events   Handler                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyF3Events() {
    if (gu8TimeIndexValue == -1) {
        return;
    }

    if (gu8TimeIndexValue == 3) {
        if (gstDataTime.tm_wday < 6) {
            gstDataTime.tm_wday++;
        } else {
            gstDataTime.tm_wday = 0;
        }
    } else if (gu8TimeIndexValue == 5) {
        if (gstDataTime.tm_mon < 12) {
            gstDataTime.tm_mon++;
        } else {
            gstDataTime.tm_mon = 1;
        }
    } else {
        return;
    }
    gu8LCDBlink = 1;
    ShowEditTime(1);
    return;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyEnterEvents  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyEnterEvents                                                  |
 | < @Description       : key Enter Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void keyEnterEvents() {
    ds1307SetDate(&gstDataTime);
    gu8SystemTimeState = 3;
}

