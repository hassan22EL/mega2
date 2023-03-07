/* 
 * File:   ProductSelect.c
 * Author: hassa
 *
 * Created on February 27, 2023, 7:50 PM
 */

#include "../inc/appRes.h"
#include "PrintAction.h"

/*
 *<@var Select Product State
 */
static uint8_t gu8SelectProductState;
/*
 * <@var current Product Index
 */
static uint8_t gu8CurrentProductIndex;
/*
 *<@var Current Product Selected
 */
static stProduct_t gsCurrentProduct;
/*
 * <@var Scoller Message
 */
static uint8_t gu8ProductLCDScoller[LCD_NUMBER_OF_BYTE];
/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyCencelEvents  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyCencelEvents                                                               |
 | < @Description       : key Cencel Events   Handler                                                   |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void SelectProductkeyCencelEvents();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF1Events  >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF1Events                                                                   |
 | < @Description       : key F1 Events   Handler                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void SelectProductkeyF1Events();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF2Events  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF2Events                                                  |
 | < @Description       : key F2 Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void SelectProductkeyF2Events();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < SelectProductCallBack  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8  SelectProductCallBack                                                   |
 | < @Description       : run in menu system driver                                                     |                                                  |                                                           
 | < @return            : 1 or 0                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SelectProductCallBack() {
    if (gu8SelectProductState == 0) {
        lcdClear();
        WriteMessage(0, MSG_PRODUCT_SELECT);
        CommanEventFunctions(SelectProductkeyF1Events, SelectProductkeyF2Events, NULL, NULL, SelectProductkeyCencelEvents);
        gu8SelectProductState = 1;
    }
    if (gu8SelectProductState == 1) {
        if (LoadCurrentProduct()) {

            gu8SelectProductState = 3;
        }
        return (0);
    }

    if (gu8SelectProductState == 2) {
        ReturnMenuCallBack();
        gu8SelectProductState = 0;
        return (1);
    }

    if (gu8SelectProductState == 3) {
        if (SaveIntoMemory(CURRENT_PRODUCT_ADDRESS, &gu8CurrentProductIndex, 1)) {

            clearScllorBuffer();
            gu8SelectProductState = 4;
        }
        return (0);
    }

    if (gu8SelectProductState == 4) {
        /*show Current Data*/
        if (systemSecondEvent()) {
            PrintProductInLCD(&gsCurrentProduct);
        }
    }
    return (0);


}



