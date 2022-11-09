/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   lcd.c
 * Author       :   Hassan Elsaied
 * Data Memory  :   number of line * number of char per line  +  4byte is default 2*16 +4 = 36Byte
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   5-hour
 * Comments     :   no comment
 */

#include "../../../inc/mega.h"
#if defined (LCD_MODULE)
#if  LCD_MODULE 
/* 
 * ******************************************************************************
 *                        Macro  Definition                                     *
 * ******************************************************************************
 */

/* 
 * ******************************************************************************
 *                        LCD  Text Alignment                                     *
 * ******************************************************************************
 */

#define  LCD_TEXT_CENTER         (0xFF)
/* 
 * ******************************************************************************
 *                        LCD  Buffer Size                                     *
 * ******************************************************************************
 */
#define  LCD_SIZE              (LCD_NUMBER_OF_BYTE * LCD_NUMBER_OF_LINE)

#define   LCD_BLINK           (0)
#define   LCD_CUSOR           (1)
#define   LCD_DISPLAY         (2)

/* 
 * ******************************************************************************
 *                        LCD  MODES                                            *
 * ******************************************************************************
 */


#define  LCD_8BIT_MODE        (0x01)
#define  LCD_4BIT_MODE        (0x02)
#define  LCD_NONINTERACTIVE   (0x03)
#define  LCD_INTERAVTIVE      (0x04)
#define  LCD_COMMAND          (0x05)
#define  LCD_DATA             (0x06)

/* 
 * ******************************************************************************
 *                        LCD  Commands                                        *
 * ******************************************************************************
 */
/* 
 * ******************************************************************************
 *                        LCD 8Bit Commands                                    *
 * ******************************************************************************
 */

#define LCD_8BIT_COMMAND                (0x30)
#define LCD_8BIT_2LINE_COMMAND          (0x38)   /*set number of line 2 and font 5*10 dot */

/* 
 * ******************************************************************************
 *                        LCD 4Bit Commands                                    *
 * ******************************************************************************
 */


#define LCD_4BIT_COMMAND           (0x20)  /*set 4bit mode*/
#define LCD_2LINE_COMMAND          (0x28)   /*set number of line 2 and font 5*10 dot */

/* 
 * ******************************************************************************
 *                        LCD Display Commands                                    *
 * ******************************************************************************
 */


#define LCD_DISPLAY_ON_COMMAND     (0x0C)  /*display ON  */
#define LCD_DISPLAY_OFF_COMMAND    (0x08) /*display off*/
#define LCD_CLEAR_COMMAND          (0x01)   /*clear data*/
#define LCD_ENTRY_SET              (0x06)   

/* 
 * ******************************************************************************
 *                        LCD CGRMA Commands                                    *
 * ******************************************************************************
 */


#define  LCD_CGRAM_ADDRESS_CHECK   (0x3F) /*last char in cgram*/
#define  LCD_CGRRAM_MODE           (0x40)
#define  LCD_DDRAM_MODE            (0x80)

/* 
 * ******************************************************************************
 *                        LCD Timing                                            *
 * ******************************************************************************
 */


#define LCD_TIMING_POWER_ON    (15) /*uint 15ms*/
#define LCD_TIMING_8BIT_LONG   (5) /*uint 5ms*/
#define LCD_TIMING_CLEAR_COMMAND   (3) /*uint 3ms*/
#define LCD_OPERATION_TIME     (40) /*uint 40us*/





/*
 * ***************************************************************************************
 *                               LCD state                                               *
 * ***************************************************************************************
 * @param  LCD_IN_PROGRESS  : lcd internal operation
 * @param  LCD_ERORR        : lcd hardware not ready
 * @param  LCD_SUCCSS       : lcd is done 
 */

#define LCD_IN_PROGRESS  0x02
#define LCD_ERORR        0x01
#define LCD_SUCCSS       0x00





/*
 * ***************************************************************************************
 *                               set position                                            *
 * ***************************************************************************************
 */

static volatile uint8_t gu8LCDPosition;
/*
 * ***************************************************************************************
 *                               set LCD Buffer                                            *
 * ***************************************************************************************
 * LCD Size = LCD number of line * lcd number of char per line
 */

static volatile uint8_t gu8LCDBuffer[LCD_SIZE];
/*
 * ***************************************************************************************
 *                               gu8LcdOPtion                                             *
 * ***************************************************************************************
 * option 
 * 1- enable or disable cursor 
 * 2- enable or disable blink
 * 3- display on or off 
 */
