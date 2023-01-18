
/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                  : csma.c                                                                      |                                  
| < Author                : Hassan Elsaied                                                              |
| < Version               : Mega2v241022                                                                |
| < Refences              : no- ref                                                                     |                                     
| < Hardware Usage        : Timer 2 and USART 0 with channel 0 only used                                |
                          : USART 0 and USART 1 with both channel used                                  |
| < File Created          : 24-10-2022                                                                  |
---------------------------------------------------------------------------------------------------------
 */

#include <stdint-gcc.h>
#include <stdint.h>

#include "../../../inc/mega.h"
#if defined CSMA_MODULE
#if CSMA_MODULE 
/*
  ----------------------------------------------------------------------------------------------------------------------------
  |                                  <timer 2 settings macros>                                                               |
  ----------------------------------------------------------------------------------------------------------------------------
  | < macro TIMER2_MODE2                      : bit 2 in control register to select timer mode (CTC or overflow  or .... )          |
  | < macro TIMER2_MODE1                      : bit 1 in control register to select timer mode (CTC or overflow  or .... )          |                                                 
  | < macro TIMER2_MODE0                      : bit 0 in control register to select timer mode (CTC or overflow  or .... )          |            
  | < macro TIMER2_PRESCALLER2                : bit 2 in control register to select prescaller (2,8,64,256,1024)                    |
  | < macro TIMER2_PRESCALLER1                : bit 1 in control register to select prescaller (2,8,64,256,1024)                    |
  | < macro TIMER2_PRESCALLER0                : bit 0 in control register to select prescaller (2,8,64,256,1024)                    |
  | < macro TIMER2_TIME_VALUE                 : compare vlaue or overflow value in hardware timer 2 register  (0 to 255)            |
  | < macro TIMER2_CLOCK_DIVID                : pre-scaller value   (2,8,64,256,1024)                                               |
  | < MICROSECONDS_PER_TIMER2_OVERFLOW        : number of us per one interrupt                                                      |
  ----------------------------------------------------------------------------------------------------------------------------
 */
#if defined(TCCR2A) && defined(WGM21) 
#define  TIMER2_MODE1    (sbi(TCCR2A, WGM21))
#define  TIMER2_MODE0    (cbi(TCCR2A, WGM20))
#endif

// set timer 2 prescale factor to 8
#if defined(__AVR_ATmega128__) ||  defined(__AVR_ATmega128A__)
// CPU specific: different values for the ATmega128
#define  TIMER2_PRESCALLER2            (cbi(TCCR2, CS22))
#define  TIMER2_PRESCALLER1            (sbi(TCCR2, CS21))
#define  TIMER2_PRESCALLER0            (cbi(TCCR2, CS20))
#define  TIMER2_MODE1                  (sbi(TCCR2, WGM21))
#define  TIMER2_MODE0                  (cbi(TCCR2, WGM20))
#elif defined(TCCR2) && defined(CS21) && defined(CS20)
// this combination is for the standard atmega8 the overflow only
#define  TIMER2_PRESCALLER2            (cbi(TCCR2, CS22))
#define  TIMER2_PRESCALLER1            (sbi(TCCR2, CS21))
#define  TIMER2_PRESCALLER0            (cbi(TCCR2, CS20))
#define  TIMER2_MODE1                  (sbi(TCCR2, WGM21))
#define  TIMER2_MODE0                  (cbi(TCCR2, WGM20))
/*the timer in normal MODE*/
#elif defined(TCCR2B) && defined(CS21) && defined(CS20)
// this combination is for the standard 168/328/1280/2560
#define TIMER2_PRESCALLER2          (cbi(TCCR2B, CS21))
#define TIMER2_PRESCALLER1          (sbi(TCCR2B, CS21))
#define TIMER2_PRESCALLER0          (cbi(TCCR2B, CS20))
#define TIMER2_MODE2                (cbi(TCCR0A, WGM22))
#elif defined(TCCR2A) && defined(CS21) && defined(CS20)
// this combination is for the __AVR_ATmega645__ series
#define  TIMER2_PRESCALLER1         (sbi(TCCR2, CS21))
#define  TIMER2_PRESCALLER0         (sbi(TCCR2, CS20))
#define  TIMER2_MODE1               (sbi(TCCR2A, WGM21));
#define  TIMER2_MODE0               (sbi(TCCR2A, WGM20));
#endif
/*
 * < @macro TIMER2_VALUE   : timer interrupt every bit rate of the Frequcy with Frequncy i/o is 11059200
 *   Buad Rate             : Descrption
     @StandBaudRate_1200   : required timer 16 bit and value is (576)  bit time  (833.33us)    un-supported
     @StandBaudRate_2400   : required timer 16 bit and value is (288)  bit time  (416.60us)    un-supported
     @StandBaudRate_4800   : support  timer 08 bit and value is (144)  bit time  (208.30us)    supported
     @StandBaudRate_9600   : support  timer 08 bit and value is (072)  bit time  (104.16us)    supported
     @StandBaudRate_19200  : support  timer 08 bit and value is (036)  bit time  (052.08us)    supported
     @StandBaudRate_38400  : support  timer 08 bit and value is (018)  bit time  (026.04us)    supported
     @StandBaudRate_57600  : support  timer 08 bit and value is (012)  bit time  (017.36us)    supported
     @StandBaudRate_76800  : support  timer 08 bit and value is (009)  bit time  (013.02us)    supported
     @StandBaudRate_115200 : support  timer 08 bit and value is (006)  bit time  (008.68us)    supported
 */
//#define  TIMER2_VALUE            (((F_CPU) / (8UL * UART0_BUADRATE))-1UL)
#if UART0_BUADRATE == StandBaudRate_9600
#define  TIMER2_VALUE      143
#elif UART0_BUADRATE == StandBaudRate_19200
#define  TIMER2_VALUE      71
#elif UART0_BUADRATE == StandBaudRate_38400
#define  TIMER2_VALUE      35
#elif UART0_BUADRATE == StandBaudRate_57600
#define  TIMER2_VALUE      23
#elif UART0_BUADRATE == StandBaudRate_76800
#define  TIMER2_VALUE      17
#elif UART0_BUADRATE == StandBaudRate_115200
#define  TIMER2_VALUE      11
#endif
/*
 ----------------------------------------------------------------------------------------------------------------
 |                  Timer Worked                                                                                |
 ----------------------------------------------------------------------------------------------------------------
 | <                                                                                                            |
 | 1- sync timer with first bit received by interrupt request the sync by reset value in                        |
 |   timer by 0 and start timer to increment bit rate after byte received (reset timer to zero and set value    |
 |   with frame parsing if any in this case mesurement the frame time and lastbyte receive Time                 |
 |  can mesurement buadrate (wire speed and detect any error between acual buadrate and design buadrate)        |
 |  T required = n  * Timer Time  ==  Frequency of Timer  = n *   Frequency Required                            |
 |  n= Frequency of Timer / Frequency Required                                                                  |      
 |  the parsing frame start after Last byte Received(TP) = xByteTime + y BitTime = (x/ByteRate) + (y/BitRate)   |
 | the bit Rate = nBit * Byte Rate == nBit is number of bit per Byte                                            |
 | TP =(nBit*x/BitRate)+(y/BitRate) = (nBit*x+y) / (BitRate)                                                    |
 | FP = 1/TP = (BitRate/(nBit*x+y)) the any Time Required when x is number of byte and y number of bit          |                                                                     
 | when the nBit Per Byte is 10 Bit and x =1 and  y = 2 BitRate = Baud rate = 19200 bps                         |
 | FP = (19200/(10*1+2)) = 1600bps == TP = 625usec =  xByteTime + y BitTime = 1*520.8+2*52.08=624.96us          |                          
 | @note 1 when any Required Time by Timer 2 from any Channel 0 or 1 can apply this eq n=(nBit*x)+y             |
 | @note 2 baud rate error detect from first start Bit enable to start BitCounte increment every Time2interrupt |
 | Frame n = has 10Byte*10Bit = 100Bit and Timer Frequency is 19200 Hz , nCount = 100 Count or nCount = 50      |
 | Frequency Required  =(BitRate/(nBit*x+y)) when nBit*x+y = number of Bit                                      |
 | Frequency Required  = 192 and nCount is 100 Count                                                            |
 | Frequency of Timer  = n *  192  = 100*192 = 19200 or 50*192 = 9600                                           |
 | when count is 50 the buad rate worked is 9600 and when count is 100 the buadrate is worked is 19200          |
 | main Function to Generate any Time  n =(nBit*x)+y when (nBit*x)+y = number of bits when x is channel number  |
 | nFrameParsingChx =   (10Bit * 1Byte)+0Bit = 10Bit time is 12*52.08us = 520.8us                               |
 | nFrameMasterBus = (10Bit*1Byte)+2Bit = 12Bit time is 12*52.08us = 624.96us                                   |
 | nFrameSlaveBus  = (10Bit*1Byte)+3Bit = 13Bit time is 677.04us when x is channel number                       |                                                                                                                      
 | Back off Time = (CW min/ sqr(Cwmax)) * CW * slot time and  slot time is 4usec,Cw min = 32 , Cw max = 1024    |
 | when CW (Contention Window) based on the number of the frame which is sent successfully                      |                                   |
 | When we have many nodes using the medium, we require small value of Back off therhlod relative to current    |
 | CW size to reduce collisionsand when we have few nodes using the medium, we require high value of backoff    |
 | to current CW size to fast collision resolution                                                              |
 | when Cw = Cw min BackOff Time is 64us and Cw = 128us and Cw = Cw max = 1024 the Bacoff time = 4096us         |                                                         
 | @case 1  the Time is   128us  + 677 us = 15 *52.08=781us                                                     |
 | @case 2  the time is  4096us  +677 us  = 92*52.08 = 4860us                                                   |
 ----------------------------------------------------------------------------------------------------------------
 */

/*
 * < @macro BIT_TIME                        : Bit time 
 */
#define  BIT_TIME                              (1000000UL/UART0_BUADRATE)/*52 us*/
/*
 * < @macro N_BITs  (nBit,x,y)              :  (nBit*x)+y   x = number of byte and y = number of bit , nBit number of bit in byte
 */
#define  N_BITs(nBit,x,y)                     (nBit*x)+y 
/*
 * < @macro  PCC(Ni,Nb,Nc,Ns)              : probability of the collision at transmission Frame 
 */
#define   PCC(Ni,Nb,Nc,Ns)                  (((Nb+Nc+Ns)/(Ni+Nb+Nc+Ns)) * Nc)
/*
 *< @macro       RIFS                       : Redused Inter-Frame Spacing Time 
 */
#define         RIFS                          N_BITs(0,0,2)/*104 us*/
/*
 *< @macro nFrameSlaveBus                    : Distrbuited Inter-Frame Spacing Time
 */
