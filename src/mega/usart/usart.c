
/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : usart.c                                                                  |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : no-used                                                                  |
| < PROGRAM USAGE            : 40 Byte with enable Uart 0, Uart 1 (20 Instruction)                      |                                    
| < Hardware Usage           : Uarts                                                                    |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#include "../../../inc/mega.h"
#if defined  USART_MODULE                                                          
#if      USART_MODULE

/* 
 ---------------------------------------------------------------------------------------------------------
 |                      <  Basic Function Definition >                                                   |
 ---------------------------------------------------------------------------------------------------------   
 */

#ifdef USART0_ENABLED
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart0Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart0Init                                                                 |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart0Init();
#endif


#ifdef USART1_ENABLED
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart1Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart1Init                                                                 |
 | < @Description       : initialization Hardware Uart1                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart1Init();
#endif

#ifdef USART2_ENABLED
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart2Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart2Init                                                                 |
 | < @Description       : initialization Hardware Uart2                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart2Init();
#endif


#ifdef USART3_ENABLED
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart3Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart3Init                                                                 |
 | < @Description       : initialization Hardware Uart3                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart3Init();
#endif
/* 
 ---------------------------------------------------------------------------------------------------------
 |                      <  Basic Function Implementions >                                                |
 ---------------------------------------------------------------------------------------------------------   
 */
#ifdef USART0_ENABLED

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart0Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart0Init                                                                 |
 | < @Description       : initialization Hardware Uart0                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart0Init() {
#if defined(ATMEGA_USART)
    UBRRH = (uint8_t) (BUAD0_REG >> 8);
    UBRRL = (uint8_t) BUAD0_REG;
    /* Enable USART receiver and transmitter and receive complete interrupt */
    UART0_CONTROL = _BV(TXCIE) | _BV(RXCIE) | (1 << RXEN) | (1 << TXEN);
    /* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL
    UCSRC = (1 << URSEL) | (3 << UCSZ0);
#else
    UCSRC = (3 << UCSZ0);
#endif
#elif defined(ATMEGA_USART0)
    UBRR0H = (uint8_t) (BUAD0_REG >> 8);
    UBRR0L = (uint8_t) BUAD0_REG;
    /* Enable USART receiver and transmitter and receive complete interrupt */
    UART0_CONTROL = _BV(RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL0
    UCSR0C = (1 << URSEL0) | (3 << UCSZ00);
#else
    UCSR0C = (3 << UCSZ00);
#endif

#elif defined(ATMEGA_UART)
    UBRRHI = (uint8_t) (BUAD0_REG >> 8);
    UBRR = (uint8_t) BUAD0_REG;
    /* Enable UART receiver and transmitter and receive complete interrupt */
    UART0_CONTROL = _BV(RXCIE) | (1 << RXEN) | (1 << TXEN)
#endif
}
#endif

#ifdef USART1_ENABLED

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart1Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart1Init                                                                 |
 | < @Description       : initialization Hardware Uart1                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart1Init() {
#if defined ATMEGA_USART1
    UBRR1H = (uint8_t) (BUAD1_REG >> 8);
    UBRR1L = (uint8_t) BUAD1_REG;

    /* Enable USART receiver and transmitter and receive complete interrupt */
    UART1_CONTROL = _BV(RXCIE1) | (1 << RXEN1) | (1 << TXEN1);

    /* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL1
    UCSR1C = (1 << URSEL1) | (3 << UCSZ10);
#else
    UCSR1C = (3 << UCSZ10);
#endif
#else 
#error "This Target not support USART 1 Plase remove t USART 1 configuration or chang target to support uart1"
#endif
}
#endif

#ifdef USART2_ENABLED

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart2Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart2Init                                                                 |
 | < @Description       : initialization Hardware Uart2                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart2Init() {
#if defined(ATMEGA_USART2)
    UBRR2H = (uint8_t) (BUAD2_REG >> 8);
    UBRR2L = (uint8_t) BUAD2_REG;

    /* Enable USART receiver and transmitter and receive complete interrupt */
    UART2_CONTROL = _BV(RXCIE2) | (1 << RXEN2) | (1 << TXEN2);

    /* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL2
    UCSR2C = (1 << URSEL2) | (3 << UCSZ20);
#else
    UCSR2C = (3 << UCSZ20);
#endif
#else 
#error "This Target not support USART 2 Plase remove t USART 2 configuration or chang target to support USART 2"
#endif
}
#endif

#ifdef USART3_ENABLED

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart3Init  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : void usart3Init                                                                 |
 | < @Description       : initialization Hardware Uart3                                                   |                    
 | < @return            : void                                                                            |
  ---------------------------------------------------------------------------------------------------------
 */
static void usart3Init() {
#if defined (ATMEGA_USART3)
    UBRR3H = (uint8_t) (BUAD3_REG >> 8);
    UBRR3L = (uint8_t) BUAD3_REG;

    /* Enable USART receiver and transmitter and receive complete interrupt */
    UART3_CONTROL = _BV(RXCIE3) | (1 << RXEN3) | (1 << TXEN3);

    /* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL3
    UCSR3C = (1 << URSEL3) | (3 << UCSZ30);
#else
    UCSR3C = (3 << UCSZ30);
#endif
#else 
#error "This Target not support USART 3 Plase remove t USART 3 configuration or chang target to support USART 3"
#endif
}
#endif


/* 
 ---------------------------------------------------------------------------------------------------------
 |                      <  user Function Implementions >                                                 |
 ---------------------------------------------------------------------------------------------------------   
 */
#ifdef USART0_ENABLED

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
void usart0PutByte(uint8_t byte) {
#if defined(ATMEGA_USART)
    UART0_DATA = byte;
#elif defined(ATMEGA_USART0)
    UART0_DATA = byte;
#elif defined(ATMEGA_UART)
    UART0_DATA = byte;
#endif
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart0GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart0GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart0 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
inline uint8_t usart0GetByte() {
    return UART0_DATA;
}
#endif

#ifdef USART1_ENABLED

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
inline void usart1PutByte(uint8_t byte) {
#if defined ATMEGA_USART1
    UART1_DATA = byte;
#endif
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart1GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart1GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart1 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
inline uint8_t usart1GetByte() {
#if defined ATMEGA_USART1
    return (UART1_DATA);
#endif
}

#endif


#ifdef USART2_ENABLED

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
inline void usart2PutByte(uint8_t byte) {
#if defined(ATMEGA_USART2)
    UART2_DATA = byte;
#endif    
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart2GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart2GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart2 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
inline uint8_t usart2GetByte() {
#if defined(ATMEGA_USART2)
    return UART2_DATA;
#endif
}


#endif

#ifdef USART3_ENABLED

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
inline void usart3PutByte(uint8_t byte) {
#if ATMEGA_USART3
    UART3_DATA = byte;
#endif
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < usart3GetByte  >                                                          |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t usart3GetByte                                                           |
 | < @Description       : load from receiver Hardware Uart3 buffer                                        |     
 | < @return            : byte received from other decives                                                |
  ---------------------------------------------------------------------------------------------------------
 */
inline uint8_t usart3GetByte() {
#if ATMEGA_USART3
    return UART3_DATA;
#endif
}

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
void usartInit() {
#if defined USART0_ENABLED
    usart0Init();
#endif

#if defined USART1_ENABLED
    usart1Init();
#endif

#if defined USART2_ENABLED
    usart2Init();
#endif

#if defined USART3_ENABLED
    usart3Init();
#endif
}

#endif
#endif