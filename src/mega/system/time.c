/*
 -----------------------------------------------------------------------------------------------------------------
 |                          <Module  Definition >                                                                |  
 -----------------------------------------------------------------------------------------------------------------
 | < FILE                   : time.c                                                                             |                                  
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


#include "../../../inc/mega.h"


/*
 -----------------------------------------------------------------------------------------------------------------
 |                          < Years Types to Seconds >                                                           |  
 -----------------------------------------------------------------------------------------------------------------
 | < marco SOLAR_YEAR             : One complete revolution of the sun, and its duration                         |
 |                                : is 365 days, 5 hours, 48 minutes and 45 seconds                              |
 |                                : which is equivalent to (365*24*60*60) + (5*60*60+48*60+45) = 31556925second. |
 | < macro ANOMALISTIX_YEAR       : The period of time in which the right ascension of the mean sun increases    |  
 |                                : by 360 degrees. Symbol, aastr. Also known as the annus fictus, or Bessel's   |
 |                                : duration is 365 days, 6 hours, 13 minutes and 53 seconds                     |
 |                                : which is equivalent to (365*24*60*60) + (6*60*60+13*60+53) = 31558433 second |
 | < macro PERIHELION_DATE        : the point in the orbit of a planet, asteroid, or comet at which it           |
 |                                : is closest to the sun.                                                       |
 |                                : --------------------------------------------------                           |
 |                                : | Year  |   Date Perihelion      |  Distance     |                           |
 |                                : |------------------------------------------------|                           | 
 |                                : | 1999  |   Jan 03  13:00 UTC    | 0.9832809  AU |                           |
 |                                  --------------------------------------------------                           |
 |                                :  1/1/1999 to 1/1/2000 (365 day  = 31536000 seconds)                          |                                    |
 |                                :  the time from 3/1/1999 13:00 UTC = 2day , 13 hour  = 13*60*60+ 2*24*60*60   |
 |                                :   = 219600 seconds (365 day -2day , 13 hour) = 31536000-219600 = 31316400    |
 | < macro SOLSTICE_DATE          : Winter Solstice	  1999 DEC 22  7:44 UTC   different  between time            |
 |                                : (22/12/1999 07:44 UTC ),(1/1/2000 00:00 UTC ) is (10 days - (7 hour,44 min)) |
 |                                : 10 * 24*60*60 - (7*60*60 + 44*60 + 0) = 836160 second                        |
 | < macro TWO_PI                 : 2 * (22/7)                                                                   |
 | < macro SOLAR_CYCLE_TIME       : time take of the 360 dgree (2*pi) is  31556925second  1-dgree  take x time   |   
 |                                : x = (31556925 / 2*Pi) = 5022440.6025                                         |
 |                                : 1-cycle step take a 5022440.6025 second                                      |
 | < macro ANOMALISTIX_CYCLE_TIME : same calc of SOLAR_CYCLE  x = (31558433 / 2*Pi) = 5022680.6082               |
 | < macro ECCENTRICITY_EARTH     : x orbital eccentricity (look referances) of the earth =(0.01671022)          |
 |                                : and 2x = 2*0.01671022 = 0.03342044                                           |
 |                                : orbital eccentricity is = c/a , c distance between the two foci  in ellipse  |
 |                                : and a is lenght of the major axis in ellipse                                 |
 | < macro  RTC_BASE_TIME         : base time start of the year                                                  |
 -----------------------------------------------------------------------------------------------------------------
 */
#define  SOLAR_YEAR              31556925
#define  ANOMALISTIX_YEAR        31558433
#define  PERIHELION_DATE         31316400 
#define  SOLSTICE_DATE           836160 
#define  TWO_PI                  6.28318530718
#define  SOLAR_CYCLE_TIME        5022440.6025    
#define  ANOMALISTIX_CYCLE_TIME  5022680.6082
#define  ECCENTRICITY_EARTH      0.03342044
#define  RTC_BASE_TIME           (2000UL)
/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < Basic Function Definition >                                                 |
 -----------------------------------------------------------------------------------------------------------------
 | < @const ascmonths     : name of the monthes per year                                                         |
 | < @const ascdays       : name of days per week                                                                |
 -----------------------------------------------------------------------------------------------------------------
 */
#if COMPILER_TYPE == GCC


