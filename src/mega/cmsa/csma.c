
/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   csma.c
 * Author       :   Hassan Elsaied
 * Data Memory  :   total byte used 0 Byte  
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   1-hour
 * Comments     :   no comment
 *  
 */
#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if defined CSMA_MODULE
#if CSMA_MODULE 

/*
--------------------------------------------------------------------------------------
|                       Frame  Format                                                |
--------------------------------------------------------------------------------------
| @member u8Address         : 0 address  the device is a master                      |
|                           : 0x01 - 0x7F the slave address                          |
|                           : 0x80 the free address ,                                |
|                           : 0x81 the block address ,                               |
|                           : 0x82 address the default address of all slave devices  |             
|                           : 0x83 board cast address                                |
--------------------------------------------------------------------------------------
| @member u8Cmd             : 0 the command of ack frame                             |
|                           : 255 the command of not ack frame                       |
|                           : 1 - 127  commands of request frame                     |
|                           : 128 - 254 comands of respones frame                    |
--------------------------------------------------------------------------------------
| @member u8ByteCount       : number of data byte in frame                           |
| @member u8Data            : 8 byte payload data                                    |
 -------------------------------------------------------------------------------------
 */
typedef struct {
    uint8_t u8Address;
    uint8_t u8Cmd;
    uint8_t u8ByteCount;
    uint8_t u8Data[8]; // 8byte data
} stFram_t;

typedef enum _eFrameIndex {
    Address = 0,
    cmd = 1,
    bytecount = 2,
    startbyte = 3
} eFrameIndex;

typedef enum _ecsmaAddrress {
    csmaFreeAddress = 0x80,
    csmaBlockAddress = 0x81,
    csmaDefaultAddress = 0x82,
    csmaBroadCastAddress = 0x83,
} ecsmaAddrress;

#if defined USART0_ENABLED
/*
----------------------------------------------------------------------------------------------------------------
|                                 Global data link layer Variables                                             |          
----------------------------------------------------------------------------------------------------------------
| @var gu16timeValue        : Data Link Layer wait required before send frame                                  |
| @var gu8collisionCounter  : Data Link Layer after detect collision wait a rand value by number of retry      |
| @var gu8csmaStatus        : Data Link Layer state of the csma : blocked or send or receive                   |                                     |
| @var gu8Address           : Data Link Layer station current address                                          |
 ---------------------------------------------------------------------------------------------------------------
 */
static volatile uint16_t gu16timeValue;
static volatile uint8_t gu8collisionCounter;
static volatile byte_Flags_t gu8csmaStatus;
static volatile uint8_t gu8Address;
/*
----------------------------------------------------------------------------------------------------------------
|                                 Global data link layer Frames                                                |          
----------------------------------------------------------------------------------------------------------------
| @gsReceiveFrame       : Data Link Layer read any frame received by this frame                                |
| @gsTransmissionFrame  :  Data Link Layer application can send any frame by this frame                        | 
 ---------------------------------------------------------------------------------------------------------------
 */
static stFram_t gsReceiveFrame;
static stFram_t gsTransmissionFrame;

/*
-----------------------------------------------------------------------------------------------
|                       Global Buffers  in physical layer                                     |          
-----------------------------------------------------------------------------------------------
| @buf gu8ReceiveBuf        : physical layer byte received  max value 12 byte                 |
| @buf gu8SendBuf           : physical layer byte sends  max value 12   byte                  |
| @buf gu8SERIAL            : physical layer serial number max value 5 byte                   |
| @var gu8ReceiveByteCount  : physical layer number of byte received index                    |
| @var gu8SendByteCount     : physical layer number of byte send index                        |
-----------------------------------------------------------------------------------------------
| @physical layer Frame : address | command | length |Data|CRC |                              |
 ----------------------------------------------------------------------------------------------
| @note : 12 byte used in physical layer in send buffer or receive buffer is                  |
|      : @address   1 byte                                                                    |
|      : @command   1 byte                                                                    |
|      : @length    1 byte                                                                    |
|      : @Data      8 byte                                                                    |
|      : @CRC       1 byte                                                                    |
|@total byte used   12 byte                                                                   |  
----------------------------------------------------------------------------------------------- 
 */
