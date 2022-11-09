
/*
------------------------------------------------------------------------------------------
|                          < Module  Definition >                                        | 
------------------------------------------------------------------------------------------
| < FILE                   : system.c                                                    |                                  
| < Author                 : overflow problem solutions created by eng /Ahmed Saied      |
|                          : and most implementations by Hassan Elsaied                  | 
| < Version                : Mega2v241022                                                |
| < References             : no-used references in this documents                        |
| < SRAM_USAGE             : 14 Byte                                                     |
| < PROGRAM_USAGE          : 634 byte (317 Instruction)                                  |
| < Hardware Usage         : Timer 0                                                     |
| < File Created          : 24-10-2022                                                   |
-------------------------------------------------------------------------------------------
 */

#include "../../../inc/mega.h"
/* 
 * ******************************************************************************
 *                          max value of the timer                                              *
 * ******************************************************************************
 */
#define SYSTEM_MAX          (0x7FFFFFFFUL)
#define SYSTEM_TIME_MAX     (0xFFFFFFFFUL)



#ifndef   N_OF_US_REQUIRED
#error  "Pelase defined N_OF_US_REQUIRED and set value 1 to n look resource.h to have n required"
#else
/* 
 * ******************************************************************************
 *                          Timer Value and Prescaller                             *
 * ******************************************************************************
 */


#if F_CPU == XTAL_08000000

#elif F_CPU == XTAL_11059200
#if   N_OF_US_REQUIRED == _0625us
#if defined(TCCR0A) && defined(WGM01) 
#define  TIMER_MODE1    (sbi(TCCR0A, WGM01))
#define  TIMER_MODE0    (cbi(TCCR0A, WGM00))
#endif

// set timer 0 prescale factor to 64
#if defined(__AVR_ATmega128__) ||  defined(__AVR_ATmega128A__)
// CPU specific: different values for the ATmega128
#define  PRESCALLER2         (sbi(TCCR0 , CS02))
#define  TIMER_MODE1         (sbi(TCCR0, WGM01))
#define  TIMER_MODE0         (cbi(TCCR0, WGM00))
#elif defined(TCCR0) && defined(CS01) && defined(CS00)
// this combination is for the standard atmega8 the overflow only
#define PRESCALLER1            (sbi(TCCR0, CS01))
#define PRESCALLER0            (sbi(TCCR0, CS00))
/*the timer in normal MODE*/
#elif defined(TCCR0B) && defined(CS01) && defined(CS00)
// this combination is for the standard 168/328/1280/2560
#define PRESCALLER1          (sbi(TCCR0B, CS01))
#define PRESCALLER0          (sbi(TCCR0B, CS00))
#define TIMER_MODE2          (sbi(TCCR0A, WGM02))
#elif defined(TCCR0A) && defined(CS01) && defined(CS00)
// this combination is for the __AVR_ATmega645__ series
#define  PRESCALLER1         (sbi(TCCR0, CS01))
#define  PRESCALLER0         (sbi(TCCR0, CS00))
#define  TIMER_MODE1         (sbi(TCCR0A, WGM01));
#define  TIMER_MODE0         (sbi(TCCR0A, WGM00));
#else
#error Timer 0 prescale factor 64 not set correctly
#endif
#define  TIME_VALUE               (108)
#define  CLOCK_DIVID              (64)
#define MICROSECONDS_PER_TIMER0_OVERFLOW  _0625us
#elif N_OF_US_REQUIRED == _1250us 
#if defined(TCCR0A) && defined(WGM01) 
#define  TIMER_MODE1    (sbi(TCCR0A, WGM01))
#define  TIMER_MODE0    (cbi(TCCR0A, WGM00))
#endif

