
/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : ZLP.h                                                                   |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 11 Byte Used by one Pin                                                  |
| < PROGRAM USAGE            : 430 Byte by One Pin Used                                                 |                                                                         |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */
#include <stdint.h>
#include <stdint-gcc.h>

#include "../../../inc/mega.h"

#if defined ZLP_MODULE
#if ZLP_MODULE

/*
---------------------------------------------------------------------------------------------------------
|                           < Macros >                                                      | 
---------------------------------------------------------------------------------------------------------
 */


/*
 *@macro   NUMBER_OF_DODS_PER_INCH                 : number of dots per inch
 */
#ifndef    NUMBER_OF_DODS_PER_INCH                     
#define    NUMBER_OF_DODS_PER_INCH                    _1IN_203DOTS
#endif
/*
 *@macro   ZLP_PRINT_RATE                           : printer speed , feed speed , slew rate speed
 */
#ifndef ZLP_PRINT_RATE       
#define ZLP_PRINT_RATE                                  _4IN_PER_SEC
#endif
/*
 *@macro   ZLP_DOTS_PER_MM                           : Set Dots per Millimeter
 */
#ifndef  ZLP_DOTS_PER_MM
#define ZLP_DOTS_PER_MM          ZLP_JM_CMD_A
#endif
#ifndef  ZLP_COMM_BUFFER
#define  ZLP_COMM_BUFFER                    (20)
#endif
/*
 * <@macro  ZLP_S_CMD_LEN                     : print Rate Command Length
 */
#define     ZLP_S_CMD_LEN                        (4)
/*
 * <@Macro ZLP_Y_CMD_LEN                 (Y Command LEngth) 
 */
#define      ZLP_Y_CMD_LEN                        (11)

/*
 * @macro :START_SET_CONFIG                       : start set Configuration
 */
#define    STOP_SET_CONFIG                (0)
/*
 * @macro :START_SET_SC_CONFIG                      : set SC CONFIG
 */
#define START_CONFIG_0                    (1)
/*
 * @macro START_SET_PR_CONFIG             : set printer rate 
 */
#define   START_CONFIG_1                   (2)
/*
 * @Macro START_SET_JM_KL_CONFIG                 :set Language and Dots Rate
 */
#define START_CONFIG_2                     (3)
/*
 * <@Macro START_DATA_0                     : set First Data
 */
#define  STOP_SET_DATA                      (0)
/*
 * <@Macro START_DATA_0                     : set First Data
 */
#define  START_SET_DATA_0                      (1)
/*
 * <@Macro START_DATA_1                     : set 2 Data
 */
#define  START_SET_DATA_1                     (2)
/*
 * <@Macro START_DATA0                     : set 3 Data
 */
#define  START_SET_DATA_2                      (3)
/*
 * <@Macro START_PRINT_TEXT                     : Print Text Now
 */
#define START_PRINT_TEXT                       (4)


/*
---------------------------------------------------------------------------------------------------------
|                           < Constant >                                                      | 
---------------------------------------------------------------------------------------------------------
 */
#if UART0_BUADRATE == StandBaudRate_1200
static const uint8_t PROGMEM ZLP_Y_CMD[] = "Y12,N,8,1\r\n";
#elif  UART0_BUADRATE == StandBaudRate_2400
static const uint8_t PROGMEM ZLP_Y_CMD[] = "Y24,N,8,1\r\n";
#elif  UART0_BUADRATE == StandBaudRate_4800
static const uint8_t PROGMEM ZLP_Y_CMD[] = "Y48,N,8,1\r\n";
#elif  UART0_BUADRATE == StandBaudRate_9600
static const uint8_t PROGMEM ZLP_Y_CMD[] = "Y96,N,8,1\r\n";
#elif  UART0_BUADRATE == StandBaudRate_19200
static const uint8_t PROGMEM ZLP_Y_CMD[] = "Y19,N,8,1\r\n";
#elif  UART0_BUADRATE == StandBaudRate_38400
static const uint8_t PROGMEM ZLP_Y_CMD[] = "Y38,N,8,1\r\n";
#endif

