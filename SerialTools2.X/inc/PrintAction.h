/* 
 * File:   PrintAction.h
 * Author: hassa
 *
 * Created on March 1, 2023, 9:01 PM
 */


/* 
 * File:   PrintAction.h
 * Author: hp
 *
 * Created on March 1, 2023, 8:40 AM
 */

#ifndef PRINTACTION_H
#define	PRINTACTION_H

#include "appRes.h"
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < PrintActionCallBack>                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintActionCallBack                                                            |  
 | < @Description       : Fun Run in any Re                                                      |                                                        |
 | < @return            : 0 the Print Action is running , 1 - Print Action is Done                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t PrintActionCallBack();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < PrintAction>                                                     |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void PrintAction                                                            |  
 | < @Description       : assignent Product To Print                                                      |                                                        |
 | < @return            : void                                                                         |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void PrintAction(stProduct_t *Product);
#endif	/* PRINTACTION_H */

