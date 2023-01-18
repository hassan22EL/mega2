/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : eeprom.c                                                                 |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : datasheet                                                                |  
| < SRAM USAGE               : 21  Byte (10 Byte Buffer + 7 Byte eeprom Descriptor , 4 Byte Time Out)   |
| < PROGRAM USAGE            : 722 Byte  (386 Instruction)                                              |                                    
| < Hardware Usage           : Internal EEPROM                                                          |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */


#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if defined (EEPROM_MODULE)
#if EEPROM_MODULE
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Time Wait   >                                               |
 --------------------------------------------------------------------------------------------------------
 | <@macro EEPORM_READ_TIME_OUT  : read operation the cpu heated 4 clock cycle to ready next instruction|
 |                               : and reay data read                                                   |
 | <@macro EEPROM_WRITE_TIME_OUT : write operation the cpu heated 2 clock cycle to ready next           | 
 |                               : instruction and write operation task 1.8ms (2clock cycle*10byte)     |
 |                               : = 20 clock cycle + 1.8ms                                             |
 --------------------------------------------------------------------------------------------------------   
 */
#define     EEPORM_READ_TIME_OUT            20 /*ms*/
#define     EEPROM_WRITE_TIME_OUT           20 /*5ms*/
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Read States   >                                             |
 --------------------------------------------------------------------------------------------------------
 */
#define    EEPROM_READ_PROGRESS            (0)             
#define    EEPROM_READ_SUCESS              (1)
#define    EEPROM_READ_ERROR               (2)
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom update States   >                                           |
 --------------------------------------------------------------------------------------------------------
 */
#define    EEPROM_UPDATE_PROGRESS            (0)             
#define    EEPROM_UPDATE_SUCESS              (1)
#define    EEPROM_UPDATE_ERROR               (2)
/* 
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Buffer   >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < Description  : any read operation used this buffer                                                 |                 
 | < Uasge        : 10 Byte                                                                             |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t gu8eeprom_read_buf[10]; /*10Byte*/

/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom struct >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < Description          : eeprom struct                                                               |
 | < Uasge                : 7 Byte                                                                      |
 | < param u8State        : state of the eeprom                                                         |                                                                    |                
 | < param size           : max number of the bytes read or write                                       |
 |                        : and this size <= max buffer length of eeprom                                |                          
 | < param u16address     : specefic address required to read or write                                  |
 | < Param u8DataIndex    : data index when read and write operation                                    |
 | < param data           : pointer of the write buffer from application                                |              
 --------------------------------------------------------------------------------------------------------
 */

typedef struct {
    volatile byte_Flags2Bit_t u8State;
    volatile uint8_t size;
    volatile uint16_t u16address;
    volatile uint8_t u8DataIndex;
    uint8_t *data;
} eeprom_descriptor_t;
static eeprom_descriptor_t gEepromDescriptor;

/*
 --------------------------------------------------------------------------------------------------------
 |                                <  eeprom Time out   >                                                |
 --------------------------------------------------------------------------------------------------------
 */
stTimer_TimeOut_t gstEepromTimeOut;


/*
 --------------------------------------------------------------------------------------------------------
 |                            < Basic Functions Defintions >                                            |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromIsBusy >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromIsBusy                                                 |
 | < @Description       : this function just check the eeprom is Ready or not                           |     
 | < @return            : 1 the eeprom is Busy                                                          |
 |                      : 0 the eeprom is Ready                                                         |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromIsBusy();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromReadOperation >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromReadOperation                                          |
 | < @Description       : this function just check the Read data with Length                            |     
 | < @return            : 1 read operation in Progress                                                  |
 |                      : 0 the eeprom is Read operation is done                                        |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromReadOperation();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromUpdateOperation >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromUpdateOperation                                        |
 | < @Description       : Read operation and check data is not equals performed write operation         |
 *                      : and verifying by read again                                                   |     
 | < @return            : 0 update operation in Progress                                                |
 |                      : 1 the eeprom is update operation is done                                      |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromUpdateOperation();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < Basic Functions Impelmentions >                                         |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromIsBusy >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromIsBusy                                                 |
 | < @Description       : this function just check the eeprom is Ready or not                           |     
 | < @return            : 1 the eeprom is Busy                                                          |
 |                      : 0 the eeprom is Ready                                                         |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromIsBusy() {
#if defined EEPE/*eeprom programing Enable*/
    return (EECR & _BV(EEPE));
