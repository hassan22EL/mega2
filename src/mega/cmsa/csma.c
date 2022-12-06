
/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                  : csma.c                                                                      |                                  
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

#include "../../../inc/mega.h"
#if defined CSMA_MODULE
#if CSMA_MODULE 

/*
 *< @marco CSMA_PHYSICAL_BUFFER  physical layer data send
 */
#define  CSMA_PHYSICAL_BUFFER    12

/*
 * < @union  comm_flags : communication flags used in driver
 */
typedef union {
    uint8_t byte;

    struct {
        unsigned CH : 2;
        unsigned SR : 2;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
    };
} comm_flags;

/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  CSMA _DATA   >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < Description                             : csma  struct                                              |
 | < Uasge                                   : 35 Byte                                                   |                                              
 | < Param u8MyAddress                       : device address is default is FE                           |                                               
 | < Param u16Time                           : watting time berfore send any frame                       |
 | < Param u8Collision                       : number of the collision  per send frame                   | 
 | < Param u8State                           : csma status (received or blocked or Transmission ,start)  |
 | < Param u8ReciveByteCount                 : number of byte received                                   |
 | < Param u8TransmissionByteCount           : number of byte transmisstion per fram                     |
 | < Param u8PhysicalLayerTransmissionBuffer : physical layer trnsmission data have 12byte               |
 | < Param u8PhysicalLayerReceiverBuffer     : physical layer rceived data have 12 byte                  |  
 | < Param gpFcomHostCallback                : Request frame Call backs                                  |
 | < Param gpFcomClientCallback              : Response Frame Call backs                                 |                                          
 ---------------------------------------------------------------------------------------------------------
 */
typedef struct {
    volatile uint8_t u8MyAddress;
    volatile uint16_t u16Time;
    volatile uint8_t u8Collision;
    volatile byte_Flags_t u8State;
    volatile uint8_t u8ReciveByteCount;
    volatile uint8_t u8TransmissionByteCount;
    volatile uint8_t u8PhysicalLayerTransmissionBuffer[CSMA_PHYSICAL_BUFFER]; /*12 byte used*/
    volatile uint8_t u8PhysicalLayerReceiverBuffer[CSMA_PHYSICAL_BUFFER]; /*12 byte used*/
    volatile pAsyncFunc_t gpFcomHostCallback;
    volatile pAsyncFunc_t gpFcomClientCallback;
} csmaChannel_t;

#ifdef USART1_ENABLED

/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  Serial _DATA   >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < Description        : csma  struct                                                                   |
 | < Uasge              : 1 Byte                                                                         |                                              
 | < Param flags        : status of the serial commuincations                                            |                                    
 ---------------------------------------------------------------------------------------------------------
 */

typedef struct {
    volatile byte_Flags_t flags;
} serialChannel_t;
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                                <CSMA  variables definitions   >                                       |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                < CSMA Channel definitions   >                                             |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  CSMA channel 0   >                                                  |
 ---------------------------------------------------------------------------------------------------------
 | < Description                             : csma channel 0 struct                                     |
 | < Uasge                                   : 35 Byte                                                   |                                              
 | < Param u8MyAddress                       : device address is default is FE                           |                                               
 | < Param u16Time                           : watting time berfore send any frame                       |
 | < Param u8Collision                       : number of the collision  per send frame                   | 
 | < Param u8State                           : csma status (received or blocked or Transmission ,start)  |
 | < Param u8ReciveByteCount                 : number of byte received                                   |
 | < Param u8TransmissionByteCount           : number of byte transmisstion per fram                     |
 | < Param u8PhysicalLayerTransmissionBuffer : physical layer trnsmission data have 12byte               |
 | < Param u8PhysicalLayerReceiverBuffer     : physical layer rceived data have 12 byte                  |  
 | < Param gpFcomHostCallback                : Request frame Call backs                                  |
 | < Param gpFcomClientCallback              : Response Frame Call backs                                 |                                          
 ---------------------------------------------------------------------------------------------------------
 */
csmaChannel_t gstcsmaCh0;




