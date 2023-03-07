/* 
 * File:   F1Print.c
 * Author: hp
 *
 * Created on March 1, 2023, 11:24 AM
 */

#include "../inc/appRes.h"


/*
 *<@var Print Product : change Values of the Product
 */

/*
 * <@var F1 Print State
 */
static uint8_t gu8F1PrintState;
/*
 * <@var save Logs
 */
static uint8_t gu8SaveNewPrintInLogs;

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < PrintF1Init>                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF1Init                                                            |  
 | < @Description       : Init all Variables in the Prinit F1 System                                                       |                                                        |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void PrintF1Init() {
    gu8F1PrintState = 0;

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < PrintF1CallBack>                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF1CallBack                                                            |  
 | < @Description       : run In system Modeule                                                      |                                                        |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t PrintF1CallBack() {
    memAddresst_t Address;
    switch (gu8F1PrintState) {
        case 0:
            if(gsCurrentProduct.Time != systemNow()) {
              
                gsCurrentProduct.PatchNumber++;
                gsCurrentProduct.Time = systemNow();
                gu8F1PrintState = 1;
            }
            break;
        case 1: /*save in memory current Load*/
            if (CurrentProductSaveNewPatch(&gsCurrentProduct)) {
                gu8F1PrintState = 2;
            }
            break;
        case 2:
            Address = ((gu8SaveNewPrintInLogs * (8)) + MEMORY_LOG_PRODUCT_ADD);
            if (SaveIntoMem(Address, (uint8_t *)&gsCurrentProduct, sizeof (stProduct_t))) {
                gu8SaveNewPrintInLogs++;
                PrintAction(&gsCurrentProduct);
                gu8F1PrintState = 3;
            }
            break;
        case 3:
            if (PrintActionCallBack()) {
                gu8F1PrintState = 0;
                return (1);
            }
            break;
        default:
            break;

    }
    return (0);
}
