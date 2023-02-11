/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : keypad.c                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 72 Byte Used                                                             |
| < PROGRAM USAGE            : (1512 Byte) (756 Instruction)                                            |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */


#include "../../../inc/mega.h"
#if defined (KEYPAD_MODULE)
#if  KEYPAD_MODULE 
/*
 ---------------------------------------------------------------------------------------------------------
 |                               <Keypad Definition>                                                     |
 ---------------------------------------------------------------------------------------------------------
 |< @KEYPAD_MAX_ROW             : max row in keypad and this value less than 8                           |
 |< @KEYPAD_MAX_COL             : max clomun in keypad and this value less than 8                        |
 |< @KEYPAD_MAX_BUFFER          : max key stored                                                         |
 |< @KEYPAD_DEDEBOUND_TIME      : time required to press or released switch                              |
 |< @KEYPAD_LONG_TIME           : time required to long press                                            |
 |< @KEYPAD_REPEAT_TIME         : time required to repeat key                                            |
 |< @KEYPAD_REPEAT_RATE         : time required between repeat key                                       |
 |< @note                       : keypad state is fixed active low                                       |                 
 ---------------------------------------------------------------------------------------------------------
 */

#ifndef      KEYPAD_MAX_ROW 
#define      KEYPAD_MAX_ROW               (4)/*default value*/
#endif




#ifndef      KEYPAD_MAX_COL               
#define      KEYPAD_MAX_COL               (4) /*default value*/
#endif




#define       KEY_DEBOUND_COUNT          ((KEYPAD_DEDEBOUND_TIME * 1000UL) / (KEY_PERIDIC_TASK*N_OF_US_REQUIRED))
#if           KEY_DEBOUND_COUNT < 255
#define       KEYPAD_DE_COUNT     KEY_DEBOUND_COUNT-1
#else 
#define       KEYPAD_DE_COUNT      255
#endif

#ifndef      KEYS_QUEUE_SIZE  
#define      KEYS_QUEUE_SIZE               (3)
#endif
/*
 ---------------------------------------------------------------------------------------------------------
 |                            < KEYPAD_COMMONS_PINS  >                                                   |
 ---------------------------------------------------------------------------------------------------------
 */

/***********************KEYPAD01 C01********************/
#ifndef KEYPAD_C01_PIN
#define KEYPAD_C01_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C02********************/
#ifndef KEYPAD_C02_PIN
#define KEYPAD_C02_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C03********************/
#ifndef KEYPAD_C03_PIN
#define KEYPAD_C03_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 C04********************/
#ifndef KEYPAD_C04_PIN
#define KEYPAD_C04_PIN          NOT_A_PIN
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < KEYPAD_SWITCH_PINS  >                                                   |
 ---------------------------------------------------------------------------------------------------------
 */
/***********************KEYPAD01 SW01********************/
#ifndef KEYPAD_SW01_PIN

+#define KEYPAD_SW01_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW02_PIN
#define KEYPAD_SW02_PIN          NOT_A_PIN
#endif

/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW03_PIN
#define KEYPAD_SW03_PIN          NOT_A_PIN
#endif
/***********************KEYPAD01 SW02********************/
#ifndef KEYPAD_SW04_PIN
#define KEYPAD_SW04_PIN         NOT_A_PIN
#endif

/****************************KEYPAD MAX EVENT****************/
#ifndef KEYPAD_MAX_EVENT  
#define  KEYPAD_MAX_EVENT          KEYPAD_MAX_ROW*KEYPAD_MAX_COL
#endif



/*
 ---------------------------------------------------------------------------------------------------------
 |                            < Create keyCloumn Keypad Definition  >                                     |
 ---------------------------------------------------------------------------------------------------------
 */
#if KEYPAD_MAX_COL == 4
#define  MAX_VALUE_READ_COL        15
#elif KEYPAD_MAX_COL == 3
#define  MAX_VALUE_READ_COL        7
#elif KEYPAD_MAX_COL == 2
#define  MAX_VALUE_READ_COL        3
#elif KEYPAD_MAX_COL == 1
#define  MAX_VALUE_READ_COL        1
#else
#error    "please define number of column used in keypad"
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                            < Create keyRows Keypad Definition  >                                      |
 ---------------------------------------------------------------------------------------------------------
 */