/**
  Number of days in each month, from January to November. December is not
 */
const uint8_t PROGMEM daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
const char PROGMEM monthsOfTheYear[12][4] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
const char PROGMEM dOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
#elif COMPILER_TYPE == XC
const uint8_t daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
const char monthsOfTheYear[12][4] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
const char dOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
#endif


/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < Basic Function Definition >                                                 |
 -----------------------------------------------------------------------------------------------------------------
 */



/**************************************************************************/
/*!
    @brief  Given a date, return number of days since 2000/01/01,
            valid for 2000--2099
    @param y Year
    @param m Month
    @param d Day
    @return Number of days
 */

/**************************************************************************/
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d);
/**************************************************************************/
/*!
    @brief  Given a number of days, hours, minutes, and seconds, return the
   total seconds
    @param days Days
    @param h Hours
    @param m Minutes
    @param s Seconds
    @return Number of seconds total
 */
/**************************************************************************/
static uint32_t time2ulong(uint16_t days, uint8_t h, uint8_t m, uint8_t s);

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < Basic Function implemention >                                               |
 -----------------------------------------------------------------------------------------------------------------
 */

/**************************************************************************/
/*!
    @brief  Given a date, return number of days since 2000/01/01,
            valid for 2000--2099
    @param y Year
    @param m Month
    @param d Day
    @return Number of days
 */

/**************************************************************************/
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= RTC_BASE_TIME)
        y -= RTC_BASE_TIME;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    if (m > 2 && y % 4 == 0)
        ++days;
    return (days + (365 * y) + ((y + 3) >> 2) - 1);
}
/**************************************************************************/
/*!
    @brief  Given a number of days, hours, minutes, and seconds, return the
   total seconds
    @param days Days
    @param h Hours
    @param m Minutes
    @param s Seconds
    @return Number of seconds total
 */

