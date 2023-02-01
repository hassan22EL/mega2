
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
#ifndef XC_TWI_H
#define	XC_TWI_H


#include "../mega.h"

#if defined  TWI_MODULE
#if TWI_MODULE


/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < Macro  Definition>                                                       |
 ----------------------------------------------------------------------------------------------------------------
 */

/*
 ----------------------------------------------------------------------------------------------------------------
 |                                <    TWI Type   >                                                             |
 ----------------------------------------------------------------------------------------------------------------                                                             |
 | < macro TWI_MASTER        : twi work as master only                                                          |
 | < macro TWI_SLAVE         : twi work as slave only                                                           |
 | < macro TWI_MASTER_SLAVE  : twi work both master or slave                                                    |
 | < macro TWI_TYPE          : select one mode of three by user look modules.h (twi interface)                  |   
 ----------------------------------------------------------------------------------------------------------------
 */
#define  TWI_MASTER         (0)
#define  TWI_SLAVE          (1)
#define  TWI_MASTER_SLAVE   (3)



#ifndef   TWI_TYPE          
#error      "Please Define TWI_TYPE"
#endif
/*
 ----------------------------------------------------------------------------------------------------------------
 |                                <    TWI Type   >                                                             |
 ----------------------------------------------------------------------------------------------------------------
 | < macro  TWI_SLAVE_NO_INTERNAL_ADDRESS        : TWI chip no have Internal address                            |
 | < macro  TWI_SLAVE_ONE_BYTE_SIZE              : TWI chip have one byte internal address 2^8 addresses        |
 | < macro  TWI_SLAVE_TWO_BYTE_SIZE              : TWI chip have two byte internal address 2^16 addresses       |
 | < macro  TWI_SLAVE_THREE_BYTE_SIZE            : TWI chip have a three byte internal address 2^24 addresses   |
 ----------------------------------------------------------------------------------------------------------------
 */
#define      TWI_SLAVE_NO_INTERNAL_ADDRESS        (0)
#define      TWI_SLAVE_ONE_BYTE_SIZE              (1)
#define      TWI_SLAVE_TWO_BYTE_SIZE              (2)
#define      TWI_SLAVE_THREE_BYTE_SIZE            (3)

/*
 ----------------------------------------------------------------------------------------------------------------
 |                                <    Pull up option   >                                                       |
 ----------------------------------------------------------------------------------------------------------------                                                             |
 | < macro TWI_PULL_ENABLE        : twi enable internal pull up                                                 |
 | < macro TWI_PULL_DIABLE        : twi disable internal pull up                                                |
 | < macro TWI_INTERNAL_PULL_UP   : select one pull option of three by user look modules.h                      |                                           
 ----------------------------------------------------------------------------------------------------------------
 */
#define    TWI_PULL_ENABLE        (0)
#define    TWI_PULL_DIABLE        (1)

#ifndef    TWI_INTERNAL_PULL_UP        
#define    TWI_INTERNAL_PULL_UP      TWI_PULL_ENABLE
#endif

/*
 ----------------------------------------------------------------------------------------------------------------
 |                                <  twi clock>                                                                 |
 ---------------------------------------------------------------------------------------------------------------- 
 */
#define    TWI_CLOCK_STANDER_100KHz                        100000UL
#define    TWI_CLOCK_STANDER_400KHz                        400000UL
#define    TWI_CLOCK_STANDER_1000KHz                       1000000UL
#define    TWI_CLOCK_STANDER_17000KHz                      1700000UL    
#define    TWI_CLOCK_STANDER_34000KHz                      3400000UL
#define    TWI_CLOCK_STANDER_5000KHz                       5000000UL
/*
 ----------------------------------------------------------------------------------------------------------------
 |                                <   twi Register value   >                                                    |
 ----------------------------------------------------------------------------------------------------------------  
 | < macro  TWI_STANDARD_MODE_SPEED   : twi work with 100KHz speed                                              |
 | < macro  TWI_FAST_MODE_SPEED       : twi work with 400KHz speed                                              |
 ----------------------------------------------------------------------------------------------------------------
 */
#define       TWI_STANDARD_MODE_SPEED                       (((F_CPU-(16UL*TWI_CLOCK_STANDER_100KHz)+(TWI_CLOCK_STANDER_100KHz))/(TWI_CLOCK_STANDER_100KHz*2UL)))                       
#define       TWI_FAST_MODE_SPEED                           (((F_CPU-(16UL*TWI_CLOCK_STANDER_400KHz)+(TWI_CLOCK_STANDER_400KHz))/(TWI_CLOCK_STANDER_400KHz*2UL)))



/*
 ----------------------------------------------------------------------------------------------------------------
 |                                <   twi assign speed by user   >                                              |
 ----------------------------------------------------------------------------------------------------------------  
 | < macro  TWI_400KHZ       : twi work with standard speed mode                                                |
 | < macro  TWI_100KHZ       : twi work with fast speed mode                                                    |
 ----------------------------------------------------------------------------------------------------------------
 */
#define     TWI_400KHZ                        (TWI_FAST_MODE_SPEED)
#define     TWI_100KHZ                        (TWI_STANDARD_MODE_SPEED)