// set timer 0 prescale factor to 64
#if defined(__AVR_ATmega128__) ||  defined(__AVR_ATmega128A__)
// CPU specific: different values for the ATmega128
#define  PRESCALLER2         (sbi(TCCR0 , CS02))
#define  TIMER_MODE1         (sbi(TCCR0, WGM01))
#define  TIMER_MODE0         (cbi(TCCR0, WGM00))
#elif defined(TCCR0) && defined(CS01) && defined(CS00)
// this combination is for the standard atmega8 the overflow only
#define PRESCALLER1            (sbi(TCCR0, CS01))
#define PRESCALLER0            (sbi(TCCR0, CS00))
/*the timer in normal MODE*/
#elif defined(TCCR0B) && defined(CS01) && defined(CS00)
// this combination is for the standard 168/328/1280/2560
#define PRESCALLER1          (sbi(TCCR0B, CS01))
#define PRESCALLER0          (sbi(TCCR0B, CS00))
#define TIMER_MODE2          (sbi(TCCR0A, WGM02))
#elif defined(TCCR0A) && defined(CS01) && defined(CS00)
// this combination is for the __AVR_ATmega645__ series
#define  PRESCALLER1         (sbi(TCCR0, CS01))
#define  PRESCALLER0         (sbi(TCCR0, CS00))
#define  TIMER_MODE1         (sbi(TCCR0A, WGM01));
#define  TIMER_MODE0         (sbi(TCCR0A, WGM00));
#else
#error Timer 0 prescale factor 64 not set correctly
#endif
#define  TIME_VALUE                        (216)
#define  CLOCK_DIVID                       (64)
#define MICROSECONDS_PER_TIMER0_OVERFLOW  _1250us
#elif N_OF_US_REQUIRED == _1875us
#define  TIME_VALUE               (81)
#define  CLOCK_DIVID              (256)
#elif N_OF_US_REQUIRED == _2500us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (108)
#define  CLOCK_DIVID              (256)
#elif N_OF_US_REQUIRED == _3125us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (135)
#define  CLOCK_DIVID              (256)
#elif N_OF_US_REQUIRED == _3750us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (162)
#define  CLOCK_DIVID              (256)
#elif N_OF_US_REQUIRED == _4375us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (189)
#define  CLOCK_DIVID              (256)
#elif N_OF_US_REQUIRED == _5000us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (216)
#define  CLOCK_DIVID              (256)
#elif N_OF_US_REQUIRED  ==  _5625us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (243)
#define  CLOCK_DIVID              (256)
#elif N_OF_US_REQUIRED  == _7500us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (81)
#define  CLOCK_DIVID              (1024)
#elif N_OF_US_REQUIRED  == _10000us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (108)
#define  CLOCK_DIVID              (1024)
#elif N_OF_US_REQUIRED  == _12500us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (135)
#define  CLOCK_DIVID              (1024)
#elif N_OF_US_REQUIRED  == _15000us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (162)
#define  CLOCK_DIVID              (1024)
#elif N_OF_US_REQUIRED  == _17500us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (189)
#define  CLOCK_DIVID              (1024)
#elif N_OF_US_REQUIRED  == _20000us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (216)
#define  CLOCK_DIVID              (1024)
#elif N_OF_US_REQUIRED  == _22500us
#define  nCS00                    ()
#define  nCS01                    ()
#define  nCS02                    ()
#define  TIME_VALUE               (243)
#define  CLOCK_DIVID              (1024)
#else
#error "please select time vaild look "
#endif
#elif F_CPU == XTAL_12000000
#elif F_CPU == XTAL_14745600
#elif F_CPU == XTAL_16000000
#elif F_CPU == XTAL_20000000
#error  "F_CPU is not suporrted"
#endif
#endif











/* 
 * ******************************************************************************
 *                          number of milli seconds per interrupt                             *
 * ******************************************************************************
 * ms = 1000 us to convert  number of us /1000
 */
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
/* 
 * ******************************************************************************
 *                          get number of us per after miils                             *
 * ******************************************************************************
 * fraction variable 0 to 1000 by divide 2^8 to fit number into
 * one byte this 1000 is max number of fraction mapping to 125
 * 
 */
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)


/* 
 * ******************************************************************************
 *                          variable                             *
 * ******************************************************************************
   @var gu32SystemTick      : system interrupt counter
 * @var g32TimeMs           : number of ms
 * @var gu8NumberOFus       : number of us per ms
 * @var g32SystemTime       : number of second in the system from last update data
 * @var gu8NumberOFusPerMs  : number of ms in second
 * 
 */
static volatile tick_t gu32SystemTick;
static volatile millis_t gu32TimeMs;
static volatile time_t gu32SystemTime;

