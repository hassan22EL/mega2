/* 
 * File:   EventsHandles.h
 * Author: hassa
 *
 * Created on February 23, 2023, 11:01 PM
 */

#ifndef EVENTSHANDLES_H
#define	EVENTSHANDLES_H

#include "appRes.h"
/*
 --------------------------------------------------------------------------------------------------------
 |                            < CommanEventHandles  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : unsigned char  CommanEventHandles                                             |
 | < @Description       : Shard Events between Multi Modules                                            |  
 | < @Param Tab         : Enable Tab or not 0 is disable tab and 1is enable tab                         |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void CommanEventHandles(pFuncParam_t Register);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ReturnMenuCallBack >                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ReturnMenuCallBack                                               |  
 | < @Description       : return value of the callback                                      |                                                    |
 | < @return            : 1                                                                           |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ReturnMenuCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < CommanEventFunctions  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : CommanEventFunctions                                          |
 | < @Description       : Register comman function                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void CommanEventFunctions(pFunc_t RegisterF1, pFunc_t RegisterF2, pFunc_t RegisterF3, pFunc_t RegisterEnter, pFunc_t RegisterCencel);

#endif	/* EVENTSHANDLES_H */

