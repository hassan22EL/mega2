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


typedef struct {
    volatile byte_Flags2Bit_t u8State;
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
static inline void _exeepromAssignAddress(uint8_t *addressbuf, uint32_t address);
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
static uint8_t __exeepromWriteBlock(uint32_t address, uint8_t *buf, uint8_t length);

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromReadBlock  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromReadBlock                                            |
 | < @Description       : this function just read data using two wire interface (TWI)                   |
 | < @param  address    : start address of the communication                                            |
 | < @param  buf        : pointer of the data                                                           |
 | < @param  length     : total byte write                                                              |
 | < @return            : ExEEPROM_READ_SUCCESS  internal Read is done                                  |                                                
 |                      : ExEEPROM_READ_PROGRESS internal Read in progress                              |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromReadBlock(uint32_t address, uint8_t *buf, uint8_t length); /*used read data buffer*/

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
 |                                   <  update operations  >                                            |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromUpdateBlock  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromUpdateBlock                                          |
 | < @Description       : in first read current address with size of the data and                       |
                        : the data is different switch to second state to write this data               |
 |                      : in the current address with size specific after write complete                |
 |                      : can read the same data from same address to verifiy this data                 |                                                  
 | < @return            : ExEEPROM_UPDATE_SUCCESS  internal update is done                              |                                                
 |                      : ExEEPROM_UPDATE_PROGRESS internal update in progress                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromUpdateBlock();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReadBlock  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  exeepromReadBlock                                              |
 | < @Description       : this function read data with specific address and size and put into           |
 |                      : interanl read buffer                                                          |                                                          
 | < @return            : ExEEPROM_READ_SUCCESS  internal Read is done                                  |                                                
 |                      : ExEEPROM_READ_PROGRESS internal Read in progress                              |                     
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t exeepromReadBlock();




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
static inline void _exeepromAssignAddress(uint8_t *addressbuf, uint32_t address) {
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
static uint8_t __exeepromWriteBlock(uint32_t address, uint8_t *buf, uint8_t length) {/*used write data buffer*/
    if (!exEEPROM_desc.u8State.B0) {
        exeepromTwiPackage.chip = EXEEPROM_MEM_ADDR;
        _exeepromAssignAddress(exeepromTwiPackage.addr, address);
        exeepromTwiPackage.addr_length = EXEEPROM_MEM_ADDR_LEN;
        exeepromTwiPackage.buffer = buf;
        exeepromTwiPackage.length = length;
        sysSetPeriodMS(&gstExeepromTimeOut, 30);
        exEEPROM_desc.u8State.B0 = 1;
    } else {
        if (twi_master_write(&exeepromTwiPackage) == TWI_SUCCESS) {
            exEEPROM_desc.u8State.B0 = 0;
            return (ExEEPROM_WRITE_SUCCESS);
        } else if (sysIsTimeoutMs(&gstExeepromTimeOut) == 0) {
            exEEPROM_desc.u8State.B0 = 0;
            /*run error call back*/
            return (ExEEPROM_WRITE_SUCCESS);
        }
    }
    return (ExEEPROM_WRITE_PROGRESS);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromReadBlock  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromReadBlock                                            |
 | < @Description       : this function just read data using two wire interface (TWI)                   |
 | < @param  address    : start address of the communication                                            |
 | < @param  buf        : pointer of the data                                                           |
 | < @param  length     : total byte write                                                              |
 | < @return            : ExEEPROM_READ_SUCCESS  internal Read is done                                  |                                                
 |                      : ExEEPROM_READ_PROGRESS internal Read in progress                              |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromReadBlock(uint32_t address, uint8_t *buf, uint8_t length) {/*used read data buffer*/
    if (exEEPROM_desc.u8State.B1 == 0) {
        exeepromTwiPackage.chip = EXEEPROM_MEM_ADDR;
        _exeepromAssignAddress(exeepromTwiPackage.addr, address);
        exeepromTwiPackage.addr_length = EXEEPROM_MEM_ADDR_LEN;
        exeepromTwiPackage.buffer = buf;
        exeepromTwiPackage.length = length;
        exEEPROM_desc.u8State.B1 = 1;
    } else {
        if (twi_master_read(&exeepromTwiPackage) == TWI_SUCCESS) {
            exEEPROM_desc.u8State.B1 = 0;
            return (ExEEPROM_READ_SUCCESS);
        } else if (sysIsTimeoutMs(&gstExeepromTimeOut) == 0) {
            exEEPROM_desc.u8State.B1 = 0;
            /*run error call back*/
            return (ExEEPROM_READ_SUCCESS);
        }
    }
    return (ExEEPROM_READ_PROGRESS);
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
        byteIndex = 16;
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
 |                                   <  update operations  >                                            |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < __exeepromUpdateBlock  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  __exeepromUpdateBlock                                          |
 | < @Description       : in first read current address with size of the data and                       |
                        : the data is different switch to second state to write this data               |
 |                      : in the current address with size specific after write complete                |
 |                      : can read the same data from same address to verifiy this data                 |                                                                                                             
 | < @return            : ExEEPROM_UPDATE_SUCCESS  internal update is done                              |                                                
 |                      : ExEEPROM_UPDATE_PROGRESS internal update in progress                          |                     
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t __exeepromUpdateBlock() {

    /*three sate read , write , read b4 ,b5*/
    switch (exEEPROM_desc.u8State.b2_3) {
        case 0:
            if (__exeepromReadBlock(exEEPROM_desc.u16address, exeeprom_read_buf, exEEPROM_desc.size) == ExEEPROM_READ_SUCCESS) {
                if (memcmp(exEEPROM_desc.data, exeeprom_read_buf, exEEPROM_desc.size) != 0) {
                    exEEPROM_desc.u8State.b2_3 = 1;
                } else {
                    return ExEEPROM_UPDATE_SUCCESS;
                }
            }
            break;
        case 1:
            if (__exeepromWritePage() == ExEEPROM_WRITE_SUCCESS) {
                exEEPROM_desc.u8State.b2_3 = 2;
            }
            break;
        case 2:
            if (__exeepromReadBlock(exEEPROM_desc.u16address, exeeprom_read_buf, exEEPROM_desc.size) == ExEEPROM_READ_SUCCESS) {
                exEEPROM_desc.u8State.b2_3 = 0;
                if (memcmp(exEEPROM_desc.data, exeeprom_read_buf, exEEPROM_desc.size) == 0)
                    return ExEEPROM_UPDATE_SUCCESS;
            }
            break;
        default:
            break;
    }

    return (ExEEPROM_UPDATE_PROGRESS);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < exeepromReadBlock  >                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  exeepromReadBlock                                              |
 | < @Description       : this function read data with specific address and size and put into           |
 |                      : interanl read buffer                                                          |                                                          
 | < @return            : ExEEPROM_READ_SUCCESS  internal Read is done                                  |                                                
 |                      : ExEEPROM_READ_PROGRESS internal Read in progress                              |                     
 --------------------------------------------------------------------------------------------------------
 */

static uint8_t exeepromReadBlock() {
    /*one state*/
    if (__exeepromReadBlock(exEEPROM_desc.u16address, exeeprom_read_buf, exEEPROM_desc.size) == ExEEPROM_READ_SUCCESS) {
        return (ExEEPROM_READ_SUCCESS);
    }
    return (ExEEPROM_READ_PROGRESS);
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
    if (exEEPROM_desc.u8State.b4_5)
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

void exeepromWriteBuffer(uint32_t address, uint8_t *buf, uint8_t length) {
    if (length > EXEEPROM_MEM_MAX_BUFFER) {
        /*error call back with memory  register as buffer error */
        return;
    }
    /*assign data into buffer*/
    exEEPROM_desc.u16address = address;
    exEEPROM_desc.pageAddress = address;
    exEEPROM_desc.size = length;
    exEEPROM_desc.pageIndex = length;
    exEEPROM_desc.data = buf;
    exEEPROM_desc.pagedata = buf;
    /*active write operation*/
    exEEPROM_desc.u8State.b4_5 = 1;
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
void exeepromWriteByte(uint32_t address, uint8_t byte) {
    /*no assign data before check is wait state or not*/

    /*assign data into buffer*/
    exEEPROM_desc.u16address = address;
    exEEPROM_desc.pageAddress = address;
    exEEPROM_desc.size = 1;
    exEEPROM_desc.pageIndex = 1;
    exEEPROM_desc.data = &byte;
    exEEPROM_desc.pagedata = &byte;
    /*active write operation*/
    exEEPROM_desc.u8State.b4_5 = 1;
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
void exeepromRequestSteram(uint32_t address, uint8_t length) {
    if (length > EXEEPROM_MEM_MAX_BUFFER) {
        /*error call back with memory  register as buffer error */
        return;
    }
    /*assign data into buffer*/
    exEEPROM_desc.u16address = address;
    exEEPROM_desc.size = length;
    exEEPROM_desc.pageIndex = length;
    exEEPROM_desc.data = exeeprom_read_buf;
    /*active read operation*/
    exEEPROM_desc.u8State.b4_5 = 2;
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


void exeepromRequestByte(uint32_t address) {
    /*assign data into buffer*/
    exEEPROM_desc.u16address = address;
    exEEPROM_desc.size = 1;
    exEEPROM_desc.data = exeeprom_read_buf;
    /*active read operation*/
    exEEPROM_desc.u8State.b4_5 = 2;
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
    /*wait operation*/
    if (!exEEPROM_desc.u8State.b4_5) {
        return;
    }

    if (exEEPROM_desc.u8State.b4_5 == 1) {
        if (__exeepromUpdateBlock() == ExEEPROM_UPDATE_SUCCESS) {
            exEEPROM_desc.u8State.b4_5 = 0;
        }
        return;
    }
    if (exEEPROM_desc.u8State.b4_5 == 2) {
        if (exeepromReadBlock() == ExEEPROM_READ_SUCCESS) {
            exEEPROM_desc.u8State.b4_5 = 0;
        }
        return;
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
    exEEPROM_desc.u8State.byte = 0x00;
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
    for (uint8_t i = 0; i < exEEPROM_desc.size; i++) {
        buf[i] = exeeprom_read_buf[i];
    }
}

#endif
#endif
