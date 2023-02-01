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
#ifndef TONE_H
#define	TONE_H

#include "../mega.h"
#if defined TONE_MODULE
#if TONE_MODULE
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
uint8_t isTonePlaying(uint8_t Index);
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
void Toneplay(gpio_t pin, uint8_t Index, uint16_t frequency, uint32_t duration, uint8_t duty);
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
void Tonestop(gpio_t pin, uint8_t Index, EN_GPIO_t defaultState);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneInit >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneInit                                                                  |  
 | < @Description       : Init I/O with MAX_PIN Used                                                     |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ToneInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ToneDriver >                                                        |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ToneDriver                                                                |  
 | < @Description       : run in background task                                                         |                                               |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ToneDriver();

#endif
#endif

#endif	/* TONE_H */