#define   CSMA_MAX_BUFFER         12

static volatile uint8_t gu8ReceiveBuf[CSMA_MAX_BUFFER];
static volatile uint8_t gu8SendBuf[CSMA_MAX_BUFFER];
static volatile uint8_t gu8ReceiveByteCount;
static volatile uint8_t gu8SendByteCount;
/*
----------------------------------------------------------------------------------------------------
|                             CRC-check                                                            | 
----------------------------------------------------------------------------------------------------
| @benfit               : CRC is based on polynomial function and divide this by polynomial        |
|                       : for example the message  X^7+x^6+X^5+X^4+X^3+X^2+X+1 the is bit          |
|                       : is 7 bit and divide this message by x^3 + X + 1                          |
|                       : the quotient (Q) = X^4+X^3+1 and reminder is (R) =  X^2 + 1              |
|                       : result  polynomial message = Q*G + R                                     |
|                       : the message contains m-bit message and number of bis and 
|                       : check sum contains r-bit  mX^r =  Q*G + R  when G G should be of degree r 
|                       : The generator polynomial  x+1 creates a checksum of length 1, which
|                       : applies even parity to the message 
 *                      : G polynomial x^12 + x^11 +x^3+ x2 +x+ 1   with r = 12bit this function 
 *                      : generate by this function  mX^r + R mod G = 0 
|                       : required function G polynomial  division circuit using shift  
|                       :  
|                       : and 
|
----------------------------------------------------------------------------------------------------
| @param   crc          : Init value                                                               |
| @param   data         : pointer to data checked                                                  | 
| @param   len          : length of the data check                                                 |
| @referenc             : https://perswww.kuleuven.be/~u0068190/Onderwijs/Extra_info/crc.pdf       |                                                              |                                                                           | 
| @return               : void                                                                     |  
----------------------------------------------------------------------------------------------------
 */
static uint8_t csmaCRCCheck(volatile uint8_t *data, volatile uint8_t len);
/*
------------------------------------------------------------------------------------------------
|                    FramNetWork                                                               | 
------------------------------------------------------------------------------------------------
| @benfit       : Data Link  Layer Received a Frame and set direction of this frame is request | 
|               : to network layer or response to network layer and run network call back      |
|               : with commands and data                                                       |
| @return       : void                                                                 |                                                                   |  
------------------------------------------------------------------------------------------------
 */

static void FramNetWork();
/*
------------------------------------------------------------------------------------------------------
|                     Decapsulate                                                                     | 
-------------------------------------------------------------------------------------------------------
| @benfit              : this function check this ture frame or not if the frame is true send the ack | 
|                      : and assign frame from physical layer to data link layer                      |
|                      : frame is not true send not ack   remove physical layer buffer and send not   |
|                      : ack frame to sender is repeat a frame                                        |
|                      : with commands and data                                                       |                                                                           | 
| @return              : void                                                                         |  
-------------------------------------------------------------------------------------------------------
 */
static void Decapsulate();
/*
------------------------------------------------------------------------------------------------
|                    Encapsulate                                                               | 
------------------------------------------------------------------------------------------------
| @benfit       : assign frame frome Data link layer to physical buffer                        | 
|               :  and start frame transmission                                                |
| @return       :  return void                                                                 |                                                                   |  
------------------------------------------------------------------------------------------------
 */
static void Encapsulate();
/*
------------------------------------------------------------------------------------------------
|                    csma_RestTimer                                                            | 
------------------------------------------------------------------------------------------------
| @benfit       : physical Layer is Busy state |                                               |
| @return       :  return void                                                                 |                                                                   |  
------------------------------------------------------------------------------------------------
 */
static void csma_RestTimer(void);
/*
------------------------------------------------------------------------------------------------
|                    csma_StartTimer                                                           | 
------------------------------------------------------------------------------------------------
| @benfit       : physical Layer is Ready state                                                |
| @return       :  return void                                                                 |                                                                   |  
------------------------------------------------------------------------------------------------
 */
