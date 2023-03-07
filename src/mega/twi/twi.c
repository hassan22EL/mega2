/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : twi.c                                                             |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : http://ww1.microchip.com/downloads/en/appnotes/00002480a.pdf      |
| < SRAM USAGE               : 8-Byte in Master Mode  && Slave mode 7 Byte                       |
| < PROGRAM USAGE            : 614 Byte (329 Instruction)   in Master mode                       |
|                            : under test in slave mode                                          |
| < Hardware Usage           : I2C                                                               |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */

#include "../../../inc/mega.h"

#if defined TWI_MODULE
#if TWI_MODULE 

/*
 --------------------------------------------------------------------------------------------------------
 |                                   <  micros  >                                                       |
 --------------------------------------------------------------------------------------------------------
 */


/*
 ----------------------------------------------------------------------------------------------------------------
 |                                <   Data State   >                                                            |
 ----------------------------------------------------------------------------------------------------------------                                                             |
 | < micro  TWI_IDLE                                : data ready to read or write                               |
 | < micro  TWI_WRITE_IADDR_WRITE_DATA              : in have internal address write data                       |
 | < micro  TWI_WRITE_IADDR_READ_DATA               : in have internal address read data                        |
 | < micro  TWI_WRITE_DATA                          : data write state                                          |
 | < micro  TWI_READ_DATA                           : data read state                                           |
 | < micro  TWI_TRANSAC_SUCCESS                     : transmit slave success                                    |
 | < micro  TWI_TRANSAC_FAIL                        : transmit slave fail                                       |  
 ----------------------------------------------------------------------------------------------------------------
 */
#define TWI_IDLE                     1
#define TWI_WRITE_IADDR_WRITE_DATA   2
#define TWI_WRITE_IADDR_READ_DATA    3
#define TWI_WRITE_DATA               4
#define TWI_READ_DATA                5
#define TWI_TRANSAC_SUCCESS          6
#define TWI_TRANSAC_FAIL             7
#define TWI_PROCESS                  8



/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < twi status mask >                                                        |
 ----------------------------------------------------------------------------------------------------------------
 */

#define TWI_TWSR_STATUS_MASK    (TWSR & 0xF8)
/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < twi write enable >                                                       |
 ----------------------------------------------------------------------------------------------------------------
 */
#define TWI_WRITE_ENABLE(SDA)   (SDA & 0xFE)
/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < twi read enable >                                                        |
 ----------------------------------------------------------------------------------------------------------------
 */
#define TWI_READ_ENABLE(SDA)    ((SDA & 0xFE) | 0x01)

/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < check system clock is defined >                                          |
 ----------------------------------------------------------------------------------------------------------------
 */
#ifndef F_CPU
#warning "This Drive need the FCPU please define f_cpu"
#endif


/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < BUS Select >                                                             |
 ----------------------------------------------------------------------------------------------------------------
 */



#define TWI_MASTER_BUS    0
#define TWI_SLAVE_BUS     1

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                <  TWI Status   >                                                              |
 -----------------------------------------------------------------------------------------------------------------
 | < @enum  TWS_BUSERROR                 : Bus error due to illegal START or STOP condition                      |
 | < @enum  TWS_START                    : A START condition has been transmitted.                               |
 | < @enum  TWS_RSTART                   : A repeated START condition has been transmitted                       |
 | < @enum  TWS_MT_SLA_ACK               : TWI chip have a three byte internal address 2^24 addresses            |
 | < @enum  TWS_MT_SLA_NACK              : SLA+W has been transmitted; ACK has been received                     |
 | < @enum  TWS_MT_DATA_ACK              : Data byte has been transmitted; ACK has been received                 |
 | < @enum  TWS_MT_DATA_NACK             : Data byte has been transmitted; NOT ACK has been received             |
 | < @enum  TWS_M_ARB_LOST               : Arbitration lost in SLA+W or data bytes(Transmitter)                  |
 |                                       : Arbitration lost in SLA+R or NOT ACK bit (Receiver)                   |
 | < @enum  TWS_MR_SLA_ACK               : SLA+R has been transmitted; ACK has been received                     |
 | < @enum  TWS_MR_SLA_NACK              : SLA+R has been transmitted; NOT ACK has been received                 |
 | < @enum  TWS_MR_DATA_ACK              : Data byte has been received; ACK has been returned                    |
 | < @enum  TWS_MR_DATA_NACK             : Data byte has been received; NOT ACK has been returned                |
 | < @enum  TWS_ST_SLA_ACK               : Own SLA+R has been received  ACK has been returned                    |
 | < @enum  TWS_ST_SLA_ACK_M_ARB_LOST    : Arbitration lost in SLA+R/W as Master; own SLA+R has been received    |
 |                                       : ACK has been returned                                                 |
 | < @enum  TWS_ST_DATA_ACK              : Data byte in TWDR has been transmitted ACK has been received          |
 | < @enum  TWS_ST_DATA_NACK             : Data byte in TWDR has been transmitted;NOT ACK has been received      |
 | < @enum  TWS_ST_DATA_ACK_LAST_BYTE    : Last data byte in TWDR has been transmitted                           |   
 |                                       : TWEA ACK has been received                                            |
 | < @enum  TWS_SR_SLA_ACK               : Own SLA+W has been received ACK has been returned                     |
 | < @enum  TWS_SR_SLA_ACK_M_ARB_LOST    : Arbitration lost in  SLA+R/W as Master;own SLA+W has been received    |
 |                                       : ACK has been returned                                                 |
 | < @enum  TWS_SR_GEN_ACK               : General call address has been received; ACK has been returned         |
 | < @enum  TWS_SR_GEN_ACK_M_ARB_LOST    : Arbitration lost in SLA+R/W as Master                                 |
 |                                       : General call address has been received; ACK has been returned         |
 | < @enum  TWS_SR_SLA_DATA_ACK          : Previously addressed with own SLA+W;data has been received            | 
 |                                       : ACK  has been returned                                                |
 | < @enum  TWS_SR_SLA_DATA_NACK         : Previously addressed with own SLA+W;data has been received            |
 |                                       : NOT ACK has been returned                                             |
 | < @enum  TWS_SR_GEN_DATA_ACK          : Previously addressed with general call;data has been received         |
 |                                       : ACK has been returned                                                 |
 | < @enum  TWS_SR_GEN_DATA_NACK         : Previously addressed with general call; data has been received        |
 |                                       : NOT ACK has been returned                                             |
 | < @enum  TWS_SR_STOP_RESTART          : A STOP condition or repeated START condition has been received        |
 |                                       : while still addressed as Slave                                        |
 -----------------------------------------------------------------------------------------------------------------
 */



