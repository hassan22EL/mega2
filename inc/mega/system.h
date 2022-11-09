/*
------------------------------------------------------------------------------------------
|                          < Module  Definition >                                        | 
------------------------------------------------------------------------------------------
| < FILE                   : system.c                                                    |                                  
| < Author                 : overflow problem solutions created by eng-Ahmed Saied       |
|                          : and most implementations by Hassan Elsaied                  | 
| < Version                : Mega2v241022                                                |
| < References             : no-used references in this documents                        |
| < SRAM_USAGE             : 14 Byte                                                     |
| < PROGRAM_USAGE          : 634 byte (317 Instruction)                                  |
| < Hardware Usage         : Timer 0                                                     |
| < File Created           : 24-10-2022                                                  |
-------------------------------------------------------------------------------------------
 */

#ifndef XC_SYS_H
#define	XC_SYS_H


#include "../mega.h"
/*work timer as */
/* 
 * ******************************************************************************
 *                        Macro  Definition                                     *
 * ******************************************************************************
 */



/* 
 * ******************************************************************************
 *                          I/O Clock                                           *
 * ******************************************************************************
 */
#ifndef F_CPU 
#warning Please define F_CPU 
#endif 

/* 
 * ******************************************************************************
 *                      setupHwTimer0                                 *
 * ******************************************************************************
 * @param  Timer  :is a store current Time 
 * @param  Period : store difference time between current time and  time to be arriver
 * 
 */
typedef struct {
    uint32_t Timer;
    uint32_t Period;
} stTimer_t;

typedef struct {
    uint32_t EndTime;
} stTimer_TimeOut_t;
/*
 * ******************************************************************************
 *                      Functions Declarations                                  *
 * ******************************************************************************
 */

/* 
 * ******************************************************************************
 *                      startHwTimer0                                 *
 * ******************************************************************************
 * enable the CTC mode interrupt 
 * enable  general interrupt
 * and set timer value
 * @return void 
 */
static inline void startHwTimer0();
/* 
 * ******************************************************************************
 *                       stopHwTimer0                                  *
 * ******************************************************************************
 * disable the CTC mode interrupt 
 * clear value from CTC register
 * clear perscaller 
 * @return void 
 * @note : is call this function the any driver  based general interrupt 
 *       : is not working after execution this function.
 */
static inline void stopHwTimer0();
/* 
 * ******************************************************************************
 *                       sysSetPeriodUs                                  *
 * ******************************************************************************
 * @benfit       : set period micro in the software timer 
 * @param psTimer: pointer of software Timer 
 * @param Period : period required y microsecond
 * @return void 
 */

static inline void sysSetPeriodUs(stTimer_TimeOut_t *psTimer, micros_t Period);
/* 
 * ******************************************************************************
 *                       sysSetPeriodMS                                          *
 * ******************************************************************************
 * @benfit       : set period by ms in the software timer 
 *@param psTimer: pointer of software Timer 
 * @param Period : period required y ms
 * @return void 
 */


static inline void sysSetPeriodMS(stTimer_TimeOut_t * psTimer, millis_t Period);
/* 
 * ******************************************************************************
 *                       sysSetPeriodS                                          *
 * ******************************************************************************
 * @benfit       : set period by second in the software timer 
 * @param psTimer: pointer of software Timer 
 * @param Period : period required by second
 * @return void 
 */

static inline void sysSetPeriodS(stTimer_TimeOut_t * psTimer, time_t Period);
/* 
 * ******************************************************************************
 *                       systemInit                                          *
 * ******************************************************************************
 * @benfit     :reset all data of the system driver
 * @return void 
 */


void systemInit();
/* 
 * ******************************************************************************
 *                       sysTimerInitMS                                          *
 * ******************************************************************************
 * @benfit          : assignment period and data delay of periodic software timer by micro system
 * @param psTimer   : pointer of software Timer 
 * @param Period    : period required by mirco    
 * @param Delay     : delay required before start periodic timer by micro count
 * @return  void 
 */
void sysTimerInitUs(stTimer_t *psTimer, micros_t Delay, micros_t Period);
/* 
 * ******************************************************************************
 *                       sysTimerInitMS                                          *
 * ******************************************************************************
 * @benfit       :assignment period and data delay of periodic software timer by ms
 * @param psTimer: pointer of software Timer 
 * @param Period : period required by ms
 * @return void 
 */

