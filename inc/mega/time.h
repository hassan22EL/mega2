
/*
 -----------------------------------------------------------------------------------------------------------------
 |                          <Module  Definition >                                                                |  
 -----------------------------------------------------------------------------------------------------------------
 | < FILE                   : time.h                                                                             |                                  
 | < Author                 : Hassan Elsaied                                                                     |
 | < Version                : Mega2v241022                                                                       |
 | < References             : https://www.sizes.com/time/year.htm#anomalistic                                    |
 |                          : http://www.astropixels.com/ephemeris/perap/perap1901.html                          |                                
 |                          : https://en.wikipedia.org/wiki/Apsis                                                |
 |                          : https://study.com/learn/lesson/orbital-eccentricity-planets-earth.html             |
 |                          : https://www.glib.com/season_dates.html                                             |
 | < SRAM_USAGE             : at create tm object is 7 byte used                                                 |
 | < PROGRAM_USAGE          :                                                                                    |
 | < Hardware Usage         : no-hardware uused                                                                  |
 | < File Created           : 24-10-2022                                                                         |
  -----------------------------------------------------------------------------------------------------------------
 */

#include "../mega.h"

#ifndef TIME_H
#define	TIME_H


#define  NUMBER_OF_SECOND_PER_DAY                      (86400UL)
#define  NUMBER_OF_SECOND_PER_HOUR                      (3600UL)
/*
 * < @mcro PRINT_BUF_TIME_lENGTH                    : Print time buffer Length
 */
#define  PRINT_BUF_TIME_lENGTH             (8)
/*
 * < @mcro PRINT_BUF_DATE_lENGTH                    : Print date buffer Length
 */
#define  PRINT_BUF_DATE_lENGTH             (15)

/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  tm struct   >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : tm struct                                                                   |
 | < Uasge                 : 9 Byte                                                                      |
 | < @param tm_sec         : seconds after the minute - [ 0 to 59 ]                                      |
 | < @param tm_min         : minutes after the hour - [ 0 to 59 ]                                        |
 | < @param tm_hour        : hours since midnight - [ 0 to 23 ]                                          |
 | < @param tm_mday        : day of the month - [ 1 to 31 ]                                              |
 | < @param tm_wday        : days since Sunday - [ 0 to 6 ]                                              |
 | < @param tm_mon         : months since January - [ 0 to 11 ]                                          |     
 | < @param tm_year        : years since 2000 [ 0 to 99 ]                                                |                       
 | < @param tm_yday        : days since January 1 - [ 0 to 365 ]                                         |
 --------------------------------------------------------------------------------------------------------
 */
typedef struct tm_s {
    uint8_t tm_sec; /*0*/
    uint8_t tm_min;
    uint8_t tm_hour;
    uint8_t tm_wday;
    uint8_t tm_mday;
    uint8_t tm_mon;
    uint8_t tm_year;
} tm_t;


/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < user Function implemention >                                               |
 -----------------------------------------------------------------------------------------------------------------
 */

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < getDate >                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : void getDate                                                                           |
 | < @Description       : convert current time form date to timestamp                                            |
 | < @Param timeptr     : ponter of the date time struct                                                         |                                                            |
 | < @return            : void                                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 */
void DateTimeFromTimeStamp(tm_t *tm, time_t t);
/**************************************************************************/
/*!
    @brief  Constructor from (year, month, day, hour, minute, second).
    @warning If the provided parameters are not valid (e.g. 31 February),
           the constructed DateTime will be invalid.
    @see   The `isValid()` method can be used to test whether the
           constructed DateTime is valid.
    @param year Either the full year (range: 2000--2099) or the offset from
        year 2000 (range: 0--99).
    @param month Month number (1--12).
    @param day Day of the month (1--31).
    @param hour,min,sec Hour (0--23), minute (0--59) and second (0--59).
 */

/**************************************************************************/
void DateTimeFromUserTime(tm_t *tm, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);

/**************************************************************************/
/*!
    @brief  Constructor for generating the build time.
    This constructor expects its parameters to be strings in the format
    generated by the compiler's preprocessor macros `__DATE__` and
    `__TIME__`. Usage:
    ```
    DateTime buildTime(__DATE__, __TIME__);
    ```
    @note The `F()` macro can be used to reduce the RAM footprint, see
        the next constructor.
    @param date Date string, e.g. "Apr 16 2020".
    @param time Time string, e.g. "18:34:56".
 */

/**************************************************************************/
void DateTimeFromString(tm_t *tm, uint8_t *date, uint8_t *time);
/**************************************************************************/
/*!
    @brief  Memory friendly constructor for generating the build time.
    This version is intended to save RAM by keeping the date and time
    strings in program memory. Use it with the `F()` macro:
    ```
    DateTime buildTime(F(__DATE__), F(__TIME__));
    ```
    @param date Date PROGMEM string, e.g. F("Apr 16 2020").
    @param time Time PROGMEM string, e.g. F("18:34:56").
 */

/**************************************************************************/
void DateTimeFromFlash(tm_t *tm, PGM_P const *date, PGM_P const *time);

/**************************************************************************/
/*!
    @brief  Return Unix time: seconds since 1 Jan 1970.
    @see The `DateTime::DateTime(uint32_t)` constructor is the converse of
        this method.
    @return Number of seconds since 1970-01-01 00:00:00.
 */

/**************************************************************************/
time_t DateTimeUnixtime(tm_t *tm);
/**************************************************************************/
/*!
    @brief  Constructor for creating a DateTime from an ISO8601 date string.
    This constructor expects its parameters to be a string in the
    https://en.wikipedia.org/wiki/ISO_8601 format, e.g:
    "2020-06-25T15:29:37"
    Usage:
    ```
    DateTime dt("2020-06-25T15:29:37");
    ```
    @note The year must be > 2000, as only the yOff is considered.
    @param iso8601dateTime
           A dateTime string in iso8601 format,
           e.g. "2020-06-25T15:29:37".
 */

/**************************************************************************/
void DateTimeFromISO8601(tm_t *tm, const char *iso8601dateTime);
/**************************************************************************/
/*!
    @brief  Check whether this DateTime is valid.
    @return true if valid, false if not.
 */

/**************************************************************************/
uint8_t DateTimeisValid(tm_t *tm);


/**************************************************************************/
/*!
    @brief  Return the day of the week.
    @return Day of week as an integer from 0 (Sunday) to 6 (Saturday).
 */

/**************************************************************************/
uint8_t DateTimeDayOfTheWeek(tm_t *tm);

/**************************************************************************/
/*!
      @brief  Return the hour in 12-hour format.
      @return Hour (1--12).
 */

/**************************************************************************/
uint8_t DateTimetwelveHour(tm_t *tm);


/**************************************************************************/
/*!
      @brief  Return the hour in 12-hour format.
      @return Hour (1--12).
 */

/**************************************************************************/

void PrintTime(tm_t *tm, uint8_t *buf);

/**************************************************************************/
/*!
      @brief  Return the hour in 12-hour format.
      @return Hour (1--12).
 */

/**************************************************************************/
void PrintDate(tm_t *tm, uint8_t *buf);
#endif	/* TIME_H */

