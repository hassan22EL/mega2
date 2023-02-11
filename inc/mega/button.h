/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : buuton.h                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no refence                                                               |
| < SRAM USAGE               : 14 Byte + BUTTON_MAX_BUFFER + 2 Byte Pointer of signal when enable       |                                             |
| < PROGRAM USAGE            : (966) 624 Byte (312 Instruction) +(342 Byte whan add signal)             |                                      
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#ifndef XC_BUTTON_H
#define	XC_BUTTON_H

#include "../mega.h"
#if defined  BUTTON_MODULE
#if BUTTON_MODULE

/*
 < @BUTTON_NOT_AN_EVENT : Indicate System Is return Not an Event (Not Button state)
 */
#define   BUTTON_NOT_AN_EVENT               (0)

/* 
 ---------------------------------------------------------------------------------------------------------
 |                     <   Events Encoded   >                                                            |
 ---------------------------------------------------------------------------------------------------------
 */
#define   BUTTON_PRESS_EVENT            (0x00)
#define   BUTTON_LONGPRESS_EVENT        (0x40)
#define   BUTTON_REPEAT_EVENT           (0x80)
#define   BUTTON_RELEASE_EVENT          (0xC0)
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KEYPAD_PRESS >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void BUTTON_PRESS                                                              |  
 | < @Description       : set or get press key event code of from switch id                              | 
 | < @Param x           : switch id look enum table in button.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define BUTTON_PRESS(x)                 (((x)&(0x3F))|BUTTON_PRESS_EVENT)
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < BUTTON_LONGPRESS >                                                  |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void BUTTON_LONGPRESS                                                          |  
 | < @Description       : set or get long press key event code of from switch id                         | 
 | < @Param x           : switch id look enum table in button.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define BUTTON_LONGPRESS(x)             (((x)&(0x3F))|BUTTON_LONGPRESS_EVENT)
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < BUTTON_REPEAT >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KEYPAD_PRESS                                                              |  
 | < @Description       : set or get repeat key event code of from switch id                             | 
 | < @Param x           : switch id look enum table in button.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define BUTTON_REPEAT(x)                (((x)&(0x3F))|BUTTON_REPEAT_EVENT)
/*
 ---------------------------------------------------------------------------------------------------------
s |                                 < BUTTON_RELEASE >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void BUTTON_RELEASE                                                            |  
 | < @Description       : set or get release key event code of from switch id                            | 
 | < @Param x           : switch id look enum table in button.h                                          |
 | < @return            : key event cod from                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
#define BUTTON_RELEASE(x)               (((x)&(0x3F))|BUTTON_RELEASE_EVENT)

typedef enum {
    /*
     ---------------------------------------------------------------------------------------------------------
     |                    BUTTONITCH ID                                                                      |
     ---------------------------------------------------------------------------------------------------------
     */

    BUTTON_INVALID_KEY,
    BUTTON01, BUTTON02, BUTTON03, BUTTON04, BUTTON05, BUTTON06, BUTTON07, BUTTON08, BUTTON09,
    BUTTON10, BUTTON11, BUTTON12, BUTTON13, BUTTON14, BUTTON15, BUTTON16, BUTTON17, BUTTON18,
    BUTTON19, BUTTON20, BUTTON21, BUTTON22, BUTTON23, BUTTON24, BUTTON25, BUTTON26, BUTTON27,
    BUTTON28, BUTTON29, BUTTON30, BUTTON31, BUTTON32, BUTTON33, BUTTON34, BUTTON35, BUTTON36,
    BUTTON37, BUTTON38, BUTTON39, BUTTON40, BUTTON41, BUTTON42, BUTTON43, BUTTON44, BUTTON45,
    BUTTON46, BUTTON47, BUTTON48, BUTTON49, BUTTON50, BUTTON51, BUTTON52, BUTTON53, BUTTON54,
    BUTTON55, BUTTON56, BUTTON57, BUTTON58, BUTTON59, BUTTON60, BUTTON61, BUTTON62, BUTTON63,
} ButtonIDs_t;

/*
 --------------------------------------------------------------------------------------------------
 |                                <   mnue Descirption   >                                        |
 --------------------------------------------------------------------------------------------------
 | < Description                   : mnue struct                                                  |
 | < Uasge                         : 5 Byte in Progrm Memeory                                     |                                     
 | < param ButtonNext              : next button in list created                                  |
 | < param Pin                     : Input Pin GPIO                                               |
 | < Param ButtonOptions           : Bit 0 Inicator the button active high or low                 |
 | <                               : Bit 1 Incator the button is Pullup Enable or not             |
 --------------------------------------------------------------------------------------------------
 */
typedef struct Button_s {
    struct Button_s const * ButtonNext; /*pointer to constant  Button_s*/
    gpio_t const Pin; /*pin ass*/
    uint8_t const ButtonOptions;
} Button_t;


/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
#if COMPILER_TYPE == GCC
extern const Button_t PROGMEM NullIButton;
#elif COMPILER_TYPE == XC
extern const Button_t NullIButton;
#endif
/*
 --------------------------------------------------------------------------------------------------
 |                           < Button  >                                                          | 
 --------------------------------------------------------------------------------------------------
 | < @Description    : create menue item                                                          |
 | < @Param Name     : Name Of Button is uqin                                                     |
 | < @Param Next     : Next Button Item the Last Button must indicator to First Button            |
 | < @Param Pin      : Button GPIO Pin                                                            |
 | < @Param Option   : four state                                                                 |
 |                   : 0  : is active low and disapled pullup                                     |
 |                   : 1  : is active low and enable pullup                                       |
 |                   : 2  : is active high and disaple pullup                                     |
 |                   : 3  : is active high and enable pullup                                      |
 | @note             : active low (at press switch pin read low)                                  |
 |                   : active high (at press switch pin read low)                                 |
 --------------------------------------------------------------------------------------------------          
 */
#if COMPILER_TYPE == GCC
#define Button(Name,Next, Pin, Option) \
    extern const Button_t PROGMEM   Next; \
    const Button_t PROGMEM Name = {&Next,Pin,Option};
#elif COMPILER_TYPE == XC
#define Button(Name,Next, Pin, Option) \
    extern const Button_t    Next; \
    const Button_t  Name = {&Next,Pin,Option};
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonScan >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void button scan                                                               |  
 | < @Description       : primitive function run every time (ex. 10ms) (user not used)                   | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonScan();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonInit >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonInit                                                                |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)       | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonGetEvent >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t buttonGetEvent                                                         |  
 | < @Description       : read key event from buffer  (user  used)                                       | 
 | < @return            : key event code                                                                 |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t buttonGetEvent();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FirstButton >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void FirstButton                                                               |  
 | < @Description       : assignment Frist Button this functon run in boot section in app                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void FirstButton(const Button_t *button);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < buttonResetEvents >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void buttonResetEvents                                                         |  
 | < @Description       : reset button with removed all events and remove counters                       |                                                                |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void buttonResetEvents();
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
void buttonSignal(const Signal_t *signal);
#endif
#endif


#endif
#endif


#endif	/* XC_BUTTON_H */