/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < twi clock pin>                                                           |
 ----------------------------------------------------------------------------------------------------------------
 */
#ifndef            TWI_SCL_PIN
#define            TWI_SCL_PIN                              NOT_A_PIN
#endif

/*
 ----------------------------------------------------------------------------------------------------------------
 |                                   < twi data pin >                                                           |
 ----------------------------------------------------------------------------------------------------------------
 */
#ifndef            TWI_SDA_PIN
#define            TWI_SDA_PIN                              NOT_A_PIN   
#endif



/*
 ----------------------------------------------------------------------------------------------------------------  
 |                          <TWI STATUS at handler >                                                            |
 ----------------------------------------------------------------------------------------------------------------  
 | < macro   TWI_SUCCESS               : TWI is done                                                            |
 | < macro   TWI_STATUS_NO_STATE       : no have any condition                                                  |
 | < macro   TWI_STATUS_TX_COMPLETE    : transmission complete                                                  |
 | < macro   TWI_STATUS_RX_COMPLETE    : receive complete                                                       |
 | < macro   TWI_STATUS_IO_ERROR       : TWI have I/O error                                                     |
 | < macro   TWI_STATUS_PROTOCOL_ERROR : TWI has error                                                          |
  ----------------------------------------------------------------------------------------------------------------  
 */

#define TWI_SUCCESS                  0
#define TWI_STATUS_NO_STATE          1
#define TWI_STATUS_TX_COMPLETE       2
#define TWI_STATUS_RX_COMPLETE       3
#define TWI_STATUS_IO_ERROR         -1
#define TWI_STATUS_PROTOCOL_ERROR   -2




#if((TWI_TYPE == TWI_SLAVE) ||   (TWI_TYPE == TWI_MASTER_SLAVE))

/*
  -----------------------------------------------------------------------------------------------------------------
 |                                <  TWI slave Descirption   >                                                    |
 ------------------------------------------------------------------------------------------------------------------
 | < Description          : Twi slave struct                                                                      |
 | < Uasge                : 4 Byte                                                                                |                                     |
 | < param rx_buffer      : pointer to receive buffer assignment from appplication used twi-slave                 |
 | < param tx_buffer      : pointer to transmission buffer assignment from appplication used twi-slave            |                                          |              
 ------------------------------------------------------------------------------------------------------------------
 */
typedef struct {
    uint8_t *rx_buffer;
    uint8_t *tx_buffer;
} twi_slave_data_buffer_t;
#endif

/*
 -----------------------------------------------------------------------------------------------------------------
 |                                <  TWI Master Descirption   >                                                  |
 -----------------------------------------------------------------------------------------------------------------
 | < Description          : Twi struct                                                                           |
 | < Uasge                : 9 Byte                                                                               |
 | < param Chip           : slave address                                                                        |
 | < param address        : buffer of internal address max used 3 byte                                           |
 | < param address length : how many byte used of 3 byte address                                                 |
 | < param buffer         : pointer of data                                                                      |
 | < param length         : number of byte data to read or write                                                 |
 | < param data           : pointer to write buffer                                                              |              
 -----------------------------------------------------------------------------------------------------------------
 */

typedef struct {
    uint8_t chip;
    uint8_t addr[3];
    uint8_t addr_length;
    uint8_t *buffer;
    uint8_t length;
    uint8_t baud_reg;
} twi_package_t;


/*
 --------------------------------------------------------------------------------------------------------
 |                                <  Master user Function Implementition >                              |
 --------------------------------------------------------------------------------------------------------
 */


#if((TWI_TYPE == TWI_MASTER) ||(TWI_TYPE == TWI_MASTER_SLAVE))
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
status_code_t twi_master_write(const twi_package_t *package);

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
status_code_t twi_master_read(const twi_package_t *package);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_get_status  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_master_get_status                                           |
 | < @Description       : get twi state of the master                                                   |                                            |        
 | < @return            : twi states from handler                                                       |                                  |
 --------------------------------------------------------------------------------------------------------
 */

status_code_t twi_master_get_status(void);

/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_master_init  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_master_init                                                 |
 | < @Description       : init data and enable pull up speed                                            |                                            |        
 | < @return            : twi status when done return STATUS_OK                                         |                         |                                  |
 --------------------------------------------------------------------------------------------------------
 */

status_code_t twi_master_init(void);

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

uint8_t twi_slave_status_get(void);
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

status_code_t twi_slave_init(uint8_t twi_slave_ownadd);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_start  >                                                      |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_slave_start                                                 |
 | < @Description       : Initiate a transaction when the bus is ready                                  |
 | < @param   package   : pointer slave buffer rx and tx                                                |                      
 | < @return            : STATUS_OK at is done                                                          |
 --------------------------------------------------------------------------------------------------------
 */

status_code_t twi_slave_start(twi_slave_data_buffer_t *package);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < twi_slave_status_reset  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : status_code_t twi_slave_status_reset                                          |
 | < @Description       : reset all state of the slave and enable slave mode                            |                     
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void twi_slave_status_reset(void);
#endif

#endif
#endif

#endif	/* XC_TWI_H */

