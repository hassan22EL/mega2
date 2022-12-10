
/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : signalGenerator.c                                                 |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : 10 Byte Per Signal   + 2 Byte Pointer to first signal in table    |
| < PROGRAM USAGE            : 1190 Byte (595 Instruction)                                       |                                     
| < Hardware Usage           : no-used                                                           |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if  defined SIGNALGENERATED_MODULE
#if  SIGNALGENERATED_MODULE

/*
 --------------------------------------------------------------------------------------------------
 |                                <   Macro   >                                      |
 --------------------------------------------------------------------------------------------------
 */
/*
 * <@avr SIGNAL_DUTY_HIGH(x , y)               :calcuale time of high from period y and duty x 
 */
#define    SIGNAL_DUTY_HIGH(x , y)          (uint16_t)((x*y)/100)

/*
 * <@avr SIGNAL_DUTY_LOW(x , y)      :     :calcuale time of low from period y and duty x 
 */
#define    SIGNAL_DUTY_LOW(x , y)           (uint16_t)(y- SIGNAL_DUTY_HIGH(x,y))
/*
 < @macro SIGNAL_NOT_STOP_CHECK :  Value of Stop  = SIGNAL_NOT_STOP - 1
 */
#define  SIGNAL_NOT_STOP_CHECK               (SIGNAL_NOT_STOP -1)

/*
 --------------------------------------------------------------------------------------------------
 |                                <   signal Descirption   >                                      |
 --------------------------------------------------------------------------------------------------
 */


typedef struct Signals_s {
    volatile uint16_t SignalPeriod; /*pin ass*/
    volatile uint16_t SignalTimerToggleCount;
    volatile uint8_t ToggleDuration;
    volatile uint8_t SleepDuration;
    volatile uint8_t SignalDurationcycles;
    volatile uint8_t SignalDuty; /*0 to 100*/
    volatile uint8_t SignalNEx;
    volatile byte_Flags_t SignalState;
}
/*
 --------------------------------------------------------------------------------------------------
 |                                <   signal Descirption   >                                      |
 --------------------------------------------------------------------------------------------------
 | < Description                   : signal struct                                                |
 | < Uasge                         : 10 Byte                                                      |                                     
 | < param SignalPeriod            : Time of one Cycle in Frequncy Require                        |
 | < Param ToggleDuration          : number of periodic this Frequncy                             |
 | < Param SleepDuration           : number of Cycle in sleep if the T = 50ms and sleep           |
                                   : duration is 3 the time watting in sleep is 3*50ms = 150ms    |
 | < Param SignalDurationcycles    : counter ro caluaclation is sleep duration and toggle duration|                                 |
 | < Param SignalTimerToggleCount  : run in ISR decrement and reset to 0                          |
 | < Param SignalDuty              : active state is low or high with 50% duty or 60 %            |
 | <@Param SignalNEx               : exeucate the signal 4 times and stop if this value is 0      |
 |                                 : the signal is not stopted by driver                          | 
 | < Param SignalState             : Signal state Per started timing                              |
 --------------------------------------------------------------------------------------------------
 */
SignalTiming_t;
/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
const Signal_t NullISignal PROGMEM = {(const Signal_t *) NULL, (const gpio_t) 0, (const uint8_t) 0};

/*
 --------------------------------------------------------------------------------------------------
 |                                <   Variables   >                                               |
 --------------------------------------------------------------------------------------------------
 */
/*
 * < @var gSignalsArray    : Indxing access of the signal data 
 */
SignalTiming_t gSignalsArray[SIGNAL_NUMBER_OF_PINS];
/*
 * remember First signal assignment
 */
static const Signal_t *gpFirstSignal;

/*
 --------------------------------------------------------------------------------------------------
 |                                < Internal Function Definition   >                              |
 --------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextSignal >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextSignal                                                           |
 | < @Description       : return Next OF The Current signal                                             |    
 | < @Param button      : pointer to constant signal                                                    |           
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const Signal_t * getNextSignal(const Signal_t *signal);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getSignalPin >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getButtonPin                                                            |
 | < @Description       : get GPIO Pin of the signal                                                    |              
 | < @Param signal      : pointer to constant signal                                                    | 
 | < @return            : Pin number look gpio.h                                                        |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const gpio_t getSignalPin(const Signal_t *signal);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getSignalIndex >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getSignalIndex                                                          |
 | < @Description       : Index signal in array                                                         |              
 | < @Param signal      : pointer to constant signal                                                    | 
 | < @return            : Index Value                                                                   |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getSignalIndex(const Signal_t *signal);
/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalToggle >                                               |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalToggle                                                       |  
 | < @Description       : Perdioc Toggle Function                                                 |  
 | < @Param signal      : signal to be action execution                                           |
 | < @return            :void                                                                     |
 --------------------------------------------------------------------------------------------------
 */
static inline void SignalToggle(const Signal_t *signal);
/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalOff >                                                  |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalOff                                                          |  
 | < @Description       : Perdioc sleep Function                                                     |  
 | < @Param signal      : signal to be action execution                                           |
 | < @return             :void                                                                    |
 --------------------------------------------------------------------------------------------------
 */