#define         DIFS                         N_BITs(0,0,6)/*312 us*/
/*
 * < @macro     SIFS                         : Shorter Inter-Farme Spacing Time 
 */
#define         SIFS                          N_BITs(0,0,4)/*208 us */
/*
 * < @macro  ACKO                           : Ack time out Received 
 */
#define         ACKO                          N_BITs(10,4,8) /*416 us*/         
/*
 * < @macro     BIFS                        : Block Inter-Frame Space
 */
#define         BIFS                          N_BITs(10,STATION_BLOCK_TIME,0) /*416 us*/
/*
 *< @macro CW_MIN                            : min value of  Contention Window              
 */
#define CW_MIN                               2
/*
 * @macro CW_MAX                             : max value of  Contention Window min 22us and max 1024us
 */
#define CW_MAX                               128 
#ifndef SERIAL_NUMBER_LENGTH
/*
 * <@macro SERIAL_NUMBER_LENGTH              : serial number Buffer Length
 */
#define    SERIAL_NUMBER_LENGTH                  (SERIAL_NUMBER_LENGTH)

#endif
/*
 * <@macro SYSTEM_DATA_RESPONSE              : Call backs run when data is received data request
 */
#define    SYSTEM_DATA_REQUEST                    (4)
/*
 * <@macro SYSTEM_DATA_RESPONSE              : Call backs run when data is received data respone
 */
#define    SYSTEM_DATA_RESPONSE                   (3)
/*
 * <@macro SYSTEM_DLINK_DOWN                 : System Commuincation Down
 */
#define    SYSTEM_DLINK_DOWN                       (2)
/*
 * <@macro SYSTEM_DATA_RESPONSE              : Call backs run when data is received managment respone
 */
#define    SYSTEM_MANAGEMNT                        (1)
/*
 * <@macro   SYSTEM_DATA_IDLE               : No Received any Data and request
 */
#define  SYSTEM_IDLE                               (0)
/*
 * <@macro PHYSICAL_LAYER_BUFFER_SIZE                     : Physical Layer Buffer Size
 */
#define   PHYSICAL_LAYER_BUFFER_SIZE                       COM_PAYLOAD_SIZE + 5
/*
 * <@macro RIFS
 */
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

#ifndef    STATION_BLOCK_TIME 
#define    STATION_BLOCK_TIME                              (50) 
#endif

#ifndef    COM_MAX_RETARY
#define    COM_MAX_RETARY                                  (10)
#endif

#ifndef   COM_PAYLOAD_SIZE                                 
#define   COM_PAYLOAD_SIZE                                 (10)
#endif
#ifndef  STATION_ASSIGN_ADDRESS
#define  STATION_ASSIGN_ADDRESS                            (0)
#endif

/*
 ----------------------------------------------------------------------------------------------------------------
 |                               < Enums >                                                                      |
 ----------------------------------------------------------------------------------------------------------------
 */

/*
 * FrameType          : Three Type Of Frame 
 */
typedef enum {
    MangmentFrame = 2,
    DataFrame = 6,
    ControlFrame = 10
} FrameType;

/*
 * FrameSubType          : Control Frame
 */
typedef enum {
    NackFrame = 1,
    AckFrame = 3,
    BlockFrame = 5,
    FreeFrame = 7
} ControlFrameSubType;

/*
 * FrameSubType          : Data Frame
 */
typedef enum {
    RequestFrame = 3,
    ResponseFrame = 7,
} DataFrameSubType;

/*
 * FrameSubType          : Management  Frame
 */
typedef enum {
    GetAddress = 3,
    AssignAddress = 5,
    RemoveAddress = 7
} ManagementFrameSubType;

/**/
typedef enum {
    DataPhysicalControlFiled = 0,
    DataPhysicalDA = 1,
    DataPhysicalSA = 2,
    DataPhysicalLength = 3,
    DataPhysicalPayload = 4
} enDataPhysical;

typedef enum {
    ControlPhysicalControlFiled = 0,
    ControlPhysicalDA = 1,
    ControlPhysicalSA = 2,
    ControlPhysicalCRC = 3
} enControlPhysical;

typedef enum {
    ManangmentPhysicalControlFiled = 0,
    ManangmentPhysicalDA = 1,
    ManangmentPhysicalSA = 2,
    ManagmnetAssignAddress = 3,
    ManangmentPhysicalSER = 4,
    ManangmentPhysicalCRC = SERIAL_NUMBER_LENGTH + ManangmentPhysicalSER,
} enManagmentPhysical;

/*
 ----------------------------------------------------------------------------------------------------------------
 |                               < Typedef >                                                                     |
 ----------------------------------------------------------------------------------------------------------------
 */
typedef uint8_t(*pFuncReceiveData_t)(uint8_t, volatile uint8_t, volatile uint8_t, volatile uint8_t *);
typedef uint8_t(*pFuncReceiveManagment_t)(uint8_t);

typedef union {
    uint8_t controlFlied;

    struct {
        /*
         *< @Flag  FTYF                 : Frame Type Format
         */
        unsigned FTYF : 4;
        /*
         *< @Flag FSTF                  :Frame SubType Form
         */
        unsigned FSTF : 3;
        /*
         *< @Flag FVTF                   : Frame Version
         */
        unsigned FVTF : 1;
    };
} ucommChannelControlFlied_t;

typedef union {
    uint8_t Flags;

    struct {
        /*
         *< @Flag CCAF                   : Clear Channel Assignemnt 
         */
        volatile unsigned CCAF : 1;
        /*
         *< @Flag ACKWSND                   : ack wait for send
         */
        volatile unsigned ACKWSND : 1;
        /*
         *< @Flag REQF                    : Last Operation has a Request
         */
        volatile unsigned REQF : 1;
        /*
         * <@Flag SERCLIF                : Sever Client Flag
         */
        volatile unsigned SERCLIF : 1;
        /*
         * <@Flag SYSTEM_STATE          : System State is Run
         */
        volatile unsigned SYSTEM_STATE : 3;

    };
} uCommFlags_t;

typedef struct {
    /*
     *<@var gu8Coillison Counter                : number of collission per frame
     */
    volatile uint8_t gu8CoillisonCounter;
    /*
     *@var DA                                   : Destination Address
     */
    volatile uint8_t DA;
    /*
     * <@var AssignAddress                        : Address Assigned  per Request 
     */
    volatile uint8_t AssignAddress;
    /*
     *<@var      gu8StationAddress                : Identifiy station is (primary key )
     */
    volatile uint8_t gu8StationAddress;
    /*
     *<@var       gu8ReceiveCount           : number of byte Received   
     */
    volatile uint8_t gu8ReceiveCount;
    /*
     *<@var         gu8TransmissionCounter    : number Of byte Transmission per    
     */
    volatile uint8_t gu8TransmissionCounter;
    /*
     * < @var         gu8ReceiveBuf               : receive buf to store received data
     */
    volatile uint8_t gu8ReceiveBuf[PHYSICAL_LAYER_BUFFER_SIZE];
    /*
     * < @var         gu8TransmissionBuf               : Tramsimission buf to set into usart
     */
    volatile uint8_t gu8TransmissionACK[ControlPhysicalCRC + 1 ];
    /*
     * < @var         gu8TransmissionBuf               : Tramsimission buf to set into usart
     */
    volatile uint8_t gu8TransmissionManagment[ManangmentPhysicalCRC + 1];
    /*
     * < @var         gu8Transmission               : receive buf to store received data
     */
    volatile uint8_t gu8TransmissionData[PHYSICAL_LAYER_BUFFER_SIZE];
    /*
     * < @var        guPhysicalFlags                    : State of Physical Layer
     */
    volatile uCommFlags_t Flags;
    /*
     * <@var        gu8DataFrameLength                   : number of byte Send by usart
     */
    volatile uint8_t gu8DataFrameLength;
    /*
     * <@var           pFunTime                           : Pointer To Function X
     */
    volatile pFuncParam_t pFunTime;
    /*
     * <@var           pFunTransmit                        : Pointer To sender Data
     */
    volatile pFuncParam_t pFunTransmit;
    /*
     * <@var           pFunStartTransmit                        : Pointer To start sender Data
     */
    volatile pFuncParam_t pFunStartTransmit;
    /*
     * <@var           pFunReceive                        : Pointer To receive Data
     */
    volatile pFuncParam_t pFunReceive;
    /*
     * <@var           pFunManagment                        : Pointer To m Data
     */
    volatile pFuncReceiveManagment_t pFunManagment;
    /*
     * <@var           pFunDataRequest                        : Pointer To Request Data
     */
    volatile pFuncReceiveData_t pFunDataRequest;
    /*
     * <@var           pFunDataResponse                        : Pointer To Response Data
     */
    volatile pFuncReceiveData_t pFunDataResponse;
    /*
     *< @var gu16TimeOut                                 :  Inter Frame Spacing Counter
     */
    volatile uint16_t gu16TimeOut;
    /*
     * < @var         gu8ReceiveBuf               : receive buf to store received data
     */
    volatile uint8_t gu8ReceiveData[COM_PAYLOAD_SIZE];
    /*
 ----------------------------------------------------------------------------------------------------------------
 |                               < Back off Timing Variables >                                                                  |
 ----------------------------------------------------------------------------------------------------------------
     */
    /*
     * <@var gu16BOFT         : back off time of the current Order ith 
     */
    volatile uint8_t gu08BOFT;
    /*
     *< @var gu16CW              :  Contention Window Counter
     */
    volatile uint8_t gu08CW;
    /*
     * <@var gu8NReTryPerFrame   : Number Of Re Try to Transmission Frame
     */
    volatile uint8_t gu8NReTryPerFrame;
} stCommLayer_t;

/*
 *<@var SerialNumberTransmission         : main Serial number
 */
uint8_t volatile gu8SerialNumberTransmission[SERIAL_NUMBER_LENGTH];
/*
 *<@var gu8SerialNumberReceived         : Received Serial number
 */
static volatile uint8_t gu8SerialNumberReceived[SERIAL_NUMBER_LENGTH];
/*
 ----------------------------------------------------------------------------------------------------------------
 |                               < Variables >                                                                  |
 ----------------------------------------------------------------------------------------------------------------
 */

#if defined USART1_ENABLED
/*
 <@var  gstCh1Timing            : Timing System Control  by channel 0
 */
static volatile stCommLayer_t gstCh1Layer;
#endif
/*
 <@var  gstCh0Layer            : Timing System Control  by channel 0
 */
static volatile stCommLayer_t gstCh0Layer;

/*
 ----------------------------------------------------------------------------------------------------------------
 |                               < Basic Function Defintion >                                                    |
 ----------------------------------------------------------------------------------------------------------------
 */