static volatile uint8_t gu8NumberOFusPerMs;
static volatile uint8_t gu8NumberOFMsPerS;
/*Fractions*/
#if defined(OCR0) 
ISR(TIMER0_COMP_vect)
#elif defined (OCR0A)
ISR(TIMER0_COMPA_vect)
#elif defined (TIMER0_OVF_vect)

ISR(TIMER0_OVF_vect)
#endif
{

    /*store data in local variables can be stored in registers*/
    millis_t m = gu32TimeMs;
    time_t s = gu32SystemTime;
    uint8_t f = gu8NumberOFusPerMs;
    uint8_t fs = gu8NumberOFMsPerS;

    /*milli event*/
    m += MILLIS_INC;
    f += FRACT_INC;
    if (f >= FRACT_MAX) {
        f -= FRACT_MAX;
        m++;
    }

    /*second event*/
    s = (m / 1000);
    fs = ((m % 1000) >> 3);

    if (fs >= FRACT_INC) {
        fs -= FRACT_INC;
        s++;
    }


    /*task is run per time*/
#if defined KEYPAD_MODULE       
#if   KEYPAD_MODULE == MODULE_ENABLE
    if (m % KEY_PERIDIC_TASK == 0) {
        keyscan();
    }
#endif
#endif
    /*stored registers into memory */
    gu32TimeMs = m;
    gu8NumberOFusPerMs = f;
    gu32SystemTime = s;
    gu8NumberOFMsPerS = fs;
    /*update second event*/


#if defined(TIMSK) &&  defined (OCIE0)
    /*auto reload*/
#elif  defined(TIMSK) && defined (TOIE0)
    TCNT0 = 0xFF - TIME_VALUE;
#elif defined(TIMSK0) && defined(OCIE0A)
    /*auto reload*/
#else
#error	Timer 0 overflow interrupt not set correctly
#endif



}

/* 
 * ******************************************************************************
 *                       systemInit                                          *
 * ******************************************************************************
 * @benfit     :reset all data of the system driver
 * @return void 
 */
void systemInit() {
    gu32SystemTick = 0;
    gu32TimeMs = 0;
    gu32SystemTime = 0;
    gu8NumberOFusPerMs = 0;
    gu8NumberOFMsPerS = 0;
}

/* 
 * ******************************************************************************
 *                       sysTimerInitMS                                          *
 * ******************************************************************************
 * @benfit          : assignment period and data delay of periodic software timer by micro system
 * @param psTimer   : pointer of software Timer 
 * @param Period    : period required by mirco    
 * @param tickDelay : delay required before start periodic timer by micro count
 * @return  void  
 */
void sysTimerInitUs(stTimer_t *psTimer, micros_t Delay, micros_t Period) {
    /*if delay > max set  delay  as max*/
    if (Delay > SYSTEM_MAX) {
        Delay = SYSTEM_MAX;
    }
    /*if period > max set  period  as max*/
    if (Period > SYSTEM_MAX) {
        Period = SYSTEM_MAX;
    }
    psTimer->Timer = systemMicros(); /*set current micros*/
    if (Delay != 0) {
        psTimer->Timer += Delay; /*delay before  start periodic timer*/
    } else {
        psTimer->Timer += Period; /*start periodic timer*/
    }
    psTimer->Period = Period; /*assignment period*/
}

/* 
 * ******************************************************************************
 *                       sysTimerInitMS                                          *
 * ******************************************************************************
 * @benfit       :assignment period and data delay of periodic software timer by ms
 * @param psTimer: pointer of software Timer 
 * @param Period : period required by ms
 * @return       : void 
 *                
 */

void sysTimerInitMS(stTimer_t *psTimer, millis_t Delay, millis_t Period) {
    /*if delay > max set  delay  as max*/
    if (Delay > SYSTEM_MAX) {
        Delay = SYSTEM_MAX;
    }
    /*if period > max set  period  as max*/
    if (Period > SYSTEM_MAX) {
        Period = SYSTEM_MAX;
    }

    psTimer->Timer = systemMillis(); /*set current millis*/
    if (Delay != 0) {
        psTimer->Timer += Delay; /*delay before  start periodic timer*/
    } else {
        psTimer->Timer += Period; /*start periodic timer*/
    }
    psTimer->Period = Period; /*assignment period*/
}