static volatile uint8_t gu8LcdOPtion;
/*
 * ***************************************************************************************
 *                              gu8LcdBufferIndex                                            *
 * ***************************************************************************************
 * Index to write current byte from buffer
 */
static volatile uint8_t gu8LcdBufferIndex;
/*
 * ***************************************************************************************
 *                              gu8LCDError                                            *
 * ***************************************************************************************
 * generate error when lcd is not ready
 * 
 */
static volatile byte_Flags_t gu8LCDFlags;
/*
 * ***************************************************************************************
 *                              lcd time out                                             *
 * ***************************************************************************************/
static stTimer_TimeOut_t gsLCDTimer;

/*
 * ***************************************************************************************
 *                              custome char tables                                            *
 * ***************************************************************************************
 * generate error when lcd is not ready
 */
static const uint8_t PROGMEM CGRAM_ZERO[] = {
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111
};
static const uint8_t PROGMEM CGRAM_ONE[] = {
    0b11111,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b11111
};
static const  PROGMEM uint8_t CGRAM_TWO[] = {
    0b11111,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11111
};
static const  PROGMEM uint8_t CGRAM_THREE[] = {
    0b11111,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11111
};
static const uint8_t PROGMEM CGRAM_FOUR[] = {
    0b11111,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11111
};
static const uint8_t PROGMEM CGRAM_FIVE[] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};


/*
 * *******************************************************************
 *                               lcdInit                             *
 * *******************************************************************
 * @benfit                 : write command to init in 4 bit mode or 8 bit mode or clear ,........etc
 * @return                 : 0  when init done 
 *                         : 1 when init in progress
 * 
 */
static uint8_t lcdInit();

/*
 * ***************************************************************************************
 *                               lcdUpdate                                               *
 * ***************************************************************************************
 * @benfit                 : write data from lcd buffer and commands required do this 
 * @return                 : LCD_ERORR when lcd is not ready   or
 *                         : LCD_SUCCSS when lcd is write buffer done
 */

static uint8_t lcdUpdate();
/*
 * *******************************************************************
 *                               lcdWaitBusy                         *
 * *******************************************************************
 * @benfit                 : check lcd is busy by read two nibble of the lcd 
 *                         : the last bit in high nibble is stste of the lcd when high the lcd is busy else lcd ready
 * @return                 : void
 */
static void lcdWaitBusy();
/*
 * *******************************************************************
 *                               lcdSendCommand                      *
 * *******************************************************************
 * @benfit                 : write data into lcd with RS is enable high
 * @return                 : void
 */
static void lcdSendByte(uint8_t u8Byte);
/*
 * *******************************************************************
 *                               lcdSendCommand                      *
 * *******************************************************************
 * @benfit                 : write command into lcd with RS is enable low
 * @return                 : void
 */
static void lcdSendCommand(uint8_t u8Cmd);
/*
 * *******************************************************************
 *                               lcdSend                             *
 * *******************************************************************
 * @benfit                 : write data into lcd no rs is active this function share with write command and data
 * @return                 : void
 */
static void lcdSend(uint8_t u8Data);
/*
 * *******************************************************************
 *                               lcdReadByte                             *
 * *******************************************************************
 * @benfit                 : write byte frome lcd
 * @return                 : read byte
 */
static uint8_t lcdReadByte();
/*
 * *******************************************************************
 *                               lcdSendCommdHigh                             *
 * *******************************************************************
 * @benfit                 : just write high nibble of the byte command
 * @return                 :void
 */
static void lcdSendCommdHigh(uint8_t u8Data);

/*
 * *******************************************************************
 *                               lcdWaitBusy                         *
 * *******************************************************************
 * @benfit                 : check lcd is busy by read two nibble of the lcd 
 *                         : the last bit in high nibble is stste of the lcd when high the lcd is busy else lcd ready
 * @return                 : void
 */
