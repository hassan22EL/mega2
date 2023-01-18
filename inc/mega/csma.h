
/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                  : csma.h                                                                      |                                  
| < Author                : Hassan Elsaied                                                              |
| < Version               : Mega2v241022                                                                |
| < Refences              : no- ref                                                                     |  
| < SRAM USAGE            : channel 0 only used 62 Byte                                                 |
|                         : channel 0 and channel 1 with serial half-duplex 130 Byte                    |
|                         : channel 0 and channel 1 with serial Full-duplex 139 Byte                    |
| < PROGRAM USAGE         : channel 0 only used  Byte ( Instructions)                                   |
|                         : channel 0 and channel 1 with serial half-duplex  Byte (Instruction)         |
|                         : channel 0 and channel 1 with serial Full-duplex  Byte Byte (Instruction)    |                                     
| < Hardware Usage        : Timer 1 and USART 0 with channel 0 only used                                |
|                         : Timer 1 and Timer 2 and USART 0 and USART 1 with channel 0 and channel 1    |
| < File Created          : 24-10-2022                                                                  |
---------------------------------------------------------------------------------------------------------
 */
#include "../mega.h"

#ifndef CSMA_H
#define	CSMA_H


#if defined CSMA_MODULE
#if CSMA_MODULE


/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < commTimerInit >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void commTimerInit                                                                                | 
 | < @Description       : configuration of timer 2 and External Interrupts                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < csmaDriver >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaDriver                                                                |                                          
 | < @Description       : Handling Received Data                                                         |                                                              |                                                                                                                          |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
void csmaDriver();
#if defined USART1_ENABLED

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param buf         : Pointer To data send Run                                                       |  
 | < @Param len         : number of byte to send  ID                                                     |
 | < @Param DA          : Destination station address                                                    |
 | < @Param Type        : Data Request or response                                                       |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
uint8_t putDataCh1(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type);
#endif
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param buf         : Pointer To data send Run                                                       |  
 | < @Param len         : number of byte to send  ID                                                     |
 | < @Param DA          : Destination station address                                                    |
 | < @Param Type        : Data Request or response                                                       |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                          |                 
 ----------------------------------------------------------------------------------------------------------
 */
uint8_t putDataCh0(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type);
#if defined USART1_ENABLED
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < CsmaChannle0Ready >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void CsmaChannle0Ready                                                         |                                          
 | < @Description       : check the channel 1 is ready or not                                            |                                                                                                                           |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */

uint8_t CsmaChannle1Ready();


#endif


#endif
#endif

#endif /*CSMA_H*/