enum {
    TWS_BUSERROR = 0x00,
    TWS_START = 0x08,
    TWS_RSTART = 0x10,
    TWS_MT_SLA_ACK = 0x18,
    TWS_MT_SLA_NACK = 0x20,
    TWS_MT_DATA_ACK = 0x28,
    TWS_MT_DATA_NACK = 0x30,
    TWS_M_ARB_LOST = 0x38,
    TWS_MR_SLA_ACK = 0x40,
    TWS_MR_SLA_NACK = 0x48,
    TWS_MR_DATA_ACK = 0x50,
    TWS_MR_DATA_NACK = 0x58,
    TWS_ST_SLA_ACK = 0xA8,
    TWS_ST_SLA_ACK_M_ARB_LOST = 0xB0,
    TWS_ST_DATA_ACK = 0xB8,
    TWS_ST_DATA_NACK = 0xC0,
    TWS_ST_DATA_ACK_LAST_BYTE = 0xC8,
    TWS_SR_SLA_ACK = 0x60,
    TWS_SR_SLA_ACK_M_ARB_LOST = 0x68,
    TWS_SR_GEN_ACK = 0x70,
    TWS_SR_GEN_ACK_M_ARB_LOST = 0x78,
    TWS_SR_SLA_DATA_ACK = 0x80,
    TWS_SR_SLA_DATA_NACK = 0x88,
    TWS_SR_GEN_DATA_ACK = 0x90,
    TWS_SR_GEN_DATA_NACK = 0x98,
    TWS_SR_STOP_RESTART = 0xA0
};


/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 Global data Variables                                                          |           
 -----------------------------------------------------------------------------------------------------------------
 * */

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 master busy state                                                             |           
 -----------------------------------------------------------------------------------------------------------------
 * */

static volatile uint8_t twi_master_busy = 0;
/*
 -----------------------------------------------------------------------------------------------------------------
 |                                 BUS Type                                                                      |           
 -----------------------------------------------------------------------------------------------------------------
 * */
static volatile uint8_t twi_mode = TWI_MASTER_BUS;

#if ((TWI_TYPE == TWI_MASTER) ||(TWI_TYPE == TWI_MASTER_SLAVE))

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                <   Master Transfer Descriptor    >                                            |
 -----------------------------------------------------------------------------------------------------------------
 | < Description           : master transfer data  struct m                                                      |
 | < Uasge                 : 6 Byte                                                                              |                                                          |
 | < param pkg             : Bus message descriptor                                                              |
 | < param addr_count      : Bus transfer address data counter                                                   |
 | < param data_count      : Bus transfer payload data counter                                                   |
 | < param state           : transfer state                                                                      |
 | < param status          : twi status                                                                          |              
 -----------------------------------------------------------------------------------------------------------------
 */