#if KEYPAD_MAX_ROW == 4
#define  MAX_VALUE_READ_ROW        15
#elif KEYPAD_MAX_ROW == 3
#define  MAX_VALUE_READ_ROW        7
#elif KEYPAD_MAX_ROW == 2
#define  MAX_VALUE_READ_ROW        3
#elif KEYPAD_MAX_ROW == 1
#define  MAX_VALUE_READ_ROW        1
#else
#error    "please define number of rows used in keypad"
#endif

#define  MAX_BIT_OF_CODE       (KEYPAD_MAX_COL +   KEYPAD_MAX_ROW)
/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Typedef                                                    |
 --------------------------------------------------------------------------------------------------------- 
 */
typedef union {
    uint8_t Flags;

    struct {
        unsigned TabCounter : 4;
        unsigned LongTabFlag : 1;
        unsigned NewCallBackHandle : 1;
        unsigned ScanTGL : 1;
        unsigned MultiTabFlag : 1;
    };
} ukeyStates_t;

/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
#if COMPILER_TYPE == GCC
const keypadConstantCode_t PROGMEM NO_CODE = {0xFF, 0, 0, (keypadConstantCode_t *) NULL};
#elif COMPILER_TYPE == XC
const keypadConstantCode_t  NO_CODE = {0xFF, 0, 0, (keypadConstantCode_t *) NULL};
#endif

/*
 ---------------------------------------------------------------------------------------------------------
 |                               Keypad scan Variables                                                   |
 --------------------------------------------------------------------------------------------------------- 
 */
/*
 * <@var gpFunKeyScan     : Pointer To Function Scan Code Run In ISR Function to get key Code
 */
static volatile pFunc_t gpFunKeyScan;
/*
 * @var guKeyScanRow            : Key scan Code With Row Value Run In ISR        
 */
static volatile uint8_t guKeyScanRow;
/*
 * @var guKeyScanCOL            : Key scan Code with Column Value Run In ISR        
 */
static volatile uint8_t guKeyScanCOL;
/*
 * @var gu8KeyCode              : System Have a New Code  form ISR
 */
static volatile uint8_t gu8KeyCode;
/*
 * @var gu8CurrentCode              : System Have a New Code 
 */
static volatile uint8_t gu8CurrentCode;
/*
 * @var gu8LastCode              : System Have a Last  Code 
 */
static volatile uint8_t gu8LastCode;
/*
 * @var gu8BeforeLastCode              : System Have a before Last Code 
 */
static volatile uint8_t gu8BeforeLastCode;
/*
 * @var gu8KeyDounceCounter     : bounce Counter to event Key
 */
static volatile uint8_t gu8KeyDounceCounter;
/*
 * <@var gpFunKeyEvents :save Call Packs array of Key events
 */
static volatile pFunckeyEvent_t gpFunKeyEvents[KEYPAD_MAX_EVENT];
/*
 * <@var gKeyEventQueue  :array of Keys  Save Last 3 keys 
 */
static stkey_t gKeyEventQueue[KEYS_QUEUE_SIZE];
/*
 * <@var  gstKeyStructescriptor          : Queue Descriptor
 */
static stBufferStructDescriptor_t gstKeyQueueStructDescriptor;
/*
 * <@var gstKeyLongPreeTimeOut           : Check Long Press TimeOut Or Not          
 */
static stTimer_TimeOut_t gstKeyLongPreeTimeOut;
/*
 * < @var gstKeyMutiTabTimeOut           :Check Multi Tab Time out    
 */
static stTimer_TimeOut_t gstKeyMultiTabTimeOut;
/*
 * <@var guKeypadFlags                  : Number of Keypad used 
 */
static volatile ukeyStates_t guKeypadFlags;
/*
 * <@var gpcKeyEvents                  : Pointer to const Key Events
 */
static const keypadConstantCode_t *gpcKeyEvents;
/*
 * <@var gpcKeyEvents                  : Pointer to const Key Events
 */
static stkey_t gGetKey;
/*
 * <@var gpcKeyEvents                  : Pointer to const Key Events
 */
