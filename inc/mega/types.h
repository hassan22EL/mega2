/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   macros.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   total byte used 0 Byte  
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   1-hour
 * Comments     :   no comment
 *  
 */

#ifndef XC_TPYES_H
#define	XC_TPYES_H

/* 
 * ******************************************************************************
 *                       Boolean data Type                                      *
 * ******************************************************************************
 */

typedef uint8_t boolean_t;
/* 
 * ******************************************************************************
 *                        Timer Data Type                                *
 * ******************************************************************************
 */
typedef uint32_t tick_t;
typedef uint32_t micros_t;
typedef uint32_t millis_t;
typedef uint32_t time_t;
/* 
 * ******************************************************************************
 *                       Call backs Functions                                     *
 * ******************************************************************************
 */

typedef void(*pFunc_t)(void);
typedef uint8_t(*pAsyncFunc_t)(void);
typedef void (*pFuncParam_t)(uint8_t);

/* 
 * ******************************************************************************
 *                       Word and byte data type                               *
 * ******************************************************************************
 */

typedef uint8_t byte;
typedef uint16_t word;
/* 
 * ******************************************************************************
 *                       Gpio data Type                                          *
 * ******************************************************************************
 */
typedef uint16_t gpio_t;

/* 
 * ******************************************************************************
 *                                Flags Byte                                    *
 * ******************************************************************************
 * @member byte : byte assignment
 * @member b0   : Bit 0 assignment in Byte
 * @member b1   : Bit 1 assignment in Byte
 * @member b2   : Bit 2 assignment in Byte
 * @member b3   : Bit 3 assignment in Byte
 * @member b4   : Bit 4 assignment in Byte
 * @member b5   : Bit 5 assignment in Byte
 * @member b6   : Bit 6 assignment in Byte
 * @member b7   : Bit 7 assignment in Byte
 */
typedef union {
    uint8_t byte;

    struct {
        unsigned b0 : 1;
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
    };
} byte_Flags_t;

typedef union {
    uint8_t byte;

    struct {
        unsigned B0 : 1;
        unsigned B1 : 1;
        unsigned b2_3 : 2;
        unsigned b4_5 : 2;
        unsigned B6 : 1;
        unsigned B7 : 1;
    };
} byte_Flags2Bit_t;

/* 
 * ******************************************************************************
 *                                User State                                    *
 * ******************************************************************************
 * Status code that may be returned by shell commands and protocol
 * implementations.
 * @note Any change to these status codes and the corresponding
 * message strings is strictly forbidden. New codes can be added,
 * however, but make sure that any message string tables are updated
 * at the same time.
 */
enum status_code {
    STATUS_OK = 0, //!< Success
    ERR_IO_ERROR = -1, //!< I/O error
    ERR_FLUSHED = -2, //!< Request flushed from queue
    ERR_TIMEOUT = -3, //!< Operation timed out
    ERR_BAD_DATA = -4, //!< Data integrity check failed
    ERR_PROTOCOL = -5, //!< Protocol error
    ERR_UNSUPPORTED_DEV = -6, //!< Unsupported device
    ERR_NO_MEMORY = -7, //!< Insufficient memory
    ERR_INVALID_ARG = -8, //!< Invalid argument
    ERR_BAD_ADDRESS = -9, //!< Bad address
    ERR_BUSY = -10, //!< Resource is busy
    ERR_BAD_FORMAT = -11, //!< Data format not recognized
    ERR_NO_TIMER = -12, //!< No timer available
    ERR_TIMER_ALREADY_RUNNING = -13, //!< Timer already running
    ERR_TIMER_NOT_RUNNING = -14, //!< Timer not running

    /**
     * @brief Operation in progress
     *
     * This status code is for driver-internal use when an operation
     * is currently being performed.
     * @note Drivers should never return this status code to any
     * callers. It is strictly for internal use.
     */
    OPERATION_IN_PROGRESS = -128,
};

typedef enum status_code status_code_t;

typedef enum {
    state_00,
    state_01,
    state_02,
    state_03,
    state_04,
    state_05,
    state_06,
    state_07,
    state_08,
    state_09,
    state_10,
    state_11,
    state_12,
    state_13,
    state_14,
    state_15,
    state_16,
    state_17,
    state_18,
    state_19,
    state_20,
    state_21,
    state_22,
    state_23,
    state_24,
    state_25,
    state_26,
    state_27,
    state_28,
    state_29,
    state_30,
    state_31,
    state_32,
    state_33,
    state_34,
    state_35,
    state_36,
    state_37,
    state_38,
    state_39,
    state_40,
    state_41,
    state_42,
    state_43,
    state_44,
    state_45,
    state_46,
    state_47,
    state_48,
    state_49,
    state_50,
    state_51,
    state_52,
    state_53,
    state_54,
    state_55,
    state_56,
    state_57,
    state_58,
    state_59,
    state_60,
    state_61,
    state_62,
    state_63,
    state_64,
    state_65,
    state_66,
    state_67,
    state_68,
    state_69,
    state_70,
    state_71,
    state_72,
    state_73,
    state_74,
    state_75,
    state_76,
    state_77,
    state_78,
    state_79,
    state_80,
    state_81,
    state_82,
    state_83,
    state_84,
    state_85,
    state_86,
    state_87,
    state_88,
    state_89,
    state_90,
    state_91,
    state_92,
    state_93,
    state_94,
    state_95,
    state_96,
    state_97,
    state_98,
    state_99
} States_t;

#endif	/* XC_TPYES_H */



