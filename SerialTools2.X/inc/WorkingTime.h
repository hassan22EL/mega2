/* 
 * File:   WorkingTime.h
 * Author: hp
 *
 * Created on February 28, 2023, 5:22 PM
 */

#ifndef WORKINGTIME_H
#define	WORKINGTIME_H

#include "appRes.h"
/*
 * <@var save Working Time
 */
extern stWorkingtime_t gstWorkingTime;
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeInit  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeInit                                                      |
 | < @Description       : Init values in Working Time                                                |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
void WorkingTimeInit();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WorkingTimeCallBack  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WorkingTimeCallBack                                                      |
 | < @Description       : Run in menu Driver                                                |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t WorkingTimeCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < LoadWorkingTime  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  LoadWorkingTime                                                      |
 | < @Description       : Load Working Time From memory                                                |                                                  |                                                           
 | < @return            : void                                                                      |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t LoadWorkingTime();
#endif	/* WORKINGTIME_H */