/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < commBackOffTime >                                                                      |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint16_t  commBackOffTime                                                                         |                 
 | < @Description       : calucation backoff time depent channel collision-based window-scaled backoff (CWSB)               |  
 | < @Param Type        : 0 the backoff time by collision state , 1 the back of time by successfully Transmission           |                                                                              
 | < @Param ID          : Channel ID                                                                                  |
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void commBackOffTime(uint8_t Type, uint8_t ID);

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
 |                                 < funRIFS >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void  funRIFS                                                                  |                                          
 | < @Description       : Run Timing Reduced Inter Frame Spacing                                         |   
 | < @Param ID          : Channel                                                        |                                                                                                                                                                                |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funRIFS(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funSIFS >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSIFS                                                                   |                                          
 | < @Description       : Run Timing Short InterFrame Spacing                                            |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                                |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funSIFS(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funDIFS >                                                          |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funDIFS                                                                   |                                          
 | < @Description       : Run Timing  Distribuited InterFrame Spacing                                    |   
 | < @Param ID          : Channel ID                                                         |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funDIFS(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funBIFS >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funBIFS                                                                   |                                          
 | < @Description       : Run Timing  Blocking Inter Frame Spacing                                       |   
 | < @Param ID          : Channel ID                                                          |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funBIFS(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funBOFT >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funBOFT                                                                   |                                          
 | < @Description       : Run Timing  Back off Time                                                      |   
 | < @Param ID          : Channel ID                                                           |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funBOFT(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funACKO >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funACKO                                                                   |                                          
 | < @Description       : Run Timing  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                           |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funACKO(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funSenderData >                                                     |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSenderData                                                             |                                          
 | < @Description       : Run Send Data                                                                  |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmitData(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funSenderManagement >                                               |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSenderManagement                                                       |                                          
 | < @Description       :Run Managment Send Data                                                         |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmitManagement(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funACKO >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSenderACK                                                              |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                             |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmitACK(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funTransmit >                                                       |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funTransmit                                                               |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |  
 | < @Param buf         : Pointer to data Transmit                                                       |
 | < @Param len         : Data Length To be send                                                         | 
 | < @Param  type       : Ack or Data                                                                    |                                                                                                                                                         |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmit(uint8_t ID, volatile uint8_t *buf, volatile uint8_t len, uint8_t type);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funStartTransmitData >                                              |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funTransmit                                                               |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |                                                                    |                                                                                                                                                         |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funStartTransmitData(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funStartTransmitManagment >                                         |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funStartTransmitManagment                                                  |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |                                                                   |                                                                                                                                                         |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funStartTransmitManagment(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < TimingHandling >                                                    |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void TimingHandling                                                            |                                          
 | < @Description       : Run Timing  by Enable Flags                                                    |                                                |                                                                                          
 | < @Param ID          : Channel ID                                                                     |                                                          |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void ResetAllTimingHandling(uint8_t ID);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < TimeCallBackRegister >                                             |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void TimeCallBackRegister                                                      |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @Param Time        : Time Out Run                                                                   |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void TimeCallBackRegister(volatile pFuncParam_t callback, uint8_t ID, volatile uint16_t Time);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < SenderCallBackRegister >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void SenderCallBackRegister                                                    |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void TransmitCallBackRegister(volatile pFuncParam_t callback, uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReTransmitCallBackRegister >                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReTransmitCallBackRegister                                                |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void StartTransmitCallBackRegister(volatile pFuncParam_t callback, uint8_t ID);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReceiveCallBackRegister >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReceiveCallBackRegister                                                   |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void ReceiveCallBackRegister(volatile pFuncParam_t callback, uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReceiveCallBackRegister >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ManagmentCallBackRegister                                                 |                                          
 | < @Description       : Ex-ecuation Managment Frame                                                    |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void ManagmentCallBackRegister(volatile pFuncReceiveManagment_t callback, uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putAck >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void putAck                                                   |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void putAck(uint8_t ID, uint8_t type);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |
 | < @Param address     : station assignment address                                                     |
 | < @Param Type        : Frame Type managment                                                           |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                           |                 
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t putManagment(uint8_t ID, volatile uint8_t *serial, volatile uint8_t address, uint8_t Type);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithNOAction >                                                |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithNOAction                                                        |                                          
 | < @Description       : Parse Frame and No Action Data                                                 |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNOAction(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithBlockingData >                                            |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithBlockingData                                                    |                                          
 | < @Description       : Parse Frame and System Active Into Blocking                                    |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithBlockingData(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithBlockingManagment >                                       |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithBlockingManagment                                               |                                          
 | < @Description       : Parse Frame and System Active Into Blocking                                    |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithBlockingManagment(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithBlocking >                                                |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithBlockingControl                                                 |                                          
 | < @Description       : Parse Frame and System Active Into Blocking                                    |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithBlockingControl(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithACKData >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithACKData                                                         |                                          
 | < @Description       : Parse Frame send ACK OR NOT ACK                                                |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNACKData(uint8_t ID);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithNACKControl >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithNACKControl                                                         |                                          
 | < @Description       : Parse Frame  ACK OR NOT ACK received or free or Bloking                        |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNACKControl(uint8_t ID);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithACKManagment >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithACKManagment                                                         |                                          
 | < @Description       : Parse Frame  and send ack by managment frames                                  |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNACKManagment(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < checkRequest >                                                      |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void checkRequest                                                              |                                          
 | < @Description       : check wait ack or not when Received error data                                 |                                                                                                            |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void checkRequest(uint8_t ID, pFuncParam_t callback, uint16_t Time);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < BusyFun >                                                          |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void BusyFun                                                                   |                                          
 | < @Description       : check comm is ready or not                                                     |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     | 
 | < @return            : 1 comm is busy                                                                 |
 |                      : 0 comm is ready                                                                |                 
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t BusyFun(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReTransmitFrame >                                                   |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReTransmitFrame                                                           |                                          
 | < @Description       : Re-assignment Frame After Nack or Ack Time Out or free                         |                                                     |  
 | < @Param Id          : Channle ID                                                                     |                                                                                                                       |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void ReTransmitFrame(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReTransmitFrameAfterBlocking >                                      |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReTransmitFrame                                                           |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param Id          : Channle ID                                                                     |                                                                                                                        |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void ReTransmitFrameAfterBlocking(uint8_t ID);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FunGetAddress >                                                     |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t FunGetAddress                                                          |                                          
 | < @Description       : Actionwith Received Command Get Address                                        |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t FunGetAddress(uint8_t ID);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FunAssignAddress >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t FunAssignAddress                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t FunAssignAddress(uint8_t ID);
/*
 ----------------------------------------------------------------------------------------------------------------
 |                               <  Interrupt Handling >                                                                  |
 ----------------------------------------------------------------------------------------------------------------
 */
#if defined PCIE2 

ISR(PCINT2_vect) {
#elif (defined (EICRA)) && (defined (EICRB))

ISR(INT4_vect) {
#else

ISR(INT0_vect) {
#endif
#if defined (USART0_ENABLED)
    ResetAllTimingHandling(0);
#endif
}
#if (defined (EICRA)) && (defined (EICRB)) && defined USART1_ENABLED

ISR(INT5_vect) {
    /* Reset All Timing and Channel 1 In  and active Busy State */
    ResetAllTimingHandling(1);
}
#endif
/*
 ----------------------------------------------------------------------------------------------------------------
 |                               < Timer Interrupt >                                                                  |
 ----------------------------------------------------------------------------------------------------------------
 */
#if defined(OCR2)

ISR(TIMER2_COMP_vect) {
#elif defined (OCR2A)

ISR(TIMER2_COMPA_vect) {
#endif
    ATOMIC_BEGIN
    if (gstCh0Layer.gu16TimeOut-- == 0) {
        if (gstCh0Layer.pFunTime != NULL) {
            gstCh0Layer.pFunTime(0);
        }
    }

    ATOMIC_END
#if defined  USART1_ENABLED

#endif
}
#if defined (USART0_ENABLED)

ISR(UART0_RECEIVE_INTERRUPT) {
    uint8_t byte;
    byte = usart0GetByte();
    if (gstCh0Layer.gu8ReceiveCount < PHYSICAL_LAYER_BUFFER_SIZE) {

        gstCh0Layer.gu8ReceiveBuf[gstCh0Layer.gu8ReceiveCount] = byte;
    }
    if (gstCh0Layer.pFunTransmit != NULL) {
        gstCh0Layer.pFunTransmit(0);
    } else {
        /*Run RIFS*/
        digitalPinWrite(GPIO_B0, GPIO_TGL);
        gstCh0Layer.gu8ReceiveCount++;
        TimeCallBackRegister(funRIFS, 0, RIFS);

    }

}
#endif
#if defined USART1_ENABLED

ISR(UART1_RECEIVE_INTERRUPT) {
    if (gstCh1Layer.gu8ReceiveCount < PHYSICAL_LAYER_BUFFER_SIZE) {
        gstCh1Layer.gu8ReceiveBuf[gstCh0Layer.gu8ReceiveCount];
    }
    if (gstCh0Layer.pFunTransmit != NULL) {
        gstCh0Layer.pFunTransmit(1);
    } else {
        /*Run RIFS*/
        TimeCallBackRegister(funRIFS, 1, RIFS);
    }
    gstCh1Layer.gu8ReceiveCount++;
}
#endif



/*
 ----------------------------------------------------------------------------------------------------------------
 |                               < External Function Implementions >                                            |
 ----------------------------------------------------------------------------------------------------------------
 */

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < commBackOffTime >                                                                      |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : uint16_t  commBackOffTime                                                                         |                 
 | < @Description       : calucation backoff time depent channel collision-based window-scaled backoff (CWSB)               |  
 | < @Param Type        : 0 the backoff time by collision state , 1 the back of time by successfully Transmission           |                                                                              
 | < @Param ID          : ChannelID                                                                                         |
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
static void commBackOffTime(uint8_t Type, uint8_t ID) {
    uint8_t cw;
    uint8_t newCw;
    uint8_t ReTry;
#if USART1_ENABLED
    if (ID) {

    } else {
#endif
        cw = gstCh0Layer.gu08CW;
        ReTry = gstCh0Layer.gu8NReTryPerFrame;

        if (Type) {
            newCw = max((((cw + 1) / 2) - 1), CW_MIN);
        } else {
            newCw = min((power2(ReTry) * (cw + 1)) - 1, CW_MAX);
        }
        // channelTime->gu08BOFT = rand() % newCw;
        gstCh0Layer.gu08CW = newCw;
        gstCh0Layer.gu08BOFT = map(random(), 0, RANDOM_MAX, 0, newCw) + gstCh0Layer.gu8CoillisonCounter;
#if USART1_ENABLED
    }
#endif
}


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
static uint8_t csmaCRCCheck(volatile uint8_t *data, volatile uint8_t len) __attribute((unused));

static uint8_t csmaCRCCheck(volatile uint8_t *data, volatile uint8_t len) {
    /*8 bit crc */
    uint8_t crc, j, i, nbyte;
    crc = 0;
    i = 0;
    j = 0;

    for (i = 0; i < len; i++) {
        nbyte = data [i];
        crc ^= nbyte;
        for (j = 0; j < 0x08; j++) {
            if (crc & 0x01)
                crc ^= 0x91;
            crc >>= 1;

        }
    }
    return crc;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ResetAllTimingHandling >                                            |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void TimingHandling                                                            |                                          
 | < @Description       : Run Timing  by Enable Flags                                                    |                                                |                                                                                          
 | < @Param  ID         : Channel ID                                                                     |                                                          |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void ResetAllTimingHandling(uint8_t ID) {
    ATOMIC_BEGIN
#if defined USART1_ENABLED
            if (ID) {
        TimeCallBackRegister(NULL, 1, 0);
        gstCh0Layer.Flags.CCAF = 0;
    } else {
#endif
        TimeCallBackRegister(NULL, 0, 0);
        ReceiveCallBackRegister(NULL, 0);
        gstCh0Layer.Flags.CCAF = 0;
        /*Reset Counter Of Timer To Zero to Restart the new Bit Period */

        /*Reset All Timing*/
#if defined USART1_ENABLED
    }
#endif
    ATOMIC_END


}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funRIFS >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void  funRIFS                                                                  |                                          
 | < @Description       : Run Timing Reduced Inter Frame Spacing                                         |   
 | < @Param ID          : Channel   ID                                                                   |                                                                                                                                                                                |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funRIFS(uint8_t ID) {

#if defined USART1_ENABLED
    if (ID) {
        ReceiveCallBackRegister(parserWithNOAction, 0);
        while (gstCh1Layer.pFunReceive != NULL) {
            gstCh1Layer.pFunReceive(0);
        }
        gstCh1Layer.gu8ReceiveCount = 0x00; /*Reset Data Into Physical Layer*/
    } else {
#endif
        ReceiveCallBackRegister(parserWithNOAction, 0);

        while (gstCh0Layer.pFunReceive != NULL) {
            gstCh0Layer.pFunReceive(0);
        }
        gstCh0Layer.gu8ReceiveCount = 0x00; /*Reset Data Into Physical Layer*/
        gstCh0Layer.Flags.CCAF = 1; /*Channel is Idle*/
        return;
#if defined  USART1_ENABLED     
    }
#endif

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funSIFS >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSIFS                                                                   |                                          
 | < @Description       : Run Timing Short InterFrame Spacing                                            |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                                |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funSIFS(uint8_t ID) {
    /*send Control Frame */
#if defined USART1_ENABLED
    if (ID) {
        while (!Empty_BUFFER1());
        usart1PutByte(gstCh1Layer.gu8TransmissionACK[0]);
        /*run start Sender Call backs*/
        TransmitCallBackRegister(funTransmitACK, 1);
        TimeCallBackRegister(NULL, 1, 0);
    } else {
#endif

        while (!Empty_BUFFER0());
        usart0PutByte(gstCh0Layer.gu8TransmissionACK[0]);
        /*run start Sender Call backs */
        TransmitCallBackRegister(funTransmitACK, 0);
        TimeCallBackRegister(NULL, 0, 0);

#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funDIFS >                                                          |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funDIFS                                                                   |                                          
 | < @Description       : Run Timing  Distribuited InterFrame Spacing                                    |   
 | < @Param ID          : Channel ID                                                         |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funDIFS(uint8_t ID) {
#if defined USART1_ENABLED  
    if (ID) {
        TimeCallBackRegister(funBOFT, 1, gstCh01Timing.gu08BOFT);
    } else {
#endif
        TimeCallBackRegister(funBOFT, 0, gstCh0Layer.gu08BOFT);
#if defined USART1_ENABLED  
    }
#endif

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funBIFS >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funBIFS                                                                   |                                          
 | < @Description       : Run Timing  Blocking Inter Frame Spacing                                       |   
 | < @Param ID          : Channel ID                                                          |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funBIFS(uint8_t ID) {
    /*Re-transmission*/
    ReTransmitFrameAfterBlocking(ID);
    return;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funBOFT >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funBOFT                                                                   |                                          
 | < @Description       : Run Timing  Back off Time                                                      |   
 | < @Param ID          : Channel ID                                                           |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funBOFT(uint8_t ID) {
    /*Active Start Transmission Buffer by UART*/
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh1Layer.pFunStartTransmit != NULL) {
            /*active DIFS Time*/
            gstCh1Layer.pFunStartTransmit(1);
        }
        TimeCallBackRegister(NULL, 1, 0);
    } else {

#endif
        if (gstCh0Layer.pFunStartTransmit != NULL) {
            /*active DIFS Time*/
            gstCh0Layer.pFunStartTransmit(0);
        }
        TimeCallBackRegister(NULL, 0, 0);
#if defined USART1_ENABLED  
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funACKO >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funACKO                                                                   |                                          
 | < @Description       : Run Timing  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                           |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funACKO(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        ReTransmitFrame(1);
    } else {
#endif
        /*active system is NOT_ACK*/
        /*Re-Transmission */
        ReTransmitFrame(0);

#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funSenderData >                                                     |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSenderData                                                             |                                          
 | < @Description       : Run Send Data                                                                  |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmitData(uint8_t ID) {
    funTransmit(ID, gstCh0Layer.gu8TransmissionManagment, gstCh0Layer.gu8DataFrameLength, 1);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funSenderManagement >                                               |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSenderManagement                                                       |                                          
 | < @Description       :Run Managment Send Data                                                         |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                                 |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmitManagement(uint8_t ID) {
    funTransmit(ID, gstCh0Layer.gu8TransmissionManagment, ManangmentPhysicalCRC + 1, 1);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funACKO >                                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funSenderACK                                                              |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |                                                                                                                                                                             |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmitACK(uint8_t ID) {
    funTransmit(ID, gstCh0Layer.gu8TransmissionACK, ControlPhysicalCRC + 1, 0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funTransmit >                                                       |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funTransmit                                                               |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |  
 | < @Param buf         : Pointer to data Transmit                                                       |
 | < @Param len         : Data Length To be send                                                         | 
 | < @Param  type       : Ack or Data                                                                    |                                                                                                                                                         |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funTransmit(uint8_t ID, volatile uint8_t *buf, volatile uint8_t len, uint8_t type) {
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh1Layer.gu8TransmissionCounter != gstCh1Layer.gu8ReceiveCount) {
            gstCh1Layer.gu8TransmissionCounter = 0;
            /*Re-transmit Active*/
            TransmitCallBackRegister(NULL, 1);
            return;
        }
        gstCh1Layer.gu8TransmissionCounter++;
        if (gstCh1Layer.gu8TransmissionCounter < len) {
            usart0PutByte(buf[gstCh1Layer.gu8TransmissionCounter]);
            return;
        }
        TransmitCallBackRegister(NULL, 1);
        gstCh1Layer.gu8TransmissionCounter = 0;
    } else {
#endif
        if (buf[gstCh0Layer.gu8TransmissionCounter] != gstCh0Layer.gu8ReceiveBuf[gstCh0Layer.gu8ReceiveCount]) {
            gstCh0Layer.gu8TransmissionCounter = 0;
            /*Re-transmit Active*/
            gstCh0Layer.gu8CoillisonCounter++;
            ReTransmitFrameAfterBlocking(0);
            TransmitCallBackRegister(NULL, 0);
            return;
        }
        gstCh0Layer.gu8TransmissionCounter++;
        gstCh0Layer.gu8ReceiveCount++;
        if (gstCh0Layer.gu8TransmissionCounter < len) {
            while (!Empty_BUFFER0());
            usart0PutByte(buf[gstCh0Layer.gu8TransmissionCounter]);
            return;
        }
        /*active ack*/
        if (type) {
            /*active wait Ack */
            TimeCallBackRegister(funACKO, 0, ACKO);
            gstCh0Layer.Flags.REQF = 1; /*active wait for Ack*/
        } else {
            gstCh0Layer.Flags.ACKWSND = 0;
        }
        gstCh0Layer.Flags.CCAF = 1;
        TransmitCallBackRegister(NULL, 0);
        gstCh0Layer.gu8TransmissionCounter = 0;
        gstCh0Layer.gu8ReceiveCount = 0;
        gstCh0Layer.gu8CoillisonCounter = 0;
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funStartTransmitData >                                              |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funTransmit                                                               |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |                                                                    |                                                                                                                                                         |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funStartTransmitData(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        while (!Empty_BUFFER1);
        usart1PutByte(gstCh1Layer.gu8Transmission[0]);
        TransmitCallBackRegister(funTransmitData, 1);
    } else {
#endif
        while (!Empty_BUFFER0());
        usart0PutByte(gstCh0Layer.gu8TransmissionData[0]);
        gstCh0Layer.gu8ReceiveCount = 0;
        gstCh0Layer.gu8TransmissionCounter = 0;
        TransmitCallBackRegister(funTransmitData, 0);
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < funStartTransmitManagment >                                         |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void funStartTransmitManagment                                                  |                                          
 | < @Description       : Run Sender  Ack Time Out                                                       |   
 | < @Param ID          : Channel ID                                                                     |                                                                   |                                                                                                                                                         |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void funStartTransmitManagment(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        while (!Empty_BUFFER1);
        usart1PutByte(gstCh1Layer.gu8TransmissionManagment[0]);
        TransmitCallBackRegister(funTransmitManagement, 1);
    } else {
#endif
        while (!Empty_BUFFER0());

        usart0PutByte(gstCh0Layer.gu8TransmissionManagment[0]);
        gstCh0Layer.gu8ReceiveCount = 0;
        gstCh0Layer.gu8TransmissionCounter = 0;

        TransmitCallBackRegister(funTransmitManagement, 0);
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < TimeCallBackRegister >                                              |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void TimeCallBackRegister                                                      |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        | 
 | < @Param ID          : channel ID                                                                     |                                                             
 | < Param Time         : Time Value To be Set                                                           |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void TimeCallBackRegister(volatile pFuncParam_t callback, uint8_t ID, volatile uint16_t Time) {
#if defined USART1_ENABLED
    if (ID) {
        gstCh1Timing.gu16TimeOut = Time;
        gstCh1Timing.pFunTime = callback;
    } else {
#endif
        gstCh0Layer.gu16TimeOut = Time;
        gstCh0Layer.pFunTime = callback;
#if defined USART1_ENABLED
    }
#endif   

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < SenderCallBackRegister >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void SenderCallBackRegister                                                    |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void TransmitCallBackRegister(volatile pFuncParam_t callback, uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        gstCh1Layer.pFunTransmit = callback;
    } else {
#endif
        gstCh0Layer.pFunTransmit = callback;
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReTransmitCallBackRegister >                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReTransmitCallBackRegister                                                |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void StartTransmitCallBackRegister(volatile pFuncParam_t callback, uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        gstCh1Layer.pFunStartTransmit = callback;
    } else {
#endif
        gstCh0Layer.pFunStartTransmit = callback;
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReceiveCallBackRegister >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReceiveCallBackRegister                                                   |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void ReceiveCallBackRegister(volatile pFuncParam_t callback, uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        gstCh1Layer.pFunReceive = callback;
    } else {
#endif
        gstCh0Layer.pFunReceive = callback;
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReceiveCallBackRegister >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ManagmentCallBackRegister                                                 |                                          
 | < @Description       : Ex-ecuation Managment Frame                                                    |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static inline void ManagmentCallBackRegister(volatile pFuncReceiveManagment_t callback, uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        gstCh1Layer.pFunManagment = callback;
    } else {
#endif
        gstCh0Layer.pFunManagment = callback;
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < checkRequest >                                                      |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void checkRequest                                                              |                                          
 | < @Description       : check wait ack or not when Received error data                                 |                                                                                                            |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void checkRequest(uint8_t ID, volatile pFuncParam_t callback, volatile uint16_t Time) {
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh1Layer.Flags.REQF) {
            TimeCallBackRegister(funACKO, 1, ACKO);
        } else {
            TimeCallBackRegister(NULL, 1, 0);
        }
    } else {
#endif
        if (gstCh0Layer.Flags.REQF) {
            TimeCallBackRegister(funACKO, 0, ACKO);
        } else {
            TimeCallBackRegister(callback, 0, Time);
        }
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithNOAction >                                                |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithNOAction                                                        |                                          
 | < @Description       : Parse Frame and No Action Data                                                 |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNOAction(uint8_t ID) {
    volatile uint8_t Byte;
    volatile uint8_t CRC;
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh1Layer.gu8ReceiveCount <= ControlPhysicalCRC) {
            ReceiveCallBackRegister(NULL, 1);
            return;
        }
        ControlFiled.controlFlied = gstCh1Layer.gu8ReceiveBuf[0];

        if (ControlFiled.FTYF == ControlFrame) {
            ReceiveCallBackRegister(parserWithBlockingControl, 1);
            return;
        }

        if (ControlFiled.FTYF == DataFrame) {
            ReceiveCallBackRegister(parserWithBlockingData, 1);
            return;
        }

        if (ControlFiled.FTYF == MangmentFrame) {
            ReceiveCallBackRegister(parserWithBlockingManagment, 1);
            return;
        }

        ReceiveCallBackRegister(NULL, 1);
        TimeCallBackRegister(NULL, 1, 0);
    } else {
#endif


        if (gstCh0Layer.gu8ReceiveCount <= ControlPhysicalCRC) {
            ReceiveCallBackRegister(NULL, 0);
            ReTransmitFrameAfterBlocking(0);
            return;
        }

        CRC = csmaCRCCheck(gstCh0Layer.gu8ReceiveBuf, gstCh0Layer.gu8ReceiveCount - 1);
        if (CRC != gstCh0Layer.gu8ReceiveBuf[ gstCh0Layer.gu8ReceiveCount - 1]) {
            ReceiveCallBackRegister(NULL, 0);
            ReTransmitFrameAfterBlocking(0);
            return;
        }
        Byte = gstCh0Layer.gu8ReceiveBuf[0] & 0x0F;

        if ((Byte) == ControlFrame) {
            ReceiveCallBackRegister(parserWithBlockingControl, 0);
            return;
        }

        if ((Byte) == DataFrame) {
            ReceiveCallBackRegister(parserWithBlockingData, 0);
            return;
        }

        if ((Byte) == MangmentFrame) {
            ReceiveCallBackRegister(parserWithBlockingManagment, 0);
            return;
        }

        ReceiveCallBackRegister(NULL, 0);
        ReTransmitFrameAfterBlocking(0);
#if defined USART1_ENABLED
    }
#endif

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithBlockingData >                                            |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithBlockingData                                                    |                                          
 | < @Description       : Parse Frame and System Active Into Blocking                                    |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithBlockingData(uint8_t ID) {
    uint8_t DA;
#if defined USART1_ENABLED
    if (ID) {
        DA = gstCh1Layer.gu8ReceiveBuf[1];
        if (DA == 0xFF) {
            ReceiveCallBackRegister(parserWithNACKData, 1);
            return;
        }

        if (DA == gstCh1Layer.gu8StationAddress) {
            ReceiveCallBackRegister(parserWithNACKData, 1);
            return;
        }
        TimeCallBackRegister(funBIFS, 1, BIFS); /*active Blocking Time*/
        ReceiveCallBackRegister(NULL, 1);
    } else {
#endif
        DA = gstCh0Layer.gu8ReceiveBuf[1];

        if (DA == 0xFF) {
            ReceiveCallBackRegister(parserWithNACKData, 0);
            return;
        }

        if (DA == gstCh0Layer.gu8StationAddress) {
            ReceiveCallBackRegister(parserWithNACKData, 0);
            return;
        }
        TimeCallBackRegister(funBIFS, 0, BIFS); /*active Blocking Time*/
        ReceiveCallBackRegister(NULL, 0);
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithBlockingManagment >                                       |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithBlockingManagment                                               |                                          
 | < @Description       : Parse Frame and System Active Into Blocking                                    |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithBlockingManagment(uint8_t ID) {
    uint8_t DA;
#if defined USART1_ENABLED
    if (ID) {
        ControlFiled.controlFlied = gstCh1Layer.gu8ReceiveBuf[0];
        DA = gstCh1Layer.gu8ReceiveBuf[1]; /*DA*/
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            serial[i] = gstCh1Layer.gu8ReceiveBuf[i + ManangmentPhysicalSER];
        }
        if (DA == 0xFF) {
            ReceiveCallBackRegister(parserWithNACKManagment, 0);
            return;
        }

        if (DA == gstCh1Layer.gu8StationAddress) {/*Match serial*/
            if (Match_2BUF(serial, gu8SerialNumberTransmission, SERIAL_NUMBER_LENGTH)) {
                ReceiveCallBackRegister(parserWithNACKManagment, 1);
            }
        }


        TimeCallBackRegister(funBIFS, 1, BIFS); /*active Blocking Time*/
        ReceiveCallBackRegister(NULL, 1);
    } else {
#endif
        DA = gstCh0Layer.gu8ReceiveBuf[1]; /*DA*/
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            gu8SerialNumberReceived[i] = gstCh0Layer.gu8ReceiveBuf[i + ManangmentPhysicalSER];
        }
        if (DA == 0xFF) {
            ReceiveCallBackRegister(parserWithNACKManagment, 0);
            return;
        }


        if (gstCh0Layer.Flags.SERCLIF) {
            ReceiveCallBackRegister(parserWithNACKManagment, 0);
            return;
        }

        if (Match_2BUF(gu8SerialNumberReceived, gu8SerialNumberTransmission, SERIAL_NUMBER_LENGTH)) {
            ReceiveCallBackRegister(parserWithNACKManagment, 0);
            return;

        }


        TimeCallBackRegister(funBIFS, 0, BIFS); /*active Blocking Time*/
        ReceiveCallBackRegister(NULL, 0);
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithBlocking >                                                |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithBlockingControl                                                 |                                          
 | < @Description       : Parse Frame and System Active Into Blocking                                    |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithBlockingControl(uint8_t ID) {
    ucommChannelControlFlied_t ControlFiled;
    uint8_t DA;
#if defined USART1_ENABLED
    if (ID) {
        ControlFiled.controlFlied = gstCh1Layer.gu8ReceiveBuf[0];
        DA = gstCh1Layer.gu8ReceiveBuf[0];
        if ((gstCh1Layer.gu8StationAddress == DA) || (DA == 0xFF)) {
            /*Active Blocking System */
            if ((ControlFiled.FSTF == AckFrame) || (ControlFiled.FSTF == NackFrame)) {
                if (!gstCh1Layer.Flags.REQF) {
                    TimeCallBackRegister(funBIFS, 1, BIFS); /*active Blocking Time*/
                    ReceiveCallBackRegister(NULL, 1);
                    return;
                }
            }
            ReceiveCallBackRegister(parserWithNACKControl, 1);
            return;
        }
        TimeCallBackRegister(funBIFS, 1, BIFS); /*active Blocking Time*/
        ReceiveCallBackRegister(NULL, 1);
    } else {
#endif
        ControlFiled.controlFlied = gstCh0Layer.gu8ReceiveBuf[0];
        DA = gstCh0Layer.gu8ReceiveBuf[1];
        if ((gstCh0Layer.gu8StationAddress == DA) || (DA == 0xFF)) {
            /*Active Blocking System */
            if ((ControlFiled.FSTF == AckFrame) || (ControlFiled.FSTF == NackFrame)) {
                if (!gstCh0Layer.Flags.REQF) {
                    TimeCallBackRegister(funBIFS, 0, BIFS); /*active Blocking Time*/
                    ReceiveCallBackRegister(NULL, 0);
                    return;
                }
            }

            ReceiveCallBackRegister(parserWithNACKControl, 0);
            return;
        }
        TimeCallBackRegister(funBIFS, 0, BIFS); /*active Blocking Time*/
        ReceiveCallBackRegister(NULL, 0);
#if defined USART1_ENABLED
    }
#endif 
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < CopyData >                                                          |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void CopyData                                                                  |                                          
 | < @Description       : Copy Data from Receiver buf To Data Received Buf                               |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |  
 | < @return            : void                                                                       |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void CopyData(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        putAck(1, AckFrame);
        /*copy data*/
        gstCh1Layer.DA = gstCh1Layer.gu8ReceiveBuf[DataPhysicalDA];
        gstCh1Layer.gu8DataFrameLength = gstCh1Layer.gu8ReceiveBuf[DataPhysicalLength];
        for (uint8_t i = 0; i < gstCh0Layer.gu8DataFrameLength; i++) {
            gstCh0Layer.gu8ReceiveData[i] = gstCh0Layer.gu8ReceiveBuf[DataPhysicalPayload + i];
        }
    }
} else {
#endif
    putAck(0, AckFrame);
    /*copy data*/
    gstCh0Layer.DA = gstCh0Layer.gu8ReceiveBuf[DataPhysicalDA];
    gstCh0Layer.gu8DataFrameLength = gstCh0Layer.gu8ReceiveBuf[DataPhysicalLength];
    for (uint8_t i = 0; i < gstCh0Layer.gu8DataFrameLength; i++) {
        gstCh0Layer.gu8ReceiveData[i] = gstCh0Layer.gu8ReceiveBuf[DataPhysicalPayload + i];
    }
}
#if defined USART1_ENABLED
}
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithACKData >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithACKData                                                         |                                          
 | < @Description       : Parse Frame send ACK OR NOT ACK                                                |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |                                                                         |                 
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNACKData(uint8_t ID) {
    uint8_t Length;
    ucommChannelControlFlied_t ControlFiled;

#if defined USART1_ENABLED
    if (ID) {
        Length = gstCh1Layer.gu8ReceiveBuf[DataPhysicalLength] + DataPhysicalPayload;
        ControlFiled.controlFlied = gstCh1Layer.gu8ReceiveBuf[0];

        if ((Length) != gstCh1Layer.gu8ReceiveCount) {
            putAck(1, NackFrame);
        } else if (gstCh1Layer.gu8ReceiveBuf[Length] != csmaCRCCheck(gstCh1Layer.gu8ReceiveBuf, Length)) {
            putAck(1, NackFrame);
        } else if (ControlFiled.FSTF == RequestFrame) {
            CopyData(1);
            gstCh1Layer.Flags.SYSTEM_STATE = SYSTEM_DATA_REQUEST;
            /*copy receive Frame In*/

        } else if (ControlFiled.FSTF == ResponseFrame) {
            CopyData(1);
            gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_DATA_RESPONSE;
        } else {
            putAck(1, NackFrame);
        }
        checkRequest(1, NULL, 0);
        ReceiveCallBackRegister(NULL, 1);
    } else {
#endif
        Length = gstCh0Layer.gu8ReceiveBuf[DataPhysicalLength] + DataPhysicalPayload;
        ControlFiled.controlFlied = gstCh0Layer.gu8ReceiveBuf[0];

        if ((Length) != gstCh0Layer.gu8ReceiveCount) {
            putAck(0, NackFrame);
        } else if (ControlFiled.FSTF == RequestFrame) {
            CopyData(0);
            gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_DATA_REQUEST;
        } else if (ControlFiled.FSTF == ResponseFrame) {
            CopyData(0);
            gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_DATA_RESPONSE;
        } else {
            putAck(0, NackFrame);

        }

        ReceiveCallBackRegister(NULL, 0);
        gstCh0Layer.Flags.ACKWSND = 1;
        return;
        /*send NACK*/
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReTransmitFrame >                                                   |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReTransmitFrame                                                           |                                          
 | < @Description       : Re-assignment Frame After Nack or Ack Time Out or free                         |                                                     |  
 | < @Param Id          : Channle ID                                                                     |                                                                                                                       |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void ReTransmitFrame(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        gstCh1Layer.Flags.REQF = 0;
        if (gstCh1Layer.gu8NReTryPerFrame < COM_MAX_RETARY) {
            gstCh1Layer.gu8NReTryPerFrame++;
            commBackOffTime(0, 1);
            if (gstCh1Layer.pFunStartTransmit != NULL) {
                TimeCallBackRegister(funDIFS, 1, DIFS); /*re-transmission Frame*/
                return;
            }
            TimeCallBackRegister(NULL, 1, 0); /*re-transmission Frame*/
            return;
        }

        gstCh1Layer.gu8NReTryPerFrame = 0;
        gstCh1Layer.pFunStartTransmit = NULL; /*frame error*/
        TimeCallBackRegister(NULL, 1, 0);
        return;
    } else {
#endif
        gstCh0Layer.Flags.REQF = 0;
        if (gstCh0Layer.gu8NReTryPerFrame < COM_MAX_RETARY) {
            gstCh0Layer.gu8NReTryPerFrame++;
            commBackOffTime(0, 0);
            if (gstCh0Layer.pFunStartTransmit != NULL) {
                TimeCallBackRegister(funDIFS, 0, DIFS); /*re-transmission Frame*/
                return;
            }
            TimeCallBackRegister(NULL, 0, 0); /*re-transmission Frame*/
            return;
        }
        gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_DLINK_DOWN;
        gstCh0Layer.gu8NReTryPerFrame = 0;
        StartTransmitCallBackRegister(NULL, 0); /*frame error*/
        TimeCallBackRegister(NULL, 0, 0);
        return;


#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReTransmitFrameAfterBlocking >                                      |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReTransmitFrame                                                           |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param Id          : Channle ID                                                                     |                                                                                                                        |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void ReTransmitFrameAfterBlocking(uint8_t ID) {
    /*start transmission*/
#if defined USART1_ENABLED
    if (ID) {

    } else {
#endif
        if ((gstCh0Layer.pFunStartTransmit != NULL)) {
            /*active DIFS Time*/
            if (gstCh0Layer.gu8CoillisonCounter < COLIISION_MAX_NUMBER) {
                commBackOffTime(0, 0);
                TimeCallBackRegister(funDIFS, 0, DIFS);
            } else {
                /*Link Down*/
                gstCh0Layer.gu8CoillisonCounter = 0;
                gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_DLINK_DOWN;
            }
            return;
        }


        TimeCallBackRegister(NULL, 0, 0);
#if defined USART1_ENABLED
    }
#endif

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithNACKControl >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithACKData                                                         |                                          
 | < @Description       : Parse Frame  ACK OR NOT ACK received or free or Bloking                        |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNACKControl(uint8_t ID) {
    ucommChannelControlFlied_t ControlFiled;
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh1Layer.gu8ReceiveCount != 4) {
            checkRequest(1, NULL, 0);
            ReceiveCallBackRegister(NULL, 1);
            return;
        }

        if (csmaCRCCheck(gstCh1Layer.gu8ReceiveBuf, 4) != gstCh1Layer.gu8ReceiveBuf[ControlPhysicalCRC]) {
            checkRequest(1, NULL, 0);
            ReceiveCallBackRegister(NULL, 0);
            return;
        }


        ControlFiled.controlFlied = gstCh1Layer.gu8ReceiveBuf[0];
        if (ControlFiled.FSTF == BlockFrame) {
            TimeCallBackRegister(funBIFS, 1, BIFS); /*active Blocking Time*/
            ReceiveCallBackRegister(NULL, 1);
            return;
        }


        if (ControlFiled.FSTF == AckFrame) {
            gstCh1Layer.Flags.REQF = 0;
            StartTransmitCallBackRegister(NULL, 1);
            commBackOffTime(1, 1);
            gstCh1Layer.gu8NReTryPerFrame = 0;
            TimeCallBackRegister(NULL, 1, 0);
            ReceiveCallBackRegister(NULL, 1);
            return;
        }

        if (ControlFiled.FSTF == NackFrame) {
            ReceiveCallBackRegister(NULL, 0);
            ReTransmitFrame(0);
            return;
        }



        if (ControlFiled.FSTF == FreeFrame) {
            if (gstCh1Layer.pFunStartTransmit != NULL) {
                TimeCallBackRegister(funDIFS, 1, DIFS);
            } else {
                TimeCallBackRegister(NULL, 1, 0);
            }
            ReceiveCallBackRegister(NULL, 1);
            return;
        }
        checkRequest(NULL, 1, 0);
        ReceiveCallBackRegister(NULL, 1);
    } else {
#endif

        if (gstCh0Layer.gu8ReceiveCount != ControlPhysicalCRC + 1) {
            checkRequest(0, NULL, 0);
            ReceiveCallBackRegister(NULL, 0);
            return;
        }


        ControlFiled.controlFlied = gstCh0Layer.gu8ReceiveBuf[0];
        if (ControlFiled.FSTF == BlockFrame) {
            TimeCallBackRegister(funBIFS, 0, BIFS); /*active Blocking Time*/
            ReceiveCallBackRegister(NULL, 0);
            return;
        }


        if (ControlFiled.FSTF == AckFrame) {
            gstCh0Layer.Flags.REQF = 0;
            StartTransmitCallBackRegister(NULL, 0);
            commBackOffTime(1, 0);
            gstCh0Layer.gu8NReTryPerFrame = 0;
            TimeCallBackRegister(NULL, 0, 0);
            ReceiveCallBackRegister(NULL, 0);
            return;
        }

        if (ControlFiled.FSTF == NackFrame) {
            ReceiveCallBackRegister(NULL, 0);
            ReTransmitFrame(0);
            return;
        }



        if (ControlFiled.FSTF == FreeFrame) {
            if (gstCh0Layer.pFunStartTransmit != NULL) {
                TimeCallBackRegister(funDIFS, 0, DIFS);
            } else {
                TimeCallBackRegister(NULL, 0, 0);
            }
            ReceiveCallBackRegister(NULL, 0);
            return;
        }
        checkRequest(0, NULL, 0);
        ReceiveCallBackRegister(NULL, 0);
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FunGetAddress >                                                     |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t FunGetAddress                                                          |                                          
 | < @Description       : Actionwith Received Command Get Address                                        |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t FunGetAddress(uint8_t ID) {

#if defined USART1_ENABLED
    if (ID) {
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            serial[i] = gstCh1Layer.gu8ReceiveBuf[ManangmentPhysicalSER + i];
        }
        if (gstCh1Layer.Flags.SERCLIF) {
            if (gstCh1Layer.AssignAddress < 128) {
                gstCh1Layer.AssignAddress++;
                if (putManagment(1, serial, gstCh1Layer.AssignAddress, AssignAddress)) {
                    return (1);
                }
            } else {
                if (putManagment(1, serial, 0xFF, RemoveAddress)) {
                    return (1);
                }
            }
        } else {
            if (putManagment(0, gu8SerialNumberTransmission, gstCh1Layer.gu8StationAddress, GetAddress)) {
                return (1);
            }
        }

    } else {

#endif


        if (gstCh0Layer.Flags.SERCLIF) {
            if (gstCh0Layer.AssignAddress < 128) {

                if (putManagment(0, gu8SerialNumberReceived, gstCh0Layer.AssignAddress, AssignAddress)) {
                    gstCh0Layer.AssignAddress++;
                    ManagmentCallBackRegister(NULL, 0);
                    return (1);
                }
                return (0);
            }
            if (putManagment(0, gu8SerialNumberReceived, 0xFF, RemoveAddress)) {
                ManagmentCallBackRegister(NULL, 0);
                return (1);
            }
            return (0);
        }
        if (gstCh0Layer.gu8StationAddress) {
            return (1);
        }
        if (putManagment(0, gu8SerialNumberTransmission, gstCh0Layer.gu8StationAddress, GetAddress)) {
            ManagmentCallBackRegister(NULL, 0);
            return (1);
        }



#if defined USART1_ENABLED
    }
#endif
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < FunAssignAddress >                                                  |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t FunAssignAddress                                                       |                                          
 | < @Description       : Actionwith Received Command Assign Address                                     |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t FunAssignAddress(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh1Layer.Flags.SERCLIF) {
            return (1);
        } else {
            gstCh1Layer.gu8StationAddress = gstCh1Layer.gu8ReceiveBuf[ManangmentPhysicalAddress];
            if (!BusyFun(1)) {
                putAck(1, FreeFrame);
                return (1);
            }
        }

    } else {

#endif
        if (gstCh0Layer.Flags.SERCLIF) {
            return (1);
        } else {
            gstCh0Layer.gu8StationAddress = gstCh0Layer.AssignAddress;

            if (!BusyFun(0)) {
                ManagmentCallBackRegister(NULL, 0);
                putAck(0, FreeFrame);
                return (1);
            }
        }
#if defined USART1_ENABLED
    }
#endif

    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < parserWithACKData >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void parserWithACKData                                                         |                                          
 | < @Description       : Parse Frame  and send ack by managment frames                                  |                                            
 | < @Param ID          : channle ID                                                                     |   
 | < @return            : void                                                                           |                                                                                       
 ---------------------------------------------------------------------------------------------------------
 */
static void parserWithNACKManagment(uint8_t ID) {
    ucommChannelControlFlied_t ControlFiled;
#if defined USART1_ENABLED
    if (ID) {

    } else {
#endif


        ControlFiled.controlFlied = gstCh0Layer.gu8ReceiveBuf[0];
        gstCh0Layer.DA = gstCh0Layer.gu8ReceiveBuf[ManangmentPhysicalSA];
        if ((ManangmentPhysicalCRC + 1) != gstCh0Layer.gu8ReceiveCount) {
            putAck(0, NackFrame);
        } else if (ControlFiled.FSTF == GetAddress) {
            putAck(0, AckFrame);
            ManagmentCallBackRegister(FunGetAddress, 0);
            gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_MANAGEMNT;
        } else if (ControlFiled.FSTF == AssignAddress) {
            putAck(0, AckFrame);
            gstCh0Layer.AssignAddress = gstCh0Layer.gu8ReceiveBuf[ManagmnetAssignAddress];
            ManagmentCallBackRegister(FunAssignAddress, 0);
            /*Active Wait For ACK*/
            gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_MANAGEMNT;
        } else if (ControlFiled.FSTF == RemoveAddress) {
            putAck(0, AckFrame);
            gstCh0Layer.gu8StationAddress = 0x00;
        } else {
            putAck(0, NackFrame);
        }
        ReceiveCallBackRegister(NULL, 0);
        gstCh0Layer.Flags.ACKWSND = 1;
        return;

#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < BusyFun >                                                          |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void BusyFun                                                                   |                                          
 | < @Description       : check comm is ready or not                                                     |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     | 
 | < @return            : 1 comm is busy                                                                 |
 |                      : 0 comm is ready                                                                |                 
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t BusyFun(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh1Layer.Flags.SYSTEM_STATE != SYSTEM_IDLE) {
            return (1);
        }

        if (!gstCh1Layer.Flags.CCAF) {
            return (1);
        }
        if (gstCh1Layer.pFunStartTransmit != NULL) {
            return (1);
        }

        if (gstCh1Layer.pFunTime == funSIFS) {
            return (1);
        }

        if (gstCh1Layer.pFunTime == funBIFS) {
            return (1);
        }
    } else {
#endif
        if (gstCh0Layer.Flags.ACKWSND) {

            return (1);
        }
        if (!gstCh0Layer.Flags.CCAF) {

            return (1);
        }
        if (gstCh0Layer.pFunStartTransmit != NULL) {
            return (1);
        }
        if (gstCh0Layer.pFunTime == funBIFS) {
            return (1);
        }
#if defined USART1_ENABLED
    }
#endif
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putAck >                                           |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void putAck                                                   |                                          
 | < @Description       : Re-Transmit Frame After Free or Block Time Out                                 |                                                     |  
 | < @Param callback    : Pointer To callback Run                                                        |  
 | < @Param ID          : channle ID                                                                     |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void putAck(uint8_t ID, uint8_t Type) {
    ucommChannelControlFlied_t Controlbyte;
#if defined USART1_ENABLED
    if (ID) {
        Controlbyte.FTYF = ControlFrame;
        Controlbyte.FSTF = Type;
        Controlbyte.FVTF = 0x00;
        gstCh1Layer.gu8TransmissionACK[ControlPhysicalControlFiled] = Controlbyte.controlFlied;
        gstCh1Layer.gu8TransmissionACK[ControlPhysicalDA] = gstCh1Layer.gu8ReceiveBuf[ControlPhysicalSA];
        gstCh1Layer.gu8TransmissionACK[ControlPhysicalSA] = gstCh1Layer.gu8StationAddress;
        gstCh1Layer.gu8TransmissionACK[ControlPhysicalCRC] = csmaCRCCheck(gstCh1Layer.gu8TransmissionACK, ControlPhysicalCRC);
        TimeCallBackRegister(funSIFS, 1, SIFS);
    } else {
#endif

        Controlbyte.FTYF = ControlFrame;
        Controlbyte.FSTF = Type;
        Controlbyte.FVTF = 0x00;
        gstCh0Layer.gu8TransmissionACK[ControlPhysicalControlFiled] = Controlbyte.controlFlied;
        gstCh0Layer.gu8TransmissionACK[ControlPhysicalDA] = gstCh0Layer.gu8ReceiveBuf[ControlPhysicalSA];
        gstCh0Layer.gu8TransmissionACK[ControlPhysicalSA] = gstCh0Layer.gu8StationAddress;
        gstCh0Layer.gu8TransmissionACK[ControlPhysicalCRC] = csmaCRCCheck(gstCh0Layer.gu8TransmissionACK, ControlPhysicalCRC);
        TimeCallBackRegister(funSIFS, 0, SIFS);
#if defined USART1_ENABLED
    }
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < putDataCh0 >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putData                                                                |                                          
 | < @Description       : Fill Data Into Buffer  and start Transmission                                  |                                                     |  
 | < @Param serial      : Pointer To serila data send Run                                                |  
 | < @Param ID          : channle ID                                                                     |
 | < @Param address     : station assignment address                                                     |
 | < @Param Type        : Frame Type managment                                                           |
 | < @return            : 0 Channle Busy with Other Data Send                                            |
 |                      : 1 Channle Ready To Request Data                                                |                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static uint8_t putManagment(uint8_t ID, volatile uint8_t *serial, volatile uint8_t address, uint8_t Type) {
    ucommChannelControlFlied_t ControlByte;
#if defined USART1_ENABLED
    if (ID) {
        if (BusyFun(1)) {
            return (0);
        }
        ControlByte.FTYF = MangmentFrame;
        ControlByte.FSTF = Type;
        ControlByte.FVTF = 0;
        gstCh1Layer.gu8TransmissionManagment[ManangmentPhysicalControlFiled] = ControlByte.controlFlied;
        gstCh1Layer.gu8TransmissionManagment[ManangmentPhysicalAddress] = address;
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            gstCh1Layer.gu8TransmissionManagment[ManangmentPhysicalSER + i] = serial[i];
        }
        gstCh1Layer.gu8TransmissionManagment[ManangmentPhysicalCRC] = csmaCRCCheck(gstCh1Layer.gu8TransmissionManagment, ManangmentPhysicalCRC);
        StartTransmitCallBackRegister(funStartTransmitManagment, 1);
        TimeCallBackRegister(funDIFS, 1, DIFS);
    } else {
#endif
        if (BusyFun(0)) {
            return (0);
        }
        ControlByte.FTYF = MangmentFrame;
        ControlByte.FSTF = Type;
        ControlByte.FVTF = 0;
        gstCh0Layer.gu8TransmissionManagment[ManangmentPhysicalControlFiled] = ControlByte.controlFlied;
        gstCh0Layer.gu8TransmissionManagment[ManangmentPhysicalDA] = gstCh0Layer.DA;
        gstCh0Layer.gu8TransmissionManagment[ManangmentPhysicalSA] = gstCh0Layer.gu8StationAddress;
        gstCh0Layer.gu8TransmissionManagment[ManagmnetAssignAddress] = address;
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            gstCh0Layer.gu8TransmissionManagment[ManangmentPhysicalSER + i] = serial[i];
        }
        gstCh0Layer.gu8TransmissionManagment[ManangmentPhysicalCRC] = csmaCRCCheck(gstCh0Layer.gu8TransmissionManagment, ManangmentPhysicalCRC);
        StartTransmitCallBackRegister(funStartTransmitManagment, 0);
        TimeCallBackRegister(funDIFS, 0, DIFS);

#if defined USART1_ENABLED
    }
#endif
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < csmaDriverChannle >                                                 |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaDriverChannle                                                         |                                          
 | < @Description       : Handling Received Data by Channle                                              |                                                              |                                                                                                                          |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
static void csmaDriverChannle(uint8_t ID) {
#if defined USART1_ENABLED
    if (ID) {
        if (gstCh0Layer.Flags.SYSTEM_STATE == SYSTEM_IDLE) {

            return;
        }

        if (gstCh1Layer.Flags.SYSTEM_STATE == SYSTEM_MANAGEMNT) {
            if (gstCh1Layer.pFunManagment != NULL) {
                if (gstCh1Layer.pFunManagment(0)) {
                    gstCh1Layer.Flags.SYSTEM_STATE = SYSTEM_IDLE;
                }
            }
            return;
        }

        if (!gstCh1Layer.gu8StationAddress) {
            return;
        }

        if (gstCh1Layer.Flags.SYSTEM_STATE == SYSTEM_DATA_REQUEST) {

            return;
        }

        if (gstCh1Layer.Flags.SYSTEM_STATE == SYSTEM_DATA_RESPONSE) {
            return;
        }
    } else {
#endif
        if (gstCh0Layer.Flags.SYSTEM_STATE == SYSTEM_IDLE) {
            return;
        }

        if (gstCh0Layer.Flags.SYSTEM_STATE == SYSTEM_DLINK_DOWN) {
            return;
        }

        if (gstCh0Layer.Flags.SYSTEM_STATE == SYSTEM_MANAGEMNT) {
            if (gstCh0Layer.pFunManagment != NULL) {
                if (gstCh0Layer.pFunManagment(0)) {
                    gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_IDLE;
                }
            }
            return;
        }

        if (!gstCh0Layer.gu8StationAddress) {
            return;
        }

        if (gstCh0Layer.Flags.SYSTEM_STATE == SYSTEM_DATA_REQUEST) {
            if (gstCh0Layer.pFunDataRequest != NULL) {
                if (gstCh0Layer.pFunDataRequest(0, gstCh0Layer.DA, gstCh0Layer.gu8DataFrameLength, gstCh0Layer.gu8ReceiveData)) {
                    gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_IDLE;
                }
            }
            return;
        }

        if (gstCh0Layer.Flags.SYSTEM_STATE == SYSTEM_DATA_RESPONSE) {
            if (gstCh0Layer.pFunDataResponse != NULL) {
                if (gstCh0Layer.pFunDataResponse(0, gstCh0Layer.DA, gstCh0Layer.gu8DataFrameLength, gstCh0Layer.gu8ReceiveData)) {
                    gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_IDLE;
                }
            }
            return;
        }
#if USART1_ENABLED
    }
#endif

}
/* 
 ---------------------------------------------------------------------------------------------------------
 |                      <user Function Implemntions >                                                 |
 ---------------------------------------------------------------------------------------------------------   
 */

/*
 ----------------------------------------------------------------------------------------------------------------------------
 |                                 < commTimerInit >                                                                        |
 ----------------------------------------------------------------------------------------------------------------------------
 | < @Function          : void commTimerInit                                                                                | 
 | < @Description       : configuration of timer 2 and External Interrupts                                                  |                                                                                   
 | < @return            : void                                                                                              |
 ----------------------------------------------------------------------------------------------------------------------------
 */
void csmaInit() {
    uint32_t Serial;
#if defined(TCCR2A) && defined(WGM21)
    TIMER2_MODE2;
    TIMER2_MODE1;
    TIMER2_MODE0;
#endif

#if defined (OCR0A) 
    OCR2A = TIMER2_VALUE;
#endif
    digitalpinMode(GPIO_B0, MODE_OUTPUT);
    digitalpinMode(GPIO_B1, MODE_OUTPUT);
    digitalpinMode(GPIO_B3, MODE_INPUT);
    digitalpinMode(GPIO_B4, MODE_INPUT);

#if defined(__AVR_ATmega128__) ||  defined(__AVR_ATmega128A__)
    // CPU specific: different values for the ATmega128
    TIMER2_PRESCALLER2;
    TIMER2_PRESCALLER1;
    TIMER2_PRESCALLER0;
    TIMER2_MODE0;
    TIMER2_MODE1;
    OCR2 = TIMER2_VALUE;
    /*Enable Interrupt*/
    sbi(TIMSK, OCIE2);
    gstCh0Layer.Flags.SERCLIF = 1;
    gstCh0Layer.AssignAddress = 1;
    ManagmentCallBackRegister(NULL, 0);
    gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_IDLE;
    for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
        gu8SerialNumberTransmission[i] = i + 1;
    }
#elif defined(TCCR2) && defined(CS21) && defined(CS20) 
    TIMER2_MODE0;
    TIMER2_MODE1;
    TIMER2_PRESCALLER2;
    TIMER2_PRESCALLER1;
    TIMER2_PRESCALLER0;
    OCR2 = TIMER2_VALUE;
    sbi(TIMSK, OCIE2);
    gstCh0Layer.Flags.SERCLIF = 0;
    gstCh0Layer.AssignAddress = 0;
    gstCh0Layer.Flags.SYSTEM_STATE = SYSTEM_MANAGEMNT;
    ManagmentCallBackRegister(FunGetAddress, 0);

    uint8_t byte = digitalPinRead(GPIO_B3) | ((digitalPinRead(GPIO_B4)) << 1);
    if (byte == 0) {
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            gu8SerialNumberTransmission[i] = i + 10;
        }
    } else if (byte == 1) {
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            gu8SerialNumberTransmission[i] = i + 20;
        }
    } else if (byte == 2) {
        for (uint8_t i = 0; i < SERIAL_NUMBER_LENGTH; i++) {
            gu8SerialNumberTransmission[i] = i + 30;
        }
    }
#elif defined(TCCR2B) && defined(CS21) && defined(CS20)
    TIMER2_PRESCALLER2;
    TIMER2_PRESCALLER0;
    TIMER2_PRESCALLER1;
    sbi(TIMSK2, OCIE2A);
#elif defined(TCCR2A) && defined(CS21) && defined(CS20)
    TIMER2_PRESCALLER1;
    TIMER2_PRESCALLER0;
    TIMER2_MODE1;
    TIMER2_MODE0;


#endif


    /*External Interrupt Worked start*/
#if defined PCIE2 
    PCMSK2 |= (1 << PCINT16);
    PCICR |= (1 << PCIE2);
#elif (defined (EICRA)) && (defined (EICRB))
#if defined USART0_ENABLED
    EICRB &= ~(1 << ISC41);
    EICRB |= (1 << ISC40);
    EIMSK |= (1 << INT4);
#endif
#if defined USART1_ENABLED
    EICRB &= ~(1 << ISC51);
    EICRB |= (1 << ISC50);
    EIMSK |= (1 << INT5);

#endif
#elif defined GICR
#if defined USART0_ENABLED
    MCUCR &= ~(1 << ISC01);
    MCUCR |= (1 << ISC00);
    GICR |= (1 << INT0);
#endif

#endif

#if defined USART0_ENABLED
    gstCh0Layer.Flags.CCAF = 1;
    gstCh0Layer.gu08BOFT = 0x00;
    gstCh0Layer.gu8NReTryPerFrame = 0;
    gstCh0Layer.gu08CW = CW_MIN;
    gstCh0Layer.gu8StationAddress = 0x00;

    gstCh0Layer.gu8ReceiveCount = 0;
    gstCh0Layer.gu8DataFrameLength = 0;
    gstCh0Layer.gu8TransmissionCounter = 0;
    TimeCallBackRegister(NULL, 0, 0);
    StartTransmitCallBackRegister(NULL, 0);
    TransmitCallBackRegister(NULL, 0);
    ReceiveCallBackRegister(NULL, 0);


#endif

#if defined USART1_ENABLED
    gstCh1Layer.Flags.CCAF = 1;
    gstCh1Layer.gu08BOFT = 0x00;
    gstCh1Layer.gu8NReTryPerFrame = 0;
    gstCh1Layer.gu08CW = CW_MIN;
    gstCh1Layer.gu8StationAddress = 0x00;
    gstCh1Layer.AssignAddress = 1;
    gstCh1Layer.gu8ReceiveCount = 0;
    gstCh1Layer.gu8DataFrameLength = 0;
    gstCh1Layer.gu8TransmissionCounter = 0;
    if (gstCh1Layer.Flags.SERCLIF) {
        gstCh1Layer.Flags.SYSTEM_STATE = SYSTEM_IDLE;
        ManagmentCallBackRegister(NULL, 1);
    } else {
        gstCh1Layer.Flags.SYSTEM_STATE = SYSTEM_MANAGEMNT;
        ManagmentCallBackRegister(FunGetAddress, 1);
    }

    TimeCallBackRegister(NULL, 0, 1);
    StartTransmitCallBackRegister(NULL, 1);
    TransmitCallBackRegister(NULL, 1);
    ReceiveCallBackRegister(NULL, 1);
#endif
    Serial = 0;
    Serial |= ((uint32_t) gu8SerialNumberTransmission[SERIAL_NUMBER_LENGTH - 1] << 24);
    Serial |= ((uint32_t) gu8SerialNumberTransmission[SERIAL_NUMBER_LENGTH - 2] << 16);
    Serial |= ((uint32_t) gu8SerialNumberTransmission[SERIAL_NUMBER_LENGTH - 3] << 8);
    Serial |= ((uint32_t) gu8SerialNumberTransmission[SERIAL_NUMBER_LENGTH - 4] << 0);
    srandom(Serial);
}

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
uint8_t putDataCh0(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type) {
    ucommChannelControlFlied_t ControlByte;
    if (!gstCh0Layer.gu8StationAddress) {
        return (0);
    }
    if (BusyFun(0)) {
        return (0);
    }
    ControlByte.FTYF = DataFrame;
    ControlByte.FSTF = Type;
    ControlByte.FVTF = 0;
    gstCh0Layer.gu8TransmissionData[DataPhysicalControlFiled] = ControlByte.controlFlied;
    gstCh0Layer.gu8TransmissionData[DataPhysicalDA] = DA;
    gstCh0Layer.gu8TransmissionData[DataPhysicalSA] = gstCh0Layer.gu8StationAddress;
    gstCh0Layer.gu8TransmissionData[DataPhysicalLength] = len;
    for (uint8_t i = 0; i < len; i++) {
        gstCh0Layer.gu8TransmissionData[i + DataPhysicalPayload] = buf[i];
    }
    gstCh0Layer.gu8TransmissionData[DataPhysicalPayload + len] = csmaCRCCheck(gstCh0Layer.gu8TransmissionData, DataPhysicalPayload + len);
    gstCh0Layer.gu8DataFrameLength = DataPhysicalPayload + len;
    StartTransmitCallBackRegister(funStartTransmitData, 0);
    TimeCallBackRegister(funDIFS, 0, DIFS);

    return (1);
}
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
 |                      : 1 Channle Ready To Request Data                                                |                                                                            |                 
 ----------------------------------------------------------------------------------------------------------
 */
uint8_t putDataCh1(uint8_t *buf, uint8_t len, uint8_t DA, uint8_t Type) {
    ucommChannelControlFlied_t ControlByte;
    if (!gstCh1Layer.gu8StationAddress) {
        return (0);
    }

    if (BusyFun(1)) {
        return (0);
    }
    ControlByte.FTYF = DataFrame;
    ControlByte.FSTF = Type;
    ControlByte.FVTF = 0;
    gstCh1Layer.gu8TransmissionData[DataPhysicalControlFiled] = ControlByte.controlFlied;
    gstCh1Layer.gu8TransmissionData[DataPhysicalDA] = DA;
    gstCh1Layer.gu8TransmissionData[DataPhysicalSA] = gstCh1Layer.gu8StationAddress;
    gstCh1Layer.gu8TransmissionData[DataPhysicalLength] = len;
    for (uint8_t i = 0; i < len; i++) {
        gstCh1Layer.gu8TransmissionData[i + DataPhysicalPayload] = buf[i];
    }
    gstCh1Layer.gu8TransmissionData[DataPhysicalPayload + len] = csmaCRCCheck(gstCh1Layer.gu8TransmissionData, DataPhysicalPayload + len);
    gstCh1Layer.gu8DataFrameLength = DataPhysicalPayload + len;
    StartTransmitCallBackRegister(funStartTransmitData, 1);
    TimeCallBackRegister(funDIFS, 1, DIFS);

    return (1);
}
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < csmaDriver >                                                        |                      
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void csmaDriver                                                                |                                          
 | < @Description       : Handling Received Data                                                         |                                                              |                                                                                                                          |
 | < @return            : void                                                                           |                 
 ----------------------------------------------------------------------------------------------------------
 */
void csmaDriver() {
#if defined USART0_ENABLED
    csmaDriverChannle(0);
#endif

#if defined USART1_ENABLED
    csmaDriverChannle(1);
#endif

}

#endif
#endif


