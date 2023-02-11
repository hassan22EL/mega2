/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : Tone.h                                                                   |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 11 Byte Used by one Pin                                                  |
| < PROGRAM USAGE            : 430 Byte by One Pin Used                                                 |                                                                         |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */
#include "../../../inc/mega.h"
#if defined TONE_MODULE
#if TONE_MODULE

/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Typedef                                                    |
 --------------------------------------------------------------------------------------------------------- 
 */
typedef struct {
    stTimer_TimeOut_t Freq;
    stTimer_TimeOut_t duration;
    uint16_t Period;
    uint8_t State;
} stTone_t;

/*
 *<@var gstTones : max tones used in system
 */
static stTone_t gstTones[TONES_MAX_PINS_USED];
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < myTone >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t myTone                                                                 |  
 | < @Description       : run Timer                                                                      |                                               |
 | < @return            :void                                                   |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void myTone(gpio_t pin, EN_GPIO_t defalutstate, stTone_t *tone);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < myTone >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t myTone                                                                 |  
 | < @Description       : run Timer                                                                      |                                               |
 | < @return            :void                                                   |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void myTone(gpio_t pin, EN_GPIO_t defalutstate, stTone_t *tone) {
    if (!tone->State) {
        return;
    }


    if (sysIsTimeoutMs(&tone->duration)) {
        if (!sysIsTimeoutUs(&tone->Freq)) {
            if (tone->Period != 0) {
                sysSetPeriodUs(&tone->Freq, tone->Period);
                digitalPinWrite(pin, GPIO_TGL);
            }
        }
    } else {
        tone->State = 0;
        digitalPinWrite(pin, defalutstate);
        return;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < isTonePlaying >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t isTonePlaying                                                          |  
 | < @Description       : check the Tone is Playing or not                                               |   
 | < @Param Index       : Signal Index in array                                                          |
 | < @return            : 1 is Playing , 0 is not Playing                                                |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t isTonePlaying(uint8_t Index) {
    return gstTones[Index].State;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Toneplay >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void Toneplay                                                                  |  
 | < @Description       : Play Tone                                                                      | 
 | < @Param Pin         : GPIO Pin access                                                                |
 | < @Param frequency   : frequency gnerated                                                             |  
 | < @Param duration    : time to generate this Frequncy                                                 |
 | < @Param Index       : Index of the Pin From 0 to max pin used -1                                     |
 | <@Param duty         : Power On Time and Power off Time                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void Toneplay(gpio_t pin, uint8_t Index, uint16_t frequency, uint32_t duration, uint8_t duty) {
    uint16_t Ton;
    uint16_t Toff;

    Ton = duty;
    Toff = 100 - duty;
    if (frequency) {
        gstTones[Index].Period = (10000UL / frequency);
    } else {
        gstTones[Index].Period = 1;
    }
    gstTones[Index].State = 1;
    sysSetPeriodMS(&gstTones[Index].duration, duration);
    sysSetPeriodUs(& gstTones[Index].Freq, (gstTones[Index].Period * Ton));
    gstTones[Index].Period = (gstTones[Index].Period * Toff);
    digitalPinWrite(pin, GPIO_TGL);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Tonestop >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t isTonePlaying                                                          |  
 | < @Description       : stop this tone                                                                 |  
 | < @Param pin         : access gpio pin                                                                |
 | < @Param  Index      : Signel Index in array                                                          |
 | < @param default     : state low or high                                                              |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void Tonestop(gpio_t pin, uint8_t Index, EN_GPIO_t defaultState) {
    gstTones[Index].State = 0;
    digitalPinWrite(pin, defaultState);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneInit >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneInit                                                                  |  
 | < @Description       : Init I/O with MAX_PIN Used                                                     |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ToneInit() {
#if TONES_MAX_PINS_USED == 4
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN1_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN2_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN3_GPIO, MODE_OUTPUT);

    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN3_GPIO, TONE_PIN3_DEFALUT_STATE);
#elif TONES_MAX_PINS_USED == 3
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN1_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN2_GPIO, MODE_OUTPUT);

    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE);
#elif TONES_MAX_PINS_USED == 2
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalpinMode(TONE_PIN1_GPIO, MODE_OUTPUT);
    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
    digitalPinWrite(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE);
#elif TONES_MAX_PINS_USED == 1
    digitalpinMode(TONE_PIN0_GPIO, MODE_OUTPUT);
    digitalPinWrite(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE);
#else 
#error "max Pin is suppor from 1 to 4 pins"
#endif

    for (uint8_t i = 0; i < TONES_MAX_PINS_USED; i++) {
        gstTones[i].State = 0;
        gstTones[i].Period = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneDriver >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneDriver                                                                |  
 | < @Description       : run in background task                                                         |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ToneDriver() {
#if TONES_MAX_PINS_USED == 4
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
    myTone(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE, &gstTones[1]);
    myTone(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE, &gstTones[2]);
    myTone(TONE_PIN3_GPIO, TONE_PIN3_DEFALUT_STATE, &gstTones[3]);
#elif TONES_MAX_PINS_USED == 3
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
    myTone(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE, &gstTones[1]);
    myTone(TONE_PIN2_GPIO, TONE_PIN2_DEFALUT_STATE, &gstTones[2]);
#elif TONES_MAX_PINS_USED == 2
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
    myTone(TONE_PIN1_GPIO, TONE_PIN1_DEFALUT_STATE, &gstTones[1]);
#elif TONES_MAX_PINS_USED == 1
    myTone(TONE_PIN0_GPIO, TONE_PIN0_DEFALUT_STATE, &gstTones[0]);
#else 
#error "max Pin is suppor from 1 to 4 pins"
#endif
}

#endif
#endif