
#include "../../../inc/mega.h"

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
uint8_t Match_2BUF(volatile uint8_t *buf1, volatile uint8_t *buf2, volatile uint8_t Length) {
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
uint8_t u16TOASII(char *s, uint16_t x) {
    uint8_t size;
    uint8_t i;
    size = 0;
    i = 0;
    char buffer[5]; /*max number is 5digit 2^16*/
    digitalpinMode(GPIO_B0, MODE_OUTPUT);
    do // write least significant digit of value that's left
    {
        digitalPinWrite(GPIO_B0, GPIO_TGL);
        buffer[i] = (x % 10) + '0';
        x /= 10;
        i++;
    } while (x);

    size += i;
    i = 0;
    while (i < size) {
        *(s++) = buffer[size - i - 1];
        i++;
    }

    return size;
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
uint8_t u8TOASII(char *s, uint8_t x) {
    uint8_t size;
    uint8_t i;
    size = 0;

    i = 0;
    char buffer[3]; /*max number is 3 digit 2^8*/

    do // write least significant digit of value that's left
    {
        buffer[i] = (x % 10) + '0';
        x /= 10;
        i++;
    } while (x);

    size += i;
    i = 0;
    while (i < size) {
        *(s++) = buffer[size - i - 1];
        i++;
    }

    return size;
}

