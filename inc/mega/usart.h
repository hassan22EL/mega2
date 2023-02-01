
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
 ---------------------------------------------------------------------------------------------------------
 |                      <  Device  Mode >                                                                |
 ---------------------------------------------------------------------------------------------------------   
 */



#if   defined(__AVR_ATmega8__) \
   || defined (__AVR_ATmega8A__)\
   || defined(__AVR_ATmega16__) \
   || defined (__AVR_ATmega16A__)\
   || defined(__AVR_ATmega32__) \
   || defined(__AVR_ATmega323__)
/* ATmega with one USART */
#define ATMEGA_USART
#define UART0_RECEIVE_INTERRUPT    USART_RXC_vect
#define UART0_TRANSMIT_INTERRUPT   USART_TXC_vect
#define UART0_UDREMPTY_INTERRUPT   USART_UDRE_vect
#define UART0_STATUS   UCSRA
#define UART0_CONTROL  UCSRB
#define UART0_DATA     UDR
#define UART0_UDRIE    UDRIE
#define  Empty_BUFFER0()                 ((UCSRA & (1<<UDRE)))
#elif defined(__AVR_ATmega8U2__) \
   || defined(__AVR_ATmega16U2__) \
   || defined(__AVR_ATmega16U4__) \
   || defined(__AVR_ATmega32U2__) \
   || defined(__AVR_ATmega32U4__) \
   || defined(__AVR_ATmega32U6__)
/* ATmega with one USART, but is called USART1 (untested) */
#define ATMEGA_USART1
#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
#define UART1_STATUS   UCSR1A
#define UART1_CONTROL  UCSR1B
#define UART1_DATA     UDR1
#define UART1_UDRIE    UDRIE1
#elif defined(__AVR_ATmega8515__) \
   || defined(__AVR_ATmega8535__)
/* ATmega with one USART */
#define ATMEGA_USART
#define UART0_RECEIVE_INTERRUPT   USART_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART_UDRE_vect
#define UART0_STATUS   UCSRA
#define UART0_CONTROL  UCSRB
#define UART0_DATA     UDR
#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega163__)
/* ATmega163 with one UART */
#define ATMEGA_UART
#define UART0_RECEIVE_INTERRUPT   UART_RX_vect
#define UART0_TRANSMIT_INTERRUPT  UART_UDRE_vect
#define UART0_STATUS   UCSRA
#define UART0_CONTROL  UCSRB
#define UART0_DATA     UDR
#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega162__)
/* ATmega with two USART */
#define ATMEGA_USART0
#define ATMEGA_USART1
#define UART0_RECEIVE_INTERRUPT   USART0_RXC_vect
#define UART1_RECEIVE_INTERRUPT   USART1_RXC_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#define UART1_STATUS   UCSR1A
#define UART1_CONTROL  UCSR1B
#define UART1_DATA     UDR1
#define UART1_UDRIE    UDRIE1
#elif defined(__AVR_ATmega64__) \
   || defined(__AVR_ATmega128__) \
   || defined (__AVR_ATmega128A__)
/* ATmega with two USART */
#define ATMEGA_USART0
#define ATMEGA_USART1
#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#define UART1_STATUS   UCSR1A
#define UART1_CONTROL  UCSR1B
#define UART1_DATA     UDR1
#define UART1_UDRIE    UDRIE1
#define  Empty_BUFFER0()                 ((UCSR0A & (1<<UDRE0)))
#define  Empty_BUFFER1()                 ((UCSR1A & (1<<UDRE1)))
#elif defined(__AVR_ATmega161__)
/* ATmega with UART */
#error "AVR ATmega161 currently not supported by this libaray !"
#elif defined(__AVR_ATmega169__)
/* ATmega with one USART */
#define ATMEGA_USART
#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART0_STATUS   UCSRA
#define UART0_CONTROL  UCSRB
#define UART0_DATA     UDR
#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega48__) \
   || defined(__AVR_ATmega88__) \
   || defined(__AVR_ATmega168__) \
   || defined(__AVR_ATmega48P__) \
   || defined(__AVR_ATmega88P__) \
   || defined(__AVR_ATmega168P__) \
   || defined(__AVR_ATmega328P__)