#if defined ZLP_PRINT_RATE == _1IN_PER_SEC
/*
 * <@const  ZLP_S_CMD                         : Print Rate Command 
 */
static const uint8_t PROGMEM ZLP_S_CMD[] = "S1\r\n";
#elif ZLP_PRINT_RATE == _2IN_PER_SEC
/*
 * <@const  ZLP_S_CMD                         : Print Rate Command 
 */
static const uint8_t PROGMEM ZLP_S_CMD[] = "S2\r\n";
#elif ZLP_PRINT_RATE == _3IN_PER_SEC
/*
 * <@const  ZLP_S_CMD                         : Print Rate Command 
 */
static const uint8_t PROGMEM ZLP_S_CMD[] = "S3\r\n";
#elif ZLP_PRINT_RATE == _4IN_PER_SEC
/*
 * <@const  ZLP_S_CMD                         : Print Rate Command 
 */
static const uint8_t PROGMEM ZLP_S_CMD[] = "S4\r\n";
#endif

/*
---------------------------------------------------------------------------------------------------------
|                           < typdef  >                                                      | 
---------------------------------------------------------------------------------------------------------
 */
typedef union {
    uint8_t Flags;

    struct {
        unsigned CONFIGSTATE : 2;
        unsigned TEXTSTATE : 2;
        unsigned TXDCOM : 1;
        unsigned PRINT_STATE : 1;
        unsigned ZLP_Busy : 1;
    };
} ZLP_FLAGS_t;

typedef union {
    uint8_t Font;

    struct {
        unsigned FontSize : 3;
        unsigned FontResulation : 4;
        unsigned ThermalTransfer : 1;
    };
} ZLP_Font_Option_t;
/*
---------------------------------------------------------------------------------------------------------
|                           < Variable >                                                      | 
---------------------------------------------------------------------------------------------------------
 */
/*
 * @var  gu16zlpWidth                           : label width max is 832 dots
 */
static volatile uint16_t gu16zlpWidth;
/*
 * @var  gu16zlpLength                     : label length max is 832 dots
 */
static volatile uint16_t gu16zlpLength;
/*
 * <@var gu8ZLPBuffer                            : uart Buffer Length
 */
static volatile uint8_t gu8ZLPBuffer [ZLP_COMM_BUFFER];
/*
 * @var gu8ZLPBufferLength                         :uart Max send Data
 */
static volatile uint8_t gu8ZLPBufferLength;
/*
 *@var gu8ZLPBufferIndex                             : uart current Send Data
 */
static volatile uint8_t gu8ZLPBufferIndex;
/*
 *@var guZLPFlags                                   : ZLP Printer state
 */
static volatile ZLP_FLAGS_t guZLPFlags;
/*
 * <@var gu8ZLPFontSize  :                      : ZLP Printer Font Size 
 */
static volatile ZLP_Font_Option_t gu8ZLPFont;
/*
 * <@var gu8ZLPX                                  :text Posision in x
 */
static volatile uint16_t gu8ZLPX;
/*
 * <@var gu8ZLPX                                  :text Posision in Y
 */
static volatile uint16_t gu8ZLPY;
/*
 * <@var gpu8ZLPTex                               : Pointer To Text Buffer
 */
static volatile uint8_t *gpu8ZLPTex;
/*
 * <@var  gu8NumberofCopies                      : Number of Lable Print
 */
static volatile uint8_t gu8NumberofCopies;
/*
 *<@var gu8TextLen                                 : User Text Length
 */
