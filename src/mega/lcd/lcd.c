
/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : lcd.c                                                             |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : https://www.sparkfun.com/datasheets/LCD/HD44780.pdf               |
| < SRAM USAGE               : 36-Byte  (32 Byte buffer , 4 byte internal used                   |
| < PROGRAM USAGE            : 1010 Byte (950 byte (475 Instruction)) + 30 Byte custom char      |                                    
| < Hardware Usage           : GPIO                                                              |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */


#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if defined (LCD_MODULE)
#if  LCD_MODULE 

/*
 -------------------------------------------------------------------------------------------------------
 |                               < Macro  Definition >                                                 |
 -------------------------------------------------------------------------------------------------------
 */

/*
 -------------------------------------------------------------------------------------------------------
 |                               <LCD  Buffer Size>                                                    |
 -------------------------------------------------------------------------------------------------------
 */
#define  LCD_SIZE              (LCD_NUMBER_OF_BYTE * LCD_NUMBER_OF_LINE)
/*
 -------------------------------------------------------------------------------------------------------
 |                               <  LCD option flags  >                                                |
 -------------------------------------------------------------------------------------------------------
 | < macro  LCD_BLINK      : bit 0 is this bit 1 enable blink or 0 disable blink                       |        
 | < macro  LCD_CUSOR      : bit 1 is this bit 1 enable cursor or 0 disable cursor                     |
 | < macro  LCD_DISPLAY    : bit 2 is this bit 1 enable display or 0 disable display                   |
 -------------------------------------------------------------------------------------------------------
 */
#define   LCD_BLINK           (0)
#define   LCD_CUSOR           (1)
#define   LCD_DISPLAY         (2)


/*
 -------------------------------------------------------------------------------------------------------
 |                               < LCD  MODES  >                                                       |
 -------------------------------------------------------------------------------------------------------
 | < macro  LCD_8BIT_MODE      : lcd work with 8 bit data                                              |        
 | < macro  LCD_4BIT_MODE      : lcd work with 4 bit data                                              |
 | < macro  LCD_NONINTERACTIVE : lcd read not active                                                   |
 | < macro  LCD_INTERAVTIVE    : lcd read active                                                       |
 -------------------------------------------------------------------------------------------------------
 
 */

#define  LCD_8BIT_MODE        (0x01)
#define  LCD_4BIT_MODE        (0x02)
#define  LCD_NONINTERACTIVE   (0x03)
#define  LCD_INTERAVTIVE      (0x04)


/*
 -------------------------------------------------------------------------------------------------------
 |                               < LCD  Commands>                                                      |
 -------------------------------------------------------------------------------------------------------
 */
/*
 -------------------------------------------------------------------------------------------------------
 |                               < LCD 8Bit Commands>                                                  |
 -------------------------------------------------------------------------------------------------------
 | < macro  LCD_8BIT_COMMAND            : lcd work with 8 bit data command                             |        
 | < macro  LCD_8BIT_2LINE_COMMAND      : set number of line 2 and font 5*10 dot                       |
 ------------------------------------------------------------------------------------------------------- 
 */

#define LCD_8BIT_COMMAND                (0x30)
#define LCD_8BIT_2LINE_COMMAND          (0x38)   

/*
 -------------------------------------------------------------------------------------------------------
 |                               < LCD 4Bit Commands>                                                  |
 -------------------------------------------------------------------------------------------------------
 | < macro  LCD_4BIT_COMMAND       : lcd work with 4 bit data command                                  |        
 | < macro  LCD_2LINE_COMMAND      : set number of line 2 and font 5*10 dot                            |
 ------------------------------------------------------------------------------------------------------- 
 */
#define LCD_4BIT_COMMAND           (0x20) 
#define LCD_2LINE_COMMAND          (0x28)   /*000101100*/

/*
 -------------------------------------------------------------------------------------------------------
 |                               <LCD Display Commands >                                               |
 -------------------------------------------------------------------------------------------------------
 | < macro  LCD_DISPLAY_ON_COMMAND       : display on command                                          |        
 | < macro  LCD_DISPLAY_OFF_COMMAND      : display off command                                         |
 | < macro  LCD_CLEAR_COMMAND            : lcd clear                                                   |
 | < macro  LCD_ENTRY_SET                : lcd entery set data                                         |
 ------------------------------------------------------------------------------------------------------- 
 */


#define LCD_DISPLAY_ON_COMMAND     (0x0C)  /*display ON  */
#define LCD_DISPLAY_OFF_COMMAND    (0x08)  /*display off*/
#define LCD_CLEAR_COMMAND          (0x01)   /*clear data*/
#define LCD_ENTRY_SET              (0x06)   

/*
 -------------------------------------------------------------------------------------------------------
 |                               <LCD CGRMA Commands >                                                 |
 -------------------------------------------------------------------------------------------------------
 | < macro  LCD_CGRAM_ADDRESS_CHECK       : check lcd is ready or not if not ready automatic re- init  |                                         
 | < macro  LCD_CGRRAM_MODE               : write data into cgram                                      |
 | < macro  LCD_DDRAM_MODE                : write data into ddram                                      |
 ------------------------------------------------------------------------------------------------------- 
 */

#define  LCD_CGRAM_ADDRESS_CHECK   (0x7F) /*last char in cgram*/
#define  LCD_CGRRAM_MODE           (0x40)
#define  LCD_DDRAM_MODE            (0x80)


/*
 -------------------------------------------------------------------------------------------------------
 |                               <LCD State>                                                           |
 -------------------------------------------------------------------------------------------------------
 | < macro  LCD_IN_PROGRESS  : lcd internal operation                                                  |
 | < macro  LCD_ERORR        : lcd hardware not ready                                                  |
 | < macro  LCD_SUCCSS       : lcd is done                                                             |
 -------------------------------------------------------------------------------------------------------
 */

#define LCD_IN_PROGRESS  0x02
#define LCD_ERORR        0x01
#define LCD_SUCCSS       0x00

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < LCD Variables >                                                    |
 --------------------------------------------------------------------------------------------------------
 */
/*
 * < @var  gu8LcdOPtion         : enable or disable cursor ,enable or disable blink, display on or off  
 */
static volatile uint8_t gu8LcdOPtion;
/* 
 * < @var  gu8LcdBufferIndex    : LCD buffer index at write data into lcd                               
 */
static volatile uint8_t gu8LcdBufferIndex;
/*
 * < @var  gu8LCDFlags          : LCD State 
 */
static volatile byte_Flags_t gu8LCDFlags;
/*
 * < @var gu8LCDPosition : indicator cursor position and blank position when update lcd |
 */
static volatile uint8_t gu8LCDPosition;
/*
 --------------------------------------------------------------------------------------------------------
 |                              < LCD Buffer >                                                          |
 --------------------------------------------------------------------------------------------------------
 */
/*
 *  < @LCD Size   : LCD number of line * lcd number of char per line
 */
static uint8_t gu8LCDBuffer[LCD_SIZE] = {' '};
/*
--------------------------------------------------------------------------------------------------------
|                                 <  custome char tables >                                             |
--------------------------------------------------------------------------------------------------------
 */
#if LCD_CUSTOM_CHAR_EN
#if COMPILER_TYPE == GCC
static const PROGMEM uint8_t CGRAM_ZERO[] = {
#elif COMPILER_TYPE == XC
static const uint8_t CGRAM_ZERO[] = {
#endif
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111
};
#if COMPILER_TYPE == GCC
static const PROGMEM uint8_t CGRAM_ONE[] = {
#elif COMPILER_TYPE == XC
static const uint8_t CGRAM_ONE[] = {
#endif
    0b11111,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b11111
};
#if COMPILER_TYPE == GCC
static const PROGMEM uint8_t CGRAM_TWO[] = {
#elif COMPILER_TYPE == XC
static const uint8_t CGRAM_TWO[] = {
#endif

    0b11111,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11111
};
#if COMPILER_TYPE == GCC
static const PROGMEM uint8_t CGRAM_THREE[] = {
#elif COMPILER_TYPE == XC
static const uint8_t CGRAM_THREE[] = {
#endif
    0b11111,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11111
};
#if COMPILER_TYPE == GCC
static const PROGMEM uint8_t CGRAM_FOUR[] = {
#elif COMPILER_TYPE == XC
static const uint8_t CGRAM_FOUR[] = {
#endif
    0b11111,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11111
};
#if COMPILER_TYPE == GCC
static const PROGMEM uint8_t CGRAM_FIVE[] = {
#elif COMPILER_TYPE == XC
static const uint8_t CGRAM_FIVE[] = {
#endif
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Basic Function Definition >                                        |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Pulse_En >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  Pulse_En                                                                |
 | < @Description       : pulse to write any data in lcd                                                |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void Pulse_En();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdPosToAddress >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdPosToAddress                                                       |
 | < @Description       : convert line number and position to lcd ram address to read or write          |
 | < @Param line        : specific line x and x from 0 to max line per lcd                              |
 | < @Param u8pos       : specific char (y) in line and                                                 |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t lcdPosToAddress(uint8_t u8line, uint8_t u8pos);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdInit >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdInit                                                               |
 | < @Description       : write command to init in 4 bit mode or 8 bit mode or clear ,........etc       |                                                         
 | < @return            : 0   init done                                                                 |
 | < @return            : 1   in progress                                                               |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t lcdInit();

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdUpdate >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdUpdate                                                             |
 | < @Description       : write data from lcd buffer and commands required do this                      |                                                         
 | < @return            : LCD_ERORR when lcd is not ready                                               |                    
 | < @return            : LCD_SUCCSS when lcd is write buffer done                                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t lcdUpdate();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdWaitBusy >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdWaitBusy                                                             |
 | < @Description       : check lcd is busy by read two nibble of the lcd the last bit in high nibble   |
 |                      : is state  of the lcd when high the lcd is busy else lcd ready                 |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdWaitBusy();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSendByte >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdSendByte                                                             |
 | < @Description       : write data into lcd with RS is enable high                                    |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSendByte(uint8_t u8Byte);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSendCommand >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdSendCommand                                                          |
 | < @Description       : write command into lcd with RS is enable low                                  |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSendCommand(uint8_t u8Cmd);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSend >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdSend                                                                 |
 | < @Description       : write data into lcd no rs is active this                                      |
 |                       : Function share with write command and data                                   |                      
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSend(uint8_t u8Data);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdReadByte >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdReadByte                                                           |
 | < @Description       : write byte frome lcd                                                          |                                           
 | < @return            : read byte                                                                     |                                                             
 --------------------------------------------------------------------------------------------------------
 */
#if __DEPUG_BY_PROUTES == 0
static uint8_t lcdReadByte();
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSendCommdHigh >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdSendCommdHigh                                                         |
 | < @Description       : just write high nibble of the byte command                                    |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSendCommdHigh(uint8_t u8Data);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < setlcdInputPin >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  setlcdInputPin                                                          |
 | < @Description       : set lcd is input and active Read Operation                                    |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void setlcdInputPin();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < setlcdOutPin >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  setlcdOutPin                                                             |
 | < @Description       : set lcd pin as out with active write Operation                                   |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void setlcdOutPin();
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Basic Function Implementions >                                     |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < Pulse_En >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  Pulse_En                                                                |
 | < @Description       : pulse to write any data in lcd                                                |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */

static void Pulse_En() __attribute__((unused));

static void Pulse_En() {
    digitalPinWrite(LCD_EN, GPIO_HIGH);
    _delay_us(1);
    digitalPinWrite(LCD_EN, GPIO_LOW);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdPosToAddress >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdPosToAddress                                                       |
 | < @Description       : convert line number and position to lcd ram address to read or write          |
 | < @Param line        : specific line x and x from 0 to max line per lcd                              |
 | < @Param u8pos       : specific char (y) in line and                                                 |                   
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t lcdPosToAddress(uint8_t u8line, uint8_t u8pos) __attribute__((unused));

static uint8_t lcdPosToAddress(uint8_t u8line, uint8_t u8pos) {
    uint8_t u8Address;
    u8pos &= 0x3F;
    u8line &= 0x03;
#if LCD_NUMBER_OF_LINE == 4
    if (u8line == 3) {
        u8Address = ((LCD_LINE3_START + (LCD_NUMBER_OF_BYTE)) + u8pos);
    } else if (u8line == 2) {
        u8Address = ((LCD_LINE2_START + (LCD_NUMBER_OF_BYTE)) + u8pos);
    } else if (u8line == 1) {
        u8Address = ((LCD_LINE1_START) + u8pos);
    } else {
        u8Address = ((LCD_LINE0_START) + u8pos);
    }
#elif LCD_NUMBER_OF_LINE == 3
    if (u8line == 2) {
        u8Address = ((LCD_LINE2_START + (LCD_NUMBER_OF_BYTE)) + u8pos);
    } else if (u8line == 1) {
        u8Address = ((LCD_LINE1_START) + u8pos);
    } else {
        u8Address = ((LCD_LINE0_START) + u8pos);
    }
#elif LCD_NUMBER_OF_LINE == 2
    if (u8line == 1) {
        u8Address = ((LCD_LINE1_START) + u8pos);
    } else {
        u8Address = ((LCD_LINE0_START) + u8pos);
    }
#else 
    u8Address = ((LCD_LINE0_START) + u8pos);
#endif
    return (u8Address);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < setlcdInputPin >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  setlcdInputPin                                                          |
 | < @Description       : set lcd is input and active Read Operation                                    |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void setlcdInputPin() {
    digitalpinMode(LCD_D4, MODE_INPUT); /* 600ns*/
    digitalpinMode(LCD_D5, MODE_INPUT); /*600ns*/
    digitalpinMode(LCD_D6, MODE_INPUT); /*600ns*/
    digitalpinMode(LCD_D7, MODE_INPUT); /*600ns*/
    digitalPinWrite(LCD_RS, GPIO_LOW); //RS=0; /*600ns*/
    digitalPinWrite(LCD_RW, GPIO_HIGH); //RW=1 /*600ns*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < setlcdOutPin >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  setlcdOutPin                                                             |
 | < @Description       : set lcd pin as out with active write Operation                                   |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void setlcdOutPin() {
    digitalpinMode(LCD_D4, MODE_OUTPUT);
    digitalpinMode(LCD_D5, MODE_OUTPUT);
    digitalpinMode(LCD_D6, MODE_OUTPUT);
    digitalpinMode(LCD_D7, MODE_OUTPUT);
    digitalPinWrite(LCD_RW, GPIO_LOW);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdWaitBusy >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdWaitBusy                                                             |
 | < @Description       : check lcd is busy by read two nibble of the lcd the last bit in high nibble   |
 |                      : is state  of the lcd when high the lcd is busy else lcd ready                 |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdWaitBusy() {
    uint8_t state;
    state = 0;
    uint16_t timeout;
    setlcdInputPin();
    timeout = microsecondsToClockCycles(100);
    do {
        digitalPinWrite(LCD_EN, GPIO_HIGH);
        _NOP();
        timeout--;
        state = digitalPinRead(LCD_D7);
        digitalPinWrite(LCD_EN, GPIO_LOW);
        Pulse_En();
    } while (state && timeout);
    if (!timeout) {
        gu8LCDFlags.b7 = 1;
    }
    setlcdOutPin();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSendByte >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdSendByte                                                             |
 | < @Description       : write data into lcd with RS is enable high                                    |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSendByte(uint8_t u8Byte) {
    lcdWaitBusy();
    digitalPinWrite(LCD_RS, GPIO_HIGH);
    lcdSend(u8Byte);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSendCommand >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdSendCommand                                                          |
 | < @Description       : write command into lcd with RS is enable low                                  |                     
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSendCommand(uint8_t u8Cmd) {
    lcdWaitBusy();
    digitalPinWrite(LCD_RS, GPIO_LOW);
    lcdSend(u8Cmd);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSend >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  lcdSend                                                                 |
 | < @Description       : write data into lcd no rs is active this                                      |
                        : Function share with write command and data                                    |                      
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSend(uint8_t u8Data) {
    /*total time 8u = 800ns *4 + 1300ns  + 800ns *4 + 1300ns = 8000ns = */
    digitalPinWrite(LCD_D4, BitCheck(u8Data, 4)); /*800ns = 600ns write + 200ns bit check*/
    digitalPinWrite(LCD_D5, BitCheck(u8Data, 5)); /*800ns = 600ns write + 200ns bit check*/
    digitalPinWrite(LCD_D6, BitCheck(u8Data, 6)); /*800ns = 600ns write + 200ns bit check*/
    digitalPinWrite(LCD_D7, BitCheck(u8Data, 7)); /*800ns = 600ns write + 200ns bit check*/
    Pulse_En(); /*1300 ns*/
    digitalPinWrite(LCD_D4, BitCheck(u8Data, 0)); /*800ns = 600ns write + 200ns bit check*/
    digitalPinWrite(LCD_D5, BitCheck(u8Data, 1)); /*800ns = 600ns write + 200ns bit check*/
    digitalPinWrite(LCD_D6, BitCheck(u8Data, 2)); /*800ns = 600ns write + 200ns bit check*/
    digitalPinWrite(LCD_D7, BitCheck(u8Data, 3)); /*800ns = 600ns write + 200ns bit check*/
    Pulse_En(); /*1300ns*/
}
#if __DEPUG_BY_PROUTES == 0

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdReadByte >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdReadByte                                                           |
 | < @Description       : write byte frome lcd                                                          |                                           
 | < @return            : read byte                                                                     |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t lcdReadByte() {
    uint8_t u8Byte;
    u8Byte = 0;
    lcdWaitBusy();
    setlcdInputPin();
    digitalPinWrite(LCD_EN, GPIO_HIGH);
    if (digitalPinRead(LCD_D4))
        u8Byte |= 0x10;
    if (digitalPinRead(LCD_D5))
        u8Byte |= 0x20;
    if (digitalPinRead(LCD_D6))
        u8Byte |= 0x40;
    digitalPinWrite(LCD_EN, GPIO_LOW);
    digitalPinWrite(LCD_EN, GPIO_HIGH);
    if (digitalPinRead(LCD_D4))
        u8Byte |= 0x01;
    if (digitalPinRead(LCD_D5))
        u8Byte |= 0x02;
    if (digitalPinRead(LCD_D6))
        u8Byte |= 0x04;
    if (digitalPinRead(LCD_D7))
        u8Byte |= 0x08;
    setlcdOutPin();
    return (u8Byte);
}
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdSendCommdHigh >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdSendCommdHigh                                                         |
 | < @Description       : just write high nibble of the byte command                                    |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static void lcdSendCommdHigh(uint8_t u8Data) {
    digitalPinWrite(LCD_RS, GPIO_LOW);
    digitalPinWrite(LCD_D4, BitCheck(u8Data, 4));
    digitalPinWrite(LCD_D5, BitCheck(u8Data, 5));
    digitalPinWrite(LCD_D6, BitCheck(u8Data, 6));
    digitalPinWrite(LCD_D7, BitCheck(u8Data, 7));
    Pulse_En();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdUpdate >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdUpdate                                                             |
 | < @Description       : write data from lcd buffer and commands required do this                      |                                                         
 | < @return            : LCD_ERORR when lcd is not ready                                               |                    
 | < @return            : LCD_SUCCSS when lcd is write buffer done                                      |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t lcdUpdate() {
#if __DEPUG_BY_PROUTES == 0
    if (!gu8LCDFlags.b1) {
        lcdSendCommand(LCD_CGRAM_ADDRESS_CHECK);
        if ((lcdReadByte()) != (LCD_CGRAM_ADDRESS_CHECK)) {
            if (lcdInit() == LCD_ERORR) {
                /*call back error*/
                gu8LCDFlags.b1 = 0;
                return LCD_ERORR;
            } else {
                digitalPinWrite(LCD_BL, GPIO_HIGH);
                gu8LCDFlags.b1 = 1;
            }
        } else {
            gu8LCDFlags.b1 = 1;
        }
    }
#endif
    if (gu8LcdBufferIndex < LCD_SIZE) {
        if (gu8LcdBufferIndex % LCD_NUMBER_OF_BYTE == 0) {
            lcdSendCommand(lcdPosToAddress((gu8LcdBufferIndex / LCD_NUMBER_OF_BYTE), 0));
        }
        lcdSendByte(gu8LCDBuffer[gu8LcdBufferIndex]);
        if (gu8LCDFlags.b7) {
            /*generate error */
            gu8LCDFlags.b1 = 0;
            gu8LCDFlags.b7 = 0;
            return LCD_ERORR;
        }
        gu8LcdBufferIndex++;
    } else {
        gu8LCDFlags.b1 = 0;
        gu8LcdBufferIndex = 0;
        lcdSendCommand(gu8LCDPosition);
        lcdSendCommand(LCD_DISPLAY_ON_COMMAND | gu8LcdOPtion);
        return (LCD_SUCCSS);
    }
    return LCD_IN_PROGRESS;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdInit >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdInit                                                               |
 | < @Description       : write command to init in 4 bit mode or 8 bit mode or clear ,........etc       |                                                         
 | < @return            : LCD_SUCESS   init done                                                        |
 | < @return            : LCD_ERROR    LCD not ready                                                    |
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t lcdInit() {
    digitalPinWrite(LCD_BL, GPIO_LOW);
    gu8LcdOPtion = LCD_DISPLAY_ON_COMMAND; /*the display on*/
    gu8LCDPosition = 0;
    gu8LcdBufferIndex = 0;
    _delay_ms(15);
    lcdSendCommdHigh(LCD_8BIT_COMMAND);
    _delay_ms(5);
    lcdSendCommdHigh(LCD_8BIT_COMMAND);
    _delay_us(100);
    lcdSendCommdHigh(LCD_8BIT_COMMAND);
    _delay_us(40);
    lcdSendCommdHigh(LCD_4BIT_COMMAND);
    _delay_us(40);
    lcdSendCommand(LCD_2LINE_COMMAND);
    lcdSendCommand(LCD_DISPLAY_ON_COMMAND);
    lcdSendCommand(LCD_CLEAR_COMMAND);
    lcdSendCommand(LCD_ENTRY_SET);
    if (gu8LCDFlags.b7) {
        gu8LCDFlags.b7 = 0;
        return LCD_ERORR;
    }
#if LCD_CUSTOM_CHAR_EN
    lcdCreateChar(0, CGRAM_ZERO);
    lcdCreateChar(1, CGRAM_ONE);
    lcdCreateChar(2, CGRAM_TWO);
    lcdCreateChar(3, CGRAM_THREE);
    lcdCreateChar(4, CGRAM_FOUR);
    lcdCreateChar(5, CGRAM_FIVE);
#endif
    return LCD_SUCCSS;
}


/*
--------------------------------------------------------------------------------------------------------
|                           < User Functions >                                                         | 
--------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdNoBlink  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdNoBlink                                                               |
 | < @Description       : lcd stop blink                                                                |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdNoBlink() {
    bitClear(gu8LcdOPtion, LCD_BLINK);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdBlink  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdBlink                                                                 |
 | < @Description       : lcd enable blink in position x ,y                                             |
 | < @Param u8line      : enable blink in specific line x and x from 0 to max line per lcd              |
 | < @Param u8pos       : enable blink in specific char (y) in line and                                 |
 |                      : y is 0 to max number of byte per line                                         |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

void lcdBlink(uint8_t u8line, uint8_t u8pos) {
    gu8LCDPosition = lcdPosToAddress(u8line, u8pos);
    bitSet(gu8LcdOPtion, LCD_BLINK);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdNoCursor  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdNoCursor                                                              |
 | < @Description       : lcd stop cursor                                                               |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
inline void lcdNoCursor() {
    bitClear(gu8LcdOPtion, LCD_CUSOR);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdCursor  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdCursor                                                                |
 | < @Description       : lcd enable blink in position x ,y                                             |
 | < @Param  u8line     : enable cursor in specific line x and x from 0 to max line per lcd             |
 | < @Param  u8Pos      : enable cursor in specific char (y) in line and                                |
 |                      : y is 0 to max number of byte per line                                         |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

inline void lcdCursor(uint8_t u8line, uint8_t u8pos) {
    gu8LCDPosition = lcdPosToAddress(u8line, u8pos);
    bitSet(gu8LcdOPtion, LCD_CUSOR);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdHwInit  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdHwInit                                                                |
 | < @Description       : lcd gpio pin init a mode input or out  or ... etc                             |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdHwInit() {
    /*4 bit mode*/
    gu8LCDFlags.byte = 0x00;
    digitalpinMode(LCD_RS, MODE_OUTPUT);
    digitalpinMode(LCD_EN, MODE_OUTPUT);
    digitalpinMode(LCD_RW, MODE_OUTPUT);
    digitalpinMode(LCD_D4, MODE_OUTPUT);
    digitalpinMode(LCD_D5, MODE_OUTPUT);
    digitalpinMode(LCD_D6, MODE_OUTPUT);
    digitalpinMode(LCD_D7, MODE_OUTPUT);
    digitalpinMode(LCD_BL, MODE_OUTPUT);
#if __DEPUG_BY_PROUTES ==1 
    lcdInit();
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdwritebuf >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdwritebuf                                                              |
 | < @Description       : write data into buffer with select position                                   |
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |
 | < @Param  pos        : write in specific char (y) in line and                                        |
 |                      : y is 0 to max number of byte per line                                         |
 | < @Param buf         : data put into lcd buffer                                                      |
 | < @Param Length      : Number of byte Load
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdwritebuf(uint8_t line, uint8_t pos, uint8_t *buf, uint8_t Length) {
    uint8_t newPos;
    newPos = (line * LCD_NUMBER_OF_BYTE) + pos;
    copyBuff(&gu8LCDBuffer[newPos], buf, Length);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdwrite >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdwrite                                                                 |
 | < @Description       : write data into buffer with select position                                   |
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |
 | < @Param  pos        : write in specific char (y) in line and                                        |
 |                      : y is 0 to max number of byte per line                                         |
 | < @Param string      : data put into lcd buffer                                                      |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdwrite(uint8_t line, uint8_t pos, const char *string) {
    uint8_t newPos;
    uint8_t length = strlen(string);
    newPos = (line * LCD_NUMBER_OF_BYTE) + pos;
    copyBuff(gu8LCDBuffer + newPos, (char *) string, length);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdCreateChar >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdCreateChar                                                            |
 | < @Description       : create custom char into lcd                                                   |
 | < @Param  u8location : write in specific location x in memory                                        |
 | < @Param  pu8Data    : pointer of the data created                                                   |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdCreateChar(uint8_t u8location, const uint8_t *pu8Data) {
    u8location &= 0x07;
    u8location *= 8;
    /*set cgram address*/
    lcdSendCommand(LCD_CGRRAM_MODE + u8location);
    for (int i = 0; i < 8; i++) {
#if COMPILER_TYPE == GCC
        lcdSendByte(pgm_read_byte(pu8Data + i));
#elif COMPILER_TYPE == XC
        lcdSendByte((pu8Data[i]));
#endif
    }
    lcdSendCommand(LCD_DDRAM_MODE);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdwriteCGRAM >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdwriteCGRAM                                                            |
 | < @Description       :  write address of the custom char  into buffer                                |
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |
 | < @Param  pos        : write in specific char (y) in line and                                        |
 |                      : y is 0 to max number of byte per line                                         |
 | < @param index       : address of char  to write into buffer                                         |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdwriteCGRAM(uint8_t line, uint8_t pos, uint8_t index) {
    uint8_t newPos;
    newPos = line * LCD_NUMBER_OF_BYTE + pos;
    gu8LCDBuffer[newPos] = index;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdClearlines >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdClearlines                                                            |
 | < @Description       : lcd can be clear a line into lcd buffer by write 0x20 into the buffer         |
 |                      : from address of the start line 0 or 1 or ..etc to end address of the line     |
 |                      : address dependent of number of char into line                                 |                                
 | < @Param  line       : write in specific line x and x from 0 to max line per lcd                     |                                        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdClearlines(bool from) {
    uint8_t x = 0x20;
    for (uint8_t i = 0; i < LCD_NUMBER_OF_BYTE; i++)
        gu8LCDBuffer[i + (from * LCD_NUMBER_OF_BYTE)] = x;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdClear >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdClear                                                                 |
 | < @Description       : lcd can be  for all lines into lcd by write 0x20 into the buffer              |
 |                      : from address of the start line 0  to end address of the line                  |         
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void lcdClear() {
    lcdClearlines(1);
    lcdClearlines(0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdDriver >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void Driver                                                                   |
 | < @Description       : run in background to write data from buffer into lcd                          |      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

void lcdDriver() {

    if (!gu8LCDFlags.b0)
        return;
    uint8_t state = lcdUpdate();
    if (state == LCD_SUCCSS || state == LCD_ERORR) {
        gu8LCDFlags.b0 = 0;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdIsBusy >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t lcdIsBusy                                                             |
 | < @Description       : check lcd is ready to write new data or not                                   |        
 | < @return            : 0 when  lcd is ready and other case lcd has not ready                         |                                                                       |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t lcdIsBusy() {
    return (gu8LCDFlags.b0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdUpdateNow >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdUpdateNow                                                             |
 | < @Description       : after write all into buffer from lcd call this function to start update       |                                    
 | < @return            : void                         |                                                |
 --------------------------------------------------------------------------------------------------------
 */
void lcdUpdateNow() {
    gu8LCDFlags.b0 = 1;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdGetLineDate >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdGetLineDate                                                           |
 | < @Description       : assignment Line Date Into app Buffer                                          |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void lcdGetLineDate(uint8_t *u8Data, uint8_t Line) {
    copyBuff(u8Data, (gu8LCDBuffer + (LCD_NUMBER_OF_BYTE * Line)), LCD_NUMBER_OF_BYTE);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < LcdWriteIndex >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void LcdWriteIndex                                                           |
 | < @Description       : assignment Index By this Function                                        |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void LcdWriteIndex(uint8_t Index, uint8_t byteDate) {
    gu8LCDBuffer[Index] = byteDate;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdWriteromFlash >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdWriteromFlash                                                         |
 | < @Description       : write Data From Flash Memeory into LCD Buffer                                 |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void lcdWriteromFlash(uint8_t line, uint8_t pos, PGM_P const *date) {
    uint8_t newPos;
    uint8_t strleng = strlen_P((const char *) date);
    newPos = (line * LCD_NUMBER_OF_BYTE) + pos;
    memcpy_P((char *) (gu8LCDBuffer + newPos), (const char *) date, strleng);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < lcdWriteString >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void lcdWriteString                                                           |
 | < @Description       : write string in cencer pos                                                    |                                           
 | < @return            : void                                                                          |                                                             
 --------------------------------------------------------------------------------------------------------
 */
void lcdWriteString(uint8_t line, PGM_P date) {
    uint8_t len;
    len = strlen_P(date);
    lcdWriteromFlash(line, (LCD_NUMBER_OF_BYTE - len) >> 1, (PGM_P const *) date);
}
#endif
#endif