/* 
 * ******************************************************************************
 *                        sysTimerInitS                                          *
 * ******************************************************************************
 * @benfit       :assignment period and data delay of periodic software timer by seconds
 * @param psTimer: pointer of software Timer 
 * @param Period : period required by seconds
 * @return void    
 */

void sysTimerInitS(stTimer_t *psTimer, time_t Delay, time_t Period) {
    /*if delay > max set  delay  as max*/
    if (Delay > SYSTEM_TIME_MAX) {
        Delay = SYSTEM_TIME_MAX;
    }
    /*if period > max set  period  as max*/
    if (Period > SYSTEM_TIME_MAX) {
        Period = SYSTEM_TIME_MAX;
    }
    psTimer->Timer = systemNow(); /*set current time*/
    if (Delay != 0) {
        psTimer->Timer += Delay; /*delay before  start periodic timer*/
    } else {
        psTimer->Timer += Period; /*start periodic timer*/
    }
    psTimer->Period = Period; /*assignment period*/
}

/* 
 * ******************************************************************************
 *                       sysIsTimeoutUs                                          *
 * ******************************************************************************
 * @benfit        : get current value from timer 0 counter and return micros and 
 *                : check of the period is expired or not by compared  system and timer stored value
 *                : the time out is return  after expired ms period
 * @param psTimer : pointer of software timer 
 * @return        : 1  when timer doesn't  expired period
 *                : 0  when timer does expired period
 */
uint8_t sysIsTimeoutUs(stTimer_TimeOut_t *psTimer) {
    millis_t End, Current;

    if (psTimer->EndTime > (SYSTEM_MAX)) {
        //error case
        return (0);
    }
    End = psTimer->EndTime;
    Current = systemMicros();
    if (((Current ^ End) & (SYSTEM_MAX + 1)) == 0) {
        if (Current >= End) {
            return (0);
        }
    }
    return (1);
}

/* 
 * ******************************************************************************
 *                       sysIsTimeoutMs                                          *
 * ******************************************************************************
 * @benfit        : check of the period is expired or not by compared  system and timer stored value
 *                : the time out is return  after expired ms period
 * @param psTimer : pointer of software timer 
 * @return        : 1  when timer doesn't  expired period
 *                : 0  when timer does expired period
 */
uint8_t sysIsTimeoutMs(stTimer_TimeOut_t *psTimer) {
    millis_t End, Current;

    if (psTimer->EndTime > (SYSTEM_MAX)) {
        //error case 
        return (0);
    }
    End = psTimer->EndTime;
    Current = systemMillis(); /*now*/
    if (((Current ^ End) & (SYSTEM_MAX + 1)) == 0) {
        if (Current >= End) {
            return (0);
        }
    }
    return (1);
}

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
uint8_t sysIsTimeoutS(stTimer_TimeOut_t *psTimer) {
    time_t End, Current;

    if (psTimer->EndTime > (SYSTEM_MAX)) {
        //error case
        return (0);
    }
    End = psTimer->EndTime;
    Current = systemNow();
    if (Current >= End) {
        return (0);
    }
    return (1);
}

/* 
 * ******************************************************************************
 *                       sysTimerResetUS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart Us
 * @param psTimer : pointer of software timer 
 * @return void
 */
void sysTimerResetUS(stTimer_t *psTimer) {
    /*reload period and add current time */
    psTimer->Timer = psTimer->Period;
    psTimer->Timer += systemMicros();
}

/* 
 * ******************************************************************************
 *                       sysTimerResetMS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart ms
 * @param psTimer : pointer of software timer 
 * @return void
 */
void sysTimerResetMS(stTimer_t *psTimer) {
    /*reload period and add current time */
    psTimer->Timer = psTimer->Period;
    psTimer->Timer += systemMillis();
}

/* 
 * ******************************************************************************
 *                       sysTimerReseS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart seconds
 * @param psTimer : pointer of software timer 
 * @return void
 */
void sysTimerResetS(stTimer_t *psTimer) {
    /*reload period and add current time */
    psTimer->Timer = psTimer->Period;
    psTimer->Timer += systemNow();
}

/* 
 * ******************************************************************************
 *                       sysTimerCheckUs                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart with us
 * @param psTimer : pointer of software timer 
 * @return        :0 when the periodic period is done and restart the next period by same value 
 *                :1 when timer doesn't  expired current period
 */