static struct {
    twi_package_t *pkg; /* Bus message descriptor */
    uint8_t addr_count; /* Bus transfer address data counter */
    uint8_t data_count; /* Bus transfer payload data counter */
    uint8_t state; /* Transfer state */
    status_code_t status; /* Transfer status */
} master_transfer;
#endif
/** Slave Transfer Descriptor */
#if((TWI_TYPE == TWI_SLAVE) ||(TWI_TYPE == TWI_MASTER_SLAVE))

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                <   Slave Transfer Descriptor    >                                             |
 -----------------------------------------------------------------------------------------------------------------
 | < Description           : slave transfer data struct                                                          |
 | < Uasge                 : 5 Byte                                                                              |                                                                                                                       |
 | < param data_buffer     : pointer of data buffer  rx_buffer and tx Buffer                                     |
 | < param data_count      : Bus transfer payload data counter                                                   |
 | < param state           : transfer state                                                                      |                                                                         |              
 -----------------------------------------------------------------------------------------------------------------
 */
static struct {
    twi_slave_data_buffer_t *data_buffer;
    uint8_t data_count;
    uint8_t state;
    int status;
} slave_transfer;
#endif



/*
 --------------------------------------------------------------------------------------------------------
 |                                <  Master Function Definition >                                       |
 --------------------------------------------------------------------------------------------------------
 */
#if((TWI_TYPE == TWI_MASTER) ||(TWI_TYPE == TWI_MASTER_SLAVE))
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_bus_reset  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_bus_reset                                                     |
 | < @Description       :reset bus busy is ready and send stop and master state is idle case            |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */


static void twi_master_bus_reset(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_read_done  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_read_done                                                     |
 | < @Description       : send ack or nack when read is required done                                   |
 | < @param data        : set byte into buffer and check is a last byte or not to send ack or nack      |          
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void twi_master_read_done(uint8_t data);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_read_last_byte  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_read_last_byte                                                      |
 | < @Description       : last byte the send nack and send stop                                          |
 | < @param data        : data last byte send                                                            |          
 | < @return            : void                                                                           |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_read_last_byte(uint8_t data);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_addr_ack  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_addr_ack                                                       |
 | < @Description       : ack or nack when send address                                                  |        
 | < @return            : void                                                                           |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_addr_ack(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_internal_addr_write  >                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_internal_addr_write                                            |
 | < @Description       : write when read data or write data and chip                                    |
 |                      : node has a internal address in first  write internal address                   |
 |                      : by specefic length after this operationcan start read or write operation       |                                  |        
 | < @return            : void                                                                           |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_internal_addr_write(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_data_write  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_data_write                                                    |
 | < @Description       : after send internal address or not and write                                  |
 |                      : SLA+Data in chip no internal address                                          |                   |
 |                      : by specefic length after this operationcan start read or write operation      |                                  |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_data_write(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_write_done  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_write_done                                                    |
 | < @Description       : this function has full write operation is slave address and                   |
 |                      : and write internal address in node have internal address and write data       |                   |
 |                      : by specefic length after this operationcan start read or write operation      |                                  |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_write_done(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_start  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_start                                                         |
 | < @Description       : send slave address and start condition                                        |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void twi_master_start(void);
#endif
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  Slave Function Definition >                                        |
 --------------------------------------------------------------------------------------------------------
 */

#if((TWI_TYPE == TWI_SLAVE) ||(TWI_TYPE == TWI_MASTER_SLAVE))
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_enable  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_enable                                                         |
 | < @Description       : target decive work as slave                                                   |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_slave_enable(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_write_byte  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_write_byte                                                     |
 | < @Description       : assignment byte into data register when slave is transmit                     |   
 | < @param data        : value set into data register                                                  |                  
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_slave_write_byte(uint8_t data);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_data_write  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_data_write                                                     |
 | < @Description       : slave transmission operation                                                  |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_slave_data_write(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_last_byte_write_done  >                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_last_byte_write_done                                           |
 | < @Description       : enable slave mode and indicator slave transmission complete                                                  |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void twi_slave_last_byte_write_done(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_data_read  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_data_read                                                      |
 | < @Description       : assignment data into rx buffer and enable slave mode                          |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_slave_data_read(uint8_t data);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_bus_reset  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_bus_reset                                                      |
 | < @Description       : reset state and send stop condition                                           |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_slave_bus_reset(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_state_get  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t twi_slave_state_get                                                   |
 | < @Description       : get slave state                                                               |                 
 | < @return            : get slave state                                                               |
 --------------------------------------------------------------------------------------------------------
 */



static uint8_t twi_slave_state_get(void);


#endif





/*
 --------------------------------------------------------------------------------------------------------
 |                                <  General Function Definition >                                        |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_interrupt_handler  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_interrupt_handler                                                   |
 | < @Description       : ISR handler                                                                   |
 |                      : work master in transmission operation                                         |
 |                      : work master in receive operation                                              |
 |                      : work slave in transmission operation                                          |
 |                      : work slave in receive operation                                               |                 |                            
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_interrupt_handler(void);


/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_interrupt_enable  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_interrupt_enable                                                    |
 | < @Description       : enable the twi interrupt                                                      |                            |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline void twi_interrupt_enable(void);

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_interrupt_disable  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_interrupt_disable                                                   |
 | < @Description       : disable the twi interrupt                                                     |                            
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline void twi_interrupt_disable(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_read_byte  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  twi_read_byte                                                  |
 | < @Description       : read current  data form data register of twi                                  |                           
 | < @return            : return current byte in data register                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline uint8_t twi_read_byte(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_write_byte  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_write_byte                                                          |
 | < @Description       : assignemnt by into data register                                              |                           
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline void twi_write_byte(uint8_t data);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_send_ack  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_send_ack                                                            |
 | < @Description       : send ack or not ack by set or  clear ack bit in control register              | 
 | < @param  ack        : state of ack determined the ack send or n-ack if ack is 1 the send else n-ack |                        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_send_ack(uint8_t ack);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_send_stop  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_send_stop                                                            |
 | < @Description       : master send stop to slave                                                     |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_send_stop(void);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_send_start  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_send_start                                                           |
 | < @Description       : master send start to slave                                                    |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_send_start(void);

/*
 --------------------------------------------------------------------------------------------------------
 |                                <  Basic Function Implementition >                                    |
 --------------------------------------------------------------------------------------------------------
 */
ISR(TWI_vect) {
    twi_interrupt_handler();
}


/*
 --------------------------------------------------------------------------------------------------------
 |                                < Master Basic Function Implementition >                              |
 --------------------------------------------------------------------------------------------------------
 */


#if((TWI_TYPE == TWI_MASTER) ||(TWI_TYPE == TWI_MASTER_SLAVE))

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_bus_reset  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_bus_reset                                                     |
 | < @Description       :reset bus busy is ready and send stop and master state is idle case            |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */


static void twi_master_bus_reset(void) {
    master_transfer.state = TWI_IDLE;
    twi_master_busy = 0;
    twi_send_stop();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_read_done  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_read_done                                                     |
 | < @Description       : send ack or nack when read is required done                                   |
 | < @param data        : set byte into buffer and check is a last byte or not to send ack or nack      |          
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void twi_master_read_done(uint8_t data) {
    if (master_transfer.state == TWI_READ_DATA) {
        master_transfer.pkg->buffer[master_transfer.data_count++] = data;
        if (master_transfer.data_count < (master_transfer.pkg->length - 1)) {
            twi_send_ack(1);
        } else {
            twi_send_ack(0);
        }
    } else {
        twi_master_bus_reset();
        master_transfer.status = ERR_PROTOCOL;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_read_last_byte  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_read_last_byte                                                      |
 | < @Description       : last byte the send nack and send stop                                          |
 | < @param data        : data last byte send                                                            |          
 | < @return            : void                                                                           |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_read_last_byte(uint8_t data) {
    if (master_transfer.state == TWI_READ_DATA) {
        master_transfer.pkg->buffer[master_transfer.data_count++] = data;
        twi_send_stop();
        master_transfer.state = TWI_IDLE;
        master_transfer.status = STATUS_OK;
        twi_master_busy = 0;
    } else {

        twi_master_bus_reset();
        master_transfer.status = ERR_PROTOCOL;
    }

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_addr_ack  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_addr_ack                                                      |
 | < @Description       : send ack or nack when send after last bye received                            |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_addr_ack(void) {
    if (master_transfer.state == TWI_READ_DATA) {
        if (master_transfer.data_count == (master_transfer.pkg->length - 1)) {
            twi_send_ack(0);
        } else {
            twi_send_ack(1);
        }
    } else {
        twi_master_bus_reset();
        master_transfer.status = ERR_PROTOCOL;
    }

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_internal_addr_write  >                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_internal_addr_write                                            |
 | < @Description       : write when read data or write data and chip                                    |
 *                      : node has a internal address in first  write internal address                   |
 *                      : by specefic length after this operationcan start read or write operation       |                                  |        
 | < @return            : void                                                                           |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_internal_addr_write(void) {
    uint8_t data;
    data = master_transfer.pkg->addr[master_transfer.addr_count];
    master_transfer.addr_count++;
    twi_write_byte(data);
    if (master_transfer.addr_count == master_transfer.pkg->addr_length) {
        if (master_transfer.state == TWI_WRITE_IADDR_WRITE_DATA) {
            master_transfer.state = TWI_WRITE_DATA;
        } else {
            master_transfer.state = TWI_READ_DATA;
        }
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_data_write  >                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_data_write                                           |
 | < @Description       : after send internal address or not and write                                  |
 |                      : SLA+Data in chip no internal address                                          |                   |
 |                      : by specefic length after this operationcan start read or write operation      |                                  |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_master_data_write(void) {
    if (master_transfer.data_count < master_transfer.pkg->length) {
        twi_write_byte(master_transfer.pkg->buffer[master_transfer.data_count++]);
    } else {
        twi_send_stop();
        master_transfer.state = TWI_IDLE;
        master_transfer.status = STATUS_OK;
        twi_master_busy = 0;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_write_done  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_write_done                                                    |
 | < @Description       : this function has full write operation is slave address and                   |
 |                      : and write internal address in node have internal address and write data       |                   |
 |                      : by specefic length after this operationcan start read or write operation      |                                  |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void twi_master_write_done(void) {
    if (TWI_WRITE_DATA == master_transfer.state) {
        twi_master_data_write();
    } else if ((TWI_WRITE_IADDR_WRITE_DATA == master_transfer.state) ||
            (TWI_WRITE_IADDR_READ_DATA == master_transfer.state)) {
        twi_master_internal_addr_write();
    } else if (TWI_READ_DATA == master_transfer.state) {
        twi_send_start();
    } else { /* abnormal */
        twi_master_bus_reset();
        master_transfer.status = ERR_PROTOCOL;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_start  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_master_start                                                         |
 | < @Description       : send slave address and start condition                                        |        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void twi_master_start(void) {
    uint8_t chip_add;

    if ((TWI_WRITE_IADDR_WRITE_DATA == master_transfer.state) || (TWI_WRITE_DATA ==
            master_transfer.state) || (TWI_WRITE_IADDR_READ_DATA ==
            master_transfer.state)) {
        chip_add = TWI_WRITE_ENABLE(master_transfer.pkg->chip);
        twi_write_byte(chip_add);
    } else if (TWI_READ_DATA == master_transfer.state) {
        chip_add = TWI_READ_ENABLE(master_transfer.pkg->chip);
        twi_write_byte(chip_add);
    } else { /* abnormal */
        twi_master_bus_reset();
        master_transfer.status = ERR_PROTOCOL;
    }
}
#endif

/*
 --------------------------------------------------------------------------------------------------------
 |                                < Slave Basic Function Implementition >                               |
 --------------------------------------------------------------------------------------------------------
 */

#if((TWI_TYPE == TWI_SLAVE) ||(TWI_TYPE == TWI_MASTER_SLAVE))
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_enable  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_enable                                                         |
 | < @Description       : target decive work as slave                                                   |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_slave_enable(void) __attribute__((always_inline, unused));

static inline void twi_slave_enable(void) {
    TWCR = (1 << TWEN) | /* Enable TWI-interface and release TWI pins */
            (1 << TWIE) | (1 << TWINT) | /* Keep interrupt enabled
	                                              * and clear the flag */
            (1 << TWEA) | (0 << TWSTA) | (0 << TWSTO) | /* Acknowledge on any
	                                                     * new requests */
            (0 << TWWC);
}
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_write_byte  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_write_byte                                                     |
 | < @Description       : assignment byte into data register when slave is transmit                     |   
 | < @param data        : value set into data register                                                  |                  
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_slave_write_byte(uint8_t data) __attribute__((always_inline, unused));

static inline void twi_slave_write_byte(uint8_t data) {
    TWDR = data;
    twi_slave_enable();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_data_write  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_data_write                                                     |
 | < @Description       : slave transmission operation                                                  |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_slave_data_write(void) {
    twi_slave_write_byte(slave_transfer.data_buffer->tx_buffer[slave_transfer.data_count++]);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_last_byte_write_done  >                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_last_byte_write_done                                           |
 | < @Description       : enable slave mode and indicator slave transmission complete                                                  |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_slave_last_byte_write_done(void) {
    slave_transfer.state = TWI_IDLE;
    slave_transfer.status = TWI_STATUS_TX_COMPLETE;

    twi_slave_enable();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_data_read  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_data_read                                                      |
 | < @Description       : assignment data into rx buffer and enable slave mode                          |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void twi_slave_data_read(uint8_t data) {
    slave_transfer.data_buffer->rx_buffer[slave_transfer.data_count++] = data;
    twi_slave_enable();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_bus_reset  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_slave_bus_reset                                                      |
 | < @Description       : reset state and send stop condition                          |                 
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static void twi_slave_bus_reset(void) {
    slave_transfer.state = TWI_IDLE;
    twi_send_stop();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_state_get  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t twi_slave_state_get                                                   |
 | < @Description       : get slave state                                                               |                 
 | < @return            : get slave state                                                               |
 --------------------------------------------------------------------------------------------------------
 */



static uint8_t twi_slave_state_get(void) {
    return slave_transfer.state;
}


#endif



/*
 --------------------------------------------------------------------------------------------------------
 |                                < General Basic Function Implementition >                             |
 --------------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_interrupt_enable  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_interrupt_enable                                                    |
 | < @Description       : enable the twi interrupt                                                      |                            |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline void twi_interrupt_enable(void) __attribute__((always_inline, unused));

static inline void twi_interrupt_enable(void) {
    TWCR |= (1 << TWIE);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_interrupt_disable  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_interrupt_disable                                                   |
 | < @Description       : disable the twi interrupt                                                     |                            
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline void twi_interrupt_disable(void) __attribute__((always_inline, unused));

static inline void twi_interrupt_disable(void) {
    TWCR &= (~(1 << TWIE));
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_read_byte  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  twi_read_byte                                                  |
 | < @Description       : read current  data form data register of twi                                  |                           
 | < @return            : return current byte in data register                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline uint8_t twi_read_byte(void) __attribute__((always_inline, unused));

static inline uint8_t twi_read_byte(void) {
    return TWDR;
}
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_write_byte  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_write_byte                                                          |
 | < @Description       : assignemnt by into data register                                              |                           
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_write_byte(uint8_t data) __attribute__((always_inline, unused));

static inline void twi_write_byte(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
}
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_send_ack  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_send_ack                                                            |
 | < @Description       : send ack or not ack by set or  clear ack bit in control register              | 
 | < @param  ack        : state of ack determined the ack send or n-ack if ack is 1 the send else n-ack |                        
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline void twi_send_ack(uint8_t ack) __attribute__((always_inline, unused));

static inline void twi_send_ack(uint8_t ack) {
    if (ack) {
        TWCR |= (1 << TWEA);
    } else {
        TWCR &= ~(1 << TWEA);
    }

    TWCR |= ((1 << TWINT) | (1 << TWIE) | (1 << TWEN)); /* Trigger the TWI */
}
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_send_stop  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_send_stop                                                            |
 | < @Description       : master send stop to slave                                                     |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */



static inline void twi_send_stop(void) __attribute__((always_inline, unused));

static inline void twi_send_stop(void) {
    TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
}
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_send_start  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void twi_send_start                                                           |
 | < @Description       : master send start to slave                                                    |                      
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

static inline void twi_send_start(void) __attribute__((always_inline, unused));

static inline void twi_send_start(void) {
    TWCR = ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_interrupt_handler  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  twi_interrupt_handler                                                   |
 | < @Description       : ISR handler                                                                   |
 |                      : work master in transmission operation                                         |
 |                      : work master in receive operation                                              |
 |                      : work slave in transmission operation                                          |
 |                      : work slave in receive operation                                               |                 |                            
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static inline void twi_interrupt_handler(void) __attribute__((always_inline, unused));

static inline void twi_interrupt_handler(void) {
    uint8_t status;
    status = TWI_TWSR_STATUS_MASK;

    switch (status) {
#if((TWI_TYPE == TWI_MASTER) ||(TWI_TYPE == TWI_MASTER_SLAVE))
        case TWS_START: /*A START condition has been transmitted.*/
        case TWS_RSTART: /*A repeated START condition has been
	                                       *transmitted.*/
            twi_master_start();
            break;

        case TWS_MT_SLA_ACK: /*SLA+W has been transmitted; ACK has
	                                        *been received.*/
        case TWS_MT_DATA_ACK: /*Data byte has been transmitted; ACK has
	                                        *been received.*/
            twi_master_write_done();
            break;

        case TWS_BUSERROR: /*Bus error due to illegal START or STOP
	                                        * condition.*/
        case TWS_MT_SLA_NACK: /*SLA+W has been transmitted; NOT ACK has
	                                        *been received.*/
        case TWS_MT_DATA_NACK: /*Data byte has been transmitted; NOT ACK
	                                        *has been received.*/
        case TWS_MR_SLA_NACK: /*SLA+R has been transmitted; NOT ACK has
	                                       *been received.*/
            twi_master_bus_reset();
            master_transfer.status = ERR_IO_ERROR;
            break;

        case TWS_MR_SLA_ACK: /*SLA+R has been transmitted; ACK has been
	                                       *received.*/
            twi_master_addr_ack();
            break;

        case TWS_MR_DATA_ACK: /*Data byte has been received; ACK has been
	                                       *returned.*/
            twi_master_read_done(twi_read_byte());
            break;

        case TWS_MR_DATA_NACK: /*Data byte has been received; NOT ACK has
	                                       *been returned.*/
            twi_master_read_last_byte(twi_read_byte());
            break;

        case TWS_M_ARB_LOST: /*Arbitration lost in SLA+W or data bytes
	                       *(Transmitter); Arbitration lost in SLA+R or
	                       *NOT ACK bit (Receiver).*/
            /* If arbitration lost indicate to application to decide either
             * switch to Slave mode or wait until the bus is free and transmit
             * a new START condition */
            master_transfer.state = TWI_IDLE;
            master_transfer.status = ERR_BUSY;
            twi_master_busy = 0;
            break;
#endif
#if((TWI_TYPE == TWI_SLAVE) ||(TWI_TYPE == TWI_MASTER_SLAVE))
        case TWS_ST_SLA_ACK: /* Own SLA+R has been received; ACK has been
		                     * returned */
        case TWS_ST_SLA_ACK_M_ARB_LOST: /* ! Arbitration lost in SLA+R/W as Master;
	                                   *own SLA+R has been received;
	                                   *ACK has been returned */
            slave_transfer.data_count = 0; /* Set buffer pointer to first data
		                            * location */

        case TWS_ST_DATA_ACK: /* Data byte in TWDR has been transmitted;
		                     * ACK has been received */
            twi_slave_data_write();
            slave_transfer.state = TWI_PROCESS;
            break;

        case TWS_ST_DATA_NACK: /* Data byte in TWDR has been transmitted;
		                     * NACK has been received. */
            /* I.e. this could be the end of the
             * transmission. */
            twi_slave_last_byte_write_done();
            break;

        case TWS_SR_GEN_ACK: /* General call address has been received;
		                     * ACK has been returned */
        case TWS_SR_GEN_ACK_M_ARB_LOST: /* ! Arbitration lost in SLA+R/W as Master; 
	                                  * General call address has been received;
	                                  *  ACK has been returned */
        case TWS_SR_SLA_ACK: /* Own SLA+W has been received ACK has been
		                     * returned */
        case TWS_SR_SLA_ACK_M_ARB_LOST: /* ! Arbitration lost in  SLA+R/W as Master;
	                                 * own SLA+W has been received; 
	                                 * ACK has been returned */
            slave_transfer.data_count = 0; /* Set buffer pointer to first data
		                            * location */
            twi_slave_enable();
            slave_transfer.state = TWI_PROCESS;

            break;

        case TWS_SR_SLA_DATA_ACK: /* Previously addressed with own SLA+W; data
		                     * has been received; ACK has been returned */
        case TWS_SR_GEN_DATA_ACK: /* Previously addressed with general call;
		                     * data has been received; ACK has been
		                     * returned */
            twi_slave_data_read(twi_read_byte());
            slave_transfer.state = TWI_PROCESS;
            break;

        case TWS_SR_STOP_RESTART: /* A STOP condition or repeated START
		                     * condition has been received while still
		                     * addressed as Slave */
            /* Enter not addressed mode and listen to address match */
            slave_transfer.state = TWI_IDLE;
            slave_transfer.status = TWI_STATUS_RX_COMPLETE;
            twi_slave_enable();
            break;

        case TWS_SR_SLA_DATA_NACK: /* Previously addressed with own SLA+W; data
		                     * has been received; NOT ACK has been
		                     * returned */
        case TWS_SR_GEN_DATA_NACK: /* Previously addressed with general call;
		                     * data has been received; NOT ACK has been
		                     * returned */
        case TWS_ST_DATA_ACK_LAST_BYTE: /* Last data byte in TWDR has been
		                         * transmitted (TWEA = ; ACK has
		                         * been received */
            twi_slave_bus_reset();
            slave_transfer.status = TWI_STATUS_IO_ERROR;
            break;
#endif
        default:
#if((TWI_TYPE == TWI_MASTER) ||(TWI_TYPE == TWI_MASTER_SLAVE))
            if (twi_mode == TWI_MASTER_BUS) {
                master_transfer.state = TWI_IDLE;
                master_transfer.status = ERR_PROTOCOL;
                twi_master_busy = 0;
                return;
            }
#endif
#if((TWI_TYPE == TWI_SLAVE) ||(TWI_TYPE == TWI_MASTER_SLAVE))
            if (twi_mode == TWI_SLAVE_BUS) {
                slave_transfer.status = TWI_STATUS_PROTOCOL_ERROR; /* Store TWI State as
		                            * errormessage, operation also
		                            * clears the Success bit */
                slave_transfer.state = TWI_IDLE;
                twi_slave_enable();
            }
#endif

            break;
    }
}






/*
 --------------------------------------------------------------------------------------------------------
 |                                <  user Function Implementition >                                    |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                                <  Master user Function Implementition >                              |
 --------------------------------------------------------------------------------------------------------
 */

#if (TWI_TYPE == TWI_MASTER ) || (TWI_TYPE == TWI_MASTER_SLAVE)

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_write  >                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_master_write                                                |
 | < @Description       : write data from master to slave                                               |        
 | < @param package     : pointer of the twi node created                                               | 
 | < @return            : twi states when done return STATUS_OK                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
status_code_t twi_master_write(const twi_package_t *package) {
    millis_t t;
    if (package == NULL) return ERR_INVALID_ARG;
    if (twi_master_busy) {
        return OPERATION_IN_PROGRESS;
    }

    master_transfer.pkg = (twi_package_t *) package;
    TWBR = package->baud_reg; /*set speed two work*/
    master_transfer.data_count = 0;
    master_transfer.addr_count = 0;

    twi_master_busy = 1;
    if (TWI_SLAVE_NO_INTERNAL_ADDRESS == master_transfer.pkg->addr_length) {
        /*SLAVE no internal address*/
        master_transfer.state = TWI_WRITE_DATA;
    } else {
        master_transfer.state = TWI_WRITE_IADDR_WRITE_DATA;
    }

    twi_send_start();
    t = (systemMillis() + 10);
    while (twi_master_busy && t > systemMillis()); /*no support time out */
    return twi_master_get_status();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_read  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_master_read                                                 |
 | < @Description       : read data from slave by master                                                |
 | < @param package     : pointer of the twi node created                                               |        
 | < @return            : twi states when done return STATUS_OK                                         |                                  |
 --------------------------------------------------------------------------------------------------------
 */

status_code_t twi_master_read(const twi_package_t *package) {
    millis_t t;
    if (package == NULL || package->length == 0) return ERR_INVALID_ARG;
    if (twi_master_busy) {
        return OPERATION_IN_PROGRESS;
    }

    master_transfer.pkg = (twi_package_t *) package;
    TWBR = package->baud_reg; /*set speed two work*/
    master_transfer.data_count = 0;
    master_transfer.addr_count = 0;
    twi_master_busy = 1;
    if (TWI_SLAVE_NO_INTERNAL_ADDRESS == master_transfer.pkg->addr_length) {
        /*SLAVE no internal address*/
        master_transfer.state = TWI_READ_DATA;
    } else {
        master_transfer.state = TWI_WRITE_IADDR_READ_DATA;
    }

    twi_send_start();
    t = (systemMillis() + 10);
    while (twi_master_busy && t > systemMillis()); /*no support time out */
    return twi_master_get_status();
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_get_status  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_master_get_status                                           |
 | < @Description       : get twi state of the master                                                   |                                            |        
 | < @return            : twi states from handler                                                       |                                  |
 --------------------------------------------------------------------------------------------------------
 */

status_code_t twi_master_get_status(void) {
    return master_transfer.status;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_init  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_master_init                                                 |
 | < @Description       : init data and enable pull up speed                                            |                                            |        
 | < @return            : twi status when done return STATUS_OK                                         |                         |                                  |
 --------------------------------------------------------------------------------------------------------
 */

status_code_t twi_master_init(void) {
    TWCR = 0x00;
    TWCR |= 1 << TWEN;
    /* ! prescaler  1UL*/
    TWSR = 0x00;
    /* ! Set bit rate  as a default 400 Khz*/
    TWBR = TWI_400KHZ;
    twi_interrupt_enable();
    twi_mode = TWI_MASTER_BUS;
#if TWI_INTERNAL_PULL_UP == TWI_PULL_ENABLE
    digitalpinMode(TWI_SDA_PIN, MODE_INPUT_PULLUP);
    digitalpinMode(TWI_SCL_PIN, MODE_INPUT_PULLUP);
#endif
    return STATUS_OK;
}


#endif
/*
 --------------------------------------------------------------------------------------------------------
 |                                <  Slave user Function Implementition >                               |
 --------------------------------------------------------------------------------------------------------
 */
#if((TWI_TYPE == TWI_SLAVE) ||(TWI_TYPE == TWI_MASTER_SLAVE))

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_status_get  >                                                 |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t twi_slave_status_get                                                  |
 | < @Description       : get twi state of the slave                                                    |                      
 | < @return            : twi states                                                                    |
 --------------------------------------------------------------------------------------------------------
 */


uint8_t twi_slave_status_get(void) {
    return slave_transfer.status;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_init  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function               : status_code_t twi_slave_init                                             |
 | < @Description            : set slave address                                                        | 
 | < @param twi_slave_ownadd : slave address to identifiy master ro speak with salve                    |                              
 | < @return                 : STATUS_OK at is done                                                     |
 --------------------------------------------------------------------------------------------------------
 */

status_code_t twi_slave_init(uint8_t twi_slave_ownadd) {
    TWAR = twi_slave_ownadd; /* Set own TWI slave address. Accept TWI
	                             * General Calls. */
    TWCR = (1 << TWEN) | /* Enable TWI-interface and
	                             * release TWI pins. */
            (0 << TWIE) | (0 << TWINT) | /* Disable TWI Interupt. */
            (0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) | /* Do not ACK on
	                                              * any requests yet. */
            (0 << TWWC);

    slave_transfer.state = TWI_IDLE;
    slave_transfer.status = TWI_STATUS_NO_STATE;

    return STATUS_OK;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_start  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_slave_start                                                 |
 | < @Description       : Initiate a transaction when the bus is ready                                  |                      
 | < @return            : STATUS_OK at is done                                                          |
 --------------------------------------------------------------------------------------------------------
 */


status_code_t twi_slave_start(twi_slave_data_buffer_t *package) {

    if (TWI_IDLE != slave_transfer.state) {
        return OPERATION_IN_PROGRESS;
    }
    /* Initiate a transaction when the bus is ready. */
    slave_transfer.data_buffer = (twi_slave_data_buffer_t *) package;
    slave_transfer.data_count = 0;
    twi_slave_status_reset();
    return STATUS_OK;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_start  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_slave_start                                                 |
 | < @Description       : reset all state of the slave and enable slave mode                            |                     
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */

void twi_slave_status_reset(void) {
    slave_transfer.state = TWI_IDLE;
    slave_transfer.status = TWI_STATUS_NO_STATE;
    twi_mode = TWI_SLAVE_BUS;
    twi_slave_enable();
}
#endif


#endif
#endif