static inline void SignalSleep(const Signal_t *signal);
/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalTask >                                                 |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalTask                                                         |  
 | < @Description       : this function run in isr to decrement the signal toggle time            |  
 | < @Param Period      : signal to be action execution                                           |
 | < @return            :void                                                                     |
 --------------------------------------------------------------------------------------------------
 */
static void SignalTask(const Signal_t *signal);
/*
 --------------------------------------------------------------------------------------------------
 |                                < Internal Function Implemetions   >                            |
 --------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextSignal >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextSignal                                                           |
 | < @Description       : return Next OF The Current signal                                             |    
 | < @Param button      : pointer to constant signal                                                    |           
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const Signal_t * getNextSignal(const Signal_t *signal) {
    return (const Signal_t *) pgm_read_word(&signal->NextSignal); /*gcc-compiler*/
    // return (const Signal_t *) (button->NextSignal); /*xc-compiler*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getSignalPin >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getButtonPin                                                            |
 | < @Description       : get GPIO Pin of the signal                                                    |              
 | < @Param signal      : pointer to constant signal                                                    | 
 | < @return            : Pin number look gpio.h                                                        |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const gpio_t getSignalPin(const Signal_t *signal) {
    return (const gpio_t) pgm_read_word(&signal->Pin); /*gcc-compiler*/
    // return (const gpio_t) (signal->Pin); /*xc-compiler*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getSignalIndex >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getSignalIndex                                                          |
 | < @Description       : Index signal in array                                                         |              
 | < @Param signal      : pointer to constant signal                                                    | 
 | < @return            : Index Value                                                                   |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getSignalIndex(const Signal_t *signal) {
    return (const uint8_t) pgm_read_byte(&signal->Index); /*gcc-compiler*/
    // return (const uint8_t) (signal->Index); /*xc-compiler*/
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalToggle >                                               |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalToggle                                                       |  
 | < @Description       : Perdioc Toggle Function                                                 |  
 | < @Param signal      : signal to be action execution                                           |
 | < @return            :void                                                                     |
 --------------------------------------------------------------------------------------------------
 */
static inline void SignalToggle(const Signal_t *signal) {
    if (!gSignalsArray[getSignalIndex(signal)].SignalState.b1) {
        gSignalsArray[getSignalIndex(signal)].SignalTimerToggleCount = PERIDIC_TIME(SIGNAL_DUTY_HIGH(gSignalsArray[getSignalIndex(signal)].SignalDuty, gSignalsArray[getSignalIndex(signal)].SignalPeriod));
    } else {
        gSignalsArray[getSignalIndex(signal)].SignalTimerToggleCount = PERIDIC_TIME(SIGNAL_DUTY_LOW(gSignalsArray[getSignalIndex(signal)].SignalDuty, gSignalsArray[getSignalIndex(signal)].SignalPeriod));
    }
    digitalPinWrite(getSignalPin(signal), GPIO_TGL);
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalOff >                                                  |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalOff                                                          |  
 | < @Description       : Perdioc sleep Function                                                     |  
 | < @Param signal      : signal to be action execution                                           |
 | < @return             :void                                                                    |
 --------------------------------------------------------------------------------------------------
 */
static inline void SignalSleep(const Signal_t *signal) {
    if (!gSignalsArray[getSignalIndex(signal)].SignalState.b2) {
        digitalPinWrite(getSignalPin(signal), GPIO_LOW);
    } else {
        digitalPinWrite(getSignalPin(signal), GPIO_HIGH);
    }
    gSignalsArray[getSignalIndex(signal)].SignalTimerToggleCount = PERIDIC_TIME(gSignalsArray[getSignalIndex(signal)].SignalPeriod) >> 1;
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalTask >                                                 |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalTask                                                         |  
 | < @Description       : this function run in isr to decrement the signal toggle time            |  
 | < @Param Period      : signal to be action execution                                           |
 | < @return            :void                                                                     |
 --------------------------------------------------------------------------------------------------
 */
static void SignalTask(const Signal_t *signal) {
    /*stop case*/
    if (!gSignalsArray[getSignalIndex(signal)].SignalState.b0) {
        return;
    }
    
    if (gSignalsArray[getSignalIndex(signal)].SignalTimerToggleCount != 0) {
        gSignalsArray[getSignalIndex(signal)].SignalTimerToggleCount--;
    } else {/*Period is done */
        /*in first period duration*/
        if (!gSignalsArray[getSignalIndex(signal)].SignalDurationcycles) {
            gSignalsArray[getSignalIndex(signal)].SignalState.b3 ^= 1;
            if (!gSignalsArray[getSignalIndex(signal)].SignalState.b3) {
                if (gSignalsArray[getSignalIndex(signal)].SignalNEx != SIGNAL_NOT_STOP_CHECK) {
                    if (gSignalsArray[getSignalIndex(signal)].SignalNEx) {
                        gSignalsArray[getSignalIndex(signal)].SignalNEx--;
                    } else {
                        SignalStop(signal);
                        return;
                    }
                }
                gSignalsArray[getSignalIndex(signal)].SignalDurationcycles = gSignalsArray[getSignalIndex(signal)].ToggleDuration;
            } else {
                gSignalsArray[getSignalIndex(signal)].SignalDurationcycles = gSignalsArray[getSignalIndex(signal)].SleepDuration;
            }

        } else {
            if (gSignalsArray[getSignalIndex(signal)].SignalState.b1) {
                gSignalsArray[getSignalIndex(signal)].SignalDurationcycles--;
            }
        }
        if (!gSignalsArray[getSignalIndex(signal)].SignalState.b3) {
            SignalToggle(signal);
        } else {
            SignalSleep(signal);
        }
        gSignalsArray[getSignalIndex(signal)].SignalState.b1 ^= 1; /*toggle flag and led*/
    }

}

/*
 --------------------------------------------------------------------------------------------------
 |                                < User Function Implemetions   >                                |
 --------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalStart >                                                |
 --------------------------------------------------------------------------------------------------
 | < @Function            : uint8_t SignalStart                                                   |  
 | < @Description         : flashing with  duty during  with Y Time                               |  
 | < @Param signal        : signal to reuired to action                                           |
 | < @Param FreqTime      : time of one cycle  in frequncy required                               | 
 | < @Param duty          : time of high and low present period                                   |
 | < @Param FreqDuration  : number of pules generated                                             |
 | <@Param  SleepDuration : number of Pulse is sleep                                              |
 | <@Param SleepState     : after flashing system is stopped the signal is high or low            |
 |                        : SLEEP_WITH_HIGH the active signal is high                             |
 |                        : SLEEP_WITH_LOW  the active signal is low                              |
 | < @Param nEx           : after siganl toggle and sleep this number the driver is stop signal   | 
 |                        : if the value is SIGNAL_NOT_STOP the driver can't stop signal          |
 |                        : the application can stop signal by stop function                      |
 | < @return              : void                                                                  |
 --------------------------------------------------------------------------------------------------
 */
void SignalStart(const Signal_t *signal, uint16_t FreqTime, uint8_t duty, uint8_t FreqDuration, uint8_t SleepDuration, uint8_t SleepState, uint8_t nEx) {
    /*start timer of the flashing and start timer of duration and active start State*/
    gSignalsArray[getSignalIndex(signal)].ToggleDuration = FreqDuration;
    gSignalsArray[getSignalIndex(signal)].SignalPeriod = (FreqTime); /*half wave of the frequncy*/
    gSignalsArray[getSignalIndex(signal)].SignalDurationcycles = FreqDuration;
    gSignalsArray[getSignalIndex(signal)].SleepDuration = SleepDuration;
    gSignalsArray[getSignalIndex(signal)].SignalDuty = duty;
    gSignalsArray[getSignalIndex(signal)].SignalTimerToggleCount = PERIDIC_TIME(SIGNAL_DUTY_HIGH(duty, FreqTime));
    gSignalsArray[getSignalIndex(signal)].SignalState.b0 = 1;
    gSignalsArray[getSignalIndex(signal)].SignalState.b2 = SleepState;
    gSignalsArray[getSignalIndex(signal)].SignalNEx = nEx - 1;
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignaStop >                                                  |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t SignaStop                                                       |  
 | < @Description       : Stopping Generation                                                     |  
 | < @Param signal      : Signal to check current state                                           |
 | < @return            : void                                                                    |
 --------------------------------------------------------------------------------------------------
 */
void SignalStop(const Signal_t *signal) {
    digitalPinWrite(getSignalPin(signal), GPIO_LOW); /*stop signal*/
    gSignalsArray[getSignalIndex(signal)].SignalState.byte = 0x00;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FirstSignal >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void FirstSignal                                                               |  
 | < @Description       : assignment Frist signal this functon run in boot section in app                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void FirstSignal(const Signal_t *signal) {
    if (signal) {
        gpFirstSignal = signal;
    }
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalsState >                                               |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalsState                                                       |  
 | < @Description       : signal is started or not                                                |                                
 | < @return            : 0 : signal is stop                                                      |
 | <                   :  1 : signal is started                                                   |
 --------------------------------------------------------------------------------------------------
 */
uint8_t SignalsState(const Signal_t *signal) {

    return (gSignalsArray[getSignalIndex(signal)].SignalState.b0);
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalsTask >                                                |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalTask                                                         |  
 | < @Description       : this function run in isr to decrement the                               |
 |                      : signal toggle time for all signals                                      |  
 | < @Param Period      : signal to be action execution                                           |
 | < @return            : void                                                                    |
 --------------------------------------------------------------------------------------------------
 */
void SignalsTask() {
    const Signal_t *i = gpFirstSignal;
    for (; i && i != &NullISignal; i = getNextSignal(i)) {
        SignalTask(i);
    }
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalsInit >                                                |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalsInit                                                        |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)|                                
 | < @return            : void                                                                    |
 --------------------------------------------------------------------------------------------------
 */
void SignalsInit() {
    const Signal_t *i = gpFirstSignal;
    for (; i && i != &NullISignal; i = getNextSignal(i)) {
        digitalpinMode(getSignalPin(i), MODE_OUTPUT);
    }
}
#endif
#endif
