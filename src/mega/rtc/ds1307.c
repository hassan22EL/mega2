
/*
------------------------------------------------------------------------------------------
|                          < Module  Definition >                                        | 
------------------------------------------------------------------------------------------
| < FILE                   : ds1307.c                                                    |                                  
| < Author                 : Hassan Elsaied                                              | 
| < Version                : Mega2v241022                                                |
| < References             : no-used references in this documents                        |
| < SRAM_USAGE             : 21 Byte                                                     |
|                          : 1-Byte state                                                |
|                          : 9-Byte TWI-interface                                        |
|                          : 7-Byte Internal Buffer                                      |
|                          : 4-Byte Time Out                                             |
| < PROGRAM USAGE          : 1888 Byte (944 Instruction)                                 |
| < Hardware Usage         : I2C  as a master                                            |
| < File Created           : 24-10-2022                                                  |
-------------------------------------------------------------------------------------------
 */

#include <stdint-gcc.h>

#include "../../../inc/mega.h"
#if defined (DS1307_MODULE)
#if  DS1307_MODULE

#ifndef TWI_MODULE 
#error  please enable TWI module and select type master mode or master slave mode us used exeeprom module
#elif (TWI_MODULE == MODULE_DIABLE)
#error  please enable TWI module and select type master mode or master slave mode us used exeeprom module
#else
#if TWI_TYPE == TWI_SLAVE
#error  select type master mode or master slave mode us used exeeprom module
#endif
#endif



/*
 -------------------------------------------------------------------------------------------------------
 |                               < Macro  Definition >                                                 |
 -------------------------------------------------------------------------------------------------------
 */


/*
 -------------------------------------------------------------------------------------------------------
 |                               < DS1307_ADDRESS >                                                    |
 -------------------------------------------------------------------------------------------------------
 */


#define  DS1307_ADDRESS          (0xD0)
/*
 -------------------------------------------------------------------------------------------------------
 |                               < Clock mode  >                                                        |
 -------------------------------------------------------------------------------------------------------
 */


#define DS1307_MODE_24H                (0)
#define DS1307_MODE_12H                (1)

#ifndef DS1307_MODE                    
#define DS1307_MODE                 DS1307_MODE_24H
#endif

/*
 -------------------------------------------------------------------------------------------------------
 |                               < internal address  >                                                 |
 -------------------------------------------------------------------------------------------------------
 */
#define  DS1307_SECONDE_ADDRESS        (0x00)
#define  DS1307_MIN_ADDRESS            (0x01)
#define  DS1307_HOUR_ADDRESS           (0x02)
#define  DS1307_DAY_ADDRESS            (0x03)
#define  DS1307_DATE_ADDRESS           (0x04)
#define  DS1307_MONTH_ADDRESS          (0x05)
#define  DS1307_YEAR_ADDRESS           (0x06)
#define  DS1307_CONTROL_ADDRESS        (0x07)

/*
 -------------------------------------------------------------------------------------------------------
 |                               < internal address Length>                                            |
 -------------------------------------------------------------------------------------------------------
 */

#define     DS1307_SLAVE_ADDRESS_LENGTH           TWI_SLAVE_ONE_BYTE_SIZE
/*
 -------------------------------------------------------------------------------------------------------
 |                               < Buffer Length  >                                                    |
 -------------------------------------------------------------------------------------------------------
 */
#define     DS1307_DATA_LENGTH                    (7)

/*
 -------------------------------------------------------------------------------------------------------
 |                               < DS1307 internal read ever n min  >                                  |
 -------------------------------------------------------------------------------------------------------
 */

#ifndef     DS1307_PERDIOC_READ_PER_MIN
#define     DS1307_PERDIOC_READ_PER_MIN                         (5UL)
#endif

#define    DS1307_PERDIOC_READ                        (DS1307_PERDIOC_READ_PER_MIN * 60UL)
/*
 -------------------------------------------------------------------------------------------------------
 |                               < DS1307 Status>                                                      |
 -------------------------------------------------------------------------------------------------------
 */

static byte_Flags_t gu8ds1307States;

/*
 -------------------------------------------------------------------------------------------------------
 |                               < DS1307 Buffer>                                                      |
 -------------------------------------------------------------------------------------------------------
 */
static uint8_t gu8ds1307Buffer[DS1307_DATA_LENGTH];
/*
 -------------------------------------------------------------------------------------------------------
 |                               < DS1307 Time Out >                                                    |
 -------------------------------------------------------------------------------------------------------
 */
static stTimer_TimeOut_t gsDs1307TimeOut;



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
static twi_package_t gstDs1307TwiPag;





