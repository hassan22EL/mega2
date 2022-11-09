/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   rtc.h
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
#ifndef XC_RTC_H
#define	XC_RTC_H
#include "../mega.h"
#if defined  DS1307_MODULE
#if DS1307_MODULE
/*
 * *******************************************************************
 *                            rtcDriver                               *
 * *******************************************************************
 * @benfit  : run a in background
 * @return  : void
 * */
void ds1307Driver();
/*
 * *******************************************************************
 *                            rtcInit                               *
 * *******************************************************************
 * @benfit  : init data 
 * @return  : void
 * */
void ds1307Init();
/* *******************************************************************
 *                            ds1307IsSetDone                               *
 * *******************************************************************
 * @benfit      : check write operation is done or not
 * @return      : 0  write operation is done
 *              : write operation in progress
 * 
 */
uint8_t ds1307IsSetDone();
#endif
#endif

#endif	/* XC_RTC_H */

