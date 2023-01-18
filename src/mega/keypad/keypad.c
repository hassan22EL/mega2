/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : keypad.c                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : (4 Byte buffer , 6 buffer dis , r*c byte internal conter , 2byte         |
| < PROGRAM USAGE            : (764)((548 Byte  (274 Instruction))+(216Byte when enable signal))        |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if defined (KEYPAD_MODULE)
#if  KEYPAD_MODULE 
/*
 ---------------------------------------------------------------------------------------------------------
 |                               <Keypad Definition>                                                     |
 ---------------------------------------------------------------------------------------------------------
 |< @KEYPAD_MAX_ROW             : max row in keypad and this value less than 8                           |
 |< @KEYPAD_MAX_COL             : max clomun in keypad and this value less than 8                        |
 |< @KEYPAD_MAX_BUFFER          : max key stored                                                         |
 |< @KEYPAD_DEDEBOUND_TIME      : time required to press or released switch                              |
 |< @KEYPAD_LONG_TIME           : time required to long press                                            |
 |< @KEYPAD_REPEAT_TIME         : time required to repeat key                                            |
 |< @KEYPAD_REPEAT_RATE         : time required between repeat key                                       |
 |< @note                       : keypad state is fixed active low                                       |                 
 ---------------------------------------------------------------------------------------------------------
 */

#ifndef      KEYPAD_MAX_ROW 
#define      KEYPAD_MAX_ROW               (4)/*default value*/
#endif




#ifndef      KEYPAD_MAX_COL               
#define      KEYPAD_MAX_COL               (4) /*default value*/
#endif

#ifndef     KEYPAD_MAX_BUFFER             
#define     KEYPAD_MAX_BUFFER              (4) /*default value*/
#endif

#ifndef   KEYPAD_DEDEBOUND_TIME
#define   KEYPAD_DEDEBOUND_TIME            (10) /*default value as 10ms*/
#endif 

#ifndef   KEYPAD_LONG_TIME               
#define   KEYPAD_LONG_TIME                   (2000) /*defalut value is 2 seconds*/
#endif


#ifndef   KEYPAD_REPEAT_TIME
#define   KEYPAD_REPEAT_TIME                 (3000) /*defalut value is 3 seconds*/
#endif

#ifndef   KEYPAD_REPEAT_RATE
#define   KEYPAD_REPEAT_RATE                 (5) /*defalut value is 5 ms*/
#endif

#define       KEY_DEPOUND_COUNT          ((KEYPAD_DEDEBOUND_TIME * 1000UL) / (KEY_PERIDIC_TASK*N_OF_US_REQUIRED))
#if           KEY_DEPOUND_COUNT < 255
#define       KEYPAD_DE_COUNT     KEY_DEPOUND_COUNT
#else 
#define       KEYPAD_DE_COUNT      255
#endif


#define       KEY_LONG_COUNT          ((KEYPAD_LONG_TIME * 1000UL) /(N_OF_US_REQUIRED * KEY_PERIDIC_TASK))
#if           KEY_LONG_COUNT < 255
#define       KEYPAD_L_COUNT     KEY_LONG_COUNT
#else 
#define       KEYPAD_L_COUNT      255
#endif

#define   KEYPAD_NOT_AN_EVENT               (0)
#define   KEYPAD_NOT_A_BUTTON               (0)



#define       KEY_REPEAT_COUNT         ((KEYPAD_REPEAT_TIME * 1000UL) /(N_OF_US_REQUIRED * KEY_PERIDIC_TASK))
#if           KEY_REPEAT_COUNT < 255
#define       KEYPAD_R_COUNT     KEY_REPEAT_COUNT
#else 
#define       KEYPAD_R_COUNT      255
#endif



#define       KEY_RATE_COUNT                ((KEYPAD_REPEAT_RATE * 1000UL) / N_OF_US_REQUIRED)
#if           KEY_RATE_COUNT < 255
#define       KEYPAD_RR_COUNT               KEY_RATE_COUNT
#else 
#define       KEYPAD_RR_COUNT      255
#endif





/*
 ---------------------------------------------------------------------------------------------------------
 |                            < KEYPAD_COMMONS_PINS  >                                                   |
 ---------------------------------------------------------------------------------------------------------
 */

/***********************KEYPAD01 C01********************/
#ifndef KEYPAD_C01_PIN
#define KEYPAD_C01_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C02********************/
#ifndef KEYPAD_C02_PIN
#define KEYPAD_C02_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C03********************/
#ifndef KEYPAD_C03_PIN
#define KEYPAD_C03_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C04********************/
#ifndef KEYPAD_C04_PIN
#define KEYPAD_C04_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C05********************/
#ifndef KEYPAD_C05_PIN
#define KEYPAD_C05_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C06*******************/
#ifndef KEYPAD_C06_PIN
#define KEYPAD_C06_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C07********************/
#ifndef KEYPAD_C07_PIN
#define KEYPAD_C07_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C08********************/
#ifndef KEYPAD_C08_PIN
#define KEYPAD_C08_PIN          NOT_A_PIN
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < KEYPAD_SWITCH_PINS  >                                                   |
 ---------------------------------------------------------------------------------------------------------
 */
/***********************KEYPAD01 SW01********************/
#ifndef KEYPAD_SW01_PIN
#define KEYPAD_SW01_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW02_PIN
#define KEYPAD_SW02_PIN          NOT_A_PIN
#endif

/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW03_PIN
#define KEYPAD_SW03_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW04_PIN
#define KEYPAD_SW04_PIN         NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW05_PIN
#define KEYPAD_SW05_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW06_PIN
#define KEYPAD_SW06_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW07_PIN
#define KEYPAD_SW07_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW08_PIN
#define KEYPAD_SW08_PIN          NOT_A_PIN
#endif



/*
 ---------------------------------------------------------------------------------------------------------
 |                            < Create keyCloumn Keypad Definition  >                                     |
 ---------------------------------------------------------------------------------------------------------
 */
#if KEYPAD_MAX_COL == 8
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN, KEYPAD_SW02_PIN, KEYPAD_SW03_PIN, KEYPAD_SW04_PIN, KEYPAD_SW05_PIN, KEYPAD_SW06_PIN, KEYPAD_SW07_PIN, KEYPAD_SW08_PIN};
#elif KEYPAD_MAX_COL == 7
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN, KEYPAD_SW02_PIN, KEYPAD_SW03_PIN, KEYPAD_SW04_PIN, KEYPAD_SW05_PIN, KEYPAD_SW06_PIN, KEYPAD_SW07_PIN};
#elif KEYPAD_MAX_COL == 6
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN, KEYPAD_SW02_PIN, KEYPAD_SW03_PIN, KEYPAD_SW04_PIN, KEYPAD_SW05_PIN, KEYPAD_SW06_PIN};
#elif KEYPAD_MAX_COL == 5
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN, KEYPAD_SW02_PIN, KEYPAD_SW03_PIN, KEYPAD_SW04_PIN, KEYPAD_SW05_PIN};
#elif KEYPAD_MAX_COL == 4
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN, KEYPAD_SW02_PIN, KEYPAD_SW03_PIN, KEYPAD_SW04_PIN};
#elif KEYPAD_MAX_COL == 3
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN, KEYPAD_SW02_PIN, KEYPAD_SW03_PIN};
#elif KEYPAD_MAX_COL == 2
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN, KEYPAD_SW02_PIN};
#elif KEYPAD_MAX_COL == 1
static const gpio_t keyCloumn[KEYPAD_MAX_COL] PROGMEM = {KEYPAD_SW01_PIN};
#else
#error    "please define number of column used in keypad"
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < Create keyRows Keypad Definition  >                                      |
 ---------------------------------------------------------------------------------------------------------
 */