static void lcdWaitBusy() {
    uint8_t state;
    state = 0;

    digitalpinMode(LCD_D4, MODE_INPUT); /* 600ns*/
    digitalpinMode(LCD_D5, MODE_INPUT); /*600ns*/
    digitalpinMode(LCD_D6, MODE_INPUT); /*600ns*/
    digitalpinMode(LCD_D7, MODE_INPUT); /*600ns*/
    digitalPinWrite(LCD_RS, GPIO_LOW); //RS=0; /*600ns*/
    digitalPinWrite(LCD_RW, GPIO_HIGH); //RW=1 /*600ns*/
    sysSetPeriodUs(&gsLCDTimer, 100);

    /*get micros and compare*/
    do {
        digitalPinWrite(LCD_EN, GPIO_HIGH);
        if (sysIsTimeoutUs(&gsLCDTimer) == 0) {
            gu8LCDFlags.b7 = 1;
            break;
        }
        state = digitalPinRead(LCD_D7);
        digitalPinWrite(LCD_EN, GPIO_LOW);
        Pulse_En();
    } while (state);

    digitalpinMode(LCD_D4, MODE_OUTPUT);
    digitalpinMode(LCD_D5, MODE_OUTPUT);
    digitalpinMode(LCD_D6, MODE_OUTPUT);
    digitalpinMode(LCD_D7, MODE_OUTPUT);
    digitalPinWrite(LCD_RW, GPIO_LOW);
}

/*
 * *******************************************************************
 *                               lcdSendCommand                      *
 * *******************************************************************
 * @benfit                 : write data into lcd with RS is enable high
 * @return                 : void
 */
static void lcdSendByte(uint8_t u8Byte) {
    lcdWaitBusy();
    digitalPinWrite(LCD_RS, GPIO_HIGH);
    lcdSend(u8Byte);
}

/*
 * *******************************************************************
 *                               lcdSendCommand                      *
 * *******************************************************************
 * @benfit                 : write command into lcd with RS is enable low
 * @return                 : void
 */
static void lcdSendCommand(uint8_t u8Cmd) {
    lcdWaitBusy();
    digitalPinWrite(LCD_RS, GPIO_LOW);
    lcdSend(u8Cmd);
}

/*
 * *******************************************************************
 *                               lcdSend                             *
 * *******************************************************************
 * @benfit                 : write data into lcd no rs is active this function share with write command and data
 * @return                 : void
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

/*
 * *******************************************************************
 *                               lcdReadByte                             *
 * *******************************************************************
 * @benfit                 : write byte frome lcd
 * @return                 : read byte
 */
static uint8_t lcdReadByte() {
    uint8_t u8Byte;
    u8Byte = 0;
    lcdWaitBusy();
    digitalpinMode(LCD_D4, MODE_INPUT);
    digitalpinMode(LCD_D5, MODE_INPUT);
    digitalpinMode(LCD_D6, MODE_INPUT);
    digitalpinMode(LCD_D7, MODE_INPUT);
    digitalPinWrite(LCD_RS, GPIO_LOW); //RS = 0
    digitalPinWrite(LCD_RW, GPIO_HIGH); //RW=1

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
    digitalPinWrite(LCD_EN, GPIO_LOW);
    digitalpinMode(LCD_D4, MODE_OUTPUT);
    digitalpinMode(LCD_D5, MODE_OUTPUT);
    digitalpinMode(LCD_D6, MODE_OUTPUT);
    digitalpinMode(LCD_D7, MODE_OUTPUT);
    digitalPinWrite(LCD_RW, GPIO_LOW); //R=1
    return (u8Byte);
}

/*
 * *******************************************************************
 *                               lcdSendCommdHigh                             *
 * *******************************************************************
 * @benfit                 : just write high nibble of the byte command
 * @return                 :void
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
 * ***************************************************************************************
 *                               lcdUpdate                                               *
 * ***************************************************************************************
 * @benfit                 : write data from lcd buffer and commands required do this 
 * @return                 : LCD_ERORR when lcd is not ready   or
 *                         : LCD_SUCCSS when lcd is write buffer done
 */

