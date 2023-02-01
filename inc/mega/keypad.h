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
#ifndef KEYPAD_H
#define	KEYPAD_H

#include "../mega.h"
#if defined  KEYPAD_MODULE
#if KEYPAD_MODULE

typedef enum KEY_STATE {
    KEY_PRESS = 0,
    MULTI_TAP = 1,
    LONG_TAP = 2,
    MULTI_KEY_PRESS = 3,
    KEY_RELEASE = 4,
    CANCELED = 5
} KEYSTATE_t;

typedef enum {
    KEY_00 = 0x00, KEY_01 = 0x01, KEY_02 = 0x02, KEY_03 = 0x03, KEY_04 = 0x04, KEY_05 = 0x05, KEY_06 = 0x06, KEY_07 = 0x07, KEY_08 = 0x08, KEY_09 = 0x09, KEY_0A = 0x0A, KEY_0B = 0x0B, KEY_0C = 0x0C, KEY_0D = 0x0D, KEY_0E = 0x0E,
    KEY_10 = 0x10, KEY_11 = 0x11, KEY_12 = 0x12, KEY_13 = 0x13, KEY_14 = 0x14, KEY_15 = 0x15, KEY_16 = 0x16, KEY_17 = 0x17, KEY_18 = 0x18, KEY_19 = 0x19, KEY_1A = 0x1A, KEY_1B = 0x1B, KEY_1C = 0x1C, KEY_1D = 0x1D, KEY_1E = 0x1E,
    KEY_20 = 0x20, KEY_21 = 0x21, KEY_22 = 0x22, KEY_23 = 0x23, KEY_24 = 0x24, KEY_25 = 0x25, KEY_26 = 0x26, KEY_27 = 0x27, KEY_28 = 0x28, KEY_29 = 0x29, KEY_2A = 0x2A, KEY_2B = 0x2B, KEY_2C = 0x2C, KEY_2D = 0x2D, KEY_2E = 0x2E,
    KEY_30 = 0x30, KEY_31 = 0x31, KEY_32 = 0x32, KEY_33 = 0x33, KEY_34 = 0x34, KEY_35 = 0x35, KEY_36 = 0x36, KEY_37 = 0x37, KEY_38 = 0x38, KEY_39 = 0x39, KEY_3A = 0x3A, KEY_3B = 0x3B, KEY_3C = 0x3C, KEY_3D = 0x3D, KEY_3E = 0x3E,
    KEY_40 = 0x40, KEY_41 = 0x41, KEY_42 = 0x42, KEY_43 = 0x43, KEY_44 = 0x44, KEY_45 = 0x45, KEY_46 = 0x46, KEY_47 = 0x47, KEY_48 = 0x48, KEY_49 = 0x49, KEY_4A = 0x4A, KEY_4B = 0x4B, KEY_4C = 0x4C, KEY_4D = 0x4D, KEY_4E = 0x4E,
    KEY_50 = 0x50, KEY_51 = 0x51, KEY_52 = 0x52, KEY_53 = 0x53, KEY_54 = 0x54, KEY_55 = 0x55, KEY_56 = 0x56, KEY_57 = 0x57, KEY_58 = 0x58, KEY_59 = 0x59, KEY_5A = 0x5A, KEY_5B = 0x5B, KEY_5C = 0x5C, KEY_5D = 0x5D, KEY_5E = 0x5E,
    KEY_60 = 0x60, KEY_61 = 0x61, KEY_62 = 0x62, KEY_63 = 0x63, KEY_64 = 0x64, KEY_65 = 0x65, KEY_66 = 0x66, KEY_67 = 0x67, KEY_68 = 0x68, KEY_69 = 0x69, KEY_6A = 0x6A, KEY_6B = 0x6B, KEY_6C = 0x6C, KEY_6D = 0x6D, KEY_6E = 0x6E,
    KEY_70 = 0x70, KEY_71 = 0x71, KEY_72 = 0x72, KEY_73 = 0x73, KEY_74 = 0x74, KEY_75 = 0x75, KEY_76 = 0x76, KEY_77 = 0x77, KEY_78 = 0x78, KEY_79 = 0x79, KEY_7A = 0x7A, KEY_7B = 0x7B, KEY_7C = 0x7C, KEY_7D = 0x7D, KEY_7E = 0x7E,
    KEY_80 = 0x80, KEY_81 = 0x81, KEY_82 = 0x82, KEY_83 = 0x83, KEY_84 = 0x84, KEY_85 = 0x85, KEY_86 = 0x86, KEY_87 = 0x87, KEY_88 = 0x88, KEY_89 = 0x89, KEY_8A = 0x8A, KEY_8B = 0x8B, KEY_8C = 0x8C, KEY_8D = 0x8D, KEY_8E = 0x8E,
    KEY_90 = 0x90, KEY_91 = 0x91, KEY_92 = 0x92, KEY_93 = 0x93, KEY_94 = 0x94, KEY_95 = 0x95, KEY_96 = 0x96, KEY_97 = 0x97, KEY_98 = 0x98, KEY_99 = 0x99, KEY_9A = 0x9A, KEY_9B = 0x9B, KEY_9C = 0x9C, KEY_9D = 0x9D, KEY_9E = 0x9E,
    KEY_A0 = 0xA0, KEY_A1 = 0xA1, KEY_A2 = 0xA2, KEY_A3 = 0xA3, KEY_A4 = 0xA4, KEY_A5 = 0xA5, KEY_A6 = 0xA6, KEY_A7 = 0xA7, KEY_A8 = 0xA8, KEY_A9 = 0xA9, KEY_AA = 0xAA, KEY_AB = 0xAB, KEY_AC = 0xAC, KEY_AD = 0xAD, KEY_AE = 0xAE,
    KEY_B0 = 0xB0, KEY_B1 = 0xB1, KEY_B2 = 0xB2, KEY_B3 = 0xB3, KEY_B4 = 0xB4, KEY_B5 = 0xB5, KEY_B6 = 0xB6, KEY_B7 = 0xB7, KEY_B8 = 0xB8, KEY_B9 = 0xB9, KEY_BA = 0xBA, KEY_BB = 0xBB, KEY_BC = 0xBC, KEY_BD = 0xBD, KEY_BE = 0xBE,
    KEY_C0 = 0xC0, KEY_C1 = 0xC1, KEY_C2 = 0xC2, KEY_C3 = 0xC3, KEY_C4 = 0xC4, KEY_C5 = 0xC5, KEY_C6 = 0xC6, KEY_C7 = 0xC7, KEY_C8 = 0xC8, KEY_C9 = 0xC9, KEY_CA = 0xCA, KEY_CB = 0xCB, KEY_CC = 0xCC, KEY_CD = 0xCD, KEY_CE = 0xCE,
    KEY_D0 = 0xD0, KEY_D1 = 0xD1, KEY_D2 = 0xD2, KEY_D3 = 0xD3, KEY_D4 = 0xD4, KEY_D5 = 0xD5, KEY_D6 = 0xD6, KEY_D7 = 0xD7, KEY_D8 = 0xD8, KEY_D9 = 0xD9, KEY_DA = 0xDA, KEY_DB = 0xDB, KEY_DC = 0xDC, KEY_DD = 0xDD, KEY_DE = 0xDE,
    KEY_E0 = 0xE0, KEY_E1 = 0xE1, KEY_E2 = 0xE2, KEY_E3 = 0xE3, KEY_E4 = 0xE4, KEY_E5 = 0xE5, KEY_E6 = 0xE6, KEY_E7 = 0xE7, KEY_E8 = 0xE8, KEY_E9 = 0xE9, KEY_EA = 0xEA, KEY_EB = 0xEB, KEY_EC = 0xEC, KEY_ED = 0xED, KEY_EE = 0xEE,
    NO_KEY = 0xFF
} KeyPadCode;