static pFunckeyEvent_t gpFunKeyEvent;
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions >                                                |
 ---------------------------------------------------------------------------------------------------------
 */
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < scanRows >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t scanRows                                                               |  
 | < @Description       : get Rows Value from Pins                                                       | 
 | < @return            : return from 0 to f                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t scanRows(void);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < RowsInputColsOutput >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void RowsInputColsOutput                                                       |  
 | < @Description       : set Rows as a InPut and Cols as OutPut                                         | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void RowsInputColsOutput(void);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyDeBoundCountFun >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyDeBoundCountFun                                                        |  
 | < @Description       : wait For de-bounce is done                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeyDeBoundCountFun(void);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyAssignCode >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyAssignCode                                                             |  
 | < @Description       : check the Code Value and Assign New Code                                       | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeyAssignCode(void);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadQueueKey >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadQueueKey                                                            |  
 | < @Description       : get Key and Put into Queue                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeypadPutIntoQueue(void);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadGetFromQueue >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadQueueKey                                                            |  
 | < @Description       : get Key from Queue and run Callback                                            | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeypadGetFromQueue(void);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadIsMultiKeyPress >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadIsMultiKeyPress                                                     |  
 | < @Description       : check the Multi KeyPrss Or Not                                                 | 
 | <@Param   Code       : Code Check Value                                                               |
 | < @return            : 0 no Multi Press 1is multi press                                               |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t KeypadIsMultiKeyPress(uint8_t Code);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextCode                                                             |
 | < @Description       : return Next OF The Current code                                               |    
 | < @Param Code      : pointer to constant code                                                        |           
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const keypadConstantCode_t * getNextCode(const keypadConstantCode_t *Code);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  getNextCode                                                             |
 | < @Description       : return code                                                                   |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return            : Const Code                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getCode(const keypadConstantCode_t *Code);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getTone >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function           : uint8_t  getTone                                                                |
 | < @Description        : return Tone Generate                                                         |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return            : Const tone                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint16_t getTone(const keypadConstantCode_t *Code);
/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getIndex >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function           : uint8_t  getIndex                                                            |
 | < @Description        : return Index of Callback                                                     |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return             : Const Index                                                                  |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getIndex(const keypadConstantCode_t *Code);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Internal Functions >                                                     |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < scanRows >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t scanRows                                                               |  
 | < @Description       : get Rows Value from Pins                                                       | 
 | < @return            : return from 0 to f                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t scanCOLs(void) {
    uint8_t cols;
    cols = 0;
#if KEYPAD_MAX_COL == 4
    bitWrite8Bit(cols, 0, digitalPinRead(KEYPAD_SW01_PIN));
    bitWrite8Bit(cols, 1, digitalPinRead(KEYPAD_SW02_PIN));
    bitWrite8Bit(cols, 2, digitalPinRead(KEYPAD_SW03_PIN));
    bitWrite8Bit(cols, 3, digitalPinRead(KEYPAD_SW04_PIN));
#elif KEYPAD_MAX_COL == 3
    bitWrite8Bit(cols, 0, digitalPinRead(KEYPAD_SW01_PIN));
    bitWrite8Bit(cols, 1, digitalPinRead(KEYPAD_SW02_PIN));
    bitWrite8Bit(cols, 2, digitalPinRead(KEYPAD_SW03_PIN));
#elif KEYPAD_MAX_COL== 2
    bitWrite8Bit(cols, 0, digitalPinRead(KEYPAD_SW01_PIN));
    bitWrite8Bit(cols, 1, digitalPinRead(KEYPAD_SW02_PIN));
#elif KEYPAD_MAX_COL == 1
    bitWrite8Bit(cols, 0, digitalPinRead(KEYPAD_SW01_PIN));
#endif
    return cols;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < scanRows >                                                          |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t scanRows                                                               |  
 | < @Description       : get Rows Value from Pins                                                       | 
 | < @return            : return from 0 to f                                                             |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t scanRows(void) {
    uint8_t rows;
    rows = 0;
#if KEYPAD_MAX_ROW == 4
    bitWrite8Bit(rows, 0, digitalPinRead(KEYPAD_C01_PIN));
    bitWrite8Bit(rows, 1, digitalPinRead(KEYPAD_C02_PIN));
    bitWrite8Bit(rows, 2, digitalPinRead(KEYPAD_C03_PIN));
    bitWrite8Bit(rows, 3, digitalPinRead(KEYPAD_C04_PIN));
#elif KEYPAD_MAX_ROW == 3
    bitWrite8Bit(rows, 0, digitalPinRead(KEYPAD_C01_PIN));
    bitWrite8Bit(rows, 1, digitalPinRead(KEYPAD_C02_PIN));
    bitWrite8Bit(rows, 2, digitalPinRead(KEYPAD_C03_PIN));
#elif KEYPAD_MAX_ROW== 2
    bitWrite8Bit(rows, 0, digitalPinRead(KEYPAD_C01_PIN));
    bitWrite8Bit(rows, 1, digitalPinRead(KEYPAD_C02_PIN));
#elif KEYPAD_MAX_ROW == 1
    bitWrite8Bit(rows, 0, digitalPinRead(KEYPAD_C01_PIN));
#endif
    return rows;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < RowsInputColsOutput >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void RowsInputColsOutput                                                       |  
 | < @Description       : set Rows as a Input Pullup and Cols as OutPut                                  | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void RowsInputColsOutput(void) {
    if (guKeypadFlags.ScanTGL == 0) {
#if KEYPAD_MAX_ROW == 4
        digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_C02_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_C03_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_C04_PIN, MODE_INPUT_PULLUP);
#elif KEYPAD_MAX_ROW == 3
        digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_C02_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_C03_PIN, MODE_INPUT_PULLUP);
#elif KEYPAD_MAX_ROW == 2
        digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_C02_PIN, MODE_INPUT_PULLUP);
#elif KEYPAD_MAX_ROW == 1
        digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT_PULLUP);
