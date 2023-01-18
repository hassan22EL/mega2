
/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : signalGenerator.h                                                 |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : 10 Byte Per Signal   + 2 Byte Pointer to first signal in table    |
| < PROGRAM USAGE            : 918 Byte (459 Instruction)                                        |                                     
| < Hardware Usage           : no-used                                                           |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#ifndef SIGNALGENERATED_H
#define	SIGNALGENERATED_H
#include "../mega.h"

#if defined SIGNALGENERATED_MODULE
#if SIGNALGENERATED_MODULE

/*
 < @macro SIGNAL_SLEEP_WITH_HIGH : Active State when Stop Toggling LED with Frequncy is High
 */
#define SIGNAL_SLEEP_WITH_HIGH                (1)
/*
 < @macro SIGNAL_SLEEP_WITH_LOW : Active State when Stop Toggling LED with Frequncy is Low
 */
#define  SIGNAL_SLEEP_WITH_LOW                (0)
/*
 < @macro SIGNAL_NOT_STOP :  Driver cna't stop siganl the application can stop siganl by stop function
 */
#define  SIGNAL_NOT_STOP               (0xFF)
/*
 < @macro SIGNAL_STOP_HIGH :  Stop with high 
 */
#define        SIGNAL_STOP_HIGH                    GPIO_HIGH
/*
 < @macro SIGNAL_STOP_LOW :  Stop with low
 */
#define        SIGNAL_STOP_LOW                       GPIO_LOW

/*
 --------------------------------------------------------------------------------------------------
 |                                <   mnue Descirption   >                                        |
 --------------------------------------------------------------------------------------------------
 | < Description                   : mnue struct                                                  |
 | < Uasge                         : 3 Byte in Progrm Memeory                                     |                                     
 | < param Pin                     : Input Pin GPIO                                               |
 | < Param Index                   : pin number into array                                        |
 --------------------------------------------------------------------------------------------------
 */
typedef struct Signal_s {
    struct Signal_s const * NextSignal; /*pointer to constant  Signal_s*/
    gpio_t const Pin; /*pin ass*/
    uint8_t const Index;
} Signal_t;
/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
extern const Signal_t PROGMEM NullISignal;
/*
 --------------------------------------------------------------------------------------------------
 |                           < signal  >                                                          | 
 --------------------------------------------------------------------------------------------------
 | < @Description    : create signal                                                              |
 | < @Param Name     : Name Of signal is uqin                                                     |
 | < @Param Next     : pointer to next signal                                                     |
 | < @Param Pin      : Signal GPIO Pin                                                            |
 | < @Param Index    : Pin number in array                                                        |
 --------------------------------------------------------------------------------------------------          
 */
#define SIGNALS(Name,Next, Pin, Index) \
    extern const Signal_t PROGMEM   Next; \
    const Signal_t PROGMEM Name = {&Next,Pin,Index};



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
 *                        : SLEEP_WITH_HIGH the active signal is high                             |
 |                        : SLEEP_WITH_LOW  the active signal is low                              |
 | < @Param nEx           : after siganl toggle and sleep this number the driver is stop signal   | 
 |                        : if the value is 0 the driver can't stop signal the application        |
 |                        : can stop signal by stop function                                      |
 | < @return              : void                                                                  |
 --------------------------------------------------------------------------------------------------
 */
void SignalStart(const Signal_t *signal, uint16_t FreqTime, uint8_t duty, uint8_t FreqDuration, uint8_t SleepDuration, uint8_t SleepState, uint8_t nEx, uint8_t StopSignal);
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
void SignalStop(const Signal_t *signal, uint8_t stopState);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FirstSignal >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void FirstSignal                                                               |  
 | < @Description       : assignment Frist signal this functon run in boot section in app                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void FirstSignal(const Signal_t *signal);
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
uint8_t SignalsState(const Signal_t *signal);
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
void SignalsTask();
/*
 --------------------------------------------------------------------------------------------------
 |                                 < SignalsInit >                                                |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void SignalsInit                                                        |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)|                                
 | < @return            : void                                                                    |
 --------------------------------------------------------------------------------------------------
 */
void SignalsInit();

#endif
#endif

#endif	/* SIGNALGENERATED_H */