typedef union {
    uint8_t u8User;

    struct {
        unsigned State : 4;
        unsigned TabCounter : 4;
    };
} ukeyUserStates_t;

typedef struct {
    uint8_t Keycode;
    ukeyUserStates_t UserState;
} stkey_t;
/*
 *Key Call back
 */
typedef uint8_t(*pFunckeyEvent_t)(stkey_t *);

/*
 --------------------------------------------------------------------------------------------------
 |                                <   mnue Descirption   >                                        |
 --------------------------------------------------------------------------------------------------
 | < Description                   : mnue struct                                                  |
 | < Uasge                         : 5 Byte in Progrm Memeory                                     |                                     
 | < param ButtonNext              : next button in list created                                  |
 | < param Pin                     : Input Pin GPIO                                               |
 | < Param ButtonOptions           : Bit 0 Inicator the button active high or low                 |
 | <                               : Bit 1 Incator the button is Pullup Enable or not             |
 --------------------------------------------------------------------------------------------------
 */
typedef struct keypadConstantCode {
    const uint8_t Code; /*pin ass*/
    const uint16_t const Tone;
    const uint8_t const Index;
    struct keypadConstantCode const *Next;
} keypadConstantCode_t;
/*
 --------------------------------------------------------------------------------------------------
 |                           < null item  >                                                       | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Button                                           |
 ---------------------------------------------------------------------------------------------------          
 */
extern const keypadConstantCode_t PROGMEM NO_CODE;
/*
 --------------------------------------------------------------------------------------------------
 |                           < Create Event  >                                                    | 
 --------------------------------------------------------------------------------------------------
 |< @Description : Indicator the End List Of The Event                                            |
 ---------------------------------------------------------------------------------------------------          
 */
#define KeypadCreateEvent(Name,Code, Tone ,Index, Next) \
extern const keypadConstantCode_t PROGMEM   Next; \
    const keypadConstantCode_t PROGMEM Name = {Code,Tone ,Index,&Next};
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyscan >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyscan                                                                   |  
 | < @Description       : primitive function run every time (ex. 10ms) (user not used)                   | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyscan();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < keyInit >                                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void keyInit                                                                   |  
 | < @Description       : initialization variables and I/O assignment with default (user not used)       | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void keyInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeyPadDriver >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeyPadDriver                                                              |  
 | < @Description       : run in background                                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void KeypadDriver();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < KeypadAssignCosntEvents >                                           |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void KeypadAssignCosntEvents                                                   |  
 | < @Description       : run Callbacks of The Const Events                                              | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void KeypadAssignCosntEvents(const keypadConstantCode_t *keyEvents);

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
void KeypadRegisterEvent(pFunckeyEvent_t callback, uint8_t Index);

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
void KeypadResetTabCounter(stkey_t *key, uint8_t Tab);
#endif
#endif
#endif	/* KEYPAD_H */

