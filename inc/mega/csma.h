
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

#ifndef CSMA_H
#define	CSMA_H

#include "../mega.h"
#if defined CSMA_MODULE
#if CSMA_MODULE
/*
---------------------------------------------------------------------------------------------------------
|                           < Uart Module  Checks >                                                     | 
---------------------------------------------------------------------------------------------------------
*/ 
#ifndef    USART_MODULE
#error    CSMA Module Must be used UART_MODULE
#elif      USART_MODULE == 0
#error     CSMA Module Must be used UART_MODULE 
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  Data Typed definitions   >                                          |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                < csma Frame  Format   >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 11 Byte                                                                     |
 | < Param u8Address       : 0 address  the device is a master                                           |
 |                         : 0x01 - 0x7F the slave address                                               |
 |                         : 0x80 the free address ,                                                     |
 |                         : 0x81 the block address ,                                                    |
 |                         : 0x82 address the default address of all slave devices                       |             
 |                         : 0x83 board cast address                                                     |
 | < Param u8Cmd           : 0 the command of ack frame                                                  |
 |                         : 255 the command of not ack frame                                            |
 |                         : 1 - 127  commands of request frame                                          |
 |                         : 128 - 254 comands of respones frame                                         |                                               
 | < Param u8ByteCount     : number of data byte in frame                                                |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
typedef struct {
    uint8_t u8Address;
    uint8_t u8Cmd;
    uint8_t u8ByteCount;
    uint8_t u8Data[8]; // 8byte data
} stFramCSMA_t;



/*
 ---------------------------------------------------------------------------------------------------------
 |                                < serial Frame  Format   >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 9 Byte                                                                      |
 | < Param u8ByteCount     : number of cmds send                                                         |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
typedef struct {
    uint8_t u8ByteCount;
    uint8_t u8Data[8]; // 8byte data
} stFramSerial_t;


/*
 ---------------------------------------------------------------------------------------------------------
 |                                < CSMA Frames definitions   >                                           |
 ---------------------------------------------------------------------------------------------------------
 */


/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  csma channel 0  Receive Frame    >                                  |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 11 Byte                                                                     |
 | < Param u8Address       : 0 address  the device is a master                                           |
 |                         : 0x01 - 0x7F the slave address                                               |
 |                         : 0x80 the free address ,                                                     |
 |                         : 0x81 the block address ,                                                    |
 |                         : 0x82 address the default address of all slave devices                       |             
 |                         : 0x83 board cast address                                                     |
 | < Param u8Cmd           : 0 the command of ack frame                                                  |
 |                         : 255 the command of not ack frame                                            |
 |                         : 1 - 127  commands of request frame                                          |
 |                         : 128 - 254 comands of respones frame                                         |                                               
 | < Param u8ByteCount     : number of data byte in frame                                                |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
extern stFramCSMA_t    gstcsmaCh0ReceiveFrame;
/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  csma channel 0  Transmission Frame    >                             |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 11 Byte                                                                     |
 | < Param u8Address       : 0 address  the device is a master                                           |
 |                         : 0x01 - 0x7F the slave address                                               |
 |                         : 0x80 the free address ,                                                     |
 |                         : 0x81 the block address ,                                                    |
 |                         : 0x82 address the default address of all slave devices                       |             
 |                         : 0x83 board cast address                                                     |
 | < Param u8Cmd           : 0 the command of ack frame                                                  |
 |                         : 255 the command of not ack frame                                            |
 |                         : 1 - 127  commands of request frame                                          |
 |                         : 128 - 254 comands of respones frame                                         |                                               
 | < Param u8ByteCount     : number of data byte in frame                                                |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
extern stFramCSMA_t    gstcsmaCh0TransmissionFrame;

#ifdef USART1_ENABLED
/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  csma channel 1  Receive Frame    >                                  |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 11 Byte                                                                     |
 | < Param u8Address       : 0 address  the device is a master                                           |
 |                         : 0x01 - 0x7F the slave address                                               |
 |                         : 0x80 the free address ,                                                     |
 |                         : 0x81 the block address ,                                                    |
 |                         : 0x82 address the default address of all slave devices                       |             
 |                         : 0x83 board cast address                                                     |
 | < Param u8Cmd           : 0 the command of ack frame                                                  |
 |                         : 255 the command of not ack frame                                            |
 |                         : 1 - 127  commands of request frame                                          |
 |                         : 128 - 254 comands of respones frame                                         |                                               
 | < Param u8ByteCount     : number of data byte in frame                                                |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
extern stFramCSMA_t    gstcsmaCh1ReceiveFrame;
/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  csma channel 1  Transmission Frame    >                             |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 11 Byte                                                                     |
 | < Param u8Address       : 0 address  the device is a master                                           |
 |                         : 0x01 - 0x7F the slave address                                               |
 |                         : 0x80 the free address ,                                                     |
 |                         : 0x81 the block address ,                                                    |
 |                         : 0x82 address the default address of all slave devices                       |             
 |                         : 0x83 board cast address                                                     |
 | < Param u8Cmd           : 0 the command of ack frame                                                  |
 |                         : 255 the command of not ack frame                                            |
 |                         : 1 - 127  commands of request frame                                          |
 |                         : 128 - 254 comands of respones frame                                         |                                               
 | < Param u8ByteCount     : number of data byte in frame                                                |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
extern stFramCSMA_t    gstcsmaCh1TransmissionFrame;
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                                < Seial Frames definitions   >                                          |
 ---------------------------------------------------------------------------------------------------------
 */

#ifdef USART1_ENABLED
/*
 *@macro FULL_DUPLEX   : serial channel worked with Full duplex mode
 */
#define  FULL_DUPLEX   (0)
/*
 *@macro HALF_DUPLEX   : serial channel worked with HALF duplex mode
 */
#define  HALF_DUPLEX   (1)
/*
 *@macro SERIAL_DIR   : serial channel worked with HALF duplex mode
 */
#ifndef   SERIAL_DIR
#define   SERIAL_DIR    HALF_DUPLEX
#endif


#if SERIAL_DIR == HALF_DUPLEX
/*
 ---------------------------------------------------------------------------------------------------------
 |                                < serial Frame  Format   >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 9 Byte                                                                      |
 | < Param u8ByteCount     : number of cmds send                                                         |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
extern stFramSerial_t gstSerialFrame;
#else
/*
 ---------------------------------------------------------------------------------------------------------
 |                                < serial Frame  Format   >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 9 Byte                                                                      |
 | < Param u8ByteCount     : number of cmds send                                                         |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
extern stFramSerial_t gstSerialTransmissionFrame;
/*
 ---------------------------------------------------------------------------------------------------------
 |                                < serial Frame  Format   >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < Description           : Fram  struct                                                                |
 | < Uasge                 : 9 Byte                                                                      |
 | < Param u8ByteCount     : number of cmds send                                                         |                                               
 | < Param u8Data          : 8 byte payload data                                                         |                                                                          
 ---------------------------------------------------------------------------------------------------------
 */
extern stFramSerial_t gstSerialReceiveFrame;
#endif

#endif


#endif
#endif

#endif /*CSMA_H*/