uint8_t sysTimerCheckUs(stTimer_t *psTimer) {
    micros_t sysmicros;
    if (psTimer->Period == SYSTEM_MAX) {
        return (0);
    }
    sysmicros = systemMicros();
    if ((((sysmicros) ^ (psTimer->Timer)) & ((SYSTEM_MAX) + 1)) == 0) {
        if (sysmicros >= psTimer->Timer) {
            if (psTimer->Period != 0) {
                psTimer->Timer += psTimer->Period;
            } else {
                psTimer->Period = SYSTEM_MAX;
            }
            return (0); /*function is done*/
        }
    }
    return (1); /*function in progress*/
}

/* 
 * ******************************************************************************
 *                       sysTimerCheckMs                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart with ms 
 * @param psTimer : pointer of software timer 
 * @return        :0 when the periodic period is done and restart the next period by same value 
 *                :1 when timer doesn't  expired current period
 */
uint8_t sysTimerCheckMs(stTimer_t *psTimer) {
    millis_t sysmillis;
    if (psTimer->Period == SYSTEM_MAX) {
        return (0);
    }
    sysmillis = systemMillis();
    if ((((sysmillis) ^ (psTimer->Timer)) & ((SYSTEM_MAX) + 1)) == 0) {
        if (sysmillis >= psTimer->Timer) {
            if (psTimer->Period != 0) {
                psTimer->Timer += psTimer->Period;
            } else {
                psTimer->Period = SYSTEM_MAX;
            }
            return (0); /*function is done*/
        }
    }
    return (1); /*function in progress*/
}

/* 
 * ******************************************************************************
 *                       sysTimerCheckS                                          *
 * ******************************************************************************
 * @benfit        : periodic timer is restart with second
 * @param psTimer : pointer of software timer 
 * @return        :0 when the periodic period is done and restart the next period by same value 
 *                :1 when timer doesn't  expired current period
 */
uint8_t sysTimerCheckS(stTimer_t *psTimer) {
    time_t systime;
    if (psTimer->Period == SYSTEM_TIME_MAX) {
        return (0);
    }
    systime = systemNow();
    if (systime >= psTimer->Timer) {
        if (psTimer->Period != 0) {
            psTimer->Timer += psTimer->Period;
        } else {
            psTimer->Period = SYSTEM_TIME_MAX;
        }
        return (0); /*function is done*/
    }
    return (1); /*function in progress*/
}

/* 
 * ******************************************************************************
 *                       getSystemTick                                          *
 * ******************************************************************************
 * @benfit     : set current timestamp from external sources for example 
 *             : up date no from computer or RTC module or network 
 * @return void
 */
void sysUpdateNow(time_t now) {
    ATOMIC_BEGIN
    gu32SystemTime = now;
    ATOMIC_END
}

/* 
 * ******************************************************************************
 *                       getSystemMillis                                          *
 * ******************************************************************************
 * @benfit     : get current millis data of the system 
 * @return     : get current millis 
 */

millis_t systemMillis() {
    millis_t milli;
    ATOMIC_BEGIN
    milli = gu32TimeMs;
    ATOMIC_END
    return milli;
}

/* 
 * ******************************************************************************
 *                       sysMicros                                          *
 * ******************************************************************************
 * @benfit        : get current micros form hardware timer 
 * @return        : time per microsecond
 */
