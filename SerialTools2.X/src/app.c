/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : app.h                                                                    |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 22-Byte                                                                  |
| < PROGRAM USAGE            : 388 Byte  (0 Instruction)                                                |                                    
| < Hardware Usage           : External eeprom Modeule                                                  |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */



#include "../inc/app.h"

//FUSES = {
//	.low = 0xFF, // LOW {SUT_CKSEL=EXTHIFXTALRES_16KCK_64MS, BODEN=CLEAR, BODLEVEL=2V7}
//	.high = 0x99, // HIGH {BOOTRST=CLEAR, BOOTSZ=1024W_1C00, EESAVE=CLEAR, CKOPT=CLEAR, SPIEN=SET, JTAGEN=SET, OCDEN=CLEAR}
//};
//
//LOCKBITS = 0xFF; // {LB=NO_LOCK, BLB0=NO_LOCK, BLB1=NO_LOCK}




KeypadCreateEvent(key1, KEY_77, 0, key2);
KeypadCreateEvent(key2, KEY_7B, 1, key3);
KeypadCreateEvent(key3, KEY_7D, 2, key4);
KeypadCreateEvent(key4, KEY_7E, 3, key5);
KeypadCreateEvent(key5, KEY_B7, 4, key6);
KeypadCreateEvent(key6, KEY_BB, 5, key7);
KeypadCreateEvent(key7, KEY_BD, 6, key8);
KeypadCreateEvent(key8, KEY_BE, 7, key9);
KeypadCreateEvent(key9, KEY_D7, 8, key10);
KeypadCreateEvent(key10, KEY_DB, 9, key11);
KeypadCreateEvent(key11, KEY_DD, 10, key12);
KeypadCreateEvent(key12, KEY_DE, 11, key13);
KeypadCreateEvent(key13, KEY_E7, 12, key14);
KeypadCreateEvent(key14, KEY_EB, 13, key15);
KeypadCreateEvent(key15, KEY_ED, 14, key16);
KeypadCreateEvent(key16, KEY_EE, 15, NO_CODE);

static uint8_t gu8appState;

void appBoot(void) {
    digitalpinMode(COMM_CONTROL, MODE_OUTPUT);
}

void appInit(void) {
    ReturnMenuCallBack();
    SystemTimeInit();
    CreateProductInit();
    PrintLableInit(); /*Regisert all start keys and reset default statte*/
    InitMem(); /*start Read data From memory*/
    gu8appState = 0;
    stopCommuincationWithOtherDevice();
    KeypadAssignCosntEvents(&key1);
}

void appSync(void) {

}

void appMain(void) {
    PrintLableCallBack();
}
/*test*/

