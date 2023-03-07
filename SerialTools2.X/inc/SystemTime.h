/* 
 * File:   SystemTime.h
 * Author: hp
 *
 * Created on February 23, 2023, 1:34 PM
 */

#ifndef SYSTEMTIME_H
#define	SYSTEMTIME_H

#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                            < TimeCallBack  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  TimeCallBack                                                   |
 | < @Description       : run in menu system driver                                                      |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SystemTimeCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < SystemTimeInit  >                                                       |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void SystemTimeInit                                                           |
 | < @Description       : system time is reset values to default values                                 |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void SystemTimeInit();


#endif	/* SYSTEMTIME_H */