#endif
#if KEYPAD_MAX_COL == 4
        digitalpinMode(KEYPAD_SW01_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_SW02_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_SW03_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_SW04_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_SW01_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_SW02_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_SW03_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_SW04_PIN, GPIO_LOW);
#elif KEYPAD_MAX_COL == 3
        digitalpinMode(KEYPAD_SW01_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_SW02_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_SW03_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_SW01_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_SW02_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_SW03_PIN, GPIO_LOW);
#elif KEYPAD_MAX_COL == 2
        digitalpinMode(KEYPAD_SW01_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_SW02_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_SW01_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_SW02_PIN, GPIO_LOW);
#elif KEYPAD_MAX_COL == 1
        digitalpinMode(KEYPAD_SW01_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_SW01_PIN, GPIO_LOW);
#endif
    } else {

#if KEYPAD_MAX_COL == 4
        digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_SW02_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_SW03_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_SW04_PIN, MODE_INPUT_PULLUP);
#elif KEYPAD_MAX_COL == 3
        digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_SW02_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_SW03_PIN, MODE_INPUT_PULLUP);
#elif KEYPAD_MAX_COL == 2
        digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT_PULLUP);
        digitalpinMode(KEYPAD_SW02_PIN, MODE_INPUT_PULLUP);
#elif KEYPAD_MAX_COL == 1
        digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT_PULLUP);
#endif

#if KEYPAD_MAX_ROW == 4
        digitalpinMode(KEYPAD_C01_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_C02_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_C03_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_C04_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_C01_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_C02_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_C03_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_C04_PIN, GPIO_LOW);
#elif KEYPAD_MAX_ROW == 3
        digitalpinMode(KEYPAD_C01_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_C02_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_C03_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_C01_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_C02_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_C03_PIN, GPIO_LOW);
#elif KEYPAD_MAX_ROW == 2
        digitalpinMode(KEYPAD_C01_PIN, MODE_OUTPUT);
        digitalpinMode(KEYPAD_C02_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_C01_PIN, GPIO_LOW);
        digitalPinWrite(KEYPAD_C02_PIN, GPIO_LOW);

#elif KEYPAD_MAX_ROW == 1
        digitalpinMode(KEYPAD_C01_PIN, MODE_OUTPUT);
        digitalPinWrite(KEYPAD_C02_PIN, GPIO_LOW);
