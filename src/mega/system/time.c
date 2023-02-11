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





#include <stdint-gcc.h>

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
 |                          < Leap Year Check >                                                                  |  
 -----------------------------------------------------------------------------------------------------------------
 */
#define  RTC_LEAP_YEAR(Y)            ((Y>0) && (!(Y%4)) && ((Y%100) || (!(Y%400))))


/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < Basic Function Definition >                                                 |
 -----------------------------------------------------------------------------------------------------------------
 | < @const ascmonths     : name of the monthes per year                                                         |
 | < @const ascdays       : name of days per week                                                                |
 -----------------------------------------------------------------------------------------------------------------
 */
#if COMPILER_TYPE == GCC
const char PROGMEM ascmonths[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
const char PROGMEM ascdays[] = "SunMonTueWedThuFriSat";
#elif COMPILER_TYPE == XC
const char ascmonths[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
const char ascdays[] = "SunMonTueWedThuFriSat";
#endif



/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < Basic Function Definition >                                                 |
 -----------------------------------------------------------------------------------------------------------------
 */
/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < timeEquation >                                                              |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : int  timeEquation                                                                      |
 | < @Description       : PF = a*sin(seta) , seta = W*t , W = 2*Pi/Ta , t = t-t0                                 |
 |                      : PF = a*sin((2*Pi/Ta)*(t-t0))  , PF = a*sin((t-t0)/ANOMALISTIX_CYCLE_TIME)              |
 |                      : ANOMALISTIX_CYCLE_TIME = Ta/2*Pi   , t0 = PERIHELION_DATE                              |
 |                      : t = reminder of the divide current time by ANOMALISTIX_YEAR , a = 1AU                  |
 |                      : dv = 2e*Pf                                                                             |
 |                      : sf = a*sin(2*(2*Pi/Ts)*(t-t0) + dv)                                                    |
 |                      : a = 1AU , Ts = SOLAR_YEAR  , t  =   reminder of the divide current time by             |
 |                      : SOLAR_YEAR and t0 = SOLSTICE_DATE  a*sin(2*(t-t0)/SOLAR_CYCLE_TIME)                    |  
 | < @Param  time       : pointer of the timestamp value                                                         |             
 | < @return            : signed interger of the Time                                                            |                                                            
 -----------------------------------------------------------------------------------------------------------------
 */
static int timeEquation(time_t *time);
/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < month_length >                                                              |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t month_length                                                                   | 
 | < @Description       : number of days per month                                                               |
 | < @Param year        : year  number                                                                           |
 | < @Param month       : month in the year                                                                      |                    
 | < @return            : number of days per month                                                               |
 -----------------------------------------------------------------------------------------------------------------
 */
static uint8_t month_length(uint8_t year, uint8_t month);


/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < __print_2Digit >                                                            |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : time_t __print_2Digit                                                                  | 
 | < @Description       : current number as 2 Digit value 20/10 = 2 , 20 %10 = 0                                 |
 |                      : and assign as a string into buffer                                                     |
 | < @Param i           : number as 2 digit to convert as a string                                               |
 | < @Param buffer      : pointer of the  buffer as a store a monthes and days name                              |
 | < @Param s           : Sperate char with time such as pirnt 00:00:00  12-4-2000, s = ':', s  = '-'            |                     
 | < @return            : void                                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 */
static void __print_2Digit(int i, uint8_t *buffer, char s);


/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < Basic Function implemention >                                               |
 -----------------------------------------------------------------------------------------------------------------
 */

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < timeEquation >                                                              |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : int  timeEquation                                                                      |
 | < @Description       : PF = a*sin(seta) , seta = W*t , W = 2*Pi/Ta , t = t-t0                                 |
 |                      : PF = a*sin((2*Pi/Ta)*(t-t0))  , PF = a*sin((t-t0)/ANOMALISTIX_CYCLE_TIME)              |
 |                      : ANOMALISTIX_CYCLE_TIME = Ta/2*Pi   , t0 = PERIHELION_DATE                              |
 |                      : t = reminder of the divide current time by ANOMALISTIX_YEAR , a = 1AU                  |
 |                      : dv = 2e*Pf                                                                             |
 |                      : sf = a*sin(2*(2*Pi/Ts)*(t-t0) + dv)                                                    |
 |                      : a = 1AU , Ts = SOLAR_YEAR  , t  =   reminder of the divide current time by             |
 |                      : SOLAR_YEAR and t0 = SOLSTICE_DATE  a*sin(2*(t-t0)/SOLAR_CYCLE_TIME)                    |  
 | < @Param  time       : pointer of the timestamp value                                                         |             
 | < @return            : signed interger of the Time                                                            |                                                            
 -----------------------------------------------------------------------------------------------------------------
 */
static int timeEquation(time_t *time) __attribute__((unused));

static int timeEquation(time_t *time) {
    int32_t u32Perihlion;
    int32_t u32Solstice;
    double PF, SF, dv;

    u32Perihlion = *time % ANOMALISTIX_YEAR;
    u32Perihlion += PERIHELION_DATE; /*t-t0 ==> t-(-t0) = t+t0*/
    PF = u32Perihlion;
    PF /= ANOMALISTIX_CYCLE_TIME; /*(t-t0 / (Ta*2PI))  */
    PF = sin(PF); /*pf = a sin seta*/
    dv = ECCENTRICITY_EARTH * PF;
    u32Solstice = *time % SOLAR_YEAR; /*t*/
    u32Solstice += SOLSTICE_DATE; /*t-t0 ==> t-(-t0) = t+t0*/
    u32Solstice *= 2;
    SF /= SOLAR_CYCLE_TIME;
    SF += dv;
    SF = sin(SF);
    /*7.66 min*/
    PF *= 459.6;
    /*9.87 min*/
    SF *= 592.2;
    u32Solstice = SF + PF;
    return -u32Solstice;
}

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < __print_2Digit >                                                            |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : time_t __print_2Digit                                                                  | 
 | < @Description       : current number as 2 Digit value 20/10 = 2 , 20 %10 = 0                                 |
 |                      : and assign as a string into buffer                                                     |
 | < @Param i           : number as 2 digit to convert as a string                                               |
 | < @Param buffer      : pointer of the  buffer as a store a monthes and days name                              |
 | < @Param s           : Sperate char with time such as pirnt 00:00:00  12-4-2000, s = ':', s  = '-'            |                     
 | < @return            : void                                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 */

static void __print_2Digit(int i, uint8_t *buffer, char s) {
    div_t res;
    res = div(i, 10);
    *buffer++ = res.quot + '0';
    *buffer++ = res.rem + '0';
    *buffer = (uint8_t) s;
}

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < month_length >                                                              |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t month_length                                                                   | 
 | < @Description       : number of days per month                                                               |
 | < @Param year        : year  number                                                                           |
 | < @Param month       : month in the year                                                                      |                    
 | < @return            : number of days per month                                                               |
 -----------------------------------------------------------------------------------------------------------------
 */
static uint8_t month_length(uint8_t year, uint8_t month) __attribute__((unused));

static uint8_t month_length(uint8_t year, uint8_t month) {
    if (month == 2)
        return 28 + RTC_LEAP_YEAR(year);

    if (month > 7)
        month++;
    return 30 + (month & 1);
}



/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < user Function implemention >                                               |
 -----------------------------------------------------------------------------------------------------------------
 */

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < getTime >                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : time_t getTime                                                                         |
 | < @Description       : convert current time form date to timestamp                                            |
 | < @Param timeptr     : ponter of the date time struct                                                         | 
 | < @return            : timestamp                                                                              |
 -----------------------------------------------------------------------------------------------------------------
 */
time_t getTime(tm_t *timeptr) {
    time_t ret;
    uint32_t tmp;
    uint8_t n, m, d, leaps;
    n = (timeptr->tm_year); /*22 , 21 , 23 , 24 number of years from 2000*/
    /*one year has a 365 days, 5 hours, 48 minutes, 45 seconds.*/
    /*every 4 years the years is 366  (4*6 hour ) = 24 Hour*/
    /*for example n = 22 the m = 21*/
    leaps = 0;
    if (n) {
        m = n - 1;
        /*leaps = ((current year -1 )/4) - ((current year-1) /100) = 21/4 -21/100 = 5*/
        /*number of leaps and remove all year is div by 100*/
        leaps = m / 4; /**/
        leaps -= m / 100;
        leaps++; /*leaps +1 = 6*/
    }
    /*current time of the years from 2000 to year 365 * number of years form 2*/
    tmp = (365UL * n) + leaps;
    d = timeptr->tm_mday - 1; /*month day start from 1 to 31 */
    /* handle Jan/Feb as a special case */
    if (timeptr->tm_mon < 2) {
        /*0 is jan , 1 is feb*/
        if (timeptr->tm_mon) {
            /*month is 1 the add jan days*/
            d += 31;
        }
    } else {
        /*month current is large than the 2  */
        /*add the month 0 (jan ) , month 1 (feb ) = 31 + 28 = 59 with add current is leap year or not */
        n = 59 + RTC_LEAP_YEAR(timeptr->tm_year + RTC_BASE_TIME); /*22+2000*/
        d += n; /*add number of days */
        /*reminder from month 2 (march) */
        n = timeptr->tm_mon - MARCH; /*reminder monthes*/
        if (n > JULY - MARCH) {
            /*n is > form different between 2(march) , 6(july)*/
            /*add the number of days from 2 , 6 (2,3,4,5,6) , (7,8,9,10,11)
             (march , april , may , june , july) , (*/
            /*31+30+31+30+31 = 153 */
            d += 153;
        }
        /*since the work as a 10 month 2 to 6 is 5 month and  7 to 11 is five month
         div this group by 2 group (31 day group ) , (30 day group)
         * 30+31 = 61 day
         */
        n %= 5; /*number of month ref of the two group  0 to 4 , 5 to 9 */
        m = n / 2; /*even and odd month month (march , may , july is odd have a 31 day
                 and AUGUST , oct and dec is odd and have a 31 day
                 */
        m *= 61; /*add two group 30 and 31 */
        d += m;
        if (n & 1) /*with odd month */
            d += 31;
    }
    /*calculate hour and min and second*/
    tmp += d;
    tmp *= SECS_PER_DAY; /*days to number of seconds*/
    ret = tmp;
    tmp = timeptr->tm_hour;
    tmp *= SECS_PER_HOUR; /*convert hour to seconds*/
    tmp += timeptr->tm_min * SECS_PER_MIN;
    tmp += timeptr->tm_sec;
    ret += tmp;
    return ret;
}

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
void getDate(tm_t *timeptr) {
    time_t Time;
    uint32_t fract;
    ldiv_t lresult;
    div_t result;
    uint16_t days, n, leapyear, years;
    Time = systemNow();
    days = Time / SECS_PER_DAY; /*number of days from 2000*/
    fract = Time % SECS_PER_DAY; /*day */
    /*get hour , min , second*/
    lresult = ldiv(fract, 60L);
    timeptr->tm_sec = lresult.rem; /*fract % 60*/
    result = div(lresult.quot, 60);
    timeptr->tm_min = result.rem;
    timeptr->tm_hour = result.quot;
    /* Determine day of week ( the epoch was a Saturday ) */
    n = days + SATURDAY; /*days + 6*/
    n %= 7; /*week have a 7 day a reminder of */
    timeptr->tm_wday = n;

    /*one year have a 365 day , 5 hour , 48 min , 45 sec = 365.25
     100 year = 100 * 365.25 = 36525
     4  year  = 4 *365.25 = 1461
     to find is a leap year
     */
    /* map into a 100 year cycle */
    /*example 22 year + 6day leap  number of days = 22*365 + 6 = 8036 day*/
    /*days + day months with a 8036/36525 = 0 *100 = 0 year*/
    lresult = ldiv((long) days, 36525L);
    years = 100 * lresult.quot;
    /* map into a 4 year cycle  example 8036 % 36525L /1461L = 5  */
    lresult = ldiv(lresult.rem, 1461L);
    years += 4 * lresult.quot; /*4 *5 = 20 the 2020 is last year*/
    days = lresult.rem; /*days is 731*/
    if (years > 100)
        days++;
    /*years is eq 100 year is leap year is 0*/
    leapyear = 1; /*inform the last leap year*/
    if (years == 100)
        leapyear = 0;
    n = 364 + leapyear; /*add day 365 or 364 */
    if (days > n) {
        /*number of days is > 365 or 364 is add year by div days by 365*/
        days -= leapyear; /*remove leap day to work with only 365 day by not 366*/
        leapyear = 0;
        result = div(days, 365); /*731 / 365  = 2year*/
        years += result.quot;
        days = result.rem; /*number of days in this year less than 365*/
    }
    timeptr->tm_year = years;
    timeptr->tm_yday = days; /*number of days per year*/
    /*28+31 + leap day*/
    n = 59 + leapyear;
    if (days < n) {
        /*the months is jan and feb*/
        result = div(days, 31);
        timeptr->tm_mon = result.quot; /*ndays is 55/31 = 1 = feb */
        timeptr->tm_mday = result.rem; /*55%31 = 24*/
    } else {
        days -= n; /*remove the feb and jun from days*/
        result = div(days, 153); /*form  month agust and dec is 153 day and march to july is 153 day*/
        timeptr->tm_mon = 2 + result.quot * 5; /*2 is jun and feb months + 5 is days > 153 is second group else is first group*/
        /* map into a 61 day  of months 30 +31 */
        result = div(result.rem, 61);
        timeptr->tm_mon += result.quot * 2; /*2 is two group*/
        /*get day by month*/
        result = div(result.rem, 31);
        timeptr->tm_mon += result.quot;
        timeptr->tm_mday = result.rem;
    }
    timeptr->tm_mday++; /* start form 1 */
}

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < PrintDate >                                                                 |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintDate                                                                         |
 | < @Description       : convert the date to assii  format sat jan 1  00:00:00                                                            |
 | < @Param timeptr     : ponter of the date time struct                                                         | 
 | < @Param buffer      : pinter to store date                                                                   |
 | < @return            : void                                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 */
//void PrintDate(tm_t * timeptr, char *buffer) {
//    uint8_t i, m, d;
//    div_t result;
//    d = timeptr->tm_wday * 3; /*name of the day week has 3 char */
//    m = timeptr->tm_mon * 3; /*name of the month is 3 char*/
//    for (i = 0; i < 3; i++) {
//        buffer[i] = pgm_read_byte(ascdays + d++); /*0 to 2 and space is index 3 ++*/
//        buffer[i + 4] = pgm_read_byte(ascmonths + m++); /*4 to 6 and space in index 7*/
//    }
//    buffer[3] = ',';
//    buffer[7] = ' ';
//    buffer += 8; /*start index of the time*/
//    __print_2Digit(timeptr->tm_mday, buffer, ' '); /*SAT  jan 5*/
//    buffer += 3; /*mday has 3 char 2 char digit and 1 char space*/
//    /*show the clock*/
//    __print_2Digit(timeptr->tm_hour, buffer, ':');
//    buffer += 3;
//    __print_2Digit(timeptr->tm_min, buffer, ':');
//    buffer += 3;
//    __print_2Digit(timeptr->tm_sec, buffer, ' ');
//    buffer += 3;
//    result = div(timeptr->tm_year + RTC_BASE_TIME, 100);
//    __print_2Digit(result.quot, buffer, ' ');
//    buffer += 2;
//    __print_2Digit(result.rem, buffer, 0);
//}

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < PrintDate >                                                                 |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintDate                                                                         |
 | < @Description       : convert the date to assii  format Fri, 20 Jan 2023                                                            |
 | < @Param timeptr     : ponter of the date time struct                                                         | 
 | < @Param buffer      : pinter to store date                                                                   |
 | < @return            : void                                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 */
void PrintDate(tm_t * timeptr, uint8_t *buffer) {
    uint8_t m, d;
    div_t result;
    d = timeptr->tm_wday * 3; /*name of the day week has 3 char */
    m = timeptr->tm_mon * 3; /*name of the month is 3 char*/
    for (uint8_t i = 0; i < 3; i++) {
#if COMPILER_TYPE == GCC
        buffer[i] = pgm_read_byte(ascdays + d++); /*0 to 2 and space is index 3 ++*/
#elif COMPILER_TYPE == XC
        buffer[i] = (ascdays[d++]); /*0 to 2 and space is index 3 ++*/
#endif
    }
    buffer[3] = ',';
    buffer += 4; /*start index of the date*/
    __print_2Digit(timeptr->tm_mday, buffer, ' '); /*SAT  jan 5*/
    for (uint8_t i = 0; i < 3; i++) {
#if COMPILER_TYPE == GCC
        buffer[i + 3] = pgm_read_byte(ascmonths + m++); /*0 to 2 and space is index 3 ++*/
#elif COMPILER_TYPE == XC
        buffer[i + 3] = (ascmonths [m++]); /*0 to 2 and space is index 3 ++*/
#endif

    }
    buffer[6] = ' ';
    buffer += 7; /*start index of the Year*/
    result = div(timeptr->tm_year + RTC_BASE_TIME, 100);
    __print_2Digit(result.quot, buffer, ' ');
    buffer += 2;
    __print_2Digit(result.rem, buffer, 0);
}

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < PrintTime >                                                                 |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintDate                                                                         |
 | < @Description       : convert the date to assii  format  00:00:00                                                            |
 | < @Param timeptr     : ponter of the date time struct                                                         | 
 | < @Param buffer      : pinter to store date                                                                   |
 | < @return            : void                                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 */
void PrintTime(tm_t * timeptr, uint8_t *buffer) {
    __print_2Digit(timeptr->tm_hour, buffer, ':');
    buffer += 3;
    __print_2Digit(timeptr->tm_min, buffer, ':');
    buffer += 3;
    __print_2Digit(timeptr->tm_sec, buffer, ' ');
}