void sysTimerInitMS(stTimer_t *psTimer, millis_t Delay, millis_t Period);
/* 
 * ******************************************************************************
 *                        sysTimerInitS                                          *
 * ******************************************************************************
 * @benfit       :assignment period and data delay of periodic software timer by seconds
 * @param psTimer: pointer of software Timer 
 * @param Period : period required by seconds
 * @return void
 */

void sysTimerInitS(stTimer_t *psTimer, time_t Delay, time_t Period);
/* 
 * ******************************************************************************
 *                       sysIsTimeoutUs                                          *
 * ******************************************************************************
 * @benfit        : get current value from timer 0 counter and return micros and 
 *                : check of the period is expired or not by compared millis system and timer stored value
 *                : the time out is return  after expired ms period
 * @param psTimer : pointer of software timer 
 * @return        : 1  when timer doesn't  expired period
 *                : 0  when timer does expired period
 */
uint8_t sysIsTimeoutUs(stTimer_TimeOut_t *psTimer);
/* 
 * ******************************************************************************
 *                       sysIsTimeoutMs                                          *
 * ******************************************************************************
 * @benfit        : check of the period is expired or not by compared micro system and timer stored value
 *                : the time out is return  after expired ms period
 * @param psTimer : pointer of software timer 
 * @return        : 1  when timer doesn't  expired period
 *                : 0  when timer does expired period
 */
uint8_t sysIsTimeoutMs(stTimer_TimeOut_t *psTimer);
/* 
 * ******************************************************************************
 *                       sysIsTimeoutS                                          *
 * ******************************************************************************
 * @benfit        : check of the period is expired or not by compared second system  system and timer stored value
 *                : the time out is return  after expired second period
 * @param psTimer : pointer of software timer 
 * @return        : 1  when timer doesn't  expired period
 *                : 0  when timer does expired period
 */
uint8_t sysIsTimeoutS(stTimer_TimeOut_t *psTimer);

/* 
 * ******************************************************************************
 *                      setupHwTimer0                                 *
 * ******************************************************************************
 * set perscaller 
 * set timer in CTC 
 * and set timer value 
 * @return void
 */
void setupHwTimer0();
/* 
 * ******************************************************************************
 *                       sysTimerResetUS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart Us
 * @param psTimer : pointer of software timer 
 * @return void
 */
void sysTimerResetUS(stTimer_t *psTimer);

/* 
 * ******************************************************************************
 *                       sysTimerResetMS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart ms
 * @param psTimer : pointer of software timer 
 * @return void
 */
void sysTimerResetMS(stTimer_t *psTimer);

/* 
 * ******************************************************************************
 *                       sysTimerReseS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart seconds
 * @param psTimer : pointer of software timer 
 * @return void
 */
void sysTimerResetS(stTimer_t *psTimer);
/* 
 * ******************************************************************************
 *                       sysTimerCheckUs                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart with us
 * @param psTimer : pointer of software timer 
 * @return        :0 when the periodic period is done and restart the next period by same value 
 *                :1 when timer doesn't  expired current period
 */
uint8_t sysTimerCheckUs(stTimer_t *psTimer);
/* 
 * ******************************************************************************
 *                       sysTimerCheckMs                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart with ms 
 * @param psTimer : pointer of software timer 
 * @return        :0 when the periodic period is done and restart the next period by same value 
 *                :1 when timer doesn't  expired current period
 */
uint8_t sysTimerCheckMs(stTimer_t *psTimer);
/* 
 * ******************************************************************************
 *                       sysTimerCheckS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart with second
 * @param psTimer : pointer of software timer 
 * @return        :0 when the periodic period is done and restart the next period by same value 
 *                :1 when timer doesn't  expired current period
 */
uint8_t sysTimerCheckS(stTimer_t *psTimer);
/* 
 * ******************************************************************************
 *                       getSystemTick                                          *
 * ******************************************************************************
 * @benfit     : set current timestamp from external sources for example 
 *             : up date no from computer or RTC module or network 
 * @return void
 */
void sysUpdateNow(time_t now);
/* 
 * ******************************************************************************
 *                       getSystemMillis                                          *
 * ******************************************************************************
 * @benfit     : get current millis data of the system 
 * @return     : get current millis 
 */