#if KEYPAD_MAX_ROW == 8
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN, KEYPAD_C02_PIN, KEYPAD_C03_PIN, KEYPAD_C04_PIN, KEYPAD_C05_PIN, KEYPAD_C06_PIN, KEYPAD_C07_PIN, KEYPAD_C08_PIN};
#elif KEYPAD_MAX_ROW == 7
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN, KEYPAD_C02_PIN, KEYPAD_C03_PIN, KEYPAD_C04_PIN, KEYPAD_C05_PIN, KEYPAD_C06_PIN, KEYPAD_C07_PIN};
#elif KEYPAD_MAX_ROW == 6
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN, KEYPAD_C02_PIN, KEYPAD_C03_PIN, KEYPAD_C04_PIN, KEYPAD_C05_PIN, KEYPAD_C06_PIN};
#elif KEYPAD_MAX_ROW == 5
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN, KEYPAD_C02_PIN, KEYPAD_C03_PIN, KEYPAD_C04_PIN, KEYPAD_C05_PIN};
#elif KEYPAD_MAX_ROW == 4
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN, KEYPAD_C02_PIN, KEYPAD_C03_PIN, KEYPAD_C04_PIN};
#elif KEYPAD_MAX_ROW == 3
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN, KEYPAD_C02_PIN, KEYPAD_C03_PIN};
#elif KEYPAD_MAX_ROW == 2
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN, KEYPAD_C02_PIN};
#elif KEYPAD_MAX_ROW == 1
static const gpio_t keyRows[KEYPAD_MAX_ROW] PROGMEM = {KEYPAD_C01_PIN};
#else
#error    "please define number of rows used in keypad"
#endif