#elif defined EEWE/*eeprom write Enable*/
    return (EECR & _BV(EEWE));
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromReadOperation >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromReadOperation                                          |
 | < @Description       : this function just   Read data with Length from Internal EEPROM               |     
 | < @return            : 0 read operation in Progress                                                  |
 |                      : 1 the eeprom is Read operation is done                                        |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromReadOperation() {
    if (!gEepromDescriptor.u8State.B1) {
        if (!__eepromIsBusy()) {
            gEepromDescriptor.u8State.B1 = 1; /*read state*/
        }
        if (sysIsTimeoutMs(&gstEepromTimeOut) == 0) {
            gEepromDescriptor.u8State.B1 = 0;
            return (EEPROM_READ_ERROR); /*error case */
        }
        return (EEPROM_READ_PROGRESS);
    }
    if (gEepromDescriptor.u8State.B1) {
        if (gEepromDescriptor.u8DataIndex < gEepromDescriptor.size) {
            EEAR = gEepromDescriptor.u16address; /*assign start address of the data*/
            EECR |= (1 << EERE); /*enable read operation*/
            gu8eeprom_read_buf[gEepromDescriptor.u8DataIndex] = EEDR; /*read data Into read buffer*/
            /*cpu stop   4 Clock Cycle*/
            gEepromDescriptor.u16address++;
            gEepromDescriptor.u8DataIndex++;
        } else {
            gEepromDescriptor.u8DataIndex = 0; /*reset data Index*/
            gEepromDescriptor.u16address = 0; /*reset address to 0*/
            gEepromDescriptor.u8State.B1 = 0; /*reset state*/
            return EEPROM_READ_SUCESS;
        }
    }
    return (EEPROM_READ_PROGRESS);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __eepromUpdateOperation >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __eepromUpdateOperation                                        |
 | < @Description       : Read operation and check data is not equals performed write operation         |
 |                      : and verifying by read again                                                   |     
 | < @return            : 0 update operation in Progress                                                |
 |                      : 1 the eeprom is update operation is done                                      |              
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __eepromUpdateOperation() {

    switch (gEepromDescriptor.u8State.b2_3) {
        case 0:
            if (!__eepromIsBusy()) {
                if (gEepromDescriptor.u8State.B7) {
                    gEepromDescriptor.u8State.b2_3 = 3; /*go to verify operation*/
                } else {
                    gEepromDescriptor.u8State.b2_3 = 1; /*go to Read Operation*/
                }
            }
            if (sysIsTimeoutMs(&gstEepromTimeOut) == 0) {
                gEepromDescriptor.u8State.B7 = 0;
                gEepromDescriptor.u8State.b2_3 = 0;
                return (EEPROM_UPDATE_ERROR);
            }
            break;
        case 1:
            if (gEepromDescriptor.u8DataIndex < gEepromDescriptor.size) {
                EEAR = gEepromDescriptor.u16address; /*assign start address of the data*/
                EECR |= (1 << EERE); /*enable read operation*/
                gu8eeprom_read_buf[gEepromDescriptor.u8DataIndex] = EEDR; /*read data Into read buffer*/
                /*cpu stop   4 Clock Cycle*/
                /*check value*/
                if (gu8eeprom_read_buf[gEepromDescriptor.u8DataIndex] != gEepromDescriptor.data[gEepromDescriptor.u8DataIndex]) {
                    gEepromDescriptor.u8State.b2_3 = 2; /*go to write operation of the data and current address*/
                } else {
                    gEepromDescriptor.u16address++; /*read next byte because pervious address byte ready exist*/
                    gEepromDescriptor.u8DataIndex++; /*read next byte because pervious address byte ready exist*/
                }
            } else {
                gEepromDescriptor.u8DataIndex = 0; /*reset data Index*/
                gEepromDescriptor.u16address = 0; /*reset address to 0*/
                gEepromDescriptor.u8State.b2_3 = 0; /*reset state*/
                gEepromDescriptor.u8State.B7 = 0; /*re-active read state*/
                return EEPROM_UPDATE_SUCESS;
            }
            break;
        case 2:
            EEAR = gEepromDescriptor.u16address; /*assignment address*/
            EEDR = gEepromDescriptor.data[gEepromDescriptor.u8DataIndex]; /*assignment data*/
            /*active write operation*/
#if defined EEPE
            EECR |= (1 << EEMPE); /*Enable In Master Mode Programming*/
            EECR |= (1 << EEPE); /*active Programming Operation*/
#elif defined EEWE
            EECR |= (1 << EEMWE); /*Enable In Master Mode Write*/
            EECR |= (1 << EEWE); /*active Write Operation*/
#endif
            sysSetPeriodMS(&gstEepromTimeOut, EEPROM_WRITE_TIME_OUT); /*re-set period time out*/
            gEepromDescriptor.u8State.b2_3 = 0; /*go to wait operation*/
            gEepromDescriptor.u8State.B7 = 1; /* after wait go to verifying state*/
            return (EEPROM_UPDATE_PROGRESS);
            break;
        case 3:
            EEAR = gEepromDescriptor.u16address; /*assign start address of the data*/
            EECR |= (1 << EERE); /*enable read operation*/
            gu8eeprom_read_buf[gEepromDescriptor.u8DataIndex] = EEDR; /*read data Into read buffer*/
            if (gu8eeprom_read_buf[gEepromDescriptor.u8DataIndex] == gEepromDescriptor.data[gEepromDescriptor.u8DataIndex]) {
                gEepromDescriptor.u16address++; /*next address*/
                gEepromDescriptor.u8DataIndex++; /*next byte*/
                gEepromDescriptor.u8State.b2_3 = 1; /*go to read operation*/
            } else {
                gEepromDescriptor.u8State.b2_3 = 2; /*go to write operation*/
            }
            break;
        default:
            break;

    }
    return (EEPROM_UPDATE_PROGRESS);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < user Functions Impelmentions >                                         |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromInit >                                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromInit                                                              |
 | < @Description       : Initialization all variables and Initialization eeorpm                        |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromInit() {
#if defined EEPM1
    /*eeprom programming with write only operation*/
    EECR &= ~(1 < EEPM0);
    EECR |= (1 < EEPM1);
#endif
    gEepromDescriptor.u16address = 0;
    gEepromDescriptor.size = 0;
    gEepromDescriptor.u8DataIndex = 0;
    gEepromDescriptor.u8State.byte = 0;
    gEepromDescriptor.data = (uint8_t *) NULL;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromDriver >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromDriver                                                            |
 | < @Description       : read and update operaion active state run in background                       |     
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromDriver() {
    uint8_t upadatestate;
    uint8_t readstate;
    if (!gEepromDescriptor.u8State.b4_5) {
        return;
    }
    if (gEepromDescriptor.u8State.b4_5 == 1) {
        /*active update state*/
        upadatestate = __eepromUpdateOperation();
        if (upadatestate == EEPROM_UPDATE_PROGRESS) {
            return;
        }
        if (upadatestate == EEPROM_UPDATE_SUCESS) {
            gEepromDescriptor.u8State.b4_5 = 0; /*go to wait state*/
            return;
        }

        if (upadatestate == EEPROM_UPDATE_ERROR) {
            gEepromDescriptor.u8State.b4_5 = 0; /*go to wait state*/
            /*enable error callback function with Internal eeprom error*/
            return;
        }
        return;
    }
    if (gEepromDescriptor.u8State.b4_5 == 2) {
        readstate = __eepromReadOperation();
        if (readstate == EEPROM_READ_PROGRESS) {
            return;
        }
        if (readstate == EEPROM_READ_SUCESS) {
            gEepromDescriptor.u8State.b4_5 = 0; /*go to wait state*/
            return;
        }
        if (readstate == EEPROM_READ_ERROR) {
            gEepromDescriptor.u8State.b4_5 = 0; /*go to wait state*/
            /*enable error callback function with Internal eeprom error*/
            return;
        }
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromWriteBuf >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromWriteBuf                                                          |
 | < @Description       : application write data into eeprom by this function to write muti row data    | 
 | < @Param address     : start address request to write data this address less than (EEPROM_END-10)    |
 | < @Param size        : number of byte write into eeprom and this size less than 10 byte in each time |
 | < @param data        : pointer to payload data into eeprom                                           |              
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromWriteBuf(uint16_t address, uint8_t size, uint8_t *data) {
    if (address + size >= E2END) return; /*error */
    /*assignment data*/
    gEepromDescriptor.u16address = address;
    gEepromDescriptor.u8DataIndex = 0;
    gEepromDescriptor.data = data;
    gEepromDescriptor.size = size;
    /*active update state*/
    gEepromDescriptor.u8State.b4_5 = 1;
    sysSetPeriodMS(&gstEepromTimeOut, EEPORM_READ_TIME_OUT);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRequestSterm >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromRequestSterm                                                      |
 | < @Description       : application read data from eeprom by this function to read muti row data      | 
 | < @Param address     : start address request to read data this address+size less than (EEPROM_END)   |
 | < @Param size        : number of byte read from eeprom and this size less than 10 byte in each time  |            
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromRequestSterm(uint16_t address, uint8_t size) {
    if (address + size >= E2END) return; /*error */
    if (size > 10) size = 10; /*read only 10*/
    /*assignment data*/
    gEepromDescriptor.u16address = address;
    gEepromDescriptor.u8DataIndex = 0;
    gEepromDescriptor.size = size;
    /*active read state*/
    gEepromDescriptor.u8State.b4_5 = 2;
    sysSetPeriodMS(&gstEepromTimeOut, EEPORM_READ_TIME_OUT);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRequestByte >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  eepromRequestByte                                                       |
 | < @Description       : application read data from eeprom by this function to read single byte data   | 
 | < @Param address     : start address request to read data this address less than (EEPROM_END)        |           
 | < @return            : void                                                                          |              
 --------------------------------------------------------------------------------------------------------
 */
void eepromRequestByte(uint16_t address) {
    if (address >= E2END)return; /*error*/
    /*assignment data*/
    gEepromDescriptor.u16address = address;
    gEepromDescriptor.u8DataIndex = 0;
    gEepromDescriptor.size = 1;
    /*active read state*/
    gEepromDescriptor.u8State.b4_5 = 2;
    sysSetPeriodMS(&gstEepromTimeOut, EEPORM_READ_TIME_OUT);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromIsBusy >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  eepromIsBusy                                                         |
 | < @Description       : chack state of Internal eeprom is ready to access new operation or not        |        
 | < @return            : 0 eeprom is ready to new operation                                            |
 |                      : 1 eeprom Internal Write Operaion in Progress                                  |
 |                      : 2 eeprom Internal Read Operaion in Progress                                   |              
 --------------------------------------------------------------------------------------------------------
 */
uint8_t eepromIsBusy() {
    return gEepromDescriptor.u8State.b4_5;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < eepromRead >                                                            |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  eepromRead                                                           |
 | < @Description       : Read data From Internal Buffer with Last Operation size                       |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void eepromRead(uint8_t *buf) {
    if (gEepromDescriptor.size == 0) return;
    for (uint8_t i = 0; i < gEepromDescriptor.size; i++) {
        buf[i] = gu8eeprom_read_buf[i];
    }
}

#endif
#endif
