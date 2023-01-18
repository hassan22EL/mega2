
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
typedef struct {
    uint8_t tm_sec;
    uint8_t tm_min;
    uint8_t tm_hour;
    uint8_t tm_mday;
    uint8_t tm_wday;
    uint8_t tm_mon;
    uint8_t tm_year;
    int16_t tm_yday;
} tm_t;

/*
 -----------------------------------------------------------------------------------------------------------------
 |                          < _WEEK_DAYS_ >                                                                      |  
 -----------------------------------------------------------------------------------------------------------------
 */
enum _WEEK_DAYS_ {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

/*
 -----------------------------------------------------------------------------------------------------------------
 |                          <  Enumerated labels for the months >                                                |  
 -----------------------------------------------------------------------------------------------------------------
 */
enum _MONTHS_ {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};


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
time_t getTime(tm_t *timeptr);
/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 < getDate >                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 | < @Function          : void getDate                                                                           |
 | < @Description       : convert current time form date to timestamp                                            |
 | < @Param timeptr     : ponter of the date time struct                                                         | 
 | < @Param timer       : pointer of the timestamp                                                               |
 | < @return            : void                                                                                   |
 -----------------------------------------------------------------------------------------------------------------
 */
void getDate(time_t *timer, tm_t *timeptr);

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
void PrintDate(tm_t * timeptr, char *buffer);
#endif	/* TIME_H */

