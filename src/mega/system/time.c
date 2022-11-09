

/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   time.c
 * Author       :   Hassan Elsaied
 * Data Memory  :   total byte used 24 Byte  in program space
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   5-hour
 * Comments     :   no comment
 *  
 */
#include "../../../inc/mega.h"


/*
 ****************************************************
 *                     converts                      *
 * **************************************************
 * @SECS_PER_MIN          : one minute have a 60 second
 * @RTC_BASE_TIME         : system start count from 2000
 * @SECS_PER_HOUR         : one hour have a 60 min and one min have a 60 second one hour = 60*60 second
 * @DAY_PER_WEEK          : on week have a 7 day 
 * @SECS_PER_DAY          : one day have a 24 hour and one hour = 60*60 ==>one day = 24*60*60 
 */


#define 	SECS_PER_MIN                  (60UL)
#define     RTC_BASE_TIME                 (2000UL)
#define 	SECS_PER_HOUR                 (3600UL)
#define 	DAY_PER_WEEK                  (7)
#define     SECS_PER_DAY                 ((SECS_PER_HOUR) * (24UL))
/*
 ****************************************************
 *            find year size                         *
 * **************************************************
 */

#define     YAER_SIZE(Y)                  ((RTC_LEAP_YEAR(Y + (RTC_BASE_TIME))) ? (366) : (365))
/*
 * *******************************************************************
 *                            Leap Year check                        *
 * *******************************************************************
 * */

#define  RTC_LEAP_YEAR(Y)            ((Y>0) && (!(Y%4)) && ((Y%100) || (!(Y%400))))

/*
 ****************************************************
 *                    Months table                       *
 * **************************************************
 */

static const uint8_t gu8RtcMonthLeapYear[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const uint8_t gu8RtcMonthYear[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*
 ****************************************************
 *                    Convert data to timestamp                     *
 * **************************************************
 * @param ptm : pointer to buffer of date data 
 * @return    : timestamp value based 2000
 */

time_t rtcConvertDateToTime(uint8_t *ptm) {
    time_t time;
    uint8_t u8temp;

    time = 0;

    if (ptm[rtc_month] > 11
            && ptm[rtc_daym] > 30
            && ptm[rtc_hour] > 23
            && ptm[rtc_min] > 59
            && ptm[rtc_sec] > 59) {
        time = systemNow();
        return time;
    } else {

        u8temp = 0;
        //convert year to day
        while (u8temp < ptm[rtc_year]) {
            time += YAER_SIZE(u8temp);
            u8temp++;
        }
        // convert month to day
        u8temp = 0;
        while (u8temp < ptm[rtc_month]) {
            if (RTC_LEAP_YEAR(ptm[rtc_year] + RTC_BASE_TIME)) {
                time += gu8RtcMonthLeapYear[u8temp];
            } else {
                time += gu8RtcMonthYear[u8temp];
            }
            u8temp++;
        }
        time += ptm[rtc_daym];
        /*convert dayes to sec*/
        time = time * (SECS_PER_DAY);
        /*add hours and min and sec*/
        time += (ptm[rtc_hour] * SECS_PER_HOUR) + (ptm[rtc_min] * 60) + ptm[rtc_sec];

        return (time);
    }
}

/*
 ************************************************************
 *            Convert timestamp to data                     *
 * **********************************************************
 * @param time    : timestamp value since 2000
 * @return ptm    : pointer to buffer to store date 
 */
void rtcConvertTimeToDate(time_t Time, uint8_t *ptm) {
    time_t rem;
    time_t Days;
    uint8_t u8Temp;

    rem = (Time % SECS_PER_DAY);

    ptm[rtc_hour] = (rem) / SECS_PER_HOUR;
    rem = (rem) % (SECS_PER_HOUR);

    ptm[rtc_min] = (rem) / (SECS_PER_MIN);
    ptm[rtc_sec] = ((rem) % (SECS_PER_MIN));


    Days = (Time / SECS_PER_DAY);
    if (Days < 1) {
        ptm[rtc_year] = 0;
        ptm[rtc_month] = 0;
        ptm[rtc_daym] = 0; //
    } else {
        /*week days 1-1-2000  (starday*/

        /*convert days to years*/
        /*start year*/
        u8Temp = 0; /*start year 2000 (00)*/
        while (Days >= YAER_SIZE(u8Temp)) {
            Days = Days - (YAER_SIZE(u8Temp));
            u8Temp++;
        }
        ptm[rtc_year] = u8Temp;
        /*month*/
        u8Temp = 0;
        if (RTC_LEAP_YEAR(ptm[rtc_year] + RTC_BASE_TIME)) {
            while (Days >= gu8RtcMonthLeapYear[u8Temp]) {
                Days = Days - gu8RtcMonthLeapYear[u8Temp];
                u8Temp++;
            }
        } else {
            while (Days >= gu8RtcMonthYear[u8Temp]) {
                Days = Days - gu8RtcMonthYear[u8Temp];
                u8Temp++;
            }
        }
        ptm[rtc_month] = u8Temp;
        ptm[rtc_daym] = Days;
    }
}