#endif



    }
    gpFunKeyScan = KeyDeBoundCountFun;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyDeBoundCountFun >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyDeBoundCountFun                                                        |  
 | < @Description       : wait For de-bounce is done                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeyDeBoundCountFun(void) {
    /*save state*/
    if (gu8KeyDounceCounter <= 1) {
        if (guKeypadFlags.ScanTGL) {
            guKeyScanCOL = scanCOLs();
        } else {
            guKeyScanRow = scanRows();
        }
        guKeypadFlags.ScanTGL = 1;
        gu8KeyDounceCounter++;
        gpFunKeyScan = RowsInputColsOutput;
        return;
    }


    if (guKeyScanCOL != scanCOLs() && guKeypadFlags.ScanTGL) {
        gu8KeyDounceCounter = 0;
        return;
    }

    if (guKeyScanRow != scanRows() && (!guKeypadFlags.ScanTGL)) {
        gu8KeyDounceCounter = 0;
        return;
    }

    if (gu8KeyDounceCounter < KEYPAD_DE_COUNT) {
        guKeypadFlags.ScanTGL ^= 1;
        gpFunKeyScan = RowsInputColsOutput;
        gu8KeyDounceCounter++;
    } else {
        guKeypadFlags.ScanTGL = 0;
        gu8KeyDounceCounter = 0;
        gpFunKeyScan = KeyAssignCode;

    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyAssignCode >                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyAssignCode                                                             |  
 | < @Description       : check the Code Value and Assign New Code                                       | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeyAssignCode(void) {

    // Set all row pins to output low
    /*scan Col*/



    if (((guKeyScanRow == MAX_VALUE_READ_ROW) && (guKeyScanCOL != MAX_VALUE_READ_COL)) || ((guKeyScanRow != MAX_VALUE_READ_ROW) && (guKeyScanCOL == MAX_VALUE_READ_COL))) {
        gpFunKeyScan = RowsInputColsOutput; /*Repeat Reading*/
        return;
    }
#if KEYPAD_MAX_COL == 4
    digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_SW02_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_SW03_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_SW04_PIN, MODE_INPUT);
#elif KEYPAD_MAX_COL == 3
    digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_SW02_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_SW03_PIN, MODE_INPUT);
#elif KEYPAD_MAX_COL == 2
    digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_SW02_PIN, MODE_INPUT);
#elif KEYPAD_MAX_COL == 1
    digitalpinMode(KEYPAD_SW01_PIN, MODE_INPUT);
#endif

#if KEYPAD_MAX_ROW == 4
    digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_C02_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_C03_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_C04_PIN, MODE_INPUT);
#elif KEYPAD_MAX_ROW == 3
    digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_C02_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_C03_PIN, MODE_INPUT);
#elif KEYPAD_MAX_ROW == 2
    digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT);
    digitalpinMode(KEYPAD_C02_PIN, MODE_INPUT);
#elif KEYPAD_MAX_ROW == 1
    digitalpinMode(KEYPAD_C01_PIN, MODE_INPUT);