static uint8_t lcdUpdate() {

    /*case 0*/
    if (!gu8LCDFlags.b0 && !gu8LCDFlags.b1) {
        lcdSendCommand((LCD_CGRRAM_MODE | LCD_CGRAM_ADDRESS_CHECK));
        if (lcdReadByte() != (LCD_CGRAM_ADDRESS_CHECK)) {
            gu8LCDFlags.b0 = 1;
            gu8LCDFlags.b1 = 0;
        }
    } else if (gu8LCDFlags.b0 && !gu8LCDFlags.b1) {
        if (lcdInit() == 0) {
            gu8LCDFlags.b0 = 0;
            gu8LCDFlags.b1 = 1;
        }
        if (gu8LCDFlags.b7) {
            gu8LCDFlags.b7 = 0;
            gu8LCDFlags.b0 = 0;
            gu8LCDFlags.b1 = 0;
            return (LCD_ERORR);
        }

    } else {
        if (gu8LcdBufferIndex < LCD_SIZE) {
            if (gu8LcdBufferIndex % LCD_NUMBER_OF_BYTE == 0) {
                lcdSendCommand(lcdPosToAddress((gu8LcdBufferIndex / LCD_NUMBER_OF_BYTE), 0));
                if (gu8LCDFlags.b7) {
                    gu8LCDFlags.b7 = 0;
                    gu8LCDFlags.b1 = 0;
                    gu8LCDFlags.b0 = 0;
                    gu8LcdBufferIndex = 0;
                    return (LCD_ERORR);
                }
            }
            lcdSendByte(gu8LCDBuffer[gu8LcdBufferIndex]);
            if (gu8LCDFlags.b7) {
                gu8LCDFlags.b7 = 0;
                gu8LCDFlags.b0 = 0;
                gu8LCDFlags.b1 = 0;
                return (LCD_ERORR);
            }
            gu8LcdBufferIndex++;
            /*break after 100u*/
        } else {
            gu8LCDFlags.b7 = 0;
            gu8LCDFlags.b0 = 0;
            gu8LCDFlags.b1 = 0;
            gu8LcdBufferIndex = 0;
            lcdSendCommand(gu8LCDPosition);
            lcdSendCommand(LCD_DISPLAY_ON_COMMAND | gu8LcdOPtion);
            return (LCD_SUCCSS);
        }
    }
    return (LCD_IN_PROGRESS);
}

/*
 * *******************************************************************
 *                               lcdInit                             *
 * *******************************************************************
 * @benfit                 : write command to init in 4 bit mode or 8 bit mode or clear ,........etc
 * @return                 : 0 : init done
 *                         : 1 in progress
 */
static uint8_t lcdInit() {


    if (!gu8LCDFlags.b3 && !gu8LCDFlags.b0) {
        sysSetPeriodMS(&gsLCDTimer, 15);
        for (uint8_t i = 0; i < LCD_SIZE; i++)
            gu8LCDBuffer[i] = ' ';
        gu8LcdOPtion = LCD_DISPLAY_ON_COMMAND; /*the display on*/
        gu8LCDPosition = 0;
        gu8LcdBufferIndex = 0;
        gu8LCDFlags.b3 = 1;
        gu8LCDFlags.b4 = 0;

    } else if (gu8LCDFlags.b3 && !gu8LCDFlags.b4) {
        if (sysIsTimeoutMs(&gsLCDTimer) == 0) {
            lcdSendCommdHigh(LCD_8BIT_COMMAND);
            gu8LCDFlags.b3 = 0;
            gu8LCDFlags.b4 = 1;
            sysSetPeriodUs(&gsLCDTimer, 4500);
        }
    } else if (!gu8LCDFlags.b3 && gu8LCDFlags.b4) {
        if (sysIsTimeoutUs(&gsLCDTimer) == 0) {
            gu8LCDFlags.b3 = 1;
            gu8LCDFlags.b4 = 1;
            sysSetPeriodUs(&gsLCDTimer, 100);
            lcdSendCommdHigh(LCD_8BIT_COMMAND);
        }
    } else {
        if (sysIsTimeoutUs(&gsLCDTimer) == 0) {
            lcdSendCommdHigh(LCD_8BIT_COMMAND);
#if GPIO2_USE_INLINE_FUNCTIONS
            _delay_us(37);
#else
            _delay_us(25);
#endif
            lcdSendCommdHigh(LCD_4BIT_COMMAND);
#if GPIO2_USE_INLINE_FUNCTIONS
            _delay_us(37);
#else
            _delay_us(25);
#endif
            lcdSendCommand(LCD_2LINE_COMMAND);
            lcdSendCommand(LCD_DISPLAY_ON_COMMAND);
            lcdSendCommand(LCD_CLEAR_COMMAND);
            lcdSendCommand(LCD_ENTRY_SET);
            /*Create custom chars*/
            lcdCreateChar(0, CGRAM_ZERO);
            lcdCreateChar(1, CGRAM_ONE);
            lcdCreateChar(2, CGRAM_TWO);
            lcdCreateChar(3, CGRAM_THREE);
            lcdCreateChar(4, CGRAM_FOUR);
            lcdCreateChar(5, CGRAM_FIVE);
            gu8LCDFlags.byte = 0x00;
            return (0);
        }
    }
    return (1);
}

