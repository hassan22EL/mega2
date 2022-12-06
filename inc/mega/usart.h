
/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : usart.h                                                                  |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : no-used                                                                  |
| < PROGRAM USAGE            : 40 Byte with enable Uart 0, Uart 1 (20 Instruction)                      |                                    
| < Hardware Usage           : Uarts                                                                    |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
*/
#ifndef USART_H
#define	USART_H

#include "../mega.h"

#if defined  USART_MODULE                                                          
#if      USART_MODULE

#ifndef  F_CPU
#error "Please Define F_CPU"
#endif
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < Macros  >                                                                  |
  ---------------------------------------------------------------------------------------------------------
*/
/*
 ---------------------------------------------------------------------------------
 |                               < UART SPEED                                    |                                      
 |-------------------------------------------------------------------------------|
 |  speed (Mbps)             |  Bit duration  |  byte rate      | byte duration  |
 |---------------------------|----------------|-----------------|----------------|  
 | @StandBaudRate_1200       |    833.33 us   |  00120 byte/s   |  8333.33 us    |                
 | @StandBaudRate_2400       |    416.66 us   |  00240 byte/s   |  4166.66 us    |                                   
 | @StandBaudRate_4800       |    208.33 us   |  00480 byte/s   |  2083.33 us    |                     
 | @StandBaudRate_9600       |    104.16 us   |  00960 byte/s   |  1041.66 us    |                            
 | @StandBaudRate_19200      |    052.08 us   |  01920 byte/s   |  0520.83 us    |                                      
 | @StandBaudRate_38400      |    026.04 us   |  03840 byte/s   |  0260.41 us    |                        
 | @StandBaudRate_57600      |    017.36 us   |  05760 byte/s   |  0173.61 us    |
 | @StandBaudRate_76800      |    013.68 us   |  07680 byte/s   |  0130.20 us    |
 | @StandBaudRate_115200     |    008.68 us   |  11520 byte/s   |  0086.00 us    |                                                                  
 ---------------------------------------------------------------------------------
 */

#define StandBaudRate_1200     (1200UL)    
#define StandBaudRate_2400     (2400UL)    
#define StandBaudRate_4800     (4800UL)   
#define StandBaudRate_9600     (9600UL)  
#define StandBaudRate_19200    (19200UL)     
#define StandBaudRate_38400    (38400UL)    
#define StandBaudRate_57600    (57600UL)    
#define StandBaudRate_76800    (76800UL)    
#define StandBaudRate_115200   (115200UL)    


#define USART_BAUD_RATE(_br_)                 (uint16_t)((float)(F_CPU * 64/ (16 * (float)(_br_)) + 0.5))
#ifdef USART0_ENABLED
#ifndef     UART0_BUADRATE
#warning   "Please defined uart0_BuadRate From table look modules.h usart"
#else
#define     BUAD0_REG                           USART_BAUD_RATE(UART0_BUADRATE) 
#define     USART0_BIT_DURATION                 ((uint16_t) ((1000000) / (float) (UART0_BUADRATE)) + .5)            
#define     USART0_BYTE_DURATION                ((uint16_t) ((100000) / (float) (UART0_BUADRATE)) + .5) 
#endif

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart0PutByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart0PutByte                                                              |
 | < @Description       : load transmission Hardware Uart0 buffer                                         |     
 | < @Param byte        : byte to send other device                                                       |
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
extern void usart0PutByte(uint8_t byte);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart0GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart0GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart0 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
extern uint8_t usart0GetByte();
#endif

#ifdef USART1_ENABLED
#ifndef     UART1_BUADRATE
#warning   "Please defined uart1_BuadRate From table look modules.h usart"
#else
#define   BUAD1_REG                               USART_BAUD_RATE(UART1_BUADRATE) 
#define     USART1_BIT_DURATION                 ((uint16_t) ((1000000) / (float) (UART1_BUADRATE)) + .5)            
#define     USART1_BYTE_DURATION                ((uint16_t) ((100000) / (float) (UART1_BUADRATE)) + .5) 
#endif

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart1PutByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart1PutByte                                                              |
 | < @Description       : load transmission Hardware Uart1 buffer                                         |     
 | < @Param byte        : byte to send other device                                                       |
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
extern void usart1PutByte(uint8_t byte);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart1GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart1GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart1 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
extern uint8_t usart1GetByte();
#endif



#ifdef USART2_ENABLED
#ifndef     UART2_BUADRATE
#warning   "Please defined uart2_BuadRate From table look modules.h usart"
#else
#define     BUAD2_REG                            USART_BAUD_RATE(UART2_BUADRATE) 
#define     USART2_BIT_DURATION                 ((uint16_t) ((1000000) / (float) (UART2_BUADRATE)) + .5)            
#define     USART2_BYTE_DURATION                ((uint16_t) ((100000) / (float) (UART2_BUADRATE)) + .5) 
#endif

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart2PutByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart2PutByte                                                              |
 | < @Description       : load transmission Hardware Uart2 buffer                                         |     
 | < @Param byte        : byte to send other device                                                       |
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
extern void usart2PutByte(uint8_t byte);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart2GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart2GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart2 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
extern uint8_t usart2GetByte();
#endif

#ifdef USART3_ENABLED
#ifndef     UART3_BUADRATE
#warning   "Please defined uart3_BuadRate From table look modules.h usart"
#else
#define   BUAD3_REG              USART_BAUD_RATE(UART3_BUADRATE) 
#define     USART3_BIT_DURATION                 ((uint16_t) ((1000000) / (float) (UART3_BUADRATE)) + .5)            
#define     USART3_BYTE_DURATION                ((uint16_t) ((100000) / (float)  (UART3_BUADRATE)) + .5) 
#endif

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart3PutByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart3PutByte                                                              |
 | < @Description       : load transmission Hardware Uart3 buffer                                         |     
 | < @Param byte        : byte to send other device                                                       |
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
extern void usart3PutByte(uint8_t byte);
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart3GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart3GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart3 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
extern uint8_t usart3GetByte();
#endif

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usartInit  >                                                              |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usartInit                                                                  |
 | < @Description       : initialization Hardware for all enabled                                         |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
void usartInit();




#endif
#endif



#endif	/* USART_H */