/*
 --------------------------------------------------------------------------------------------------------- 
 |                                            < Notes >                                                  | 
 --------------------------------------------------------------------------------------------------------- 
 | <@note : keypad run every system tick (number of micro seconds) and scan                              |
 |        : the de-bounce is every fixed 20ms the counter                                                |
 |        : Increment 20000/ number of micro seconds for example the system micro                        |
 |        : seconds is 1250 us each interrupt and depounds is 20ms                                       |
 |        : counter reach the (20000/1250)  = 16                                                         |
 |        : long time counter 2*10^6 / 1250 = 1600 to reduce this the scan run                           |
 |        : every 10ms       20/10 =  2                                                                  |
 |        : long time        2000/10 = 200                                                               |
 |        : long time max    2560/10  =256                                                               |
 |        : to reduce scan every 20ms                                                                    |
 |        : this is limit of the time required                                                           |
  --------------------------------------------------------------------------------------------------------
 */
#define MAX_COUNTER            (KEYPAD_MAX_ROW*KEYPAD_MAX_COL)
/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Variables                                                   |
 --------------------------------------------------------------------------------------------------------- 
 */
/*
 * @var gu8KeypadBufferEvents  : keypad buffer to store events
 */
static uint8_t gu8KeypadBufferEvents[KEYPAD_MAX_BUFFER];
/*
 * @var gstKeypadDescriptor  : create buffer as a ring buffer operations
 */
static stByteBufDescriptor_t gstKeypadDescriptor;
/*
 * @var gu8keypadCounters  : keypad counter de-bounds buffer
 */
static uint8_t gu8keypadCounters[MAX_COUNTER];
/*
 * @var gu8KeypadLastKey  : last repeated key
 */
static volatile uint8_t gu8KeypadLastKey;
/*
 * @var gu8KeypadRepeatCounter  : repeat time to create new char
 */
static volatile uint8_t gu8KeypadRepeatCounter;
#if defined (SIGNALGENERATED_MODULE)
#if (SIGNALGENERATED_MODULE)
/*
 * @var gpSignalActionATPressSw  : pointer to signal to action on buzzer or LED at press any switch in keypad
 */