/*
 * *******************************************************************
 *                               lcdHwInit                           *
 * *******************************************************************
 * @benfit                 : lcd  hardware init such gpio pins a
 * @return                 : void
 */

void lcdHwInit() {
    /*4 bit mode*/
    gu8LCDFlags.byte = 0x00;
    if ((LCD_RS == NOT_A_PIN) ||
            (LCD_EN == NOT_A_PIN) ||
            (LCD_RW == NOT_A_PIN) ||
            (LCD_D4 == NOT_A_PIN) ||
            (LCD_D5 == NOT_A_PIN) ||
            (LCD_D6 == NOT_A_PIN) ||
            (LCD_D7 == NOT_A_PIN))

        return;
    digitalpinMode(LCD_RS, MODE_OUTPUT);
    digitalpinMode(LCD_EN, MODE_OUTPUT);
    digitalpinMode(LCD_RW, MODE_OUTPUT);
    digitalpinMode(LCD_D4, MODE_OUTPUT);
    digitalpinMode(LCD_D5, MODE_OUTPUT);
    digitalpinMode(LCD_D6, MODE_OUTPUT);
    digitalpinMode(LCD_D7, MODE_OUTPUT);
}

/*
 * *******************************************************************
 *                               lcdNoBlink                           *
 * *******************************************************************
 * @benfit                 : lcd stop blink
 * @return                 : void
 */

void lcdNoBlink() {
    bitClear(gu8LcdOPtion, LCD_BLINK);
}

/*
 * *******************************************************************
 *                               lcdNoBlink                           *
 * *******************************************************************
 * @benfit                 : lcd enable blink in position x,y 
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param u8pos            : pos char of in the line char 0 or 1 or .........etc
 * @return                 : void
 */
void lcdBlink(uint8_t u8line, uint8_t u8pos) {
    gu8LCDPosition = lcdPosToAddress(u8line, u8pos);
    bitSet(gu8LcdOPtion, LCD_BLINK);
}

/*
 * *******************************************************************
 *                               lcdNoCursor                           *
 * *******************************************************************
 * @benfit                 : lcd stop cursor
 * @return                 : void
 */


void lcdNoCursor() {
    bitClear(gu8LcdOPtion, LCD_CUSOR);
}

/*
 * *******************************************************************
 *                               lcdCursor                           *
 * *******************************************************************
 * @benfit                 : lcd enable cursor in position x,y 
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param u8pos            : pos char of in the line char 0 or 1 or .........etc
 * @return                 : void
 */
void lcdCursor(uint8_t u8line, uint8_t u8pos) {
    gu8LCDPosition = lcdPosToAddress(u8line, u8pos);
    bitSet(gu8LcdOPtion, LCD_CUSOR);
}

/*
 * *******************************************************************
 *                               lcdwrite                           *
 * *******************************************************************
 * @benfit                 : write data into buffer with select position
 * param line              : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  of  the string in the line char 0 or 1 or .........etc
 * string                  : pointer to string to write into buffer
 * @return                 : void
 */

void lcdwrite(uint8_t line, uint8_t pos, const char *string) {
    uint8_t newPos;
    if (pos != LCD_TEXT_CENTER) {
        newPos = line * LCD_NUMBER_OF_BYTE + pos;
    } else {
        newPos = line * LCD_NUMBER_OF_BYTE + ((LCD_NUMBER_OF_BYTE - strlen(string)) / 2);
    }
    for (uint8_t i = 0; i < strlen(string); i++)
        gu8LCDBuffer[newPos + i] = string[i];
    gu8LCDFlags.b5 = 1;
}

/*
 * *******************************************************************
 *                               lcdIsCurrentNumber                  *
 * *******************************************************************
 * @benfit                 : check is specific position is a number or not into buffer
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  of  the char in the line char 0 or 1 or .........etc
 * @return                 : 0 is buffer not contains a number in position and  1 if the position is a number
 */
uint8_t lcdIsCurrentNumber(uint8_t line, uint8_t pos) {
    uint8_t newPos;
    newPos = line * LCD_NUMBER_OF_BYTE + pos;
    if (gu8LCDBuffer[newPos] >= '0' && gu8LCDBuffer[newPos] <= '9')
        return (1);
    return (0);
}

