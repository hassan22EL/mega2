
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


static const char zlp_config0[] PROGMEM = "I8,A,001";
static const char zlp_config1[] PROGMEM = "Q203,024";
static const char zlp_config2[] PROGMEM = "q831";
static const char zlp_config3[] PROGMEM = "rN";
#if ZLP_PRINT_RATE == _1IN_PER_SEC
static const char zlp_config4[] PROGMEM = "S1";
#elif ZLP_PRINT_RATE == _2IN_PER_SEC
static const char zlp_config4[] PROGMEM = "S2";
#elif ZLP_PRINT_RATE == _3IN_PER_SEC
static const char zlp_config4[] PROGMEM = "S3";
#elif ZLP_PRINT_RATE == _4IN_PER_SEC
static const char zlp_config4[] PROGMEM = "S4";
#endif
static const char zlp_config5[] PROGMEM = "D12";
static const char zlp_config6[] PROGMEM = "ZT";
static const char zlp_config7[] PROGMEM = "JF";
#if PRINTER_TYPE==1 
static const char zlp_config8[] PROGMEM = "OL";
#else
static const char zlp_config8[] PROGMEM = "OD";
#endif
static const char zlp_config9[] PROGMEM = "R212,0";
static const char zlp_config10[] PROGMEM = "f100";
static const char zlp_config11[] PROGMEM = "N";

static const char zlp_config12[] PROGMEM = "A   ,   , , ,1,1,N,\"";
static const char zlp_config13[] PROGMEM = "B   ,   , ,1,2,2,45,N,\"";
static const char zlp_config14[] PROGMEM = "\"\r\n";
static const char zlp_config15[] PROGMEM = "P  ,1";
PGM_P const ZlpMessages[] PROGMEM = {
    zlp_config0,
    zlp_config1,
    zlp_config2,
    zlp_config3,
    zlp_config4,
    zlp_config5,
    zlp_config6,
    zlp_config7,
    zlp_config8,
    zlp_config9,
    zlp_config10,
    zlp_config11,
    zlp_config12,
    zlp_config13,
    zlp_config14,
    zlp_config15,
};




/*
---------------------------------------------------------------------------------------------------------
|                           < Variable >                                                      | 
---------------------------------------------------------------------------------------------------------
 */
/*
 * <@var gpu8ZLPTex                               : Pointer To Text Buffer
 */
static uint8_t gu8ZLPTexbuffer[54];
/*
 *<@var gu8TextLen                                 : User Text Length
 */
static uint8_t gu8TextIndex;

/*
 *<@var gu8BARCODE_LENGTH
 */
static uint8_t gu8DataLength;


/*
 * app state
 */
static uint8_t gu8ZlpState;
static uint8_t gu8ZlpConigIndex;

/*
---------------------------------------------------------------------------------------------------------
|                           < ISR Function  >                                                         | 
---------------------------------------------------------------------------------------------------------
 */


ISR(UART0_TRANSMIT_INTERRUPT) {
    if (gu8TextIndex < gu8DataLength) {
        while (!Empty_BUFFER0());
        usart0PutByte(gu8ZLPTexbuffer[gu8TextIndex++]);
    } else {
        gu8TextIndex = 0;
        gu8DataLength = 0;
        gu8ZlpState = 0;
    }
    return;
}

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
    gu8TextIndex = 0;
    gu8DataLength = 0;
    gu8ZlpState = 0;
    gu8ZlpConigIndex = 0;
}

