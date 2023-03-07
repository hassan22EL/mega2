#include <stdint.h>

#include "../inc/PrintLable.h"


MenuItem(System, NullItem, NullItem, NullItem, TimeSystem, NULL, Menu_Lable, "0.SYSTEM");
MenuItem(TimeSystem, NProduct, SProduct, System, NullItem, SystemTimeCallBack, TimeSystem_Lable, "1.Time");
MenuItem(NProduct, SProduct, TimeSystem, System, NullItem, CreateProductCallBack, NProduct_Lable, "2.New Poduct"); /*Create New Product*/
MenuItem(SProduct, WorkingTime, NProduct, System, NullItem, SelectProductCallBack, SProduct_Lable, "3.Products"); /*Select Main Product to Print by Product Number*/
MenuItem(WorkingTime, DeviceType, SProduct, System, NullItem, WorkingTimeCallBack, WorkingTime_Lable, "4.Working Time"); /*Select Main Product to Print by Product Number*/
MenuItem(DeviceType, TimeSystem, WorkingTime, System, NullItem, DeviceTypeCallBack, DeviceType_Lable, "5.Device"); /*Select Main Product to Print by Product Number*/
/*
 *<@var Print Lable CallBacks Function
 */
static uint8_t gu8MemInitMem;
/*
 *<@var Print Lable CallBacks Function
 */
static uint8_t gu8MemPowerOn;
/*
 *<@var Print Lable CallBacks Function
 */
static uint8_t gu8PrintLable;
/*
 * F1 Print State
 */
static uint8_t gu8PrintF1State;
/*
 * F1 Print State
 */
static uint8_t gu8PrintF2State;
/*
 * F1 Print State
 */
static uint8_t gu8PrintF2Toggle;
/*
 * F1 Print State
 */
static uint8_t gu8StartSystemFromDisable;

/*
 * Data Save Into print
 */
static stProductPrint_t gstProductF1Print;
/*
 * Save In LoG file
 */
static uint8_t gu8LogData;
/*
 * <@var gu8EEpromState : State Value of memory
 */
static uint8_t gu8MemReadState;
/*
 * <@var gu8EEpromState : State Value of memory
 */
static uint8_t gu8MemWriteState;
/*
 * <@var gu8EEpromState : State Value of memory
 */
static uint8_t gu8MEMBuffer[EXEEPROM_MEM_MAX_BUFFER];
/*
 * <@var 
 */
