#include "../inc/appRes.h"

static uint8_t * gpProuctString;
/*
 * <@var gu8LastIndex          : Last Product Created in the system
 */
static uint8_t gu8LastProuct;
/*
 <@var Create Product State   : Create PRoduct Sate Function
 */
static uint8_t gu8CreateProductState;
/*
 * <@var Typing Index : Index of the current Char
 */
static uint8_t gu8TypingIndex;
/*
 * <@var Typin char 
 */
static uint8_t gu8TypingChar[5];
/*
 * <@var gu8ModelSave       : save Model
 */
static uint8_t gu8ModelSave;
/*
 * static StringLength;  
 */
static uint8_t gu8StringLength;
/*
 * static product 
 */
static stProductString_t gsProductstrings;
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void UpdateLCD();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_1(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_2(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_3(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_5(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_6(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_7(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_9(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_10(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_11(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_14(stkey_t *key);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < appProductEventNumbers >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void appTimeEventNumbers                                                       |  
 | < @Description       : Incremnt Pos after Edit  and update action                                     |                                                    |
 | < @return            : void                                                                           |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ProductEventNumbers(stkey_t *key, uint8_t maxTab);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductCencelEvent  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  CreateProductCencelEvent                                                |
 | < @Description       : Cencel Event assignment                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ProductCencelEvent();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductEnterEvent  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  CreateProductCencelEvent                                                |
 | < @Description       : Enter Event assignment                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ProductEnterEvent();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductF1Event  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ProductF1Event                                                |
F1 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ProductF1Event();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < CreateProductCallBack  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  CreateProductCallBack                                                   |
 | < @Description       : run in menu system driver                                                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t CreateProductCallBack() {
    memAddresst_t Address;
    if (gu8CreateProductState == 0) {
        KeypadRegisterEvent(keyProduct_1, 0);
        KeypadRegisterEvent(keyProduct_2, 1);
        KeypadRegisterEvent(keyProduct_3, 2);
        KeypadRegisterEvent(keyProduct_5, 4);
        KeypadRegisterEvent(keyProduct_6, 5);
        KeypadRegisterEvent(keyProduct_7, 6);
        KeypadRegisterEvent(keyProduct_9, 8);
        KeypadRegisterEvent(keyProduct_10, 9);
        KeypadRegisterEvent(keyProduct_11, 10);
        KeypadRegisterEvent(keyProduct_14, 13);
        lcdClear();
        lcdBlink(1, 0);
        WriteMessage(0, MSG_PRODUCT_NAME + gu8ModelSave);
        CommanEventFunctions(ProductF1Event, NULL, NULL, ProductEnterEvent, ProductCencelEvent);
        gu8CreateProductState = 1;
    }

    if (gu8CreateProductState == 1) {
        /*load Last Index*/
        return (0);
    }



    if (gu8CreateProductState == 2) {
        if (gu8LastProuct >= 99) {
            gu8CreateProductState = 3;
            return (0);
        }
        Address = (gu8LastProuct * (sizeof (stProduct_t)) + MEMORY_START_PRODUCT_ADD);
        if (SaveIntoMemory(Address, &gsProductstrings.ProductName[0], (sizeof (stProductString_t)))) {
            gu8LastProuct++;
            gu8CreateProductState = 4;
        }
        return (0);
    }



    if (gu8CreateProductState == 3) {
        ReturnMenuCallBack();
        gu8CreateProductState = 0;
        gu8TypingIndex = 0;
        return (1);
    }
    if (gu8CreateProductState == 4) {
        if (SaveIntoMemory(LAST_PRODUCT_ADDRESS, &gu8LastProuct, 1)) {
            gu8CreateProductState = 3;
        }
        return (0);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductCencelEvent  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  CreateProductCencelEvent                                                |
 | < @Description       : Cencel Event assignment                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ProductCencelEvent() {

    gu8CreateProductState = 3;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductEnterEvent  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  CreateProductCencelEvent                                                |
 | < @Description       : Enter Event assignment                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ProductEnterEvent() {
    if (gu8TypingIndex == 0) {
        lcdClear();
        lcdNoBlink();
        WriteMessage(0, MSG_PRODUCT_OPS);
        WriteMessage(1, MSG_PRODUCT_EMPTY_BUFFER);
        return;
    }
    if (!gu8ModelSave) {
        gu8StringLength = 12;
        gu8ModelSave = 1;
        gu8CreateProductState = 0;
        gpProuctString = &(gsProductstrings.VersionName[0]);
        gsProductstrings.LengthName = gu8TypingIndex;
    } else {

        gu8ModelSave = 0;
        gu8StringLength = 30;
        gu8CreateProductState = 2; /*save*/
        gsProductstrings.LengthVersion = gu8TypingIndex;
        gpProuctString = &(gsProductstrings.ProductName[0]);
        ReturnMenuCallBack();
    }
    gu8TypingIndex = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductF1Event  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ProductF1Event                                                |
F1 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void ProductF1Event() {
    /*Remove  Name*/
    if (gu8TypingIndex == 0) {

        return;
    }
    gpProuctString[gu8TypingIndex] = ' ';
    gu8TypingIndex--;
    UpdateLCD();
}

static void UpdateLCD() {

    uint8_t start;
    uint8_t Length;
    uint8_t Blink;
    lcdClearlines(1);
    if (gu8TypingIndex < LCD_NUMBER_OF_BYTE) {
        start = 0;
        Length = gu8TypingIndex;
        Blink = gu8TypingIndex;
    } else {

        start = gu8TypingIndex - LCD_NUMBER_OF_BYTE;
        Blink = LCD_NUMBER_OF_BYTE - 1;
        Length = LCD_NUMBER_OF_BYTE;
    }
    lcdwritebuf(1, 0, ((&gpProuctString[0]) + start), Length);
    lcdBlink(1, Blink);
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_2(stkey_t * key) {
    gu8TypingChar[0] = 'A';
    gu8TypingChar[1] = 'B';
    gu8TypingChar[2] = 'C';
    gu8TypingChar[3] = '2';
    ProductEventNumbers(key, 4);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_3(stkey_t * key) {
    gu8TypingChar[0] = 'D';
    gu8TypingChar[1] = 'E';
    gu8TypingChar[2] = 'F';
    gu8TypingChar[3] = '3';
    ProductEventNumbers(key, 4);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_5(stkey_t * key) {
    gu8TypingChar[0] = 'G';
    gu8TypingChar[1] = 'H';
    gu8TypingChar[2] = 'I';
    gu8TypingChar[3] = '4';
    ProductEventNumbers(key, 4);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_6(stkey_t * key) {

    gu8TypingChar[0] = 'J';
    gu8TypingChar[1] = 'K';
    gu8TypingChar[2] = 'L';
    gu8TypingChar[3] = '5';
    ProductEventNumbers(key, 4);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_7(stkey_t * key) {

    gu8TypingChar[0] = 'M';
    gu8TypingChar[1] = 'N';
    gu8TypingChar[2] = 'O';
    gu8TypingChar[3] = '6';
    ProductEventNumbers(key, 4);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_9(stkey_t * key) {

    gu8TypingChar[0] = 'P';
    gu8TypingChar[1] = 'Q';
    gu8TypingChar[2] = 'R';
    gu8TypingChar[3] = 'S';
    gu8TypingChar[4] = '7';
    ProductEventNumbers(key, 5);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_10(stkey_t * key) {

    gu8TypingChar[0] = 'T';
    gu8TypingChar[1] = 'U';
    gu8TypingChar[2] = 'V';
    gu8TypingChar[3] = '8';
    ProductEventNumbers(key, 4);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_11(stkey_t * key) {

    gu8TypingChar[0] = 'W';
    gu8TypingChar[1] = 'X';
    gu8TypingChar[2] = 'Y';
    gu8TypingChar[3] = 'Z';
    gu8TypingChar[4] = '9';
    ProductEventNumbers(key, 5);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_14(stkey_t * key) {
    gu8TypingChar[0] = ' ';
    gu8TypingChar[1] = '.';
    gu8TypingChar[2] = '0';
    ProductEventNumbers(key, 3);
    return (1);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < appProductEventNumbers >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void appTimeEventNumbers                                                       |  
 | < @Description       : Incremnt Pos after Edit  and update action                                     |                                                    |
 | < @return            : void                                                                           |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void ProductEventNumbers(stkey_t *key, uint8_t maxTab) {
    if (key->TabCounter >= maxTab) {
        KeypadResetTabCounter(key, 0);
    }

    switch (key->State) {

        case KEY_PRESS:
            if (gu8TypingIndex < gu8StringLength) {
                gu8TypingIndex++;
            } else {
                return;
            }
        case MULTI_TAP:
            gpProuctString[gu8TypingIndex - 1] = gu8TypingChar[key->TabCounter];
            UpdateLCD();
            break;
        default:
            break;
    }

    return;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < CreateProductInit >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void CreateProductInit                                                        |  
 | < @Description       : Create Product system                                                         |                                                    |
 | < @return            : void                                                                          |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void CreateProductInit() {
    for (uint8_t i = 0; i < 30; i++) {
        if (i < 12) {

            gsProductstrings.VersionName[i] = ' ';
        }
        gsProductstrings.ProductName[i] = ' ';
    }
    gpProuctString = &(gsProductstrings.ProductName[0]);
    gsProductstrings.LengthName = 0;
    gu8StringLength = 30;
    gu8LastProuct = 0;
    gu8ModelSave = 0;
    gu8TypingIndex = 0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyProduct_1(stkey_t * key) {
    if (key->State == KEY_PRESS) {
        /*key number Time Event*/
        if (gu8TypingIndex < gu8StringLength)
            gu8TypingIndex++;
        gpProuctString[gu8TypingIndex - 1] = '1';
        UpdateLCD();
    }
    KeypadResetTabCounter(key, 1);

    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductGetLastIndex  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : ProductGetLastIndex                                                           |
 | < @Description       : get Last Index Value                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ProductGetLastIndex() {

    return gu8LastProuct;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductSetLastIndex  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : ProductSetLastIndex                                                           |
 | < @Description       : load Last Index Value From Memeory and set Into Variable                                                         |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void ProductSetLastIndex(uint8_t LastIndex) {
    gu8LastProuct = LastIndex;
}