
#include <stdint-gcc.h>

#include "../../../inc/mega.h"
static volatile uint8_t position = 0;
/*
  ---------------------------------------------------------------------------------------------------------
 |                            < uxxTOASII  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t u32TOASII                                                               |
 | < @Description       : Convert nBit Binary To ASII                                                    |                    
 | < @return            :  Number Of Digit                                                                |                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
static uint8_t uXXToASII(uint8_t *s, uint32_t x, uint8_t max);

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < uxxTOASII  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t u32TOASII                                                               |
 | < @Description       : Convert nBit Binary To ASII                                                    |                    
 | < @return            :  Number Of Digit                                                                |                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
static uint8_t uXXToASII(uint8_t *s, uint32_t x, uint8_t max) {
    uint8_t size;
    uint8_t i;
    size = 0;
    i = 0;

    if (x == 0) {
        for (uint8_t i = 0; i < max; i++) {
            s[i] = '0';
        }
        return (2);
    }

    while (i < max) {
        if (x != 0) {
            s[max - 1 - i] = (x % 10) + '0';
            x /= 10;
        } else {
            s[(max - 1) - i] = '0'; /*s[3-1-0] = s[2] ,s[1] , s[0] , */
            size++;
        }
        i++;
    }


    return (size);
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < u8Decoder  >                                                              |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t u8Decoder                                                               |
 | < @Description       : n*2^n decoder                                                                   |                    
 | < @return            :  decode value                                                                   |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t u8Decoder(uint8_t Value, uint8_t Number_of_outLine) {

    if (!Value) {
        return ((Number_of_outLine - 1) & 0x01);
    }

    for (uint8_t i = 0; i < Number_of_outLine; i++) {
        if (i == Value) {
            return ((Value & 0x01) << i) & (Number_of_outLine - 1);
        }
    }
    return ((Number_of_outLine - 1) & 0x01);
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < map  >                                                              |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t map                                                                        |
 | < @Description       : mapping value 0 to 1024 to 0 to 5                                               |                    
 | < @return            :  decode value                                                                   |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t map(uint32_t x, uint8_t in_min, uint32_t in_max, uint8_t out_min, uint8_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < power2  >                                                              |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t power2                                                                        |
 | < @Description       : mapping value 0 to 1024 to 0 to 5                                               |                    
 | < @return            :  decode value                                                                   |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t power2(uint8_t x) {
    uint8_t y = 1;
    if (x == 0) {
        return 1;
    }
    for (uint8_t i = 0; i < x; i++) {
        y *= 2;
    }
    return y;
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < Match_2BUF  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t Match_2BUF                                                              |
 | < @Description       : two buffer is equles or not                                                     |                    
 | < @return            :  0 not match                                                                    |
                        : 1 two buffer match                                                              |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t Match_2BUF(uint8_t *buf1, uint8_t *buf2, uint8_t Length) {
    for (uint8_t i = 0; i < Length; i++) {
        if (buf1[i] != buf2[i]) {
            return (0);
        }

    }
    return (1);
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < u16TOASII  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t u16TOASII                                                               |
 | < @Description       : Convert 16Bit Binary To ASII                                                    |                    
 | < @return            :  Number Of Digit                                                                |                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t u16TOASII(uint8_t *s, uint16_t x) {
    return uXXToASII(s, (uint32_t) x, 5);
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < u8TOASII  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t u8TOASII                                                               |
 | < @Description       : Convert 8Bit Binary To ASII                                                    |                    
 | < @return            :  Number Of Digit                                                                |                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t u8TOASII(uint8_t *s, uint8_t x) {
    return uXXToASII(s, (uint32_t) x, 3);
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < hex8TOASII  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t hex8TOASII                                                              |
 | < @Description       : Convert 8Bit Hexnumber To ASII                                                  |                    
 | < @return            :  void                                                                           |                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
void hex8TOASII(uint8_t *s, uint8_t x) {
    uint8_t low;
    uint8_t high;


    low = x & 0x0F;
    high = (x & 0xF0) >> 4;
    s[0] = high;
    s[1] = low;
    s[0] += (high < 10 ? '0' : ('A' - 10));
    s[1] += (low < 10 ? '0' : ('A' - 10));
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < cpyStringToBuff  >                                                        |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t hex8TOASII                                                              |
 | < @Description       : copy data from const location to run time buffer location                       | 
 | < @Param  s          : Const String                                                                    |
 | < @Param  x          : buffer                                                                          |  
 | < @Param len         : Length of data copy                                                             |
 | < @return            :  len of const string                                                            |                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
void cpyStringToBuff(const char *s, uint8_t *x, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        x[i] = (uint8_t) s[i];
    }
}

/*
  ---------------------------------------------------------------------------------------------------------
 |                            < u32TOASII  >                                                             |
  ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t u32TOASII                                                               |
 | < @Description       : Convert 32Bit Binary To ASII                                                    |                    
 | < @return            :  Number Of Digit                                                                |                                                           |
  ---------------------------------------------------------------------------------------------------------
 */
uint8_t u32TOASII(uint8_t *s, uint32_t x) {
    return uXXToASII(s, x, 10);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Edit2Digit >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void Edit2Digit                                                                |  
 | < @Description       : Edit Digit Into Number                                                         |                                                    |
 | < @return            : New Number Value                                                               |                                                                                                              |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t Edit2Digit(uint8_t Number, uint8_t DigitIndex, uint8_t Value) {
    uint8_t NewNumber;
    uint8_t s[3];
    u8TOASII(s, Number);
    s[DigitIndex] = Value + '0';
    NewNumber = (((s[1] - '0')*10) + (s[2] - '0'));
    return NewNumber;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < scllormessage>                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void scllormessage                                                             |  
 | < @Description       :sclloer message into buffer                                                     |                                                        |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void scllormessage(uint8_t *buffer, uint8_t *s, uint8_t MessageLength, uint8_t BufferSize) {
    // shift the buffer

    uint8_t buffsize = BufferSize;
    uint8_t wordsize = MessageLength;
    uint8_t icstsize = wordsize + buffsize;
    for (uint8_t i = 0; i < (buffsize - 1); i++)
        buffer[i] = buffer[i + 1];
    buffer[buffsize - 1] = position < wordsize ? s[position] : ' ';
    position = (position + 1) % icstsize;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < DecToBcdFun>                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void DecToBcdFun                                                             |  
 | < @Description       :convert number decmal to BCD                                                     |                                                        |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t DecToBcdFun(uint8_t value) {
    return (((value % 10) & (0x0F)) + (((value / 10) << 4) & (0xF0)));
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < BcdToDecFun>                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void BcdToDecFun                                                               |  
 | < @Description       :convert number BCD to Decimal                                                   |                                                        |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t BcdToDecFun(uint8_t value) {
    return ((value & 0x0F) + (((value >> 4) & (0x0F)) * 10));
}

/**************************************************************************/
/*!
    @brief  Convert a string containing two digits to uint8_t, e.g. "09" returns
   9
    @param p Pointer to a string containing two digits
 */

/**************************************************************************/
uint8_t conv2d(uint8_t *p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

void print2d(uint8_t value, uint8_t * p, uint8_t start) {
    p[start] = (value / 10) + '0';
    p[start + 1 ] = (value % 10) + '0';
}

void print3d(uint8_t value, uint8_t *p, uint8_t start) {
    print2d((value / 10), p, start);
    p[start + 2 ] = (value % 10) + '0';
}

void ResetScollMessage() {
    position = 0;
}

void copyBuff(void *des, void *src, uint8_t len) {
    uint8_t *srcbuf;
    uint8_t *desbuf;
    srcbuf = (uint8_t *) (src);
    desbuf = (uint8_t *) (des);
    for (uint8_t h = 0; h < len; h++) {
        desbuf[h] = srcbuf[h];
    }
}


/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintMessage  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintMessage                                                       |
  | < @Description       : Print Message Into Buffer Array                                                    |
  |                      : PrintMessage                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
 uint8_t PrintMessage(uint8_t *buf, uint8_t start, uint8_t MsgIndex , PGM_P const *message) {
    const char *date = (const char *) pgm_read_word(&message[MsgIndex]);
    uint8_t strleng = strlen_P(date);
    memcpy_P((char *) (buf + start), date, strleng);
    return strleng;

}