/*
 * *******************************************************************
 *                              lcdCreateChar                        *
 * *******************************************************************
 * @benfit                 : create custom char into lcd 
 * @param u8location       : the address of the custome char to be create
 * @pu8Data                 : pointer to data of the char 
 * @return                 : void
 */

void lcdCreateChar(uint8_t u8location, const uint8_t *pu8Data) {
    u8location &= 0x07;
    u8location *= 8;
    /*set cgram address*/
    lcdSendCommand(LCD_CGRRAM_MODE + u8location);
    for (int i = 0; i < 8; i++) {
        lcdSendByte(pu8Data[i]);
    }
    lcdSendCommand(LCD_DDRAM_MODE);
}

/*
 * *******************************************************************
 *                               lcdwrite                           *
 * *******************************************************************
 * @benfit                 : write address of the custom char  into buffer with select position
 * @param line              : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  of  the custome char  in the line char 0 or 1 or .........etc
 * index                   : address of char  to write into buffer
 * @return                 : void
 */

void lcdwriteCGRAM(uint8_t line, uint8_t pos, uint8_t index) {
    uint8_t newPos;
    newPos = line * LCD_NUMBER_OF_BYTE + pos;
    gu8LCDBuffer[newPos] = index;
    gu8LCDFlags.b5 = 1;
}

/*
 * *********************************************************************************************************************
 *                               getlcdData                                                                            *
 * *********************************************************************************************************************
 * @benfit                 : get data frome lcd buffer start form pos as assignment into pointer of the string read 
 *                         : and max length data to be get is max size of the data pointer can to be read
 * @param str               : pointer to assignment data read from buffer
 * @param line             : line number 0 or 1 or 2 or ........etc 
 * @param pos              : start pos  into buffer to be read  in the line char 0 or 1 or .........etc
 * @return                 : void
 */
void getlcdData(char *str, uint8_t line, uint8_t pos) {
    uint8_t i, u8count;
    i = line * LCD_NUMBER_OF_BYTE + pos;
    u8count = 0;
    while (gu8LCDBuffer[i] != 0x20) {
        str[u8count++] = gu8LCDBuffer[i];
        i++;
        if (i % LCD_NUMBER_OF_BYTE == 0) {
            break;
        }
    }
}

/*
 * *******************************************************************
 *                               lcdClearlines                           *
 * *******************************************************************
 * @benfit                 : lcd can be clear a line into lcd buffer by write 0x20 into the buffer from address of the start line
 *                         :  0 or 1 or ..etc to end address of the line address dependent of number of char into line 
 * @param from             : start address of line  0 or 1 or ...........etc
 * @return                 : void
 */

void lcdClearlines(uint8_t from) {
    for (uint8_t i = from * LCD_NUMBER_OF_BYTE; i < LCD_SIZE; i++) {
        gu8LCDBuffer[i] = 0x20;
    }
    gu8LCDFlags.b5 = 1;
}

/*
 * ***************************************************************************************************************
 *                                lcdClearlines                                                                   *
 * ***************************************************************************************************************
 * @benfit                 : lcd can be clear a buffer for all lines into lcd by write 0x20 into the buffer
 *                         : from address of the  line 0 to line n  
 * @return                 : void
 */
void lcdClear() {
    for (uint8_t j = 0; j < LCD_SIZE; j++) {
        gu8LCDBuffer[j] = 0x20;
    }
    gu8LCDFlags.b5 = 1;
}

/* ***************************************************************************************************************
 *                                Lcd Driver                                                                  *
 * ***************************************************************************************************************
 * @benfit                 : run at back ground of the system if is error or success run user 
 * @return                 : void
 */

void lcdDriver() {
    uint8_t state;
    if (!gu8LCDFlags.b5) {
        return;
    }
    state = lcdUpdate();
    if (state == LCD_SUCCSS) {
        gu8LCDFlags.b5 = 0;
        return;
    }
    if (state == LCD_ERORR) {
        /*run callback of the system error*/
        gu8LCDFlags.b5 = 0;
        return;
    }
}

/* ***************************************************************************************************************
 *                                 lcdIsBusy                                                                  *
 * ***************************************************************************************************************
 * @benfit                 : check lcd  is ready to write new data or not
 * @return                 : 0 when  lcd is ready or 1 lcd has not ready
 */

uint8_t lcdIsBusy() {
    return (gu8LCDFlags.b5);
}

#endif
#endif