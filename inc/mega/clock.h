/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   clock.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   No Byte
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   25-10-2022  20:00:00
 * End Data     :   25-10-2022  20:15:00
 * Work Time    :   15-min
 * Comments     :   no comment
 *  
 */

#ifndef XC_CLOCK_H
#define	XC_CLOCK_H
#include "../resource.h"
/*
 ****************************************************
 *                     clock                          *
 * **************************************************
 */
#define  XTAL_01000000                  (1000000UL)
/*
 ****************************************************
 *                     8MHz                          *
 * **************************************************
 */
#define     XTAL_08000000               (8000000UL)
/*
 ****************************************************
 *                     11.0592MHz                          *
 * **************************************************
 */
#define     XTAL_11059200               (11059200UL)
/*
 ****************************************************
 *                     12MHz                          *
 * **************************************************
 */
#define     XTAL_12000000               (20000000UL)

/*
 ****************************************************
 *                     20MHz                          *
 * **************************************************
 */
#define     XTAL_14745600               (14745600UL)

/*
 ****************************************************
 *                     16MHz                          *
 * **************************************************
 */
#define     XTAL_16000000               (16000000UL)
/*
 ****************************************************
 *                     20MHz                         *
 * **************************************************
 */
#define     XTAL_20000000               (20000000UL)


/*
 ********************************************************************************************
 *                     Defined number of micro second per interrupt                         *
 * ******************************************************************************************
 */
#ifndef F_CPU
#error "Please defined F_CPU in resource.h"
#else
#if    F_CPU == XTAL_08000000
#elif  F_CPU == XTAL_11059200
/*
 * ******************************************
 * number of micro second required is 625us *
 * ******************************************
 */
#define     _0625us            (625UL)
/*
 * ******************************************
 * number of micro second required is 1250us *
 * ******************************************
 */
#define     _1250us             (1250UL)
/*
 * ******************************************
 * number of micro second required is 1250us *
 * ******************************************
 */
#define     _1250us             (1250UL)
/*
 * ******************************************
 * number of micro second required is 1875us *
 * ******************************************
 */
#define     _1875us             (1875UL)
/*
 * ******************************************
 * number of micro second required is 2500us *
 * ******************************************
 */
#define     _2500us            (2500UL)
/*
 * ******************************************
 * number of micro second required is 3125us *
 * ******************************************
 */
#define     _3125us              (3125UL)
/*
 * ******************************************
 * number of micro second required is 3750us *
 * ******************************************
 */
#define     _3750us              (3750UL)
/*
 * ******************************************
 * number of micro second required is 1250us *
 * ******************************************
 */
#define     _4375us             (4375UL)
/*
 * ******************************************
 * number of micro second required is 5000UL *
 * ******************************************
 */
#define     _5000us             (5000UL)
/*
 * ******************************************
 * number of micro second required is 5625UL *
 * ******************************************
 */
#define     _5625us             (5625UL)
/*
 * ******************************************
 * number of micro second required is 7500us *
 * ******************************************
 */
#define     _7500us             (7500UL)
/*
 * ******************************************
 * number of micro second required is 10000 *
 * ******************************************
 */
#define     _10000us             (10000UL)
/*
 * ******************************************
 * number of micro second required is 12500us *
 * ******************************************
 */
#define     _12500us             (12500UL)
/*
 * ******************************************
 * number of micro second required is 1500us *
 * ******************************************
 */
#define     _15000us              (15000UL)
/*
 * ******************************************
 * number of micro second required is 17500us *
 * ******************************************
 */
#define     _17500us               (17500UL)
/*
 * ******************************************
 * number of micro second required is 20000us *
 * ******************************************
 */
#define     _20000us             (20000UL)
/*
 * ******************************************
 * number of micro second required is 225000us *
 * ******************************************
 */
#define     _22500us             (22500UL)

#elif  F_CPU == XTAL_12000000

#elif  F_CPU == XTAL_14745600
#elif  F_CPU == XTAL_16000000
#elif  F_CPU == XTAL_20000000
#elif  F_CPU == XTAL_01000000 
#define      _32000us             (32000UL)
#else
#error "F_CPU is not supported"
#endif
#endif
/* 
 * *****************************************************************************
 *                        Active and de-active module                          *
 * *****************************************************************************
 */
#define      MODULE_DIABLE          (0)
#define      MODULE_ENABLE          (1)

/* 
 * *****************************************************************************
 *                        PERIOD_TASK                                           *
 * *****************************************************************************
 */


#define  PERIDIC_TIME(x)        (((x*1000UL)/(N_OF_US_REQUIRED))+ (1/2UL))

#ifndef   KEY_PREDIOC_TASK_TIME
#define   KEY_PERIDIC_TASK                      PERIDIC_TIME(20)     
#else
#define   KEY_PERIDIC_TASK                      PERIDIC_TIME(KEY_PREDIOC_TASK_TIME)
#endif

#ifndef       BUTTON_PREDIOC_TASK_TIME
#define       BUT_PERIDIC_TASK                  PERIDIC_TIME(20)
#else
#define       BUT_PERIDIC_TASK                  PERIDIC_TIME(BUTTON_PREDIOC_TASK_TIME)
#endif


#define   MAX_PERODIC_TASKS_TIME                PERIDIC_TIME(PERIODICALLY_TASKS_MAX_TIME)



#endif	/* XC_CLOCK_H */