static void csma_StartTimer(uint16_t u16Value);



static void FramNetWork();

/*
------------------------------------------------------------------------------------------------------
|                     Decapsulate                                                                     | 
-------------------------------------------------------------------------------------------------------
| @benfit              : this function check this ture frame or not if the frame is true send the ack | 
|                      : and assign frame from physical layer to data link layer                      |
|                      : frame is not true send not ack   remove physical layer buffer and send not   |
|                      : ack frame to sender is repeat a frame                                        |
|                      : with commands and data                                                       |                                                                           | 
| @return              : void                                                                         |  
-------------------------------------------------------------------------------------------------------
 */
static void Decapsulate() {

}
/*
------------------------------------------------------------------------------------------------
|                    Encapsulate                                                               | 
------------------------------------------------------------------------------------------------
| @benfit       : assign frame frome Data link layer to physical buffer                        | 
|               :  and start frame transmission                                                |                                        |
| @return       :  return void                                                                 |                                                                   |  
------------------------------------------------------------------------------------------------
 */
static void Encapsulate();

/*
------------------------------------------------------------------------------------------------
|                    csma_RestTimer                                                            | 
------------------------------------------------------------------------------------------------
| @benfit       : physical Layer is Busy state |                                               |
| @return       :  return void                                                                 |                                                                   |  
------------------------------------------------------------------------------------------------
 */
static void csma_RestTimer(void) {

}

/*
------------------------------------------------------------------------------------------------
|                    csma_StartTimer                                                           | 
------------------------------------------------------------------------------------------------
| @benfit       : physical Layer is Ready state                                                |
| @return       :  return void                                                                 |                                                                   |  
------------------------------------------------------------------------------------------------
 */
static void csma_StartTimer(uint16_t u16Value);

/*
----------------------------------------------------------------------------------------------------
|                             CRC-check                                                            | 
----------------------------------------------------------------------------------------------------
| @benfit               : CRC is based on polynomial function and divide this by polynomial        |
|                       : for example the message  X^7+x^6+X^5+X^4+X^3+X^2+X+1 the is bit          |
|                       : is 7 bit and divide this message by x^3 + X + 1                          |
|                       : the quotient (Q) = X^4+X^3+1 and reminder is (R) =  X^2 + 1              |
|                       : result  polynomial message = Q*G + R                                     |
|                       : the message contains m-bit message and number of bis and 
|                       : check sum contains r-bit  mX^r =  Q*G + R  when G G should be of degree r 
|                       : The generator polynomial  x+1 creates a checksum of length 1, which
|                       : applies even parity to the message 
 *                      : G polynomial x^12 + x^11 +x^3+ x2 +x+ 1   with r = 12bit this function 
 *                      : generate by this function  mX^r + R mod G = 0 
|                       : required function G polynomial  division circuit using shift  
|@example               : G = 1101  and mX = 100100000  divide mx/G and get R 
|                       : 1/1 = 1 * 1101 = 1001-1101 = 1000 / 1101 = 1  .........etc
|
|
----------------------------------------------------------------------------------------------------
| @param   crc          : Init value                                                               |
| @param   data         : pointer to data checked                                                  | 
| @param   len          : length of the data check                                                 |
| @referenc             : https://perswww.kuleuven.be/~u0068190/Onderwijs/Extra_info/crc.pdf       |                                                              |                                                                           | 
| @return               : void                                                                     |  
----------------------------------------------------------------------------------------------------
 */
static uint8_t csmaCRCCheck(volatile uint8_t *data, volatile uint8_t len) {
    /*8 bit crc */
    uint8_t crc, j, i, byte;
    crc = 0;
    i = 0;
    j = 0;

    for (i = 0; i < len; i++) {
        byte = data [i];
        crc ^= byte;
        for (j = 0; j < 8; j++) {
            if (crc & 1)
                crc ^= 0x91;
            crc >>= 1;

        }
    }
    return crc;
}


#endif



#endif
#endif