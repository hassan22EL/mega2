/*
------------------------------------------------------------------------------------------
|                          < Module  Definition >                                        | 
------------------------------------------------------------------------------------------
| < FILE                   : exeeprom.c                                                  |                                  
| < Author                 : Hassan Elsaied                                              | 
| < Version                : Mega2v241022                                                |
| < References             : no-used references in this documents                        |
| < SRAM_USAGE             : 40 Byte                                                     |
|                          : @TWI  9 Byte Used                                           |
|                          : @Time Out  4 Byte                                           |
|                          : @eeprom description 11 Byte                                 |
|                          : @Internal Read Buffer default used 16 Byte                  |
| < PROGRAM_USAGE          : 944 byte (501 Instruction)                                 |
| < Hardware Usage         : I2C  as Master                                              |
| < File Created           : 24-10-2022                                                  |
-------------------------------------------------------------------------------------------
 */



#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if defined (EX_EEPROM_MODULE)
#if  EX_EEPROM_MODULE 

/*
 --------------------------------------------------------------------------------------------------------
 |                                      < TWI check Enable  >                                           |
 --------------------------------------------------------------------------------------------------------
 */

#ifndef TWI_MODULE 
#error  please enable TWI module and select type master mode or master slave mode us used exeeprom module
#else 
#if TWI_TYPE == TWI_SLAVE ||  (TWI_MODULE == MODULE_DIABLE)
#error  select type master mode or master slave mode us used exeeprom module
#endif
#endif
/*
 --------------------------------------------------------------------------------------------------------
 |                                <   Macro  Definition    >                                            |
 --------------------------------------------------------------------------------------------------------
 */


/*
 --------------------------------------------------------------------------------------------------------
 |                                < ex-eeprom Write  State    >                                         |
 --------------------------------------------------------------------------------------------------------
 */
#define ExEEPROM_WRITE_SUCCESS           0
#define ExEEPROM_WRITE_PROGRESS          1
/*
 --------------------------------------------------------------------------------------------------------
 |                                < ex-eeprom Read State    >                                           |
 --------------------------------------------------------------------------------------------------------
 */

#define ExEEPROM_READ_SUCCESS            0
#define ExEEPROM_READ_PROGRESS           1
/*
 --------------------------------------------------------------------------------------------------------
 |                                < ex-eeprom update State    >                                         |
 --------------------------------------------------------------------------------------------------------
 */
#define ExEEPROM_UPDATE_SUCCESS         0
#define ExEEPROM_UPDATE_PROGRESS        1

/*
 --------------------------------------------------------------------------------------------------------
 |                                < ex-eeprom Internal address Length>                                  |
 --------------------------------------------------------------------------------------------------------
 */
#ifndef  EXEEPROM_MEM_ADDR_LEN
#define  EXEEPROM_MEM_ADDR_LEN           TWI_SLAVE_TWO_BYTE_SIZE
#endif
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  ex-eeprom slave Address   >                                        |
 --------------------------------------------------------------------------------------------------------
 */
#ifndef  EXEEPROM_MEM_ADDR
#define  EXEEPROM_MEM_ADDR               0xA0
#endif
/* 
 --------------------------------------------------------------------------------------------------------
 |                                <  Page Size   >                                                      |
 --------------------------------------------------------------------------------------------------------
 */
#ifndef   EXEEPROM_MEM_PAGE_SIZE
#define   EXEEPROM_MEM_PAGE_SIZE         32
#endif
/* 
 --------------------------------------------------------------------------------------------------------
 |                                < ex-eeprom Buffer Length   >                                         |
 --------------------------------------------------------------------------------------------------------
 */
#ifndef   EXEEPROM_MEM_MAX_BUFFER
#define   EXEEPROM_MEM_MAX_BUFFER     16
#endif
/* 
 --------------------------------------------------------------------------------------------------------
 |                                <  TWI SPEED   >                                                      |
 --------------------------------------------------------------------------------------------------------
 */
