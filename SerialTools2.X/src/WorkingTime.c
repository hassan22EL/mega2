/* 
 * File:   WorkingTime.c
 * Author: hp
 *
 * Created on February 28, 2023, 5:21 PM
 */



#include "../inc/appRes.h"
/*
 * <@var Hour Movent
 */
static uint8_t guMoveHour;

/*
 * <@var save Working Time
 */
stWorkingtime_t gstWorkingTime;
/*
 * <@var save Working Time
 */
static stWorkingHour_t gsEditWorkingTime;

/*
 * <@var Working Time State
 */
static uint8_t gu8WorkingTimeState;
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeF1  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeF1                                                      |
 | < @Description       : up houres from start to 23                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeF1();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeF2  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeInit                                                      |
 | < @Description       : down hour from last to 0                                                |                                                  |                                                           
 | < @return            : void                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeF2();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeF3  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeF3                                                      |
 | < @Description       : move from one hour to second hour                                                 |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeF3();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeEnter  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeEnter                                                      |
 | < @Description       : save value into memory with load working time                                                 |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeEnter();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeCenecl  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeCenecl                                                      |
 | < @Description       : Return to menu call backs                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeCenecl();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorikingTimeUpdateLcd  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorikingTimeUpdateLcd                                                      |
 | < @Description       : update Values in LCD                                              |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorikingTimeUpdateLcd();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeInit  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeInit                                                      |
 | < @Description       : Init values in Working Time                                                |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
void WorkingTimeInit() {
    gu8WorkingTimeState = 0;
    guMoveHour = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeCallBack  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeCallBack                                                      |
 | < @Description       : Run in menu Driver                                                |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t WorkingTimeCallBack() {
    tm_t Date1;
    tm_t Date2;
    if (gu8WorkingTimeState == 0) {
        lcdClear();
        CommanEventFunctions(WorkingTimeF1, WorkingTimeF2, WorkingTimeF3, WorkingTimeEnter, WorkingTimeCenecl);
        WriteMessage(0, MSG_WORKTIME_SET);
        lcdBlink(1, 0);
        DateTimeFromTimeStamp(&Date1, gstWorkingTime.StartTime);
        DateTimeFromTimeStamp(&Date2, gstWorkingTime.EndTime);
        gsEditWorkingTime.StartHour = Date1.tm_hour;
        gsEditWorkingTime.EndHour = Date2.tm_hour;
        WorikingTimeUpdateLcd();
        gu8WorkingTimeState = 1;
        return (0);
    }
    if (gu8WorkingTimeState == 1) {
        return (0);
    }

    if (gu8WorkingTimeState == 2) {
        if (SaveIntoMemory(CURRENT_WORKINGTIME_ADDRESS, (uint8_t *) & gstWorkingTime, 8)) {
            gu8WorkingTimeState = 3;
        }
        return (0);
    }

    if (gu8WorkingTimeState == 3) {
        ReturnMenuCallBack();
        gu8WorkingTimeState = 0;
        lcdNoBlink();
        guMoveHour = 0;
        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeF1  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeF1                                                      |
 | < @Description       : up houres from start to 23                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeF1() {
    uint8_t *buf = &gsEditWorkingTime.StartHour;
    uint8_t Value = *(buf + guMoveHour);
    if (Value < 23) {
        Value += 1;
    } else {
        Value = 0;
    }
    *(buf + guMoveHour) = Value;
    WorikingTimeUpdateLcd();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeF2  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeInit                                                      |
 | < @Description       : down hour from last to 0                                                |                                                  |                                                           
 | < @return            : void                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeF2() {
    uint8_t *buf = &gsEditWorkingTime.StartHour;
    uint8_t Value = *(buf + guMoveHour);

    if (Value > 0) {
        Value--;
    } else {
        Value = 23;
    }
    *(buf + guMoveHour) = Value;
    WorikingTimeUpdateLcd();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeF3  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeF3                                                      |
 | < @Description       : move from one hour to second hour                                                 |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeF3() {
    uint8_t value;
    guMoveHour ^= 1;
    if (guMoveHour) {
        value = 14;
    } else {
        value = 0;
    }
    lcdBlink(1, value);
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeEnter  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeEnter                                                      |
 | < @Description       : save value into memory with load working time                                                 |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeEnter() {
    tm_t Date;
    DateTimeFromTimeStamp(&Date, systemNow());
    Date.tm_min = 0;
    Date.tm_sec = 0;
    Date.tm_hour = gsEditWorkingTime.StartHour;
    gstWorkingTime.StartTime = DateTimeUnixtime(&Date);
    Date.tm_hour = gsEditWorkingTime.EndHour;
    gstWorkingTime.EndTime = DateTimeUnixtime(&Date);

    /*23:00:00 6-3-2023*/
    if (gsEditWorkingTime.StartHour >= gsEditWorkingTime.EndHour) {/*start > end*/
        gstWorkingTime.EndTime += NUMBER_OF_SECOND_PER_DAY; /*the d*/
    }
    gu8WorkingTimeState = 2;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeCenecl  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeCenecl                                                      |
 | < @Description       : Return to menu call backs                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorkingTimeCenecl() {
    gu8WorkingTimeState = 3;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < LoadWorkingTime  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  LoadWorkingTime                                                      |
 | < @Description       : Load Working Time From memory                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorikingTimeUpdateLcd  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorikingTimeUpdateLcd                                                      |
 | < @Description       : update Values in LCD                                              |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
static void WorikingTimeUpdateLcd() {
    uint8_t buf[2];
    uint8_t buf2[2];
    print2d(gsEditWorkingTime.StartHour, buf, 0);
    print2d(gsEditWorkingTime.EndHour, buf2, 0);
    lcdwritebuf(1, 0, buf, 2);
    lcdwritebuf(1, 14, buf2, 2);
    lcdUpdateNow();
}