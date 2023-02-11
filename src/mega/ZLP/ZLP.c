
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

#define   ZLP_CONFIG_MAX_CMD          13
#if COMPILER_TYPE == GCC
static const uint8_t ZLP_CONIG_CMD[ZLP_CONFIG_MAX_CMD][12] PROGMEM = {
#elif COMPILER_TYPE == XC
static const uint8_t ZLP_CONIG_CMD[ZLP_CONFIG_MAX_CMD][12]  = {
#endif
    {8, 0, 0, 0, 'I', '8', ',', 'A', ',', '0', '0', '1'},
    {4, 0, 0, 0, '\r', '\n', '\r', '\n'},
    {8, 3, 1, 0, 'Q', ',', '0', '2', '4'},
    {4, 0, 0, 0, 'q', '8', '3', '1'},
    {2, 0, 0, 0, 'r', 'N'},
#if ZLP_PRINT_RATE == _1IN_PER_SEC
    {2, 0, 0, 0, 'S', '1'},
#elif ZLP_PRINT_RATE == _2IN_PER_SEC
    {2, 0, 0, 0, 'S', '2'},
#elif ZLP_PRINT_RATE == _3IN_PER_SEC
    {2, 0, 0, 0, 'S', '3'},
#elif ZLP_PRINT_RATE == _4IN_PER_SEC
    {2, 0, 0, 0, 'S', '4'},
#endif
    {3, 2, 1, 3, 'D'},
    {2, 0, 0, 0, 'Z', 'T'},
    {2, 0, 0, 0, 'J', 'F'},
    {2, 1, 1, 5, 'O'},
    {6, 3, 1, 6, 'R', ',', '0'},
    {4, 0, 0, 0, 'f', '1', '0', '0'},
    {1, 0, 0, 0, 'N'},
};
#define       BITMAP_ARRAY_LENGTH_BYTES        (24)
#define       BITMAP_ARRAY_LENGTH_INDEX        (41)
#if COMPILER_TYPE == GCC
const uint8_t bitmapArray [BITMAP_ARRAY_LENGTH_INDEX][BITMAP_ARRAY_LENGTH_BYTES] PROGMEM = {
#elif COMPILER_TYPE == XC
const uint8_t bitmapArray [BITMAP_ARRAY_LENGTH_INDEX][BITMAP_ARRAY_LENGTH_BYTES] = {
#endif
    {0x47, 0x57, 0x31, 0x30, 0x30, 0x2C, 0x30, 0x30, 0x38, 0x2C, 0x32, 0x31, 0x2C, 0x34, 0x36, 0x2C, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xc1, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xfe},
    {0x1f, 0xff, 0xc0, 0x00, 0x1e, 0x07, 0xff, 0x81, 0xf8, 0x00, 0x3f, 0x00, 0x00, 0xe0, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x1f, 0xf8, 0xff, 0xff, 0x80},
    {0x00, 0x1e, 0x07, 0xff, 0x01, 0xf0, 0x00, 0x1f, 0x00, 0x00, 0x70, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x7f, 0xc3, 0xff, 0xff, 0x00, 0x00, 0x7e, 0x03},
    {0xfe, 0x01, 0xe0, 0x00, 0x0f, 0x00, 0x00, 0x3c, 0x00, 0x07, 0xff, 0xff, 0xc1, 0xff, 0x0f, 0xff, 0xfe, 0x07, 0xff, 0xfe, 0x01, 0xfe, 0x01, 0xc1},
    {0xff, 0x07, 0x07, 0xfc, 0x1f, 0xe0, 0xff, 0xff, 0xff, 0x03, 0xfc, 0x3f, 0xff, 0xfe, 0x0f, 0xff, 0xfe, 0x00, 0xfc, 0x01, 0xc1, 0xff, 0x07, 0x07},
    {0xfe, 0x1f, 0xe1, 0xff, 0xff, 0xfe, 0x0f, 0xf0, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xfe, 0x00, 0xf8, 0x01, 0xc1, 0xff, 0x07, 0x07, 0xfc, 0x1f, 0xe1},
    {0xff, 0xff, 0xf8, 0x1f, 0xc3, 0xff, 0xff, 0xff, 0x00, 0x00, 0x7e, 0x00, 0x78, 0x41, 0xc1, 0xff, 0x07, 0x07, 0xf8, 0x3f, 0xe1, 0xff, 0xff, 0xe0},
    {0x7f, 0x0f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3e, 0x08, 0x30, 0xc1, 0xc0, 0x00, 0x07, 0x00, 0x00, 0x7f, 0xe1, 0xff, 0xff, 0xc1, 0xfc, 0x3f, 0xf8},
    {0x1f, 0xff, 0xc0, 0x00, 0x1e, 0x0c, 0x20, 0xc1, 0xc0, 0x00, 0x07, 0x00, 0x00, 0x7f, 0xe1, 0xff, 0xff, 0x03, 0xf8, 0x7f, 0x80, 0x0f, 0xff, 0xff},
    {0xfc, 0x1e, 0x0e, 0x01, 0xc1, 0xc0, 0x00, 0x07, 0x00, 0x00, 0x3f, 0xe1, 0xff, 0xfe, 0x07, 0xe1, 0xfc, 0x00, 0x07, 0xff, 0xff, 0xfe, 0x1e, 0x0e},
    {0x03, 0xc1, 0xc0, 0x00, 0x07, 0x07, 0xfc, 0x1f, 0xe1, 0xff, 0xfc, 0x0f, 0x83, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xfc, 0x1e, 0x0f, 0x03, 0xc1, 0xc1},
    {0xff, 0x07, 0x07, 0xfe, 0x0f, 0xe1, 0xff, 0xf8, 0x1f, 0x0f, 0xff, 0xe0, 0x00, 0x0f, 0x80, 0x00, 0x1e, 0x0f, 0x87, 0xc1, 0xc1, 0xff, 0x07, 0x07},
    {0xfe, 0x0f, 0xe1, 0xff, 0xf0, 0x3e, 0x1f, 0xff, 0xf8, 0x00, 0x0f, 0x00, 0x00, 0x3e, 0x0f, 0xff, 0xc1, 0xc1, 0xff, 0x07, 0x07, 0xfe, 0x0f, 0xe1},
    {0xff, 0xe0, 0x38, 0x3f, 0xff, 0xf8, 0x10, 0x0e, 0x00, 0x00, 0x7e, 0x0f, 0xff, 0xc1, 0xc1, 0xff, 0x07, 0x07, 0xfe, 0x0f, 0xe1, 0xff, 0xc0, 0x70},
    {0x7f, 0xff, 0xf0, 0x30, 0x0f, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xc3, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xe1, 0xff, 0x80, 0x60, 0xff, 0xff, 0xe0},
    {0x70, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xc0, 0xff, 0xff, 0xe0, 0xe0, 0x3f, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xc1, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x87, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xfe, 0x0f, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xfc, 0x3f, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0x00, 0x03, 0xf8, 0x7c, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80},
    {0x3f, 0xe1, 0xf8, 0x1f, 0xff, 0x00, 0x1c, 0x01, 0xe3, 0xfc, 0x7e, 0x30, 0x01, 0x8f, 0x00, 0x71, 0xf8, 0xe0, 0x03, 0xff, 0xff, 0xff, 0x87, 0xf0},
    {0x3f, 0xfe, 0x00, 0x38, 0x00, 0xe3, 0xfc, 0x7e, 0x38, 0x03, 0x8e, 0x00, 0x30, 0xf8, 0xc0, 0x07, 0xff, 0xff, 0xfe, 0x1f, 0xc0, 0xff, 0xfe, 0x3f},
    {0xf8, 0xfc, 0x63, 0xfc, 0x7e, 0x3f, 0x1f, 0x8c, 0x7e, 0x30, 0x78, 0x87, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x83, 0xff, 0xfe, 0x3f, 0xf8, 0xfc, 0x63},
    {0xfc, 0x7e, 0x3f, 0x1f, 0x8c, 0x7e, 0x30, 0x18, 0xc7, 0xff, 0xff, 0xff, 0xf0, 0xfe, 0x07, 0xff, 0xff, 0x00, 0x38, 0xfc, 0x63, 0xfc, 0x7e, 0x3f},
    {0x1f, 0x8c, 0x7e, 0x31, 0x08, 0xe0, 0x07, 0xff, 0xff, 0xc3, 0xfc, 0x1f, 0xff, 0xff, 0x80, 0x18, 0xfc, 0x63, 0xfc, 0x7e, 0x3f, 0x1f, 0x8c, 0x7e},
    {0x31, 0x80, 0xf0, 0x03, 0xff, 0xff, 0x0f, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0x18, 0xfc, 0x63, 0xfc, 0x7e, 0x3f, 0x1f, 0x8c, 0x7e, 0x31, 0xc0, 0xff},
    {0xe3, 0xff, 0xf8, 0x7f, 0x81, 0xff, 0xff, 0xff, 0x00, 0x38, 0x00, 0xe0, 0x06, 0x00, 0x7f, 0x1f, 0x8e, 0x00, 0x31, 0xf0, 0xe0, 0x07, 0xff, 0xe1},
    {0xff, 0x07, 0xff, 0xff, 0xfe, 0x00, 0x3c, 0x01, 0xe0, 0x07, 0x00, 0xff, 0x1f, 0x8f, 0x00, 0x71, 0xf8, 0xc0, 0x07, 0xff, 0x0f, 0xfc, 0x3f, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0D, 0x0A}
};



/*
---------------------------------------------------------------------------------------------------------
|                           < Variable >                                                      | 
---------------------------------------------------------------------------------------------------------
 */
/*
 * <@var gu8ZLPBuffer                            : uart Buffer Length
 */
static volatile uint8_t gu8ZLPVerBuffer [9];
/*
 * <@var gu8ZLPBuffer                            : uart Buffer Length
 */
static volatile uint8_t gu8ZLPDataBuffer[10];
/*
 * @var gu8ZLPBufferLength                         :uart Max send Data
 */
static volatile uint8_t gu8ZLPBufferLength;
/*
 *@var gu8ZLPBufferIndex                             : uart current Send Data
 */
static volatile uint8_t gu8ZLPBufferIndex;
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
 * <@var gpFunZlP                                  : Current Execution 
 */
static volatile pFunc_t gpFunZlP;
/*
 *<@var gu8BARCODE_LENGTH
 */
static volatile uint8_t gu8DataLength;
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
 |                                 < ZLPsetText >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPsetText                                                            |  
 | < @Description       : set ZLPsetText                                                   | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPsetText();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPsetText >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPsetText                                                            |  
 | < @Description       : set ZLPsetText                                                   | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPsetText();

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintG >                                                         |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPrintG                                                                 |  
 | < @Description       : Print Stored Images By Printers                                                |                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPPrintG();
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
|                           < ISR Function  >                                                         | 
---------------------------------------------------------------------------------------------------------
 */



ISR(UART0_TRANSMIT_INTERRUPT) {
    if (gpFunZlP != NULL) {
        gpFunZlP();
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
    if (gu8ZLPBufferIndex == 0) {
        usart0PutByte('P');
    } else if (gu8ZLPBufferIndex == 1) {
        usart0PutByte(gu8NumberofCopies);
    } else if (gu8ZLPBufferIndex == 2) {
        usart0PutByte(',');
    } else if (gu8ZLPBufferIndex == 3) {
        usart0PutByte('1');
    } else if (gu8ZLPBufferIndex == 4) {
        usart0PutByte('\r');
    } else if (gu8ZLPBufferIndex == 5) {
        usart0PutByte('\n');
        gu8ZLPBufferIndex = 0;
        gu8ZLPBufferLength = 0;
        gpFunZlP = NULL;
        return;
    }
    gu8ZLPBufferIndex++;
    return;
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

    /*send array*/
    uint8_t maxFL;
    uint8_t maxVL;
    uint8_t startV;
    uint8_t IndexV;


    if (gu8ZLPBufferLength < ZLP_CONFIG_MAX_CMD) {
#if COMPILER_TYPE == GCC
        maxFL = pgm_read_byte(&ZLP_CONIG_CMD[gu8ZLPBufferLength][0]);
        maxVL = pgm_read_byte(&ZLP_CONIG_CMD[gu8ZLPBufferLength][1]);
        startV = pgm_read_byte(&ZLP_CONIG_CMD[gu8ZLPBufferLength][2]);
        IndexV = pgm_read_byte(&ZLP_CONIG_CMD[gu8ZLPBufferLength][3]);
#elif COMPILER_TYPE == XC
        maxFL = (ZLP_CONIG_CMD[gu8ZLPBufferLength][0]);
        maxVL = (ZLP_CONIG_CMD[gu8ZLPBufferLength][1]);
        startV = (ZLP_CONIG_CMD[gu8ZLPBufferLength][2]);
        IndexV = (ZLP_CONIG_CMD[gu8ZLPBufferLength][3]);
#endif
        if (gu8ZLPBufferIndex < maxFL) {
            /*condition value*/
            if ((gu8ZLPBufferIndex == startV) && (startV != 0)) {
                if ((gu8TextLength < maxVL)) {
                    usart0PutByte(gu8ZLPVerBuffer[IndexV + gu8TextLength]);
                    gu8TextLength++;
                } else {
                    gu8TextLength = 0;
#if COMPILER_TYPE == GCC
                    usart0PutByte(pgm_read_byte(&ZLP_CONIG_CMD[gu8ZLPBufferLength][gu8ZLPBufferIndex + 4])); /**/
#elif COMPILER_TYPE == XC
                    usart0PutByte((ZLP_CONIG_CMD[gu8ZLPBufferLength][gu8ZLPBufferIndex + 4])); /**/
#endif
                    gu8ZLPBufferIndex++;
                }
                return;
            }
#if COMPILER_TYPE == GCC
            usart0PutByte(pgm_read_byte(&ZLP_CONIG_CMD[gu8ZLPBufferLength][gu8ZLPBufferIndex + 4]));
#elif COMPILER_TYPE == XC
            usart0PutByte((ZLP_CONIG_CMD[gu8ZLPBufferLength][gu8ZLPBufferIndex + 4]));
#endif
            gu8ZLPBufferIndex++;
            return;
        }




        if (gu8ZLPBufferIndex == maxFL) {
            usart0PutByte('\r');
            gu8ZLPBufferIndex++;
            return;
        }

        if (gu8ZLPBufferIndex > maxFL) {
            usart0PutByte('\n');
            gu8ZLPBufferIndex = 0;
            gu8ZLPBufferLength++;
            return;
        }
    }

    gpFunZlP = NULL;
    gu8ZLPBufferLength = 0;
    gu8ZLPBufferIndex = 0;
    gu8TextLength = 0;
    return;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintG >                                                         |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPrintG                                                                 |  
 | < @Description       : Print Stored Images By Printers                                                |                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPPrintG() {

    if (gu8ZLPBufferIndex >= BITMAP_ARRAY_LENGTH_BYTES) {
        gu8ZLPBufferLength++;
        gu8ZLPBufferIndex = 0;
    }
    /*send Log*/
    if (gu8ZLPBufferLength >= BITMAP_ARRAY_LENGTH_INDEX) {
        gu8ZLPBufferIndex = 0;
        gu8ZLPBufferLength = 0;
        gpFunZlP = NULL;
        return;
    }
#if COMPILER_TYPE == GCC
    usart0PutByte(pgm_read_byte(&bitmapArray[gu8ZLPBufferLength][gu8ZLPBufferIndex]));
#elif COMPILER_TYPE == XC
    usart0PutByte(bitmapArray[gu8ZLPBufferLength][gu8ZLPBufferIndex]);
#endif
    gu8ZLPBufferIndex++;

    return;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPsetText >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPsetText                                                            |  
 | < @Description       : set ZLPsetText                                                   | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ZLPsetText() {
    uint8_t index;
    index = 0;
    if (gu8ZLPBufferIndex >= gu8ZLPBufferLength) {
        usart0PutByte('\n');
        gpFunZlP = NULL;
        gu8ZLPBufferLength = 0;
        gu8ZLPBufferIndex = 0;
        gu8TextLength = 0;
        return;
    }




    if (gu8ZLPBufferIndex == gu8ZLPBufferLength - 1) {
        usart0PutByte('\r');
        gu8ZLPBufferIndex++;
        return;
    }

    if (gu8ZLPBufferIndex == gu8ZLPBufferLength - 2) {
        usart0PutByte('\"');
        gu8ZLPBufferIndex++;
        return;
    }


    if (gu8ZLPBufferIndex >= gu8DataLength) {
        usart0PutByte(gpu8ZLPTex[gu8ZLPBufferIndex - gu8DataLength]);
        gu8ZLPBufferIndex++;
        gu8TextLength++;
        return;
    }



    if (gu8ZLPBufferIndex < gu8DataLength && gu8ZLPBufferIndex >= 17) {
        gu8TextLength = 0;
        index = gu8ZLPBufferIndex - 17; /*18,19,20   = 0,1,2,3  , 18,19,20,21,22 = 0,1,2,3,4*/
        if (gu8ZLPDataBuffer[0] == 'A') {
            if (index == 0) {
                usart0PutByte('N');
            } else if (index == 1) {
                usart0PutByte(',');
            } else if (index == 2) {
                usart0PutByte('\"');
            }
        } else if (gu8ZLPDataBuffer[0] == 'B' && index < 6) {
            if (index == 0) {
                usart0PutByte('4');
            } else if (index == 1) {
                usart0PutByte('0');
            } else if (index == 2) {
                usart0PutByte(',');
            } else if (index == 3) {
                usart0PutByte('N');
            } else if (index == 4) {
                usart0PutByte(',');
            } else if (index == 5) {
                usart0PutByte('\"');
            }
        }
        gu8ZLPBufferIndex++;
        return;
    }
    if (gu8ZLPBufferIndex == 13) {
        usart0PutByte('1');
    } else if ((gu8ZLPBufferIndex != 0) && (gu8ZLPBufferIndex != 2) && (gu8ZLPBufferIndex != 6) && (!(gu8ZLPBufferIndex & 0x01))) {
        usart0PutByte(',');
    } else {

        usart0PutByte(gu8ZLPDataBuffer[gu8TextLength++]);
    }
    gu8ZLPBufferIndex++;
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

    gu8ZLPBufferIndex = 0;
    gu8ZLPBufferLength = 0;
    gu8TextLength = 0;
    gpFunZlP = NULL;
    ZLPLableSize(2, 1);
    ZLPMediaType(0, 12);
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

    /*the max width is 4.09 inch = 831 dot */
    uint16_t LengthByDodts;
    uint16_t offset;
    uint8_t s[5];
    /*the dived the */
    offset = ((831 - (width * NUMBER_OF_DODS_PER_INCH)) >> 1);
    LengthByDodts = (Length * NUMBER_OF_DODS_PER_INCH);
    u16TOASII(s, LengthByDodts); /*0,1,2*/
    gu8ZLPVerBuffer[0] = s[2];
    gu8ZLPVerBuffer[1] = s[3];
    gu8ZLPVerBuffer[2] = s[4];
    u16TOASII(s, offset); /*6,7,8*/
    gu8ZLPVerBuffer[6] = s[2];
    gu8ZLPVerBuffer[7] = s[3];
    gu8ZLPVerBuffer[8] = s[4];
}

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
    uint8_t s[3];
    u8TOASII(s, Resulation);
    gu8ZLPVerBuffer[3] = s[1];
    gu8ZLPVerBuffer[4] = s[2];
    if (Type) {
        gu8ZLPVerBuffer[5] = 'L';
    } else {

        gu8ZLPVerBuffer[5] = 'D';
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintText >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function             : void ZLPMediaType                                                           |  
 | < @Description          : Set Media Type  direct thermal media and thermal transfer media             | 
 | < @Param s              : Pointer to text Buffer                                                      |
 | < @Param Len            : Number of Char In Text Buffer                                               |
 | < @return               : void                                                                        |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPrintText(uint8_t *s, uint8_t Len) {
    /*calucate x and Y*/
    gpu8ZLPTex = s;
    gu8ZLPBufferLength = (Len + gu8DataLength + 2); /*10B+2B+7B+2B*/
    gu8ZLPBufferIndex = 0;
    gu8TextLength = 0;
    gpFunZlP = ZLPsetText;

    while (!Empty_BUFFER0());
    usart0PutByte('\n');
    /*set Print Text Call Back*/
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
    if (gpFunZlP != NULL) {

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

        LableCopies = 1 + '0';
    }
    gu8ZLPBufferIndex = 0;
    gu8TextLength = 0;
    gu8ZLPBufferLength = 5;
    gu8NumberofCopies = LableCopies + '0';
    gpFunZlP = ZLPPrint;

    while (!Empty_BUFFER0());
    usart0PutByte('\n');

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
void ZLPsetData(uint16_t x, uint16_t y, uint8_t Font, uint8_t Rotation, uint8_t Type) {
    /*Set Into Buffer*/
    uint8_t s[5];
    if (Type == ZLP_BAR) {
        gu8ZLPDataBuffer[0] = 'B';
        gu8ZLPDataBuffer[8] = '3';
        gu8ZLPDataBuffer[9] = '3';
        gu8DataLength = 23;
    } else {

        gu8DataLength = 20;
        gu8ZLPDataBuffer[0] = 'A';
        gu8ZLPDataBuffer[8] = Font;
        gu8ZLPDataBuffer[9] = '1';
    }
    gu8ZLPDataBuffer[7] = (Rotation + '0');
    u16TOASII(s, x);
    gu8ZLPDataBuffer[1] = s[2];
    gu8ZLPDataBuffer[2] = s[3];
    gu8ZLPDataBuffer[3] = s[4];
    u16TOASII(s, y);
    gu8ZLPDataBuffer[4] = s[2];
    gu8ZLPDataBuffer[5] = s[3];
    gu8ZLPDataBuffer[6] = s[4];
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
void ZLPClearLastLable() {
    gpFunZlP = ZLPsetConfig;

    while (!Empty_BUFFER0());
    usart0PutByte('\n');
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
void ZLPPirentLOGO() {
    gpFunZlP = ZLPPrintG;
    while (!Empty_BUFFER0());
    usart0PutByte('\n');
}





#endif
#endif