#ifndef  EXEEPROM_BUS_SPEED
#define  EXEEPROM_BUS_SPEED      TWI_400KHZ
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                <  TWI Access   >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < Description          : Twi struct                                                                  |
 | < Uasge                : 9 Byte                                                                      |
 | < param Chip           : slave address                                                               |
 | < param address        : buffer of internal address max used 3 byte                                  |
 | < param address length : how many byte used of 3 byte address                                        |
 | < param buffer         : pointer of data                                                             |
 | < param length         : number of byte data to read or write                                        |
 | < param data           : pointer to write buffer                                                     |              
 --------------------------------------------------------------------------------------------------------
 */


static twi_package_t exeepromTwiPackage;

/* 
 --------------------------------------------------------------------------------------------------------
 |                                <  ex-eeprom Buffer   >                                               |
 --------------------------------------------------------------------------------------------------------
 | < Description  : any read operation used this buffer                                                 |                 
 | < Uasge        : 16 Byte                                                                             |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t exeeprom_read_buf[EXEEPROM_MEM_MAX_BUFFER]; /*16Byte*/

/*
 --------------------------------------------------------------------------------------------------------
 |                                <  ex-eeprom struct >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < Description          : ex-eeprom struct                                                            |
 | < Uasge                : 11 Byte                                                                     |
 | < param u8State        : state of the eeprom                                                         |
 |                        : B0 used in twi write                                                        |
 |                        : B1 used with twi read                                                       |
 |                        : B2 , B3 used in update eeprom                                               |  
 |                        : B4 , B5 used in eeprom driver                                               |
 |                        : B6 , B7                                                                     |                
 | < param size           : max number of the bytes read or write                                       |
 |                        : and this size <= max buffer length of eeprom                                |    
 | < param pageIndex      : copy size to page write a data                                              |
 | < param pageAddress    : copy specefic the address into page to write data                           |                      
 | < param u16address     : specefic address required to read or write                                  |
 | < param data           : pointer of the write buffer from application                                |
 | < param pagedata       : copy of  pointer of the write                                               |
 |                        : buffer from application to work with page                                   |              
 --------------------------------------------------------------------------------------------------------
 */
typedef union {
    uint8_t flags;

    struct {
        unsigned DS : 2;
        unsigned RW : 1;
        unsigned WF : 1;
    };

} ExEEPROMState;

typedef struct {
    volatile ExEEPROMState u8State;
    volatile uint8_t size;
    volatile uint8_t pageIndex;
    volatile uint16_t pageAddress;
    volatile uint16_t u16address;
    uint8_t *data;
    uint8_t *pagedata;
} exEEPROM_descriptor_t;



static volatile exEEPROM_descriptor_t exEEPROM_desc;


/*
 --------------------------------------------------------------------------------------------------------
 |                                <  ex-eeprom Time out   >                                             |
 --------------------------------------------------------------------------------------------------------
 */
stTimer_TimeOut_t gstExeepromTimeOut;

/*
 --------------------------------------------------------------------------------------------------------
 |                                   <  Basic operations  >                                             |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                            < _exeepromAssignAddress  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  _exeepromAssignAddress                                                  |
 | < @Description       : convert address to number of byte                                             |
 | < @param addressbuf  : buffer load the address after convert pointer twi address                     |
 | < @param address     : current address to  be convert to number of byte                              |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void _exeepromAssignAddress(uint8_t *addressbuf, memAddresst_t address);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromWriteBlock  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromWriteBlock                                           |
 | < @Description       : this function just write data using two wire interface (TWI)                  |
 | < @param  address    : start address of the communication                                            |
 | < @param  buf        : pointer of the data                                                           |
 | < @param  length     : total byte write                                                              |
 | < @return            : ExEEPROM_WRITE_SUCCESS  internal write is done                                |                                                
 |                      : ExEEPROM_WRITE_PROGRESS internal operation in progress                        |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromWriteBlock(memAddresst_t address, uint8_t *buf, uint8_t length);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromWritePage  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromWritePage                                            |
 | < @Description       : update block is a read data and compare with write data                       |
 *                      : if not equal is write data                                                    |                                                           
 | < @return            : ExEEPROM_WRITE_SUCCESS  internal write is done                                |                                                
 |                      : ExEEPROM_WRITE_PROGRESS internal operation in progress                        |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromWritePage(); /*write page*/
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromAssignData  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromAssignData                                           |
 | < @Description       : assignData                                                                    |
 *                      : if not equal is write data                                                    |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromAssignData  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromAssignData                                           |
 | < @Description       : assignData                                                                    |
 *                      : if not equal is write data                                                    |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void __exeepromAssignData(memAddresst_t Address, uint8_t *buf, uint8_t length, uint8_t RW);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromAssignTWIData  >                                              |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromAssignTWIData                                        |
 | < @Description       : assign Data Into TWI                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void __exeepromAssignTWIData(memAddresst_t Address, uint8_t *buf, uint8_t length);