/* TLS-Added 48P/88P/168P/328P */
/* ATmega with one USART */
#define ATMEGA_USART0
#define UART0_RECEIVE_INTERRUPT   USART_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATmega329__) \
   || defined(__AVR_ATmega649__) \
   || defined(__AVR_ATmega325__) \
   || defined(__AVR_ATmega3250__) \
   || defined(__AVR_ATmega645__) \
   || defined(__AVR_ATmega6450__)
/* ATmega with one USART */
#define ATMEGA_USART0
#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATmega3290__) \
   || defined(__AVR_ATmega6490__)
/* TLS-Separated these two from the previous group because of inconsistency in the USART_RX */
/* ATmega with one USART */
#define ATMEGA_USART0
#define UART0_RECEIVE_INTERRUPT   USART_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATmega2560__) \
   || defined(__AVR_ATmega1280__) \
   || defined(__AVR_ATmega640__)
/* ATmega with four USART */
#define ATMEGA_USART0
#define ATMEGA_USART1
#define ATMEGA_USART2
#define ATMEGA_USART3
#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
#define UART2_RECEIVE_INTERRUPT   USART2_RX_vect
#define UART3_RECEIVE_INTERRUPT   USART3_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
#define UART2_TRANSMIT_INTERRUPT  USART2_UDRE_vect
#define UART3_TRANSMIT_INTERRUPT  USART3_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#define UART1_STATUS   UCSR1A
#define UART1_CONTROL  UCSR1B
#define UART1_DATA     UDR1
#define UART1_UDRIE    UDRIE1
#define UART2_STATUS   UCSR2A
#define UART2_CONTROL  UCSR2B
#define UART2_DATA     UDR2
#define UART2_UDRIE    UDRIE2
#define UART3_STATUS   UCSR3A
#define UART3_CONTROL  UCSR3B
#define UART3_DATA     UDR3
#define UART3_UDRIE    UDRIE3
#elif defined(__AVR_ATmega644__)
/* ATmega with one USART */
#define ATMEGA_USART0
#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATmega164P__) \
   || defined(__AVR_ATmega324P__) \
   || defined(__AVR_ATmega644P__) \
   || defined(__AVR_ATmega644PA__) \
   || defined(__AVR_ATmega1284P__)
/* ATmega with two USART */
#define ATMEGA_USART0
#define ATMEGA_USART1
#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#define UART1_STATUS   UCSR1A
#define UART1_CONTROL  UCSR1B
#define UART1_DATA     UDR1
#define UART1_UDRIE    UDRIE1
#endif
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


#if UART0_BUADRATE == StandBaudRate_1200
#define   BUAD0_REG            575
#elif UART0_BUADRATE == StandBaudRate_2400
#define   BUAD0_REG            287
#elif UART0_BUADRATE == StandBaudRate_4800
#define   BUAD0_REG            143
#elif UART0_BUADRATE == StandBaudRate_9600
#define   BUAD0_REG            71
#elif UART0_BUADRATE == StandBaudRate_19200
#define   BUAD0_REG            35
#elif UART0_BUADRATE == StandBaudRate_38400
#define   BUAD0_REG            17
#elif UART0_BUADRATE == StandBaudRate_57600
#define   BUAD0_REG            11
#elif UART0_BUADRATE == StandBaudRate_76800
#define   BUAD0_REG            8
#elif UART0_BUADRATE == StandBaudRate_115200
#define   BUAD0_REG            5
#endif



#ifdef USART0_ENABLED
#ifndef     UART0_BUADRATE
#warning   "Please defined uart0_BuadRate From table look modules.h usart"
#else

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
void usart0PutByte(uint8_t byte);
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

