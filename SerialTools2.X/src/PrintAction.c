
/*
 *
 */
#include <stdint.h>

#include "../inc/appRes.h"
#define       BITMAP_ARRAY_LENGTH_BYTES        (24)
#define       BITMAP_ARRAY_LENGTH_INDEX        (41)
/*
 * static PrintAction State
 */
static uint8_t gu8PrintActionState;
/*
 *
 */
static stProduct_t *gpPrintActionProduct;

static uint8_t gu8LogoData;

uint8_t gu8PrintActionBuffer[32];

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < PrintActionCallBack>                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintActionCallBack                                                            |  
 | < @Description       : Fun Run in any Re                                                      |                                                        |
 | < @return            : 0 the Print Action is running , 1 - Print Action is Done                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t PrintActionCallBack() {
    uint8_t size = 0;
    memAddresst_t Address;
    if (ZLPPrintState()) {
        return (0);
    }
    switch (gu8PrintActionState) {
        case 0:
            /*wait for */
            lcdClear();
            WriteMessage(0, MSG_PRINT_LABLE);
            WriteMessage(1, MSG_PRODUCT_PLEASE_WAIT);
            gu8PrintActionState = 1;
            break;
        case 1:
            /*wait for sen*/
            if (ZLPClearLastLable()) {
                gu8LogoData = 0;
                gu8PrintActionState = 2;
            }
            break;
        case 2:
            Address = gu8LogoData * BITMAP_ARRAY_LENGTH_BYTES + MEMORY_LOGO_ADDRESS;
            if (gu8LogoData < BITMAP_ARRAY_LENGTH_INDEX) {
                if (LoadFromMemory(Address, gu8PrintActionBuffer, BITMAP_ARRAY_LENGTH_BYTES)) {
                    ZLPPirentLOGO(gu8PrintActionBuffer, BITMAP_ARRAY_LENGTH_BYTES);
                    gu8LogoData++;
                }
                return (0);
            }
            gu8PrintActionState = 3;
            gu8LogoData = 0;
            break;
        case 3:
            if (gpPrintActionProduct->ProductStrings.LengthName) {
                copyBuff(gu8PrintActionBuffer, gpPrintActionProduct->ProductStrings.ProductName, gpPrintActionProduct->ProductStrings.LengthName);
                ZLPsetData(gu8PrintActionBuffer, gpPrintActionProduct->ProductStrings.LengthName, 10, 55, 'a', ZLP_ROTAION_0, ZLP_TEXT);
            }
            gu8PrintActionState = 4;
            break;
        case 4:
            if (gpPrintActionProduct->ProductStrings.LengthVersion) {
                size = appPrintMessage(gu8PrintActionBuffer, 0, MSG_PRODUCT_VERSION);
                copyBuff(gu8PrintActionBuffer + size, (gpPrintActionProduct->ProductStrings.VersionName), gpPrintActionProduct->ProductStrings.LengthVersion);
                size += gpPrintActionProduct->ProductStrings.LengthVersion;
                ZLPsetData(gu8PrintActionBuffer, size, 10, 78, 'a', ZLP_ROTAION_0, ZLP_TEXT);
            }
            gu8PrintActionState = 5;
            break;
        case 5:
            size = appPrintMessage(gu8PrintActionBuffer, 0, MSG_PRODUCT_SERIAL);
            size = PrintProductSerial(gu8PrintActionBuffer, size, (&gpPrintActionProduct->ProductPrint));
            ZLPsetData(gu8PrintActionBuffer, size, 10, 101, 'a', ZLP_ROTAION_0, ZLP_TEXT);
            gu8PrintActionState = 6;
            break;
        case 6:
            size = PrintProductSerial(gu8PrintActionBuffer, 0, (&gpPrintActionProduct->ProductPrint));
            ZLPsetData(gu8PrintActionBuffer, size, 10, 125, 'a', ZLP_ROTAION_0, ZLP_BAR);
            gu8PrintActionState = 7;
            break;
        case 7:
            u16TOASII(gu8PrintActionBuffer, gpPrintActionProduct->ProductPrint.PrintCode);
            ZLPsetData(gu8PrintActionBuffer, 5, 10, 170, 'a', ZLP_ROTAION_0, ZLP_TEXT);
            gu8PrintActionState = 8;
            break;
        case 8:
            size = appPrintMessage(gu8PrintActionBuffer, 0, MSG_LABLE_SITE);
            ZLPsetData(gu8PrintActionBuffer, size, 101, 170, 'a', ZLP_ROTAION_0, ZLP_TEXT);
            gu8PrintActionState = 9;
            break;
        case 9:
            size = appPrintMessage(gu8PrintActionBuffer, 0, MSG_LABLE_MADE);
            ZLPsetData(gu8PrintActionBuffer, size, 395, 20, 'a', ZLP_ROTAION_90, ZLP_TEXT);
            gu8PrintActionState = 10;
            break;
        case 10:
            ZLPPrintNOW(1);
            gu8PrintActionState = 0;
            return (1);
            break;
        default:
            gu8PrintActionState = 0;
            break;
    }
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < PrintActionInit>                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintActionInit                                                            |  
 | < @Description       : Init all Variables in the Prinit Action System                                                       |                                                        |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void PrintActionInit() {
    gu8PrintActionState = 0;
    gu8LogoData = 0;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < PrintAction>                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintAction                                                            |  
 | < @Description       : assignent Product To Print                                                      |                                                        |
 | < @return            : void                                                                         |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void PrintAction(stProduct_t *Product) {
    gu8PrintActionState = 0;
    gu8LogoData = 0;
    gpPrintActionProduct = Product;
}