///*
// ---------------------------------------------------------------------------------------------------------
// |                                 < ZLPLableLength >                                                    |
// ---------------------------------------------------------------------------------------------------------
// | < @Function          : void ZLPMediaType                                                              |  
// | < @Description       : Set Lable Length                                                               | 
// | < @Param Length      : lable length per Inch                                                          |                       
// | < @return            : void                                                                           |
// ---------------------------------------------------------------------------------------------------------
// */
//void ZLPLableSize(uint8_t width, uint8_t Length) {
//    /*the dived the */
//    gu16offset = ((831 - (width * NUMBER_OF_DODS_PER_INCH)) >> 1);
//    gu16LengthByDodts = (Length * NUMBER_OF_DODS_PER_INCH);
//
//}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPMediaType >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPMediaType                                                              |  
 | < @Description       : Set Media Type  direct thermal media and thermal transfer media                | 
 | < @Param Type        : 0 Direct thermal media                                                         |                       
 |                      : 1 Thermal transfer media                                                       |
 | < @Param Resulation  : Reslation from 1-15
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPMediaType(uint8_t Type, uint8_t Resulation) {

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintState >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ZLPPrintState                                                         |  
 | < @Description       : pirent state is ready To print new data or not                                | 
 | < @return            : 1 ZLP Printer is Busy                                                         |                       
 |                      : 0 ZLP Printer is Ready                                                        |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t ZLPPrintState() {
    return gu8ZlpState;
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
    uint8_t s[2];
    gu8ZlpState = 1;
    print2d(LableCopies, s, 0);
    gu8DataLength = PrintMessage(gu8ZLPTexbuffer, 0, 15, ZlpMessages);
    copyBuff(gu8ZLPTexbuffer + 1, s, 2);
    gu8ZLPTexbuffer[gu8DataLength] = '\r';
    gu8ZLPTexbuffer[gu8DataLength + 1] = '\n';
    gu8DataLength += 2;
    while (!Empty_BUFFER0());
    usart0PutByte(gu8ZLPTexbuffer[gu8TextIndex++]);

}

/*
---------------------------------------------------------------------------------------------------------
|                                 < ZLPsetPos >                                                         |
---------------------------------------------------------------------------------------------------------
| < @Function          : void ZLPsetPos                                                                 |  
| < @Description       : set X,Y poision after send command                                             | 
| < @Param X           : Text Pos in X-Axis                                                             |
| < @Param Y           : Text Pos in Y-Axis                                                             |
| < @Param Font        : Font Size selct from '1' to '9' and a-z and A-Z                                |
| < @PAram Ration      : Select from 0 to 3 when 0 is normal , 1 is 90 and 2 = 180 , 3 =270             |
| < @Param Type        : Select From
| < @return            : void                                                                           |                                                                         |
---------------------------------------------------------------------------------------------------------
 */
void ZLPsetData(uint8_t *s, uint8_t Len, uint16_t x, uint16_t y, uint8_t Font, uint8_t Rotation, uint8_t Type) {
    uint8_t s1[5];
    uint8_t s2[5];
    gu8ZlpState = 1;
    gu8DataLength = PrintMessage(gu8ZLPTexbuffer, 0, 12 + Type, ZlpMessages);
    u16TOASII(s1, x);
    u16TOASII(s2, y);
    for (uint8_t i = 0; i < 3; i++) {
        gu8ZLPTexbuffer[i + 1] = s1[i + 2];
        gu8ZLPTexbuffer[i + 5] = s2[i + 2];
    }
    gu8ZLPTexbuffer[9] = Rotation + '0';
    if (!Type) {
        gu8ZLPTexbuffer[11] = Font;
    }
    copyBuff(gu8ZLPTexbuffer + gu8DataLength, s, Len);
    gu8DataLength += Len;
    gu8DataLength += PrintMessage(gu8ZLPTexbuffer, gu8DataLength, 14, ZlpMessages);
    while (!Empty_BUFFER0());
    usart0PutByte(gu8ZLPTexbuffer[gu8TextIndex++]);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPClearLastLable >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPClearLastLable                                                         |  
 | < @Description       : Clear last Print Before send Next Lable                                        |                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t ZLPClearLastLable() {
    if (gu8ZlpConigIndex < 12) {
        gu8ZlpState = 1;
        gu8DataLength = PrintMessage(gu8ZLPTexbuffer, 0, gu8ZlpConigIndex++, ZlpMessages);
        gu8ZLPTexbuffer[gu8DataLength] = '\r';
        gu8ZLPTexbuffer[gu8DataLength + 1] = '\n';
        gu8DataLength += 2;
        while (!Empty_BUFFER0());
        usart0PutByte(gu8ZLPTexbuffer[gu8TextIndex++]);
        return (0);
    }
    gu8ZlpConigIndex = 0;
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPirentLOGO >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPirentLOGO                                                         |  
 | < @Description       : ZLP Custome Log                                       |                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPirentLOGO(uint8_t *data, uint8_t Length) {
    gu8ZlpState = 1;
    copyBuff(gu8ZLPTexbuffer, data, Length);
    gu8DataLength = Length;
    while (!Empty_BUFFER0());
    usart0PutByte(gu8ZLPTexbuffer[gu8TextIndex++]);
}



#endif
#endif