#ifdef USART1_ENABLED
/*
 ---------------------------------------------------------------------------------------------------------
 |                                <  CSMA channel 1   >                                                  |
 ---------------------------------------------------------------------------------------------------------
 | < Description                             : csma channel 1 struct                                     |
 | < Uasge                                   : 35 Byte                                                   |                                              
 | < Param u8MyAddress                       : device address is default is FE                           |                                               
 | < Param u16Time                           : watting time berfore send any frame                       |
 | < Param u8Collision                       : number of the collision  per send frame                   | 
 | < Param u8State                           : csma status (received or blocked or Transmission ,start)  |
 | < Param u8ReciveByteCount                 : number of byte received                                   |
 | < Param u8TransmissionByteCount           : number of byte transmisstion per fram                     |
 | < Param u8PhysicalLayerTransmissionBuffer : physical layer trnsmission data have 12byte               |
 | < Param u8PhysicalLayerReceiverBuffer     : physical layer rceived data have 12 byte                  |  
 | < Param gpFcomHostCallback                : Request frame Call backs                                  |
 | < Param gpFcomClientCallback              : Response Frame Call backs                                 |                                          
 ---------------------------------------------------------------------------------------------------------
 */
csmaChannel_t gstcsmaCh1;
#endif

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
stFramCSMA_t gstcsmaCh0ReceiveFrame;
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
stFramCSMA_t gstcsmaCh0TransmissionFrame;

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
stFramCSMA_t gstcsmaCh1ReceiveFrame;
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
stFramCSMA_t gstcsmaCh1TransmissionFrame;
#endif
/*
 ---------------------------------------------------------------------------------------------------------
 |                                < Serial  variables definitions   >                                    |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                < Serial Channel definitions   >                                       |
 ---------------------------------------------------------------------------------------------------------
 */
#ifdef USART1_ENABLED
/*
 ---------------------------------------------------------------------------------------------------------
 |                                <   Serial Channel    >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < Description        : serial channel    struct                                                       |
 | < Uasge              : 1 Byte                                                                         |                                              
 | < Param flags        : status of the serial commuincations                                            |                                    
 ---------------------------------------------------------------------------------------------------------
 */
serialChannel_t gstserialCh;

/*
 ---------------------------------------------------------------------------------------------------------
 |                                < Serial Frames definitions   >                                        |
 ---------------------------------------------------------------------------------------------------------
 */



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
stFramSerial_t gstSerialFrame;
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
stFramSerial_t gstSerialTransmissionFrame;
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
stFramSerial_t gstSerialReceiveFrame;
#endif

#endif
#ifdef USART1_ENABLED
/*
 ---------------------------------------------------------------------------------------------------------
 | < @var gu8communicationFlags : general flags used                                                     | 
 ---------------------------------------------------------------------------------------------------------
 | < @CH     :                                                                                           |
 |                   --------------------------------------------------------------------------          |
 |                   | CH |                    Description                                    |          |
 |                   --------------------------------------------------------------------------          |
 |                   |  0 |  channel 0 worked as csma_c and channel 1 worked as csma_c        |          |
 |                   --------------------------------------------------------------------------          |                  
 |                   |  1 |  channel 0 worked as csma_c and channel 1 worked as serial        |          |
 |                   --------------------------------------------------------------------------          |
 |                   |  2 |  channel 0 worked as serial and channel 1 worked as csma_c        |          |
 |                   --------------------------------------------------------------------------          |
 |                   |  3 |  channel 0 worked as serial and channel 1 worked as serial        |          |
 |                   --------------------------------------------------------------------------          |
 |  < @SR    :                        Serial number assignment                                |          |
 |                   --------------------------------------------------------------------------          |
 |                   | SR |                    Description                                    |          |
 |                   --------------------------------------------------------------------------          |
 |                   |  0 | serial number not assignment                                      |          |
 |                   --------------------------------------------------------------------------          |                  
 |                   |  1 | serial number assignment with channel 0 (channel 0 slave)         |          |
 |                   --------------------------------------------------------------------------          |
 |                   |  2 | serial number assignment with channel 1 (channel 1 slave)         |          |
 |                   --------------------------------------------------------------------------          |
 |                   |  3 | removed serial number                                             |          |
 |                   --------------------------------------------------------------------------          |
 |  < @note          : CH default  :used is channel 0 worked as csma_c and channel 1 worked as serial    | 
 ---------------------------------------------------------------------------------------------------------
 */