static uint8_t gu8showTimeState;
/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableF1Event  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableF1Event                                                        |
 | < @Description       : Print New Lable action                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableF1Event();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableF2Event  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableF2Event                                                        |
 | < @Description       : Reset Patch of specific Number                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableF2Event();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableF3Event  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableF3Event                                                        |
 | < @Description       : Print specific Lable by Print Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableF3Event();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableModeEvent  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableModeEvent                                                        |
 | < @Description       : Print specific Lable by Print Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t PrintLableModeEvent(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableNumbersEvent  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableNumbersEvent                                                        |
 | < @Description       : Print specific Lable by Print Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableShow();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintF1CallBack  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF1CallBack                                                        |
 | < @Description       : F1 CallBacks                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintF1CallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintF2CallBack  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF2CallBack                                                          |
 | < @Description       : F2 Function                                                                   |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintF2CallBack(); /*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintF3CallBack  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF3CallBack                                                        |
 | < @Description       : F3 Function                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintF3CallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < F2EvnetNumber  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void F2EvnetNumber                                                          |
 | < @Description       : write Reset Patch                                            |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void F2EvnetNumber(uint8_t s);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < MemPowerOn >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void MemPowerOn                                                        |  
 | < @Description       : Load Data Into MEM                                        |                                                    |
 | < @return            : void                                               |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void MemPowerOn();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < F2EvnetNumber  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void F2EvnetEnter                                                             |
 | < @Description       : reset current model patch to specif value                                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void F2EvnetEnter();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < F2EvnetNumber  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void F2EvnetCencel                                                          |
 | < @Description       : cencel of this option                                           |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void F2EvnetCencel();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < AddressCurrentProduct  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void AddressCurrentProduct                                                        |
 | < @Description       : Load address of the current Product                                           |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void PrintLableInit() {
    lcdClear();
    gu8MemPowerOn = 0;

    gu8PrintLable = 1;
    gu8PrintF1State = 0;
    gu8PrintF2State = 0;
    gu8PrintF2Toggle = 0;
    ReturnMenuCallBack();
    clearScllorBuffer();
    ClearsystemSecondEvent();
    KeypadRegisterEvent(PrintLableModeEvent, 12);
    CommanEventFunctions(PrintLableF1Event, PrintLableF2Event, PrintLableF3Event, NULL, NULL);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableF1Event  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableF1Event                                                        |
 | < @Description       : Print New Lable action                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableF1Event() {
    gu8PrintLable = 3;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableF2Event  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableF2Event                                                        |
 | < @Description       : Reset Patch of specific Number                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableF2Event() {
    gu8PrintLable = 4;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableF3Event  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableF3Event                                                        |
 | < @Description       : Print specific Lable by Print Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableF3Event() {
    gu8PrintLable = 5;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableCallBack  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableCallBack                                                        |
 | < @Description       : Main Function To Print Lable                                        |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void PrintLableCallBack() {

    switch (gu8PrintLable) {
        case 0:
            MemPowerOn();
            break;
        case 1:
            PrintLableShow();
            break;
        case 2:
            if (menuIsOpen() == 0) {/*close the Menue*/
                PrintLableInit();
            }
            break;
        case 3:
            PrintF1CallBack();
            break;
        case 4:
            PrintF2CallBack();
            break;
        case 5:
            PrintF3CallBack();
            break;
        default:
            PrintLableInit();
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableNumbersEvent  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableNumbersEvent                                                        |
 | < @Description       : Print specific Lable by Print Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintLableShow() {
    tm_t Date;
    uint8_t buf[LCD_NUMBER_OF_BYTE] = {0x20};
    uint8_t *Byte;
    time_t t;
    if (lcdIsBusy())
        return;

    if (!systemSecondEvent())
        return;
    Byte = (uint8_t *) (&Date);
    DateTimeFromTimeStamp(&Date, systemNow());
    for (uint8_t i = 0; i < 2; i++) {
        print2d(Byte[2 - i], buf, i * 3);
        print2d((Byte [4 + i]), buf, ((i * 3) + 11));
    }
    buf[13] = '-';
    if (systemReadHalfSecond()) {
        buf[2] = ':';
    } else {
        buf[2] = ' ';
    }
    lcdwritebuf(0, 0, buf, LCD_NUMBER_OF_BYTE);
    t = systemNow();
    switch (gu8showTimeState) {
        case 0:
            if ((t < gstWorkingTime.StartTime) || ((t >= gstWorkingTime.EndTime))) {
                ReturnMenuCallBack();
                KeypadRegisterEvent(PrintLableModeEvent, 12);
                LoadCurrentProductPrintIntoIntoPrint(&gstProductF1Print);
                gstProductF1Print.PrintCode++;
                gstWorkingTime.StartTime += NUMBER_OF_SECOND_PER_DAY;
                gstWorkingTime.EndTime += NUMBER_OF_SECOND_PER_DAY;
                WriteMessage(1, MSG_SYSTEM_DIABLED);
                gu8showTimeState = 1; /*start off state*/
                return;
            }
            PrintProductInLCD();
            break;
        case 1:
            if (CurrentProductSaveNewPatch(&gstProductF1Print)) {
                gu8showTimeState = 2;
            }
            break;
        case 2:
            if (SaveIntoMemory(CURRENT_WORKINGTIME_ADDRESS, (uint8_t *) & gstWorkingTime, 8)) {
                gu8showTimeState = 3;
            }
            break;
        case 3:
            if ((t >= gstWorkingTime.StartTime) && ((t < gstWorkingTime.EndTime))) {
                PrintLableInit();
                gu8showTimeState = 0;
            }
            break;
        default:
            gu8showTimeState = 0;
            break;
    }
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintLableModeEvent  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintLableModeEvent                                                        |
 | < @Description       : Print specific Lable by Print Lable Code and Patch Number                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t PrintLableModeEvent(stkey_t * key) {
    if (key->State == KEY_PRESS) {
        ReturnMenuCallBack();
        menuStart(&System);
        gu8PrintLable = 2;
    }
    KeypadResetTabCounter(key, 1);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintF1CallBack  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF1CallBack                                                        |
 | < @Description       : F1 CallBacks                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintF1CallBack() {
    memAddresst_t Address;
    switch (gu8PrintF1State) {
        case 0:
            ReturnMenuCallBack();
            LoadCurrentProductPrintIntoIntoPrint(&gstProductF1Print);
            if (gstProductF1Print.Time < systemNow()) {
                gstProductF1Print.PatchNumber++;
                gstProductF1Print.Time = systemNow();
                if (getSystemType()) {
                    StartConnected(&gstProductF1Print);
                    gu8PrintF1State = 1;
                } else {
                    gu8PrintF1State = 2;
                }
            }
            break;
        case 1:
            if (ConnectionDecive()) {
                gu8PrintF1State = 2;
            }
            break;
        case 2:
            /*save Current Into Memory*/
            if (CurrentProductSaveNewPatch(&gstProductF1Print)) {
                gu8PrintF1State = 3;
            }
            break;
        case 3:
            Address = (gu8LogData * sizeof (stProductPrint_t)) + MEMORY_LOG_PRODUCT_ADD;
            if (SaveIntoMemory(Address, (uint8_t *) (&gstProductF1Print), sizeof (stProductPrint_t))) {
                gu8LogData++;
                gu8PrintF1State = 4;
            }
            break;
        case 4:

            if (SaveIntoMemory(CURRENT_LOGDATA_INDEX_ADDRESS, &gu8LogData, 1)) {
                PrintCurrentProduct();
                gu8PrintF1State = 5;
            }
            break;
        case 5:
            if (PrintActionCallBack()) {
                PrintLableInit();
            }
            break;
        default:
            PrintLableInit();
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintF2CallBack  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF2CallBack                                                          |
 | < @Description       : F2 Function                                                                   |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintF2CallBack() {
    uint8_t s[2];
    switch (gu8PrintF2State) {
        case 0:
            ReturnMenuCallBack();
            CommanEventHandles(F2EvnetNumber);
            CommanEventFunctions(NULL, NULL, NULL, F2EvnetEnter, F2EvnetCencel);
            lcdClear();
            LoadCurrentProductPrintIntoIntoPrint(&gstProductF1Print);
            WriteMessage(0, MSG_RESET_PATCH);
            print2d(gstProductF1Print.PatchNumber, s, 0);
            lcdwritebuf(1, 0, s, 2);
            lcdBlink(1, 0);
            lcdUpdateNow();
            gu8PrintF2State = 1;
            break;
        case 1:
            break;
        case 2:
            if (CurrentProductSaveNewPatch(&gstProductF1Print)) {
                PrintLableInit();
            }
            break;
        default:
            PrintLableInit();
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < PrintF3CallBack  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintF3CallBack                                                        |
 | < @Description       : F3 Function                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void PrintF3CallBack() {
    PrintLableInit();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < setLogDataIndex  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void setLogDataIndex                                                          |
 | < @Description       : set log index from other modules                                              |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void setLogDataIndex(uint8_t logIndex) {
    gu8LogData = logIndex;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < F2EvnetNumber  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void F2EvnetNumber                                                          |
 | < @Description       : write Reset Patch                                            |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void F2EvnetNumber(uint8_t s) {
    uint8_t s2[2];
    print2d(gstProductF1Print.PatchNumber, s2, 0);
    s2[gu8PrintF2Toggle] = s;
    gstProductF1Print.PatchNumber = conv2d(s2);
    lcdwritebuf(1, 0, s2, 2);
    gu8PrintF2Toggle ^= 1;
    lcdBlink(1, gu8PrintF2Toggle);
    lcdUpdateNow();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < F2EvnetNumber  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void F2EvnetEnter                                                             |
 | < @Description       : reset current model patch to specif value                                     |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void F2EvnetEnter() {
    gu8PrintF2State = 2;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < F2EvnetNumber  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void F2EvnetCencel                                                          |
 | < @Description       : cencel of this option                                           |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void F2EvnetCencel() {
    PrintLableInit();
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < MemPowerOn >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void MemPowerOn                                                        |  
 | < @Description       : Load Data Into MEM                                        |                                                    |
 | < @return            : void                                               |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
static void MemPowerOn() {
    memAddresst_t address;
    switch (gu8MemPowerOn) {
        case 0:/**/
            if (LoadFromMemory(0, gu8MEMBuffer, 3)) {
                if ((gu8MEMBuffer[0] == 23) && (gu8MEMBuffer[1] == 11) && (gu8MEMBuffer[2] == 96)) {
                    gu8MemPowerOn = 2;
                    return;
                }
                WriteMessage(1, MSG_MEM_INIT);
                WriteMessage(0, MSG_PRODUCT_PLEASE_WAIT);
                gu8MemPowerOn = 1;
            }
            break;
        case 1:/*Reset Mem*/
            if (exeepromReady()) {
                if (gu8MemInitMem == 224) {
                    gu8MemInitMem = 0;
                    gu8MEMBuffer[0] = 23;
                    gu8MEMBuffer[1] = 11;
                    gu8MEMBuffer[2] = 96;
                    exeepromWriteBuffer(0, gu8MEMBuffer, 32);
                    PrintLableInit();

                }
                for (uint8_t i = 0; i < 32; i++) {
                    gu8MEMBuffer[i] = 0x00;
                }
                address = (gu8MemInitMem << 5) + 32; /*go to Index second Page*/
                exeepromWriteBuffer(address, gu8MEMBuffer, 32);
                gu8MemInitMem++;
            }
            break;
        case 2:/*load current Index and Last Index*/
            if (LoadFromMemory(LAST_PRODUCT_ADDRESS, gu8MEMBuffer, 12)) {
                ProductSetLastIndex(gu8MEMBuffer[0]);
                ProductSetCurrentIndex(gu8MEMBuffer[1]);
                setDeciveActive(gu8MEMBuffer[2]);
                gu8LogData = gu8MEMBuffer[3];
                copyBuff(&gstWorkingTime, gu8MEMBuffer + 4, 8);
                gu8MemPowerOn = 3;
            }
            break;
        case 3:/*load current Product*/
            if (LoadCurrentProduct()) {
                PrintLableInit();
                gu8MemPowerOn = 0;
            }
            break;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < LoadFromMemory >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                                        |  
 | < @Description       : load Data From memory with specific                                            |                                                    |
 | < @return            : return done value of the memory                                                |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t LoadFromMemory(memAddresst_t address, uint8_t *buf, uint8_t nByte) {
    if (exeepromReady() == 0)
        return (0);
    if (gu8MemReadState) {
        exEepromRead(gu8MEMBuffer);
        copyBuff(buf, gu8MEMBuffer, nByte);
        gu8MemReadState = 0;
        return (1);
    }
    exeepromRequestSteram(address, nByte);
    gu8MemReadState = 1;
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < LoadFromMemory >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                                        |  
 | < @Description       : save data into  memory with specific                                            |                                                    |
 | < @return            : return done value of the memory                                                |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t SaveIntoMemory(memAddresst_t address, uint8_t *buf, uint8_t nByte) {
    if (exeepromReady() == 0)
        return (0);
    if (gu8MemWriteState) {
        gu8MemWriteState = 0;
        return (1);
    }
    copyBuff(gu8MEMBuffer, buf, nByte);
    exeepromWriteBuffer(address, gu8MEMBuffer, nByte);
    gu8MemWriteState = 1;
    return (0);
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < InitMem >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void InitMem                                                        |  
 | < @Description       : init all values in memory                                          |                                                    |
 | < @return            : void                                               |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void InitMem() {
    gu8MemReadState = 0;
    gu8MemWriteState = 0;
    gu8PrintLable = 0;
}