/*
 --------------------------------------------------------------------------------------------------------
 |                                   <  Basic operations  >                                             |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < _exeepromAssignAddress  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  _exeepromAssignAddress                                                  |
 | < @Description       : convert address to number of byte                                             |
 | < @param addressbuf  : buffer load the address after convert pointer twi address                     |
 | < @param address     : current address to  be convert to number of byte                              |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void _exeepromAssignAddress(uint8_t *addressbuf, memAddresst_t address) {
#if EXEEPROM_MEM_ADDR_LEN == TWI_SLAVE_THREE_BYTE_SIZE
    addressbuf[0] = (uint8_t) (address >> 16);
    addressbuf[1] = (uint8_t) (address >> 8);
    addressbuf[2] = (uint8_t) (address >> 0);
#elif EXEEPROM_MEM_ADDR_LEN == TWI_SLAVE_TWO_BYTE_SIZE
    addressbuf[0] = (uint8_t) (address >> 8);
    addressbuf[1] = (uint8_t) (address >> 0);
#elif EXEEPROM_MEM_ADDR_LEN == TWI_SLAVE_ONE_BYTE_SIZE
    addressbuf[0] = (uint8_t) (address >> 0);
#elif EXEEPROM_MEM_ADDR_LEN == TWI_SLAVE_NO_INTERNAL_ADDRESS
    return;
#endif
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromWriteBlock  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromWriteBlock                                           |
 | < @Description       : this function just write data using two wire interface (TWI)                  |
 | < @param  address    : start address of the communication                                            |
 | < @param  buf        : pointer of the data                                                           |
 | < @param  length     : total byte write                                                              |
 | < @return            : ExEEPROM_WRITE_SUCCESS  internal write is done                                |                                                
 |                      : ExEEPROM_WRITE_PROGRESS internal operation in progress                        |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromWriteBlock(memAddresst_t address, uint8_t *buf, uint8_t length) {/*used write data buffer*/
    if (!exEEPROM_desc.u8State.WF) {
        __exeepromAssignTWIData(address, buf, length);
        exEEPROM_desc.u8State.WF = 1;
    } else {
        if (twi_master_write(&exeepromTwiPackage) == TWI_SUCCESS) {
            exEEPROM_desc.u8State.WF = 0;
            return (ExEEPROM_WRITE_SUCCESS);
        }
    }
    return (ExEEPROM_WRITE_PROGRESS);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromAssignTWIData  >                                              |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromAssignTWIData                                        |
 | < @Description       : assign Data Into TWI                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void __exeepromAssignTWIData(memAddresst_t Address, uint8_t *buf, uint8_t length) {
    _exeepromAssignAddress(exeepromTwiPackage.addr, Address);
    exeepromTwiPackage.buffer = buf;
    exeepromTwiPackage.length = length;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromWritePage  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromWritePage                                            |
 | < @Description       : update block is a read data and compare with write data                       |
 *                      : if not equal is write data                                                    |                                                           
 | < @return            : ExEEPROM_WRITE_SUCCESS  internal write is done                                |                                                
 |                      : ExEEPROM_WRITE_PROGRESS internal operation in progress                        |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromWritePage() {/*write page*/
    volatile uint8_t bytesUntilPageBoundary;
    volatile uint8_t byteIndex;
    if (exEEPROM_desc.pageIndex > 0) {
        bytesUntilPageBoundary = EXEEPROM_MEM_PAGE_SIZE - exEEPROM_desc.pageAddress % EXEEPROM_MEM_PAGE_SIZE;
        byteIndex = EXEEPROM_MEM_MAX_BUFFER;
        if (byteIndex > exEEPROM_desc.pageIndex)
            byteIndex = exEEPROM_desc.pageIndex;
        if (byteIndex > bytesUntilPageBoundary)
            byteIndex = bytesUntilPageBoundary;

        if (__exeepromWriteBlock(exEEPROM_desc.pageAddress, exEEPROM_desc.pagedata, byteIndex) != ExEEPROM_WRITE_SUCCESS) {
            return (ExEEPROM_WRITE_PROGRESS);
        }
        exEEPROM_desc.pageAddress += byteIndex;
        exEEPROM_desc.pagedata += byteIndex;
        exEEPROM_desc.pageIndex -= byteIndex;
    } else {
        /*return size value*/
        return (ExEEPROM_WRITE_SUCCESS);
    }
    return (ExEEPROM_WRITE_PROGRESS);
}
/*
 --------------------------------------------------------------------------------------------------------
 |                                   <  user operations  >                                               |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReset  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void exeepromReset                                                            |
 | < @Description       : in at24cxx is reset eeprom after power unstable to remove last operation      |                                                          
 --------------------------------------------------------------------------------------------------------
 */



void exeepromReset() {
    /*the at24cxx is reset up 9 clock */
    digitalpinMode(TWI_SCL_PIN, MODE_OUTPUT);
    digitalPinWrite(TWI_SCL_PIN, GPIO_HIGH);
    for (uint8_t i = 0; i < 23; i++) {
        /*9clock cycle with 400Khz 1.25u high and 1.25u low*/
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        digitalPinWrite(TWI_SCL_PIN, GPIO_LOW);
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        _NOP();
        digitalPinWrite(TWI_SCL_PIN, GPIO_HIGH);
    }
    digitalpinMode(TWI_SCL_PIN, MODE_INPUT_PULLUP); /*restore the default case*/
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReady  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char   exeepromReady                                                 |
 | < @Description       : before any write or call this function and check the driver in wait state     |
 *                      : or not if driver in wait state can be write or read and chcek after to        |
 *                      : write operation is done to be write or read other operation                   |
 *                      : and check after read to write or read or data into internal buffer is ready   |                                                         
 | < @return            : 0  driver is busy state                                                       |
 *                      : 1 driver is ready state  (wait state)                                         |                    
 --------------------------------------------------------------------------------------------------------
 */
uint8_t exeepromReady() {
    /*no assign data before check is wait state or not*/
    if (exEEPROM_desc.u8State.DS != 0)
        return (0);
    return (1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromWriteBuffer  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromWriteBuffer                                                     |
 | < @Description       : this function assignent data into ex-eeprom description                       |
 *                      : and enable update  fuction                                                    |
 | < @param  address    : specefic address to write data witj specific size                             |
 | < @param  buf        : pointer of the data from application                                          |
 | < @param  length     : total number of bytes to  write into ex-eeprom                                |
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */

void exeepromWriteBuffer(memAddresst_t address, uint8_t *buf, uint8_t length) {
    if (length > EXEEPROM_MEM_MAX_BUFFER) {
        /*error call back with memory  register as buffer error */
        return;
    }
    /*assign data into buffer*/

    __exeepromAssignData(address, buf, length, 0);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromAssignData  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromAssignData                                           |
 | < @Description       : assignData                                                                    |
 *                      : if not equal is write data                                                    |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static void __exeepromAssignData(memAddresst_t Address, uint8_t *buf, uint8_t length, uint8_t RW) {
    exEEPROM_desc.u16address = Address;
    exEEPROM_desc.pageAddress = Address;
    exEEPROM_desc.size = length;
    exEEPROM_desc.pageIndex = length;
    exEEPROM_desc.data = buf;
    exEEPROM_desc.pagedata = buf;
    /*active write operation*/
    exEEPROM_desc.u8State.DS = 1;
    exEEPROM_desc.u8State.RW = RW;
    __exeepromAssignTWIData(Address, exeeprom_read_buf, length);
    sysSetPeriodMS(&gstExeepromTimeOut, 100);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromWriteByte  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromWriteByte                                                       |
 | < @Description       : this function assignent data into ex-eeprom description                       |
 *                      : and enable update  function with update one byte                              |
 | < @param  address    : specefic address to write data with write one byte                            |
 | < @param  byte       : data write into ex-eeprom                                                     |                               
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void exeepromWriteByte(memAddresst_t address, uint8_t byteD) {
    /*no assign data before check is wait state or not*/
    __exeepromAssignData(address, &byteD, 1, 0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReadBuffer  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromReadBuffer                                                      |
 | < @Description       : this function assignent data into ex-eeprom description                       |
 *                      : and enable read  fuction and after compelete the data found                   |
 *                      : in internal buffer with specefic length                                       |
 | < @param  address    : specefic address to write data witj specific size                             |                                         
 | < @param  length     : total number of bytes to read from ex-eeprom                                  |
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void exeepromRequestSteram(memAddresst_t address, uint8_t length) {
    if (length > EXEEPROM_MEM_MAX_BUFFER) {
        /*error call back with memory  register as buffer error */
        return;
    }
    __exeepromAssignData(address, exeeprom_read_buf, length, 1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReadByte  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromReadByte                                                        |
 | < @Description       : this function assignment data into ex-eeprom description                      |
 *                      : and enable read  fuction and after compelete the data found                   |
 *                      : in internal buffer with specefic one byte                                     |
 | < @param  address    : specefic address to write data with specific one byte                         |                     
 | < @return            : void                                                                          |                    
 --------------------------------------------------------------------------------------------------------
 */


void exeepromRequestByte(memAddresst_t address) {
    /*assign data into buffer*/
    __exeepromAssignData(address, exeeprom_read_buf, 1, 1);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromDriver  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromDriver                                                          |
 | < @Description       : mangment data between user and driver if enable read operation                |
 |                      : switch state from wait state to read operation id done switch state           |
 |                      : form read to wait and same operation with update operation                    |
 |                      : and enable read  fuction and after compelete the data found                   |
 |                      : in internal buffer with specefic one byte                                     |                                    
 | < @return            : void                                                                          |                    
 --------------------------------------------------------------------------------------------------------
 */

void exeepromDriver() {
    switch (exEEPROM_desc.u8State.DS) {
        case 0:
            break;
        case 1:
            if (twi_master_read(&exeepromTwiPackage) == TWI_SUCCESS) {
                if (exEEPROM_desc.u8State.RW) {
                    exEEPROM_desc.u8State.DS = 0;
                    return;
                }
                exEEPROM_desc.u8State.DS = 2;
            }
            break;
        case 2:
            if (Match_2BUF(exEEPROM_desc.data, exeeprom_read_buf, exEEPROM_desc.size)) {
                exEEPROM_desc.u8State.DS = 0;
                return;
            }
            exEEPROM_desc.u8State.DS = 3;
            break;
        case 3:
            if (__exeepromWritePage() == ExEEPROM_WRITE_SUCCESS) {
                __exeepromAssignTWIData(exEEPROM_desc.u16address, exeeprom_read_buf, exEEPROM_desc.size);
                exEEPROM_desc.u8State.DS = 1;
            }
            break;
        default:
            break;
    }

    if (sysIsTimeoutMs(&gstExeepromTimeOut) == 0) {
        exEEPROM_desc.u8State.DS = 0;
    }

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exEepromInit  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  exeepromDriver                                                          |
 | < @Description       : assignment default values of the ex-eeprom after powr on and start            |
 |                      : application the data into Read buffer is start application is 0xFF            |                                                     
 | < @return            : void                                                                          |                    
 --------------------------------------------------------------------------------------------------------
 */

void exEepromInit() {
    exeepromTwiPackage.baud_reg = EXEEPROM_BUS_SPEED;
    for (uint8_t i = 0; i < EXEEPROM_MEM_MAX_BUFFER; i++)
        exeeprom_read_buf [i] = 0xFF; /*default value of the read data */
    exEEPROM_desc.data = NULL;
    exEEPROM_desc.size = 0;
    exEEPROM_desc.u16address = 0x0000;
    exEEPROM_desc.u8State.flags = 0x00;
    exEEPROM_desc.u8State.DS = 0;
    exeepromTwiPackage.chip = EXEEPROM_MEM_ADDR;
    exeepromTwiPackage.addr_length = EXEEPROM_MEM_ADDR_LEN;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exEepromRead >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t  exEepromRead                                                         |
 | < @Description       : Read data From Internal Buffer with Last Operation size                       |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void exEepromRead(uint8_t *buf) {
    copyBuff(buf , &exeeprom_read_buf[0] ,exEEPROM_desc.size );
}

#endif
#endif