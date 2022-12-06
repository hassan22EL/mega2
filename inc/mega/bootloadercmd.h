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
 * < @macro  BOOT_SET_SERAIL : decive ready to receive any cmd
 */
#define      BOOT_SET_SERAIL                              0x80 
/*
 * < @macro  BOOT_SET_SERAIL_RES : assignment serial to channel 0 response
 */
#define      BOOT_SET_SERAIL_RES                          0x81
/*
 * < @macro  BOOT_ASSIGN_SERIAL_CH0 : assignment serial to channel 0
 */
#define      BOOT_ASSIGN_SERIAL_CH0                       0x82
/*
 * < @macro  BOOT_ASSIGN_SERIAL_CH0_RES : assignment serial to channel 0 Response
 */
#define      BOOT_ASSIGN_SERIAL_CH0_RES                   0x83
/*
 * < @macro  BOOT_ASSIGN_SERIAL_CH1 : assignment serial channel 1
 */
#define      BOOT_ASSIGN_SERIAL_CH1                       0x84
/*
 * < @macro  BOOT_ASSIGN_SERIAL_CH1_RES : assignment serial channel 1 Response
 */
#define      BOOT_ASSIGN_SERIAL_CH1_RES                   0x85
/*
 * < @macro  BOOT_REMOVE_SERIAL : remove serail 
 */
#define      BOOT_REMOVE_SERIAL                           0x86
/*
 * < @macro  BOOT_REMOVE_SERIAL_RES : remove serail Resposne
 */
#define      BOOT_REMOVE_SERIAL_RES                       0x87


/*
 * < @macro  BOOT_PROGREAMMING : Download hex data and write into program memory
 */
#define      BOOT_PROGREAMMING        0x01

#endif	/* BOOTLOADER_CMD_H */