/**************************************************************************/
static uint32_t time2ulong(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24UL + h) * 60 + m) * 60 + s;
}



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
void DateTimeFromTimeStamp(tm_t *tm, time_t t) {

    tm->tm_sec = t % 60;
    t /= 60;
    tm->tm_min = t % 60;
    t /= 60;
    tm->tm_hour = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;
    for (tm->tm_year = 0;; ++tm->tm_year) {
        leap = tm->tm_year % 4 == 0;
        if (days < 365U + leap)
            break;
        days -= 365 + leap;
    }
    for (tm->tm_mon = 1; tm->tm_mon < 12; ++tm->tm_mon) {
        uint8_t daysPerMonth = pgm_read_byte(daysInMonth + tm->tm_mon - 1);
        if (leap && tm->tm_mon == 2)
            ++daysPerMonth;
        if (days < daysPerMonth)
            break;
        days -= daysPerMonth;
    }
    tm->tm_mday = days + 1;
    tm->tm_wday = (days + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}
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
void DateTimeFromUserTime(tm_t *tm, uint16_t year, uint8_t month, uint8_t day, uint8_t hour,
        uint8_t min, uint8_t sec) {
    if (year >= RTC_BASE_TIME)
        year -= RTC_BASE_TIME;
    tm->tm_year = year;
    tm->tm_mon = month;
    tm->tm_mday = day;
    tm->tm_hour = hour;
    tm->tm_min = min;
    tm->tm_sec = sec;
}

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
    @param date Date string, e.g. "Fri 15 APR 2016".
    @param time Time string, e.g. "18:34:56".
 */

/**************************************************************************/
void DateTimeFromString(tm_t *tm, uint8_t *date, uint8_t *time) {
    tm->tm_mday = conv2d(date);
    tm->tm_mon = conv2d(date + 3);
    tm->tm_year = conv2d(date + 8);
    tm->tm_hour = conv2d(time);
    tm->tm_min = conv2d(time + 3);
    tm->tm_sec = conv2d(time + 6);
}
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
void DateTimeFromFlash(tm_t *tm, PGM_P const *date, PGM_P const *time) {
    char buff[11];
    memcpy_P(buff, date, PRINT_BUF_DATE_lENGTH);
    tm->tm_mday = conv2d((uint8_t *) buff);
    tm->tm_mon = conv2d((uint8_t *) buff + 3);
    tm->tm_year = conv2d((uint8_t *) buff + 8);

    memcpy_P(buff, time, PRINT_BUF_TIME_lENGTH);
    tm->tm_hour = conv2d((uint8_t *) buff);
    tm->tm_min = conv2d((uint8_t *) buff + 3);
    tm->tm_sec = conv2d((uint8_t *) buff + 6);

}

/**************************************************************************/
/*!
    @brief  Return Unix time: seconds since 1 Jan 1970.
    @see The `DateTime::DateTime(uint32_t)` constructor is the converse of
        this method.
    @return Number of seconds since 1970-01-01 00:00:00.
 */

/**************************************************************************/
time_t DateTimeUnixtime(tm_t *tm) {
    time_t t;
    uint16_t days = date2days(tm->tm_year, tm->tm_mon, tm->tm_mday);
    t = time2ulong(days, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return t;
}
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
void DateTimeFromISO8601(tm_t *tm, const char *iso8601dateTime) {
    char ref[] = "2000-01-01T00:00:00";
    memcpy(ref, iso8601dateTime, min(strlen(ref), strlen(iso8601dateTime)));
    tm->tm_year = conv2d((uint8_t *) ref + 2);
    tm->tm_mon = conv2d((uint8_t *) ref + 5);
    tm->tm_mday = conv2d((uint8_t *) ref + 8);
    tm->tm_hour = conv2d((uint8_t *) ref + 11);
    tm->tm_min = conv2d((uint8_t *) ref + 14);
    tm->tm_sec = conv2d((uint8_t *) ref + 17);
}
/**************************************************************************/
/*!
    @brief  Check whether this DateTime is valid.
    @return true if valid, false if not.
 */

/**************************************************************************/
uint8_t DateTimeisValid(tm_t *tm) {
    tm_t other;
    time_t t;
    if (tm->tm_year >= 100)
        return 0;
    t = DateTimeUnixtime(tm);
    DateTimeFromTimeStamp(&other, t);
    return (tm->tm_year == other.tm_year) && (tm->tm_mon == other.tm_mon) && (tm->tm_mday == other.tm_mday) && (tm->tm_hour == other.tm_hour) &&
            (tm->tm_min == other.tm_min) && (tm->tm_sec == other.tm_sec);
}


/**************************************************************************/
/*!
    @brief  Return the day of the week.
    @return Day of week as an integer from 0 (Sunday) to 6 (Saturday).
 */

/**************************************************************************/
uint8_t DateTimeDayOfTheWeek(tm_t *tm) {
    uint16_t day = date2days(tm->tm_year, tm->tm_mon, tm->tm_mday);
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}


/**************************************************************************/
/*!
      @brief  Return the hour in 12-hour format.
      @return Hour (1--12).
 */

/**************************************************************************/
uint8_t DateTimetwelveHour(tm_t *tm) {
    if (tm->tm_hour == 0 || tm->tm_hour == 12) { // midnight or noon
        return 12;
    } else if (tm->tm_hour > 12) { // 1 o'clock or later
        return tm->tm_hour - 12;
    } else { // morning
        return tm->tm_hour;
    }
}




/**************************************************************************/
/*!
    @brief  Convert the DateTime to seconds since 1 Jan 2000
    The result can be converted back to a DateTime with:
    DateTime(SECONDS_FROM_1970_TO_2000 + value)
    @return Number of seconds since Fri 15 APR 2016.
 */

/**************************************************************************/
void PrintTime(tm_t *tm, uint8_t *buf) {
    print2d(tm->tm_hour, buf, 0);
    buf[2] = ':';
    print2d(tm->tm_min, buf, 3);
    buf[5] = ':';
    print2d(tm->tm_sec, buf, 6);
}

/**************************************************************************/
/*!   @brief  Print Date Sat 23 NOV 1996   
 */

/**************************************************************************/
void PrintDate(tm_t *tm, uint8_t *buf) {
    for (uint8_t i = 0; i < 3; i++) {
        buf[i] = pgm_read_byte(&dOfTheWeek[tm->tm_wday][i]);
        buf[i + 7] = pgm_read_byte(&monthsOfTheYear[tm->tm_mon-1][i]);
    }
    buf[3] = ' ';
    print2d(tm->tm_mday, buf, 4);
    buf[6] = ' ';
    buf[10] = ' ';
    buf[11] = '2';
    buf[12] = '0';
    print2d(tm->tm_year, buf, 13);
}