/*
 --------------------------------------------------------------------------------------------------------
 |                                   <  Basic operations  >                                             |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Convertdecimal_BCD  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Convertdecimal_BCD                                                |
 | < @Description       : convert buffer decimal to bcd or convert buffer bcd to decimal                |
 | < @param buf         : pointer to buffer date to convert contains                                    |
 | < @param state       : state is 0 bcd to decimal and 1 convert decimal to bcd                        |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void ds1307Convertdecimal_BCD(uint8_t *buf, uint8_t state);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Write  >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Write                                                             |
 | < @Description       : write data from buffer to hardware                                            |
 | < @return            : 0 write operation in progress                                                 |
 |                      : 1 write operation is done                                                     |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t ds1307Write();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Read>                                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Read                                                              |
 | < @Description       : write data from hardware into buffer                                          |
 | < @return            : 0 write operation in progress                                                 |
 |                      : 1 write operation is done                                                     |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t ds1307Read();

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Convertdecimal_BCD  >                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Convertdecimal_BCD                                                |
 | < @Description       : convert buffer decimal to bcd or convert buffer bcd to decimal                |
 | < @param buf         : pointer to buffer date to convert contains                                    |
 | < @param state       : state is 0 bcd to decimal and 1 convert decimal to bcd                        |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
static void ds1307Convertdecimal_BCD(uint8_t *buf, uint8_t state) {
    if (state) {

        for (uint8_t i = 0; i < DS1307_DATA_LENGTH; i++)
            buf[i] = decToBcd(buf[i]);

    } else {

        for (uint8_t i = 0; i < DS1307_DATA_LENGTH; i++)
            buf[i] = BcdToDec(buf[i]);

    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Write  >                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Write                                                             |
 | < @Description       : write data from buffer to hardware                                            |
 | < @return            : 0 write operation in progress                                                 |
 |                      : 1 write operation is done                                                     |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t ds1307Write() {
    if (!gu8ds1307States.b2) {
        /*convert from timestamp to date*/
        ds1307Convertdecimal_BCD(gu8ds1307Buffer, 1);
        gu8ds1307Buffer[rtc_sec] |= 0x80;
        gu8ds1307States.b2 = 1;
        /*set time out*/
        sysSetPeriodMS(&gsDs1307TimeOut, 30);

    } else {
        if (twi_master_write(&gstDs1307TwiPag) == TWI_SUCCESS) {
            gu8ds1307States.b2 = 0;
            /*update now by buffer*/
            rtcConvertTimeToDate(systemNow(), gu8ds1307Buffer);
            return (1);
        }
        if (sysIsTimeoutMs(&gsDs1307TimeOut) == 0) {
            /*call back memory error*/
            gu8ds1307States.b2 = 0;
            return (1);
        }
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Read>                                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Read                                                              |
 | < @Description       : write data from hardware into buffer                                          |
 | < @return            : 0 write operation in progress                                                 |
 |                      : 1 write operation is done                                                     |
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t ds1307Read() {
    if (twi_master_read(&gstDs1307TwiPag) == TWI_SUCCESS) {
        /*convert bcd to decimal*/
        ds1307Convertdecimal_BCD(gu8ds1307Buffer, 0);
        /*set system now*/
        sysUpdateNow(rtcConvertDateToTime(gu8ds1307Buffer));
        return (1);
    }
    if (sysIsTimeoutMs(&gsDs1307TimeOut) == 0) {
        /*call back Ds1307 error*/
        return (1);
    }

    return (0);
}


/*
 --------------------------------------------------------------------------------------------------------
 |                                   <  user operations  >                                              |
 --------------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Init>                                                             |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Init                                                              |
 | < @Description       : reset all data to default                                                     |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void ds1307Init() {
    gu8ds1307States.byte = 0x00;
    /* DS1307 Chip defined */
    gstDs1307TwiPag.chip = DS1307_ADDRESS;
    gstDs1307TwiPag.addr[0] = 0x00;
    gstDs1307TwiPag.addr_length = DS1307_SLAVE_ADDRESS_LENGTH;
    gstDs1307TwiPag.buffer = gu8ds1307Buffer;
    gstDs1307TwiPag.length = DS1307_DATA_LENGTH;
    /*DS - Chip Speed*/
    gstDs1307TwiPag.baud_reg = TWI_100KHZ;
    for (uint8_t i = 0; i < DS1307_DATA_LENGTH; i++)
        gu8ds1307Buffer[i] = 0x00;

}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307Driver>                                                           |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307Driver                                                            |
 | < @Description       : run in background to read or write operation                                  |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void ds1307Driver() {
    if (gu8ds1307States.b0) {
        if (ds1307Write()) {
            /*re- init timer period last read*/
            sysSetPeriodS(&gsDs1307TimeOut, DS1307_PERDIOC_READ);
            gu8ds1307States.b0 = 0;
        }
        return;
    }

    if (gu8ds1307States.b1) {
        if (ds1307Read()) {
            /*re- init timer period last read*/
            sysSetPeriodS(&gsDs1307TimeOut, DS1307_PERDIOC_READ);
            gu8ds1307States.b1 = 0;
        }
        return;
    }
    /*current soft update*/
    if (sysIsTimeoutS(&gsDs1307TimeOut) == 0) {
        /*read is start and set time out 30 ms*/
        sysSetPeriodMS(&gsDs1307TimeOut, 30);
        gu8ds1307States.b1 = 1;
        return;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307IsSetDone>                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307IsSetDone                                                         |
 | < @Description       : check write operation is done or not                                          |
 | < @return            : 0  write operation is done                                                    |
 |                      : 1  write operation is progress                                                |
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ds1307IsSetDone() {
    return gu8ds1307States.b0;
}

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ds1307SetDate>                                                          |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  ds1307IsSetDone                                                         |
 | < @Description       : hardware start from speceific date                                            |
 | < @Param tm          : pointer of the date start                                                     |
 | < @return            : void                                                                          |
 --------------------------------------------------------------------------------------------------------
 */
void ds1307SetDate(stm_t *tm) {
    gu8ds1307Buffer[rtc_sec] = tm->sec;
    gu8ds1307Buffer[rtc_min] = tm->min;
    gu8ds1307Buffer[rtc_hour] = tm->hour;
    gu8ds1307Buffer[rtc_dayw] = tm->dayw;
    gu8ds1307Buffer[rtc_daym] = tm->daym;
    gu8ds1307Buffer[rtc_month] = tm->month;
    gu8ds1307Buffer[rtc_year] = tm->year;
    gu8ds1307States.b0 = 1;
}


#endif
#endif