/*
 --------------------------------------------------------------------------------------------------------
 |                            < LoadCurrentProduct  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  LoadCurrentProduct                                                      |
 | < @Description       : load current Product from memory                                               |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t LoadCurrentProduct() {
    if (LoadFromMemory((gu8CurrentProductIndex * (sizeof (stProduct_t)) + MEMORY_START_PRODUCT_ADD), (uint8_t *) (&gsCurrentProduct), sizeof (stProduct_t))) {
        gsCurrentProduct.ProductPrint.Code = (gu8CurrentProductIndex + 1);
        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyCencelEvents  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyCencelEvents                                                               |
 | < @Description       : key Cencel Events   Handler                                                   |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void SelectProductkeyCencelEvents() {
    gu8SelectProductState = 2;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF1Events  >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF1Events                                                                   |
 | < @Description       : key F1 Events   Handler                                                       |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void SelectProductkeyF1Events() {
    if (gu8CurrentProductIndex < ProductGetLastIndex() - 1) {
        gu8CurrentProductIndex++;
    } else {
        gu8CurrentProductIndex = 0;
    }
    gu8SelectProductState = 1; /*save current Index*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyF2Events  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : keyF2Events                                                  |
 | < @Description       : key F2 Events   Handler                                                |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void SelectProductkeyF2Events() {
    if (gu8CurrentProductIndex > 0) {
        gu8CurrentProductIndex--;
    } else {
        gu8CurrentProductIndex = ProductGetLastIndex();
    }
    gu8SelectProductState = 1; /*save current Index*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < getProductCurrentInex  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : getProductCurrentInex                                                           |
 | < @Description       : get Current Index Value                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getProductCurrentInex() {
    return (gu8CurrentProductIndex);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductSetCurrentIndex  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : ProductSetCurrentIndex                                                        |
 | < @Description       : load current Index Value From Memeory and set Into Variable                                             |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void ProductSetCurrentIndex(uint8_t currentIndex) {
    gu8CurrentProductIndex = currentIndex;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < CurrentProductSaveNewPatch  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void CurrentProductSaveNewPatch                                                        |
 | < @Description       : save new time and patch number                                           |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t CurrentProductSaveNewPatch(stProductPrint_t *des) {
    copyBuff(&gsCurrentProduct.ProductPrint, des, sizeof (stProductPrint_t));
    memAddresst_t Address = (gu8CurrentProductIndex * (sizeof (stProduct_t))) + sizeof (stProductString_t) + MEMORY_START_PRODUCT_ADD;
    if (SaveIntoMemory(Address, (uint8_t *) (&gsCurrentProduct.ProductPrint), sizeof (stProductPrint_t))) {
        return (1);
    }
    return (0);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintProductInLCD  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintProductInLCD                                                       |
  | < @Description       : Print Full Product in LCD                                                     |
  |                      : NURSE MASTER UNIT-MUV0.0-0123456789-002-001                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void PrintProductInLCD() {
    uint8_t buf[61];
    uint8_t size = 0;
    if (gsCurrentProduct.ProductStrings.LengthName) {
        for (uint8_t i = 0; i < gsCurrentProduct.ProductStrings.LengthName; i++) {
            buf[i] = gsCurrentProduct.ProductStrings.ProductName[i];
        }
        size = gsCurrentProduct.ProductStrings.LengthName;
        buf[size] = '-';
        size++;
    }
    if (gsCurrentProduct.ProductStrings.LengthVersion) {
        for (uint8_t i = 0; i < gsCurrentProduct.ProductStrings.LengthVersion; i++) {
            buf[size + i] = gsCurrentProduct.ProductStrings.VersionName[i];
        }
        size += gsCurrentProduct.ProductStrings.LengthVersion;
        buf[size] = '-';
        size += 1;
    }
    size = PrintProductSerial(buf, size, &gsCurrentProduct.ProductPrint); /*16-17*/
    scllormessage(gu8ProductLCDScoller, buf, size, LCD_NUMBER_OF_BYTE);
    lcdwritebuf(1, 0, gu8ProductLCDScoller, LCD_NUMBER_OF_BYTE);
    lcdUpdateNow();

}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < clearScllorBuffer  >                                                    |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  clearScllorBuffer                                                       |
  | < @Description       : clear scoller buffer                                                          |                                            |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void clearScllorBuffer() {
    for (uint8_t i = 0; i < LCD_NUMBER_OF_BYTE; i++) {
        gu8ProductLCDScoller[i] = ' ';
    }
    lcdClearlines(1);
    lcdUpdateNow();
    ResetScollMessage();
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintCurrentProduct  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintCurrentProduct                                                      |
  | < @Description       : Print Product Call Back Action                                                 |                                            |                                                           
  | < @return            : 0 or not                                                                           |                     
  --------------------------------------------------------------------------------------------------------
 */
void PrintCurrentProduct() {
    PrintAction(&gsCurrentProduct);
}

/*
  --------------------------------------------------------------------------------------------------------
  |                            < LoadCurrentProductPrintIntoIntoPrint  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  LoadCurrentProductPrintIntoIntoPrint                                    |
  | < @Description       :Load Last Print Into to Print struct to new Current Action                     |                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void LoadCurrentProductPrintIntoIntoPrint(stProductPrint_t *des) {
    copyBuff(des, &(gsCurrentProduct.ProductPrint), sizeof (stProductPrint_t));
}

