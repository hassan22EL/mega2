/*
 ---------------------------------------------------------------------------------------------------------
 |                           < Module  Definition >                                                      | 
 ---------------------------------------------------------------------------------------------------------
 | < FILE                  : bootloadercmd.h                                                             |                                  
 | < Author                : Hassan Elsaied                                                              |
 | < Version               : Mega2v241022                                                                |
 | < Refences              : no- ref                                                                     |  
 | < SRAM USAGE            : no-used data                                                                |
 | < PROGRAM USAGE         : no-used                                                                     |                                 
 | < Hardware Usage        : no used                                                                     |
 | < File Created          : 24-10-2022                                                                  |
 ---------------------------------------------------------------------------------------------------------
 */
#ifndef BOOTLOADER_CMD_H
#define	BOOTLOADER_CMD_H

/*
 ---------------------------------------------------------------------------------------------------------
 |                           < Serial number commands >                                                  | 
 ---------------------------------------------------------------------------------------------------------
 */

/*
 ---------------------------------------------------------------------------------------------------------
 |                           <Requeset Commands >                                                        | 
 ---------------------------------------------------------------------------------------------------------
 */
/*
 * < @macro  BOOT_SET_SERAIL : decive ready to receive any cmd
 */
#define      BOOT_SET_SERAIL                              0x80 
/*
 * < @macro  BOOT_REMOVE_SERIAL : remove serail 
 */
#define      BOOT_REMOVE_SERIAL                           0x81
/*
 * < @macro  BOOT_STOP_SERIAL : Stop Writting Serial
 */
#define      BOOT_STOP_SERIAL                             0x82




/*
 ---------------------------------------------------------------------------------------------------------
 |                           <Response Commands >                                                        | 
 ---------------------------------------------------------------------------------------------------------
 */


/*
 * < @macro  BOOT_SET_SERAIL_RES : assignment serial to channel 0 response
 */
#define      BOOT_SET_SERAIL_RES                          0x83

/*
 * < @macro  BOOT_REMOVE_SERIAL_RES : remove serail Resposne
 */
#define      BOOT_REMOVE_SERIAL_RES                       0x84
/*
 * < @macro  BOOT_SERIAL_DATA_RES :  serail Resposne of the store data
 */
#define      BOOT_SERIAL_DATA_RES                         0x85


/*
 ---------------------------------------------------------------------------------------------------------
 |                           <Programming Commands Commands >                                            | 
 ---------------------------------------------------------------------------------------------------------
 */

/*
 * < @macro  BOOT_PROGREAMMING : Download hex data and write into program memory
 */
#define      BOOT_PROGREAMMING        0x01

#endif	/* BOOTLOADER_CMD_H */