millis_t systemMillis();
/* 
 * ******************************************************************************
 *                       sysMicros                                          *
 * ******************************************************************************
 * @benfit        : get current micros form hardware timer 
 * @return        : time per microsecond
 */
micros_t systemMicros();

/* 
 * ******************************************************************************
 *                       sysGetCurrent Time                                          *
 * ******************************************************************************
 * @benfit       : get time stamp value
 * @return       : current time stamp step is one seconde
 */
time_t systemNow();
/* 
 * ******************************************************************************
 *                       systemRTC Time                                          *
 * ******************************************************************************
 * @benfit       : update the rtc function
 *               : this function run in back ground please don't call the function
 * @return       : current time stamp step is one second
 */
void systemRTC();

/*
 * ******************************************************************************
 *                   in lineFunctions Implementations                           *
 * ******************************************************************************
 */


/* 
 * ******************************************************************************
 *                      startHwTimer0                                 *
 * ******************************************************************************
 * enable the CTC mode interrupt 
 * enable  general interrupt
 * and set timer value
 * @return void 
 */
static inline void startHwTimer0() __attribute__((always_inline, unused));

static inline void startHwTimer0() {
    // enable timer 0 overflow interrupt
#if defined(TIMSK) &&  defined (OCIE0)
    sbi(TIMSK, OCIE0);
#elif  defined(TIMSK) && defined (TOIE0)
    sbi(TIMSK, TOIE0);
#elif defined(TIMSK0) && defined(OCIE0A)
    sbi(TIMSK0, OCIE0A);
#else
#error	Timer 0 overflow interrupt not set correctly
#endif
    sei();
}

/* 
 * ******************************************************************************
 *                       stopHwTimer0                                  *
 * ******************************************************************************
 * disable the CTC mode interrupt 
 * clear value from CTC register
 * clear perscaller 
 * @return void 
 * @note : is call this function the any driver  based on general interrupt 
 *       : is not working after execution this function.
 */
static inline void stopHwTimer0() __attribute__((always_inline, unused));

static inline void stopHwTimer0() {
    cli(); //
    // enable timer 0 overflow interrupt
#if defined(TIMSK) &&  defined (OCIE0)
    cbi(TIMSK, OCIE0);
#elif  defined(TIMSK) && defined (TOIE0)
    cbi(TIMSK, TOIE0);
#elif defined(TIMSK0) && defined(OCIE0A)
    cbi(TIMSK0, OCIE0A);
#else
#error	Timer 0 overflow interrupt not set correctly
#endif
}


/* 
 * ******************************************************************************
 *                       sysSetPeriod                                  *
 * ******************************************************************************
 * @benfit       : set period tick in the software timer 
 * @param psTimer: pointer of software Timer 
 * @param Period : period required y microsecond
 * @return void 
 */
static inline void sysSetPeriodUs(stTimer_TimeOut_t *psTimer, micros_t Period) __attribute__((always_inline, unused));

static inline void sysSetPeriodUs(stTimer_TimeOut_t *psTimer, micros_t Period) {
    /*no convert this data assign end Data*/
    psTimer->EndTime = systemMicros() + Period;

}

/* 
 * ******************************************************************************
 *                       sysSetPeriodMS                                          *
 * ******************************************************************************
 * @benfit       : set period by ms in the software timer 
 *@param psTimer: pointer of software Timer 
 * @param Period : period required by ms
 * @return void 
 */
static inline void sysSetPeriodMS(stTimer_TimeOut_t *psTimer, millis_t Period) __attribute__((always_inline, unused));

static inline void sysSetPeriodMS(stTimer_TimeOut_t* psTimer, millis_t Period) {
    psTimer->EndTime = systemMillis() + Period;
}

/* 
 * ******************************************************************************
 *                       sysSetPeriodS                                          *
 * ******************************************************************************
 * @benfit       : set period by second in the software timer 
 * @param psTimer: pointer of software Timer 
 * @param Period : period required by second
 * @return void 
 */

static inline void sysSetPeriodS(stTimer_TimeOut_t* psTimer, time_t Period) {
    psTimer->EndTime = systemNow() + Period;
}

#endif	/* XC_SYS_H */