static const Signal_t *gpSignalActionATPressSw;
#endif
#endif
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadstoreKey >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keypadstoreKey                                                            |  
 | < @Description       : check state of the key and state of the current counter depounds               | 
 | < @Param index       : this index of  current counter in keypad buffer                                |
 | < @param PinC        : this pin column to check state is press or release                             |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void keypadstoreKey(volatile uint8_t index, volatile gpio_t pinC);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadstoreKey >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keypadstoreKey                                                            |  
 | < @Description       : check state of the key and state of the current counter depounds               | 
 | < @Param index       : this index of  current counter in keypad buffer                                |
 | < @param PinC        : this pin column to check state is press or release                             |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void keypadstoreKey(volatile uint8_t index, volatile gpio_t pinC) {
    uint8_t u8Event;
    u8Event = KEYPAD_NOT_AN_EVENT;
    if (!digitalPinRead(pinC)) {
        gu8keypadCounters[index]++;
        if (gu8keypadCounters[index] > KEYPAD_L_COUNT) {
            gu8keypadCounters[index] = KEYPAD_L_COUNT;
        } else if (gu8keypadCounters[index] == KEYPAD_L_COUNT) {
            u8Event = KEYPAD_LONGPRESS(index + 1);
        } else if (gu8keypadCounters[index] == KEYPAD_DE_COUNT) {
            u8Event = KEYPAD_PRESS(index + 1);
            gu8KeypadLastKey = (index + 1); //current Id +1 
            gu8KeypadRepeatCounter = KEYPAD_R_COUNT;
        }
    } else {
        if (gu8keypadCounters[index] >= KEYPAD_DE_COUNT) {
            //Release State
            //reset counter after de-bound
            gu8keypadCounters[index] = 0;
            u8Event = KEYPAD_RELEASE(index + 1);
            if (gu8KeypadLastKey == (index + 1))
                gu8KeypadLastKey = KEYPAD_NOT_A_BUTTON;
        }
    }
    /*store data into buffer*/
    if (u8Event != KEYPAD_NOT_AN_EVENT) {
#if defined(SIGNALGENERATED_MODULE)
#if SIGNALGENERATED_MODULE
        if (putByte(&gstKeypadDescriptor, u8Event)) {
            if (u8Event == KEYPAD_PRESS(index + 1)) {
                SignalStart(gpSignalActionATPressSw, 64, 100, 1, 1, SIGNAL_SLEEP_WITH_LOW, 1, SIGNAL_STOP_LOW);
            }
        } else {
            if (u8Event == KEYPAD_PRESS(index + 1)) {
                SignalStart(gpSignalActionATPressSw, 200, 100, 1, 1, SIGNAL_SLEEP_WITH_LOW, 1, SIGNAL_STOP_LOW);
            }
        }
#else
        putByte(&gstKeypadDescriptor, u8Event);
#endif
#else
        putByte(&gstKeypadDescriptor, u8Event);
#endif
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyInit >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyInit                                                                   |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)       | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyInit() {
    /*set columns as input pull up*/
    gpio_t pin;
    for (uint8_t i = 0; i < KEYPAD_MAX_COL; i++) {
        digitalpinMode(pgm_read_word(keyCloumn + i), MODE_INPUT_PULLUP); /*initialization as Input*/
    }
    /*set rows out  */
    for (uint8_t i = 0; i < KEYPAD_MAX_ROW; i++) {
        pin = pgm_read_word(keyRows + i);
        digitalpinMode(pin, MODE_INPUT); /*initialization as output*/
        //  digitalPinWrite(pin, GPIO_HIGH); /*default value*/
    }
    /*initialization as time counters of each key*/
    for (uint8_t i = 0; i < (MAX_COUNTER); i++) {
        gu8keypadCounters[i] = 0x00;
    }
    /*initialization as keypad buffer as a ring buffer*/
    byteBufferInit(&gstKeypadDescriptor, gu8KeypadBufferEvents, KEYPAD_MAX_BUFFER);
    /*initialization as time of repeat counters of each key*/
    gu8KeypadRepeatCounter = 0;
    gu8KeypadLastKey = 0;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyscan >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyscan                                                                   |  
 | < @Description       : primitive function run every time (ex. 10ms) (user not used)                   | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyscan() {
    /*this function*/
    volatile uint8_t i;
    volatile uint8_t j;
    gpio_t pin;
    for (i = 0; i < KEYPAD_MAX_ROW; i++) {
        pin = pgm_read_word(keyRows + i);
        digitalpinMode(pin, MODE_OUTPUT);
        for (j = 0; j < KEYPAD_MAX_COL; j++) {
            keypadstoreKey(((i * KEYPAD_MAX_COL) + j), pgm_read_word(keyCloumn + j));
        }
        digitalpinMode(pin, MODE_INPUT);
    }
    //Repeat State
    if (gu8KeypadLastKey != KEYPAD_NOT_A_BUTTON) {
        if (--gu8KeypadRepeatCounter == 0) {
            gu8KeypadRepeatCounter = KEYPAD_RR_COUNT;
            putByte(&gstKeypadDescriptor, KEYPAD_REPEAT(gu8KeypadLastKey));
        }
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadGetEvent >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t keypadGetEvent                                                         |  
 | < @Description       : read key event from buffer  (user  used)                                       | 
 | < @return            : key event code                                                                 |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t keypadGetEvent() {
    uint8_t u8keypadevent;
    if (getByte(&gstKeypadDescriptor, &u8keypadevent)) {
        if (u8keypadevent) {
            return u8keypadevent;
        } else {
            return KEYPAD_NOT_AN_EVENT;
        }
    }
    return KEYPAD_NOT_AN_EVENT;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadResetEvents >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keypadResetEvents                                                         |  
 | < @Description       : reset keypad with removed all events and remove counters                       |                                                                |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keypadResetEvents() {
    for (uint8_t i = 0; i < KEYPAD_MAX_BUFFER; i++) {
        gu8KeypadBufferEvents[i] = KEYPAD_NOT_AN_EVENT;
    }
    /*clear all counters*/
    for (uint8_t i = 0; i < (KEYPAD_MAX_ROW * KEYPAD_MAX_COL); i++) {
        gu8keypadCounters[i] = 0x00;
    }
}

#if defined (SIGNALGENERATED_MODULE) 
#if (SIGNALGENERATED_MODULE)

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keypadSignal >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void button buttonSignal                                                       |  
 | < @Description       : Assignment signal to generate fixed signal at press any  switch in keypad      | 
 | < @Param signal      : pointer to signal to generate event with time at buffer is full and            |
 |                      : switch keypad press                                                            |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keypadSignal(const Signal_t *signal) {
    if (signal && signal != &NullISignal) {
        gpSignalActionATPressSw = signal;
    }
}
#endif
#endif



#endif
#endif