static volatile uint8_t gu8TextLength;
/*
---------------------------------------------------------------------------------------------------------
|                           < Internal Function Definitions >                                             | 
---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPsetConfig >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPsetConfig                                                            |  
 | < @Description       : set Configuration of the                                                     | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPsetConfig();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPsetData >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPsetData                                                            |  
 | < @Description       : set Data                                                   | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPsetText();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrint >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPrint                                                                 |  
 | < @Description       : set Print Command                                                             | 
 | < @return            : void                                                                          |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPPrint();

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPISR >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPISR                                                                  |  
 | < @Description       : run in ISR                                                                   | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPISR();

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSendFirstByte >                                                  |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSendFirstByte                                                          |  
 | < @Description       : send first Byte                                                                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPSendFirstByte(uint8_t Length);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSetBuffer >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSetBuffer                                                              |  
 | < @Description       : set data Const Into Buffer                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPSetBufferConstPGM(const uint8_t *buf, uint8_t Length, uint8_t LastIndex);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSetBufferConst >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSetBufferConst                                                              |  
 | < @Description       : set data Const Into Buffer                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPSetBufferConst(const char *buf, uint8_t Length, uint8_t LastIndex);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSetBuffer >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSetBuffer                                                              |  
 | < @Description       : set data  Into Buffer                                                          | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPSetBuffer(uint8_t volatile *buf, uint8_t Length, uint8_t LastIndex);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPgetTextHight >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ZLPgetTextHight                                                              |  
 | < @Description       : get Y  Of the Font    from Font Size                                         | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPgetTextWidth();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPgetTextHight >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ZLPgetTextHight                                                              |  
 | < @Description       : get Y  Of the Font    from Font Size                                         | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPgetTextHight();

/*
---------------------------------------------------------------------------------------------------------
|                           < ISR Function  >                                                         | 
---------------------------------------------------------------------------------------------------------
 */

ISR(UART0_TRANSMIT_INTERRUPT) {
    ZLPISR();
}