micros_t systemMicros() {
    tick_t currentInterruptTick;
    uint8_t t;
    ATOMIC_BEGIN
    currentInterruptTick = gu32SystemTick;
#if defined(TCNT0)
    t = TCNT0;
#elif defined(TCNT0L)
    t = TCNT0L;
#else
#error TIMER 0 not defined
#endif

#if defined(TIFR) &&   defined (OCF0)
    if ((TIFR & _BV(OCF0)) && (t >= OCR0)) /*the overflow at top value*/
        currentInterruptTick++;
#elif  defined(TIFR) && defined (TOV0)
    if ((TIFR & _BV(TOV0)) && (t < (256))) /*the overflow at max value*/
        currentInterruptTick++;
#elif defined(TIFR0) && defined(OCF0A)
    if ((TIFR0 & _BV(OCF0A)) && (t >= OCR0A)) /*the overflow at at compare match value*/
        currentInterruptTick++;
#else
#error	Timer 0  interrupt not set correctly
#endif

    /*
     *
     * first method
     * for example 500 us = (500/1000000) * 11059200 clock cycle/sec = 5529.6 clock cycle 
     * number of clock cycle per sec / clock  divide = timer count per  500us = 86.4 + (number of interrupt * interrupt period)
     * the 86.6 is defined this value between 86 and 87 
     *  first interrupt period and timer required per us is x
     * (x*F_CPU / 1000000UL) = n clock cycle
     * time value in first interrupt (TVIFI) is = n clock cycle / clock divide 
     * TVIFI =  (x*F_CPU / 1000000UL) / clock divide
     * TVIFI =   x*F_CPU / (10^6 * clock divide)
     * TVIF  * (10^6 * clock divide) =  x*F_CPU
     * x = (10^6 * clock divide)*TVIF /F_CPU
     * at assume the time value 86 
     * x= 1000000UL *64 * 86  /F_CPU = 497.6 +.5 = 498 error is 2 us ==> error parentage is (2/500)*100 =.4%
     * at assume the time value 87 
     * this solution is  large than 2^32 at multi value to that not recommend solution
     * (CLOCK_DIVID*1000000UL  * (t + (currentInterruptTick * TIME_VALUE))) / F_CPU;
     * x= 1000000UL *64 * 87  /F_CPU = 503.47 +.5 = 503 error is 3 us ==> error parentage  is (3/500) *100 =.6%
     * most application is check period by compare large than or equal 500 
     * most error error parentage  is (3/500) *100  = .6%
     * second method 
     * for example 500 us = (500) * (n  clock cycle/us) since clock cycle per us = F_CPU /10^6
     * 11059200 /  10^6     ==> 11 the .059200 is removed by assign data in integer
     * (CLOCK_DIVID*  * (t + (currentInterruptTick * TIME_VALUE))) / clockCyclesPerMicrosecond();
     * TVIFI = n clock cycle per us /clock divide
     * TVIFI = 500*11   / 64 is 85.9 time value between 86 or 85
     * TVIFI =   x * clock cycle per us / clock divide)) 
     *  x = TVIFI *(clock divide/clock cycle per us) = 86*(64/11) = 500 error parentage  is (1/500) *100 =0% 
     *  */
    ATOMIC_END
    return ((currentInterruptTick * TIME_VALUE) + t) * (CLOCK_DIVID / clockCyclesPerMicrosecond());


}

/* 
 * ******************************************************************************
 *                       sysGetCurrent Time                                          *
 * ******************************************************************************
 * @benfit       : get time stamp value
 * @return       : current time stamp step is one seconde
 */
time_t systemNow() {
    time_t time;
    ATOMIC_BEGIN
    time = gu32SystemTime;
    ATOMIC_END
    return time;
}

/* 
 * ******************************************************************************
 *                      setupHwTimer0                                 *
 * ******************************************************************************
 * set perscaller 
 * set timer in CTC 
 * and set timer value 
 * @return void
 */

void setupHwTimer0() {

#if defined(TCCR0A) && defined(WGM01) 
    TIMER_MODE1;
    TIMER_MODE0;
#endif

#if defined (OCR0A) 
    OCR0A = TIME_VALUE;
#endif



#if defined(__AVR_ATmega128__) ||  defined(__AVR_ATmega128A__)
    // CPU specific: different values for the ATmega128
    PRESCALLER2;
    TIMER_MODE1;
    TIMER_MODE0;
    /*load ctc value*/
    OCR0 = TIME_VALUE;
#elif defined(TCCR0) && defined(CS01) && defined(CS00) 
    // this combination is for the standard atmega8 the overflow only
    PRESCALLER1;
    PRESCALLER0;
    /*load timer value*/
    TCNT0 = 0xFF - TIME_VALUE; /*counter no reload value after interrupt can reload this value in Timer*/
#elif defined(TCCR0B) && defined(CS01) && defined(CS00)
    PRESCALLER1;
    PRESCALLER0;
    TIMER_MODE2;
#elif defined(TCCR0A) && defined(CS01) && defined(CS00)
    PRESCALLER1;
    PRESCALLER0;
    TIMER_MODE1;
    TIMER_MODE0;
#else
#error Timer 0 prescale factor not set correctly
#endif

}
