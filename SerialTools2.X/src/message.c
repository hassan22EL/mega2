
#include <stdint.h>

#include "../inc/appRes.h"
const char string_1[] PROGMEM = "Name";
const char string_2[] PROGMEM = "Model";
const char string_3[] PROGMEM = "Select";
const char string_4[] PROGMEM = "Waitting";
const char string_5[] PROGMEM = "Saving";
const char string_6[] PROGMEM = "Empty";
const char string_7[] PROGMEM = "OPs...";
const char string_8[] PROGMEM = "VERSION:";
const char string_9[] PROGMEM = "SERIAL  :";
const char string_10[] PROGMEM = "Set Work Time";
const char string_11[] PROGMEM = "www.smartsol-eg.com";
const char string_12[] PROGMEM = "MADE IN EGYPT";
const char string_13[] PROGMEM = "Print";
const char string_14[] PROGMEM = "MEMORY INIT";
const char string_15[] PROGMEM = "RESPONSE FROM";
const char string_16[] PROGMEM = "RS485 DEVICE";
const char string_17[] PROGMEM = "NOT CONNECTED";
const char string_18[] PROGMEM = "DEVICE";
const char string_19[] PROGMEM = "DISABLED";
const char string_20[] PROGMEM = "ENABLED";
const char string_21[] PROGMEM = "RD";
const char string_22[] PROGMEM = "OK\r\n";
const char string_23[] PROGMEM = "\r\n";
const char string_24[] PROGMEM = "RESET PATCH";
const char string_25[] PROGMEM = "SYSTEM DISABLED";




PGM_P const Messages[] PROGMEM = {
    string_1,
    string_2,
    string_3,
    string_4,
    string_5,
    string_6,
    string_7,
    string_8,
    string_9,
    string_10,
    string_11,
    string_12,
    string_13,
    string_14,
    string_15,
    string_16,
    string_17,
    string_18,
    string_19,
    string_20,
    string_21,
    string_22,
    string_23,
    string_24,
    string_25,
};

/*
 --------------------------------------------------------------------------------------------------------
 |                            < WriteMessage  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WriteMessage                                                   |
 | < @Description       : Write Message From message Buffer                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void WriteMessage(uint8_t lin, uint8_t Index) {
     PGM_P String =(PGM_P ) pgm_read_word(&Messages[Index]);
    lcdWriteString(lin, String);
    lcdUpdateNow();
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintProductSerial  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintProductSerial                                                      |
  | < @Description       : Print Serial in Format xxxxxxxxxx-xxx-xxx                                     |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t PrintProductSerial(uint8_t *buf, uint8_t start, stProductPrint_t *ProductPrint) {
    /*covvert u32 to asii*/
    /*0-9 is time*/
    /*10 is -*/
    /*11 - 12 , 13 is Code*/
    /*14 is -*/
    /*15 ,16 , 17 is Patch*/
    uint8_t vindex = start;
    u32TOASII((uint8_t *) (buf + start), ProductPrint->Time);
    vindex += 10;
    buf[vindex] = '-';
    vindex++;
    u8TOASII((uint8_t *) (buf + vindex), ProductPrint->Code);
    vindex += 3;
    buf[vindex] = '-';
    vindex++;
    print2d(ProductPrint->PatchNumber, buf, vindex);
    vindex += 2;
    return vindex;
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < messageCompareString  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  messageCompareString                                                      |
  | < @Description       : compare buffer with string                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t messageCompareString(uint8_t *buf, uint8_t Index, uint8_t length) {
    const char *date = (const char *) pgm_read_word(&Messages[Index]);
    if (memcmp_P(buf, date, length) == 0) {
        return (1);
    }
    return (0);
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
uint8_t appPrintMessage(uint8_t *buf, uint8_t start, uint8_t MsgIndex) {
    return PrintMessage(buf, start, MsgIndex, Messages);

}