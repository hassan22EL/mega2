/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : buuton.c                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no refence                                                               |
| < SRAM USAGE               : 14 Byte + BUTTON_MAX_BUFFER + 2 Byte Pointer of signal when enable       |                                             |
| < PROGRAM USAGE            : (966) 624 Byte (312 Instruction) +(342 Byte whan add signal)             |                                      
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */


#include <stdint-gcc.h>

#include "../../../inc/mega.h"

#if defined  BUTTON_MODULE
#if BUTTON_MODULE
/*
 < @BUTTON_NOT_A_BUTTON : This Button is not button used from list       
 */
#define   BUTTON_NOT_A_BUTTON               (0)

/*   
 < @BUTTON_MAX_BUFFER      :  max event store by default 4                       
 */
#ifndef   BUTTON_MAX_BUFFER
#define   BUTTON_MAX_BUFFER                   (1)
#endif
/*   
 < @NUMBER_OF_BUTTON      :  number of button used                     
 */
#ifndef NUMBER_OF_BUTTON
#define NUMBER_OF_BUTTON (1)
#endif
/*                                           
 < @BUTTON_DEDEBOUND_TIME      : time required to press or released switch                              
 */
#ifndef  BUTTON_DEDEBOUND_TIME
#define  BUTTON_DEDEBOUND_TIME           (20)
#endif
/*
 < @BUTTON_LONG_TIME           : time required to long press                                            
 */
#ifndef BUTTON_LONG_TIME 
#define BUTTON_LONG_TIME                (2000)
#endif
#ifndef     BUTTON_REPEAT_TIME
#define     BUTTON_REPEAT_TIME          (3000)
#endif
/* 
 < @BUTTON_REPEAT_TIME         : time required to repeat button                                            
 */
#ifndef     BUTTON_REPEAT_RATE
#define     BUTTON_REPEAT_RATE          (5)
#endif


/*
 < @BUT_DEPOUND_COUNT         : number of Interrupt per de-debound time                                    
 */
#define       BUT_DEPOUND_COUNT          ((BUTTON_DEDEBOUND_TIME * 1000UL) / (BUT_PERIDIC_TASK*N_OF_US_REQUIRED))
#if           BUT_DEPOUND_COUNT < 255

/*
 < @BUTTON_DE_COUNT         : number of Interrupt per de-debound time                                    
 */
#define       BUTTON_DE_COUNT     BUT_DEPOUND_COUNT
#else

/*
 < @BUTTON_DE_COUNT         : number of Interrupt per de-debound time                                    
 */
#define       BUTTON_DE_COUNT      255
#endif

/*
 < @BUT_LONG_COUNT         : number of Interrupt per long time                                    
 */
#define       BUT_LONG_COUNT          ((BUTTON_LONG_TIME * 1000UL) /(N_OF_US_REQUIRED * BUT_PERIDIC_TASK))
#if           BUT_LONG_COUNT < 255
/*
 < @BUTTON_L_COUNT         : number of Interrupt per long time                                    
 */
#define       BUTTON_L_COUNT     BUT_LONG_COUNT
#else 
/*
 < @BUTTON_L_COUNT         : number of Interrupt per long time                                    
 */
#define       BUTTON_L_COUNT      255
#endif




/*
 < @BUT_REPEAT_COUNT         : number of Interrupt per Repeat  time                                    
 */
#define       BUT_REPEAT_COUNT         ((BUTTON_REPEAT_TIME * 1000UL) /(N_OF_US_REQUIRED * BUT_PERIDIC_TASK))
#if           BUT_REPEAT_COUNT < 255
/*
 < @BUTTON_R_COUNT         : number of Interrupt per Repeat  time                                    
 */
#define       BUTTON_R_COUNT     BUT_REPEAT_COUNT
#else 
/*
 < @BUTTON_R_COUNT         : number of Interrupt per Repeat  time                                    
 */
#define       BUTTON_R_COUNT      255
#endif

/*
 < @BUT_RATE_COUNT         : number of Interrupt per Repeat char rate time                                    
 */
#define       BUT_RATE_COUNT                ((BUTTON_REPEAT_RATE * 1000UL) / N_OF_US_REQUIRED)
#if           BUT_RATE_COUNT < 255
/*
 < @BUTTON_RR_COUNT         : number of Interrupt per Repeat char rate time                                    
 */
#define       BUTTON_RR_COUNT               BUT_RATE_COUNT
#else 
/*
 < @BUTTON_RR_COUNT         : number of Interrupt per Repeat char rate time                                    
 */
#define       BUTTON_RR_COUNT      255
#endif