/*
---------------------------------------------------------------------------------------------------------
|                           < Internal Function Implementions >                                         | 
---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSendFirstByte >                                                  |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSendFirstByte                                                          |  
 | < @Description       : send first Byte                                                                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPSendFirstByte(uint8_t Length) {
    guZLPFlags.TXDCOM = 1;
    gu8ZLPBufferLength = Length;
    while (!Empty_BUFFER0());
    usart0PutByte((gu8ZLPBuffer[0]));
    gu8ZLPBufferIndex++;

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPsetConfig >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPsetConfig                                                            |  
 | < @Description       : set Configuration of the                                                     | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPsetConfig() {
    uint8_t j;
    char s[5];
    uint8_t resulation;
    uint8_t size;

    j = 0;




    if (guZLPFlags.CONFIGSTATE == STOP_SET_CONFIG) {
        return;
    }

    if (guZLPFlags.TXDCOM) {
        return;
    }

    if (guZLPFlags.CONFIGSTATE == START_CONFIG_0) {
        j = ZLPSetBufferConstPGM(ZLP_Y_CMD, ZLP_Y_CMD_LEN, j); /*send communication Info*/
        j = ZLPSetBufferConstPGM(ZLP_S_CMD, ZLP_S_CMD_LEN, j); /*send Speed Configuration*/
        j = ZLPSetBufferConst("ZT\r\n", 4, j); /*Print from top*/
        guZLPFlags.CONFIGSTATE = START_CONFIG_1;
        ZLPSendFirstByte(j);
        return;
    }
    if (guZLPFlags.CONFIGSTATE == START_CONFIG_1) {
        /*send Width and Length*/
        j = ZLPSetBufferConst("q", 1, j); /*1Byte*/
        size = u16TOASII(s, gu16zlpWidth);
        j = ZLPSetBufferConst(s, size, j); /*max 5 Byte*/
        j = ZLPSetBufferConst("\r\n", 2, j); /*2Byte*/
        j = ZLPSetBufferConst("Q", 1, j); /*Just One Byte Send*/
        size = u16TOASII(s, gu16zlpLength);
        j = ZLPSetBufferConst(s, size, j); /*max 5 Byte*/
        j = ZLPSetBufferConst(",024\r\n", 6, j); /*6Byte*/
        guZLPFlags.CONFIGSTATE = START_CONFIG_2;
        ZLPSendFirstByte(j);
        return;
    }

    if (guZLPFlags.CONFIGSTATE == START_CONFIG_2) {
        j = ZLPSetBufferConst("D", 1, j);
        resulation = gu8ZLPFont.FontResulation;
        size = u8TOASII(s, resulation);
        j = ZLPSetBufferConst(s, size, j);
        j = ZLPSetBufferConst("\r\n", 2, j);
        j = ZLPSetBufferConst("O\r\n", 3, j); /*Disable all Option*/
        if (!gu8ZLPFont.ThermalTransfer) {
            j = ZLPSetBufferConst("OD\r\n", 4, j); /*enable Thermal Direct Printer*/
        }
        j = ZLPSetBufferConst("OL\r\n", 4, j); /*enable Feed Button Direct Printer*/
        j = ZLPSetBufferConst("UN\r\n", 4, j); /*disable error report system*/
        guZLPFlags.CONFIGSTATE = STOP_SET_CONFIG;
        guZLPFlags.ZLP_Busy = 0;
        ZLPSendFirstByte(j);
        return;
    }

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPsetData >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPsetData                                                            |  
 | < @Description       : set Data                                                   | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPsetText() {
    uint8_t j;
    uint8_t size;
    uint8_t fontsize;

    char s[5];
    j = 0;


    if (guZLPFlags.TEXTSTATE == STOP_SET_DATA) {
        return;
    }
    if (guZLPFlags.TXDCOM) {
        return;
    }

    if (guZLPFlags.TEXTSTATE == START_SET_DATA_0) {
        j = ZLPSetBufferConst("A", 1, j); /*send Text Command used 1Byte*/
        size = u16TOASII(s, gu8ZLPX); /*convert  X position to text*/
        j = ZLPSetBufferConst(s, size, j); /*send position of text in X-axis used max 5 Byte */
        j = ZLPSetBufferConst(",", 1, j); /*send  Next Parameter used 1 Byte*/
        size = u16TOASII(s, gu8ZLPY); /*convert  Y position to text*/
        j = ZLPSetBufferConst(s, size, j); /*send position of text in Y-axis used max 5 Byte */
        j = ZLPSetBufferConst(",", 1, j); /*send  Next Parameter used 1 Byte*/
        j = ZLPSetBufferConst("0", 1, j); /*send  Text Rotation*/
        j = ZLPSetBufferConst(",", 1, j); /*send  Next Parameter used 1 Byte*/
        fontsize = gu8ZLPFont.FontSize;
        size = u8TOASII(s, fontsize); /*convert  X position to text*/
        j = ZLPSetBufferConst(s, size, j); /*send Text Font size From 1 - 5*/
        j = ZLPSetBufferConst(",", 1, j); /*send  Next Parameter used 1 Byte*/
        guZLPFlags.TEXTSTATE = START_SET_DATA_1; /*next Send Value*/
        ZLPSendFirstByte(j); /*start Send buffer*/
        return;
    }


    if (guZLPFlags.TEXTSTATE == START_SET_DATA_1) {
        /*send Horizontal Multiplier Parameter */
        /*send Vertical Multiplier Parameter */
        /*Send Reverse Image Parameter*/
        /*Send Reverse Start of Text Value*/
        /*used 7Byte*/
        j = ZLPSetBufferConst("1,1,N,\"", 7, j);
        if (gu8TextLength > (ZLP_COMM_BUFFER - 7)) {
            j = ZLPSetBuffer(gpu8ZLPTex, 13, j); /*send 13 Byte */
            gu8TextLength -= (ZLP_COMM_BUFFER - 7);
        } else {
            j = ZLPSetBuffer(gpu8ZLPTex, gu8TextLength, j); /*send */
            gu8TextLength = 0;
        }
        guZLPFlags.TEXTSTATE = START_SET_DATA_2; /*next Send Value*/
        ZLPSendFirstByte(j); /*start Send buffer*/
        return;
    }

    if (guZLPFlags.TEXTSTATE == START_SET_DATA_2) {
        if (gu8TextLength != 0) {
            j = ZLPSetBuffer(gpu8ZLPTex, gu8TextLength, j); /*send Re*/
            gu8TextLength = 0;
        }
        j = ZLPSetBufferConst("\"\r\n", 3, j); /*send End of Text and  End of Command*/

        guZLPFlags.TEXTSTATE = STOP_SET_DATA; /*next Send Value*/
        ZLPSendFirstByte(j); /*start Send buffer*/
        guZLPFlags.ZLP_Busy = 0;
        return;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrint >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPrint                                                                 |  
 | < @Description       : set Print Command                                                             | 
 | < @return            : void                                                                          |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPPrint() {
    uint8_t j;
    char s[3];
    uint8_t size;
    j = 0;
    if (!guZLPFlags.PRINT_STATE) {
        return;
    }

    if (guZLPFlags.TXDCOM) {
        return;
    }
    //           j = ZLPSetBufferConst("N\r\n", 3, j); /*Clear Buffer Before Send Label used 3Byte*/
    j = ZLPSetBufferConst("P1,", 3, j);
    size = u8TOASII(s, gu8NumberofCopies);
    j = ZLPSetBufferConst(s, size, j);
    j = ZLPSetBufferConst("\r\n,", 2, j);
    ZLPSendFirstByte(j); /*start Send buffer*/
    guZLPFlags.ZLP_Busy = 0;
    guZLPFlags.PRINT_STATE = 0;

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPgetTextHight >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ZLPgetTextHight                                                              |  
 | < @Description       : get Y  Of the Font    from Font Size                                         | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPgetTextHight() {
#if NUMBER_OF_DODS_PER_INCH <= _1IN_203DOTS
    if (gu8ZLPFont.FontSize < 5) {
        return ((4 * gu8ZLPFont.FontSize) + 8);
    }
    return (48);


#else
    if (gu8ZLPFont.FontSize < 5) {
        return ((8 * gu8ZLPFont.FontSize) + 12);
    }
    return (80);

#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPgetTextHight >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ZLPgetTextHight                                                              |  
 | < @Description       : get Y  Of the Font    from Font Size                                         | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPgetTextWidth() {

#if NUMBER_OF_DODS_PER_INCH <= _1IN_203DOTS
    if (gu8ZLPFont.FontSize < 5) {
        return ((2 * gu8ZLPFont.FontSize) + 6);
    }
    return (32);


#else
    if (gu8ZLPFont.FontSize < 5) {
        return ((4 * gu8ZLPFont.FontSize) + 8);
    }
    return (48);
#endif
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPISR >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPISR                                                                  |  
 | < @Description       : ZLPISR                                                                       | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPISR() {
    /*send new byte*/
    if (gu8ZLPBufferIndex < gu8ZLPBufferLength) {
        while (!Empty_BUFFER0());
        usart0PutByte(gu8ZLPBuffer[gu8ZLPBufferIndex++]);
    } else {

        guZLPFlags.TXDCOM = 0;
        gu8ZLPBufferLength = 0;
        gu8ZLPBufferIndex = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSetBuffer >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSetBuffer                                                              |  
 | < @Description       : set data Const Into Buffer                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPSetBufferConstPGM(const uint8_t *buf, uint8_t Length, uint8_t LastIndex) {
    for (uint8_t i = 0; i < Length; i++) {

        gu8ZLPBuffer[i + LastIndex] = pgm_read_byte(buf + i);
    }
    return (LastIndex + Length);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSetBufferConst >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSetBufferConst                                                              |  
 | < @Description       : set data Const Into Buffer                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPSetBufferConst(const char *buf, uint8_t Length, uint8_t LastIndex) {
    for (uint8_t i = 0; i < Length; i++) {

        gu8ZLPBuffer[i + LastIndex] = (uint8_t) buf [i];
    }
    return (LastIndex + Length);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPSetBuffer >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPSetBuffer                                                              |  
 | < @Description       : set data  Into Buffer                                                          | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t ZLPSetBuffer(uint8_t volatile *buf, uint8_t Length, uint8_t LastIndex) {
    for (uint8_t i = 0; i < Length; i++) {

        gu8ZLPBuffer[i + LastIndex] = buf[i];
    }
    return (LastIndex + Length);
}
/*
---------------------------------------------------------------------------------------------------------
|                           < ISR Function  >                                                         | 
---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPInit >                                                         |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPInit                                                                 |  
 | < @Description       : set Init Variables                                                           | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPInit() {
    gu8ZLPBufferIndex = 0;
    gu8ZLPBufferLength = 0;
    guZLPFlags.CONFIGSTATE = START_CONFIG_0;
    guZLPFlags.TEXTSTATE = STOP_SET_DATA;
    guZLPFlags.ZLP_Busy = 1;
    guZLPFlags.TXDCOM = 0;
    gu16zlpLength = 203; /*1Inch */
    gu16zlpWidth = 406; /*4Inch*/
    gu8ZLPX = 0;
    gu8ZLPY = 0;
    gu8ZLPFont.FontResulation = 12;
    gu8ZLPFont.FontSize = 4;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPDriver >                                                         |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPDriver                                                                 |  
 | < @Description       : background task                                                                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPDriver() {
    ZLPsetConfig();
    ZLPsetText();
    ZLPPrint();
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPLableLength >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPMediaType                                                              |  
 | < @Description       : Set Lable Length                                                               | 
 | < @Param Length      : lable length per Inch                                                          |                       
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPLableSize(uint8_t width, uint8_t Length) {
    /*convert Length From Inch To Dots*/
    uint16_t LengthByDodts;
    uint16_t widthByDodts;
    widthByDodts = width * NUMBER_OF_DODS_PER_INCH;
    LengthByDodts = Length * NUMBER_OF_DODS_PER_INCH;
    gu16zlpLength = LengthByDodts;
    gu16zlpWidth = widthByDodts;
    guZLPFlags.CONFIGSTATE = START_CONFIG_1;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPMediaType >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPMediaType                                                              |  
 | < @Description       : Set Media Type  direct thermal media and thermal transfer media                | 
 | < @Param Type        : 0 Direct thermal media                                                         |                       
 |                      : 1 Thermal transfer media                                                       |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPMediaType(uint8_t Type) {

    gu8ZLPFont.ThermalTransfer = Type;
    guZLPFlags.CONFIGSTATE = START_CONFIG_2;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPMediaType >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPMediaType                                                              |  
 | < @Description       : Set Media Type  direct thermal media and thermal transfer media                | 
 | < @Param Type        : 0 Direct thermal media                                                         |                       
 |                      : 1 Thermal transfer media                                                       |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPFont(uint8_t Fontsize, uint8_t FontResulation) {

    gu8ZLPFont.FontResulation = FontResulation;
    gu8ZLPFont.FontSize = Fontsize;
    guZLPFlags.CONFIGSTATE = START_CONFIG_2;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintText >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function             : void ZLPMediaType                                                           |  
 | < @Description          : Set Media Type  direct thermal media and thermal transfer media             | 
 | < @Param x              : Position  in x                                                              |                       
 | < @Param margin         : text margin in top and bottom                                               |
 | < @Param s              : Pointer to text Buffer                                                      |
 | < @Param Len            : Number of Char In Text Buffer                                               |
 | < @return               : void                                                                        |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPrintText(uint16_t x, uint8_t margin, uint8_t *s, uint8_t Len) {
    /*calucate x and Y*/
    uint16_t TextWidth;
    uint16_t Y;

    if (Len > ZLP_COMM_BUFFER) {
        return;
    }
    TextWidth = Len * ZLPgetTextWidth();
    if (gu16zlpWidth < TextWidth) {
        return;
    }

    Y = margin;
    Y += gu8ZLPY; /*save Last Y*/
    if (Y > gu16zlpLength) {
        Y = margin;
    }
    Y += margin + ZLPgetTextHight();
    gu8ZLPY = Y;
    gu8ZLPX = x;
    gpu8ZLPTex = s;
    gu8TextLength = Len;
    guZLPFlags.ZLP_Busy = 1;
    guZLPFlags.TEXTSTATE = START_SET_DATA_0;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintState >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ZLPPrintState                                                         |  
 | < @Description       : pirent state is ready To print new data or not                                | 
 | < @return            : 0 ZLP Printer is Busy                                                         |                       
 |                      : 1 ZLP Printer is Ready                                                        |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t ZLPPrintState() {
    if (guZLPFlags.ZLP_Busy) {
        return (0);
    }
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintNOW >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPrintNOW                                                               |  
 | < @Description       : Print after send Comand                                                        | 
 | < @Param Copies      : Number Of Lable Print                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPrintNOW(uint8_t LableCopies) {
    if (!LableCopies) {
        LableCopies = 1;
    }
    gu8NumberofCopies = LableCopies;
    guZLPFlags.ZLP_Busy = 1;
    guZLPFlags.PRINT_STATE = 1;
}

#endif
#endif