volatile comm_flags gu8communicationFlags;
#endif
volatile uint8_t DeviceSerialNumber[5]; /*store value in program memory*/

/* 
 ---------------------------------------------------------------------------------------------------------
 |                      <  Basic Function Definition >                                                   |
 ---------------------------------------------------------------------------------------------------------   
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < CRC-check   >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function           : void CRC-check                                                                |
 | < @Description        : CRC is based on polynomial function and divide this by polynomial             |
 |                       : for example the message  X^7+x^6+X^5+X^4+X^3+X^2+X+1 the is bit               |
 |                       : is 7 bit and divide this message by x^3 + X + 1                               |
 |                       : the quotient (Q) = X^4+X^3+1 and reminder is (R) =  X^2 + 1                   |
 |                       : result  polynomial message = Q*G + R                                          |
 |                       : the message contains m-bit message and number of bis and                      |
 |                       : check sum contains r-bit  mX^r =  Q*G + R  when G G should be of degree r     |
 |                       : The generator polynomial  x+1 creates a checksum of length 1, which           |
 |                       : applies even parity to the message                                            |
 |                       : G polynomial x^12 + x^11 +x^3+ x2 +x+ 1   with r = 12bit this function        |
 |                       : generate by this function  mX^r + R mod G = 0                                 |
 |                       : required function G polynomial  division circuit using shift                  |
 |                       : @example G = 1101  and mX = 100100000  divide mx/G and get R                  |
 |                       : 1/1 = 1 * 1101 = 1001-1101 = 1000 / 1101 = 1  .........etc                    |
 | < @Param crc          : Init value                                                                    |
 | < @Param data         : pointer to data checked                                                       | 
 | < @Param len          : length of the data check                                                      |
 | < @Referenc           : https://perswww.kuleuven.be/~u0068190/Onderwijs/Extra_info/crc.pdf            |                     
 | < @return             : void                                                                          |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t csmaCRCCheck(volatile uint8_t *data, volatile uint8_t len);
/* 
 ---------------------------------------------------------------------------------------------------------
 |                      <  Basic Function Implemntions >                                                 |
 ---------------------------------------------------------------------------------------------------------   
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < CRC-check   >                                                            |
 ---------------------------------------------------------------------------------------------------------
 | < @Function           : void CRC-check                                                                |
 | < @Description        : CRC is based on polynomial function and divide this by polynomial             |
 |                       : for example the message  X^7+x^6+X^5+X^4+X^3+X^2+X+1 the is bit               |
 |                       : is 7 bit and divide this message by x^3 + X + 1                               |
 |                       : the quotient (Q) = X^4+X^3+1 and reminder is (R) =  X^2 + 1                   |
 |                       : result  polynomial message = Q*G + R                                          |
 |                       : the message contains m-bit message and number of bis and                      |
 |                       : check sum contains r-bit  mX^r =  Q*G + R  when G G should be of degree r     |
 |                       : The generator polynomial  x+1 creates a checksum of length 1, which           |
 |                       : applies even parity to the message                                            |
 |                       : G polynomial x^12 + x^11 +x^3+ x2 +x+ 1   with r = 12bit this function        |
 |                       : generate by this function  mX^r + R mod G = 0                                 |
 |                       : required function G polynomial  division circuit using shift                  |
 |                       : @example G = 1101  and mX = 100100000  divide mx/G and get R                  |
 |                       : 1/1 = 1 * 1101 = 1001-1101 = 1000 / 1101 = 1  .........etc                    |
 | < @Param crc          : Init value                                                                    |
 | < @Param data         : pointer to data checked                                                       | 
 | < @Param len          : length of the data check                                                      |
 | < @Referenc           : https://perswww.kuleuven.be/~u0068190/Onderwijs/Extra_info/crc.pdf            |                     
 | < @return             : void                                                                          |
 ---------------------------------------------------------------------------------------------------------
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