#endif
    gu8KeyCode = guKeyScanRow | (guKeyScanCOL << KEYPAD_MAX_ROW);
    guKeyScanRow = 0;
    guKeyScanCOL = 0;
    gpFunKeyScan = RowsInputColsOutput; /*stop Isr run*/
    return;

}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadGetFromQueue >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadQueueKey                                                            |  
 | < @Description       : get Key from Queue and run Callback                                            | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeypadGetFromQueue(void) {
    if (!guKeypadFlags.NewCallBackHandle) {
        if (getStruct(&gstKeyQueueStructDescriptor, &gGetKey)) {
            const keypadConstantCode_t *i = gpcKeyEvents;
            for (; i && i != &NO_CODE; i = getNextCode(i)) {
                gpFunKeyEvent = gpFunKeyEvents[getIndex(i)];
                if (gpFunKeyEvent != NULL && gGetKey.Keycode == getCode(i)) {
                    /*tone Generation*/
#if defined TONE_MODULE
#if TONE_MODULE
                    Toneplay(TONE_PIN0_GPIO, 0, getTone(i), 50, 100);
#endif
#endif
                    guKeypadFlags.NewCallBackHandle = 1;
                    return;
                }
            }
            return;
        }
        return;
    }

    if (gpFunKeyEvent(&gGetKey)) {
        gpFunKeyEvent = NULL;
        guKeypadFlags.NewCallBackHandle = 0;
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadQueueKey >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadQueueKey                                                            |  
 | < @Description       : get Key and Put into Queue                                                     | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static void KeypadPutIntoQueue(void) {

    stkey_t key;

    if (gu8CurrentCode == gu8KeyCode) {
        /*same key check long press time out */
        if ((guKeypadFlags.LongTabFlag) && (!sysIsTimeoutS(&gstKeyLongPreeTimeOut))) {
            /*Long Tab is Done */
            key.Keycode = gu8CurrentCode;
            key.UserState.State = LONG_TAP;
            guKeypadFlags.LongTabFlag = 0;
            putStruct(&gstKeyQueueStructDescriptor, &key); /*Put Key Into Queue*/
            return;
        }


        return;
    }
    ATOMIC_BEGIN
    /*assignment a new Key*/
    gu8BeforeLastCode = gu8LastCode;
    gu8LastCode = gu8CurrentCode;
    gu8CurrentCode = gu8KeyCode;
    key.Keycode = gu8CurrentCode;
    ATOMIC_END
    if (gu8CurrentCode == NO_KEY) {
        /*release action*/
        key.UserState.State = KEY_RELEASE;
        guKeypadFlags.LongTabFlag = 0;
    } else if (!KeypadIsMultiKeyPress(gu8CurrentCode) && gu8LastCode == NO_KEY) {/*press before*/
        /*Press Action*/
        sysSetPeriodS(&gstKeyLongPreeTimeOut, KEYPAD_LONGPREE_TIMEOUT); /*active Long Press Time*/
        guKeypadFlags.LongTabFlag = 1; /*long Press is OK*/
        if (gu8CurrentCode == gu8BeforeLastCode && (sysIsTimeoutS(&gstKeyMultiTabTimeOut)) && !guKeypadFlags.MultiTabFlag) {
            key.UserState.TabCounter = guKeypadFlags.TabCounter++;
            key.UserState.State = MULTI_TAP;
        } else {
            /*time Out of the Multi tap or last not equles before lastkey */
            guKeypadFlags.TabCounter = 0;
            key.UserState.TabCounter = 0;
            guKeypadFlags.MultiTabFlag = 0;
            key.UserState.State = KEY_PRESS;
        }
        sysSetPeriodS(&gstKeyMultiTabTimeOut, KEYPAD_MULTITAP_TIMEOUT);
    } else {
        /*multi key Press*/
        key.UserState.State = MULTI_KEY_PRESS;
        guKeypadFlags.TabCounter = 0;
        guKeypadFlags.LongTabFlag = 0;
    }
    putStruct(&gstKeyQueueStructDescriptor, &key); /*Put Key Into Queue*/
    return;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadIsMultiKeyPress >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadIsMultiKeyPress                                                     |  
 | < @Description       : check the Multi KeyPrss Or Not                                                 | 
 | <@Param   Code       : Code Check Value                                                               |
 | < @return            : 0 no Multi Press 1is multi press                                               |                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
static uint8_t KeypadIsMultiKeyPress(uint8_t Code) {
    uint8_t ctr = 0;
    for (uint8_t i = 0; i < MAX_BIT_OF_CODE; i++) {
        if (!bitRead(Code, i)) {
            ctr++;
        }
    }
    if (ctr > 2) {

        return (1);
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getNextCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  getNextCode                                                             |
 | < @Description       : return Next OF The Current code                                               |    
 | < @Param Code      : pointer to constant code                                                        |           
 | < @return            : pointer to constant value stored in program memory                            |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const keypadConstantCode_t * getNextCode(const keypadConstantCode_t *Code) {
#if COMPILER_TYPE == GCC
    return (const keypadConstantCode_t *) pgm_read_word(&Code->Next); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const keypadConstantCode_t *) (Code->Next); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getCode >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  getCode                                                             |
 | < @Description       : return code                                                                   |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return            : Const Code                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getCode(const keypadConstantCode_t *Code) {
#if COMPILER_TYPE == GCC
    return (const uint8_t) pgm_read_byte(&Code->Code); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const uint8_t) (Code->Code); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getTone >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function           : uint8_t  getTone                                                                |
 | < @Description        : return Tone Generate                                                         |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return            : Const tone                                                                    |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint16_t getTone(const keypadConstantCode_t *Code) {
#if COMPILER_TYPE == GCC
    return (const uint16_t) pgm_read_byte(&Code->Tone); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const uint8_t) (Code->Tone); /*xc-compiler*/
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 < getIndex >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function           : uint8_t  getIndex                                                            |
 | < @Description        : return Index of Callback                                                     |    
 | < @Param Code         : pointer to constant code                                                     |           
 | < @return             : Const Index                                                                  |                                                             
 --------------------------------------------------------------------------------------------------------
 */
static const uint8_t getIndex(const keypadConstantCode_t *Code) {
#if COMPILER_TYPE == GCC
    return (const uint8_t) pgm_read_byte(&Code->Index); /*gcc-compiler*/
#elif COMPILER_TYPE == XC
    return (const uint8_t) (Code->Index); /*xc-compiler*/
#endif
}
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ISR Functions >                                                     |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyscan >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyscan                                                                   |  
 | < @Description       : primitive function run every time (ex. 10ms) (user not used)                   | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyscan() {
    if (gpFunKeyScan != NULL) {
        gpFunKeyScan();
    }
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < Loop Functions >                                                     |
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyInit >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyInit                                                                   |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)       | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyInit() {
    gpFunKeyScan = RowsInputColsOutput;
    gu8KeyDounceCounter = 0;
    gu8KeyCode = NO_KEY;
    gu8BeforeLastCode = NO_KEY;
    gu8LastCode = NO_KEY;
    gu8CurrentCode = NO_KEY;
    gpcKeyEvents = &NO_CODE;
    gpFunKeyEvent = NULL;
    structBufferInit(&gstKeyQueueStructDescriptor, gKeyEventQueue, KEYS_QUEUE_SIZE, sizeof (stkey_t));
    for (uint8_t i = 0; i < KEYPAD_MAX_EVENT; i++) {
        gpFunKeyEvents[i] = NULL;
    }
    for (uint8_t i = 0; i < KEYS_QUEUE_SIZE; i++) {
        gKeyEventQueue[i].UserState.State = KEY_RELEASE;
        gKeyEventQueue[i].UserState.TabCounter = 0;
        gKeyEventQueue[i].Keycode = 0xFF;
    }
    gGetKey.Keycode = 0xFF;
    gGetKey.UserState.State = KEY_RELEASE;
    gGetKey.UserState.TabCounter = 0;
    guKeypadFlags.Flags = 0x00;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadAssignCosntEvents >                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadAssignCosntEvents                                                   |  
 | < @Description       : run Callbacks of The Const Events                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void KeypadAssignCosntEvents(const keypadConstantCode_t *keyEvents) {
    if (keyEvents && keyEvents != &NO_CODE)
        gpcKeyEvents = keyEvents;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadRegisterEvent >                                               |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadRegisterEvent                                                       |  
 | < @Description       : register call back function into Array                                         | 
 | < @Param callback    : callback Function                                                              |
 | < @Param Index       : Event Index                                                                    | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void KeypadRegisterEvent(pFunckeyEvent_t callback, uint8_t Index) {
    gpFunKeyEvents[Index] = callback;
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyPadDriver >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyPadDriver                                                              |  
 | < @Description       : run in pack ground                                                             | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void KeypadDriver() {
    /*Enable scan*/
    KeypadPutIntoQueue();
    KeypadGetFromQueue();
}

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadResetTabCounter >                                             |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadResetTabCounter                                                     |  
 | < @Description       : Reset Tab Counter                                                              | 
 | < @Param key         : pointer to assignment key                                                      |
 | < @Param tab         : Support Multitab or not                                                        |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void KeypadResetTabCounter(stkey_t *key, uint8_t Tab) {
    guKeypadFlags.TabCounter = 0;
    key->UserState.TabCounter = 0;
    guKeypadFlags.MultiTabFlag = Tab;

}
#endif
#endif