
#include "../inc/appRes.h"

static pFuncParam_t gpkeyNumberEventValue;
static pFunc_t gpF1_Action;
static pFunc_t gpF2_Action;
static pFunc_t gpF3_Action;
static pFunc_t gpEnterAction;
static pFunc_t gpCencelAction;
static uint8_t gu8ByteValueNumber;
static pFunc_t gpF_Action;
/*
 --------------------------------------------------------------------------------------------------------
 |                            < InitNumberCallBacks  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InitNumberCallBacks                                                       |
 | < @Description       : Initliaztion value of Pinter callback                                          |                                                  |                                                           
 | < @return            : void                                                                           |                     
 --------------------------------------------------------------------------------------------------------
 */
static void InitNumberCallBacks(uint8_t s);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_1(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_2(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_3(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_4(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_5(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_6(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_7(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_8(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_9(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_10(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_11(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_12(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_14(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                       |
 | < @Description       : key1 Event Handle                                                             |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_15(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                   |
 | < @Description       : key1 Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_16(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyNumbers  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  keyNumbers                                                   |
 | < @Description       : keyNumbers Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyNumbers(stkey_t *key);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyEvent  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  keyEvent                                                   |
 | < @Description       : keyNumbers Event keyEvent                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyEvent(stkey_t *key);

/*
 --------------------------------------------------------------------------------------------------------
 |                            < CommanEventHandles  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  CommanEventHandles                                             |
 | < @Description       : Shard Events between Multi Modules                                            |  
 | < @Param Tab         : Enable Tab or not 0 is disable tab and 1is enable tab                         |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void CommanEventHandles(pFuncParam_t Register) {
    KeypadRegisterEvent(keyTime_1, 0);
    KeypadRegisterEvent(keyTime_2, 1);
    KeypadRegisterEvent(keyTime_3, 2);
    KeypadRegisterEvent(keyTime_5, 4);
    KeypadRegisterEvent(keyTime_6, 5);
    KeypadRegisterEvent(keyTime_7, 6);
    KeypadRegisterEvent(keyTime_9, 8);
    KeypadRegisterEvent(keyTime_10, 9);
    KeypadRegisterEvent(keyTime_11, 10);
    KeypadRegisterEvent(keyTime_14, 13);
    gpkeyNumberEventValue = Register;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < CommanEventFunctions  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : CommanEventFunctions                                          |
 | < @Description       : Register comman function                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void CommanEventFunctions(pFunc_t RegisterF1, pFunc_t RegisterF2, pFunc_t RegisterF3, pFunc_t RegisterEnter, pFunc_t RegisterCencel) {
    if (RegisterF1 != NULL) {
        gpF1_Action = RegisterF1;
        KeypadRegisterEvent(keyTime_4, 3);
    }
    if (RegisterF2 != NULL) {
        gpF2_Action = RegisterF2;
        KeypadRegisterEvent(keyTime_8, 7);
    }
    if (RegisterF3 != NULL) {
        gpF3_Action = RegisterF3;
        KeypadRegisterEvent(keyTime_12, 11);
    }
    if (RegisterCencel != NULL) {
        gpCencelAction = RegisterCencel;
        KeypadRegisterEvent(keyTime_15, 14);
    }
    if (RegisterEnter != NULL) {
        gpEnterAction = RegisterEnter;
        KeypadRegisterEvent(keyTime_16, 15);
    }
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
static uint8_t keyTime_1(stkey_t *key) {
    gu8ByteValueNumber = '1';
    keyNumbers(key);
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
static uint8_t keyTime_2(stkey_t * key) {
    gu8ByteValueNumber = '2';
    keyNumbers(key);
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
static uint8_t keyTime_3(stkey_t * key) {
    gu8ByteValueNumber = '3';
    keyNumbers(key);
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
static uint8_t keyTime_5(stkey_t * key) {
    gu8ByteValueNumber = '4';
    keyNumbers(key);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < key1Time  >                                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  key1Time                                                       |
 | < @Description       : key1 Event Handle                                                             |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyTime_6(stkey_t * key) {
    gu8ByteValueNumber = '5';
    keyNumbers(key);
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
static uint8_t keyTime_7(stkey_t * key) {
    gu8ByteValueNumber = '6';
    keyNumbers(key);
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
static uint8_t keyTime_9(stkey_t * key) {
    gu8ByteValueNumber = '7';
    keyNumbers(key);
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
static uint8_t keyTime_10(stkey_t * key) {
    gu8ByteValueNumber = '8';
    keyNumbers(key);
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
static uint8_t keyTime_11(stkey_t * key) {
    gu8ByteValueNumber = '9';
    keyNumbers(key);
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

/*0---> A,B,C,D*/
static uint8_t keyTime_14(stkey_t * key) {
    gu8ByteValueNumber = '0';
    keyNumbers(key);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < InitNumberCallBacks  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void InitNumberCallBacks                                                       |
 | < @Description       : Initliaztion value of Pinter callback                                          |                                                  |                                                           
 | < @return            : void                                                                           |                     
 --------------------------------------------------------------------------------------------------------
 */
static void InitNumberCallBacks(uint8_t s) {

    return;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReturnMenuCallBack >                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                               |  
 | < @Description       : return value of the callback                                      |                                                    |
 | < @return            : 1                                                                           |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ReturnMenuCallBack() {
    for (uint8_t i = 0; i < KEYPAD_MAX_EVENT; i++) {
        KeypadRegisterEvent(NULL, i);
    }
    gpkeyNumberEventValue = InitNumberCallBacks;
    gpCencelAction = NULL;
    gpEnterAction = NULL;
    gpF1_Action = NULL;
    gpF2_Action = NULL;
    gpF3_Action = NULL;
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
static uint8_t keyTime_12(stkey_t * key) {
    if (key->State == KEY_PRESS) {

        gpF3_Action();
    }
    KeypadResetTabCounter(key, 1);
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
static uint8_t keyTime_16(stkey_t * key) {
    gpF_Action = gpEnterAction;
    keyEvent(key);
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
static uint8_t keyTime_15(stkey_t * key) {
    gpF_Action = gpCencelAction;
    keyEvent(key);
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
static uint8_t keyTime_4(stkey_t * key) {
    gpF_Action = gpF1_Action;
    keyEvent(key);
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
static uint8_t keyTime_8(stkey_t * key) {
    gpF_Action = gpF2_Action;
    keyEvent(key);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyNumbers  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  keyNumbers                                                   |
 | < @Description       : keyNumbers Event Handle                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyNumbers(stkey_t *key) {
    if (key->State == KEY_PRESS) {
        /*key number Time Event*/
        gpkeyNumberEventValue(gu8ByteValueNumber);
    }
    KeypadResetTabCounter(key, 1);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < keyEvent  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  keyEvent                                                   |
 | < @Description       : keyNumbers Event keyEvent                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t keyEvent(stkey_t *key) {
    if (key->State == KEY_PRESS && gpF_Action != NULL) {
        gpF_Action();
    }
    KeypadResetTabCounter(key, 1);
    return (1);
}