/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
const Button_t NullIButton PROGMEM = {(const Button_t *) NULL, (const gpio_t) 0, (const uint8_t) 0};
/*
 * remember First Button assignment
 */
static const Button_t *gpFirstButton;
/*
 * Buttons Counters assignment
 */
static uint8_t gu8ButtonCounters[NUMBER_OF_BUTTON];
/*
 * @var gu8ButtonLastKey  : last repeated key
 */
static volatile uint8_t gu8ButtonLastKey;
/*
 * @var gu8ButtonRepeatCounter  : repeat time to create new char
 */
static volatile uint8_t gu8ButtonRepeatCounter;
/*
 * @var gu8ButtonBufferEvents  : Button buffer to store events
 */
static uint8_t gu8ButtonBufferEvents[BUTTON_MAX_BUFFER];
/*
 * @var gstKeypadDescriptor  : create buffer as a ring buffer operations
 */
static stByteBufDescriptor_t gstButtonDescriptor;
#if defined (SIGNALGENERATED_MODULE)
#if (SIGNALGENERATED_MODULE)
/*
 * @var gpSignalActionATPressButton  : pointer to signal to action on buzzer or LED at press any Button
 */
static const Signal_t *gpSignalActionATPressButton;
#endif
#endif
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Internal Function Defintion>                                        |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextButton >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextButton                                                           |
 | < @Description       : return Next OF The Current Button                                             |    
 | < @Param button      : pointer to constant Button                                                    |           
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const Button_t * getNextButton(const Button_t *button);

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getButtonPin >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getButtonPin                                                            |
 | < @Description       : get GPIO Pin of the Button                                                    |              
 | < @Param button      : pointer to constant Button                                                    | 
 | < @return            : Pin number look gpio.h                                                        |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const gpio_t getButtonPin(const Button_t *button);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getButtonOption >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getButtonOption                                                         |
 | < @Description       : Button option value                                                           |              
 | < @Param button      : pointer to constant Button                                                    | 
 | < @return            : option value                                                                  |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getButtonOption(const Button_t *button);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < scanButton >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function                : void  scanButton                                                        |
 | < @Description             : scan Button and get event                                               |    
 | < @Param u8CounterIndex    : pointer to constant Button                                              | 
 | < @Param ButtonPin         : GPIO Pin                                                                |
 | < @Param ButtonPriority    : Button Active High Or Low                                               |
 | < @return                  : void                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void scanButton(uint8_t u8CounterIndex, gpio_t ButtonPin, uint8_t ButtonPriority);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Internal Function Implemtions>                                       |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextButton >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextButton                                                           |
 | < @Description       : return Next OF The Current Button                                             | 
 | < @Param button        : pointer to constant Button                                                  |                   
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const Button_t * getNextButton(const Button_t *button) {
    return (const Button_t *) pgm_read_word(&button->ButtonNext); /*gcc-compiler*/
    // return (const Button_t *) (button->ButtonNext); /*xc-compiler*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getButtonPin >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getButtonPin                                                            |
 | < @Description       : get GPIO Pin of the Button                                                    |              
 | < @Param button      : pointer to constant Button                                                    | 
 | < @return            : Pin number look gpio.h                                                        |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const gpio_t getButtonPin(const Button_t *button) {
    return (const gpio_t) pgm_read_word(&button->Pin); /*gcc-compiler*/
    // return (const gpio_t) (button->Pin); /*xc-compiler*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getButtonOption >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getButtonOption                                                         |
 | < @Description       : Button option value                                                           |              
 | < @Param button      : pointer to constant Button                                                    | 
 | < @return            : option value                                                                  |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getButtonOption(const Button_t *button) {
    return (const uint8_t) pgm_read_byte(&button->ButtonOptions); /*gcc-compiler*/
    // return (const uint8_t) (button->ButtonOptions); /*xc-compiler*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < scanButton >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function                : void  scanButton                                                        |
 | < @Description             : scan Button and get event                                               |    
 | < @Param u8CounterIndex    : pointer to constant Button                                              | 
 | < @Param ButtonPin         : GPIO Pin                                                                |
 | < @Param ButtonPriority    : Button Active High Or Low                                               |
 | < @return                  : void                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void scanButton(uint8_t u8CounterIndex, gpio_t ButtonPin, uint8_t ButtonPriority) {
    uint8_t u8Event;
    if (ButtonPin == NOT_A_PIN) { /*Invalid Pin*/
        return;
    }
    u8Event = BUTTON_NOT_AN_EVENT; /*default case of the Button is a Not an any Event Generated*/
    if (digitalPinRead(ButtonPin) == ButtonPriority) {/*switch Press*/
        gu8ButtonCounters[u8CounterIndex]++; /*Increment Current Counter of the Button*/
        if (gu8ButtonCounters[u8CounterIndex] > BUTTON_L_COUNT) {/*check long period is complete*/
            gu8ButtonCounters[u8CounterIndex] = BUTTON_L_COUNT; /*set current time is long press*/
        } else if (gu8ButtonCounters[u8CounterIndex] == BUTTON_L_COUNT) { /*check time equals long press time*/
            u8Event = BUTTON_LONGPRESS(u8CounterIndex + 1); /*set event is long press*/
        } else if (gu8ButtonCounters[u8CounterIndex] == BUTTON_DE_COUNT) {/*check de-bound period is complete*/
            u8Event = BUTTON_PRESS(u8CounterIndex + 1); /*set event is  press*/
            gu8ButtonLastKey = (u8CounterIndex + 1); //current Id +1  
            gu8ButtonRepeatCounter = BUTTON_R_COUNT;
        }
    } else { /*switch Release*/
        if (gu8ButtonCounters[u8CounterIndex] >= BUTTON_DE_COUNT) { //reset counter after de-bound
            gu8ButtonCounters[u8CounterIndex] = 0; /*reset counter to zero*/
            u8Event = BUTTON_RELEASE(u8CounterIndex + 1); /*set event as a release event*/
            if (gu8ButtonLastKey == (u8CounterIndex + 1))
                gu8ButtonRepeatCounter = BUTTON_NOT_A_BUTTON;
        }
    }

    /*Put Into Buffer Event*/
    if (u8Event != BUTTON_NOT_AN_EVENT) {
        putByte(&gstButtonDescriptor, u8Event);
    }
}
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < USER Function >                                                        |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonScan >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void button scan                                                               |  
 | < @Description       : primitive function run every time (ex. 10ms) (user not used)                   | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonScan() {
    uint8_t Index;
    Index = 0;
    const Button_t *i = gpFirstButton;
    for (; i && i != &NullIButton; i = getNextButton(i)) {
        scanButton(Index, getButtonPin(i), getButtonOption(i) >> 1);
        Index++;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonInit >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonInit                                                                |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)       |                            |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonInit() {

    /*initialization as time counters of each key*/
    for (uint8_t i = 0; i < (NUMBER_OF_BUTTON); i++) {
        gu8ButtonCounters[i] = 0x00;
    }
    /*Initialization as keypad buffer as a ring buffer*/
    byteBufferInit(&gstButtonDescriptor, gu8ButtonBufferEvents, BUTTON_MAX_BUFFER);
    /*Initialization as time of repeat counters of each key*/
    gu8ButtonRepeatCounter = 0;
    gu8ButtonLastKey = 0;
    /*Initialization Pins in First check option is odd number or not and Less Than the 4*/
    const Button_t *i = gpFirstButton;
    for (; i && i != &NullIButton; i = getNextButton(i)) {
        if (getButtonOption(i) & 0x01) { /*enable Pullup*/
            digitalpinMode(getButtonPin(i), MODE_INPUT_PULLUP);
        } else {
            digitalpinMode(getButtonPin(i), MODE_INPUT);
        }
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonGetEvent >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t buttonGetEvent                                                         |  
 | < @Description       : read button event from buffer  (user  used)                                       | 
 | < @return            : button event code                                                                 |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t buttonGetEvent() {
    uint8_t u8event;
    if (getByte(&gstButtonDescriptor, &u8event))
        return u8event;
    return BUTTON_NOT_A_BUTTON;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FirstButton >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void FirstButton                                                               |  
 | < @Description       : assignment Frist Button this functon run in boot section in app                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void FirstButton(const Button_t *button) {
    if (button && button != &NullIButton)
        gpFirstButton = button;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonResetEvents >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonResetEvents                                                         |  
 | < @Description       : reset button with removed all events and remove counters                       |                                                                |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonResetEvents() {
    for (uint8_t i = 0; i < BUTTON_MAX_BUFFER; i++) {
        gu8ButtonBufferEvents[i] = BUTTON_NOT_A_BUTTON;
    }
    for (uint8_t i = 0; i < NUMBER_OF_BUTTON; i++) {
        gu8ButtonCounters[i] = 0x00;
    }
}
#if defined (SIGNALGENERATED_MODULE) 
#if (SIGNALGENERATED_MODULE)

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonSignal >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void button buttonSignal                                                       |  
 | < @Description       : Assignment signal to generate fixed signal at press Button                     | 
 | < @Param signal      : pointer to signal to generate event with time at buffer is full and            |
 |                      : button press                                                                   |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonSignal(const Signal_t *signal) {
    if (signal && signal != &NullISignal) {
        gpSignalActionATPressButton = signal;
    }
}

#endif
#endif

#endif
#endif