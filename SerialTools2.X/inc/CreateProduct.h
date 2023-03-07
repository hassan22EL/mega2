/* 
 * File:   CreateProduct.h
 * Author: hassa
 *
 * Created on February 25, 2023, 10:16 PM
 */

#ifndef CREATEPRODUCT_H
#define	CREATEPRODUCT_H
#include "appRes.h"



/*
 --------------------------------------------------------------------------------------------------------
 |                            < CreateProductCallBack  >                                                         |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  CreateProductCallBack                                                   |
 | < @Description       : run in menu system driver                                                      |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t CreateProductCallBack();

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < CreateProductInit >                                                |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void CreateProductInit                                                        |  
 | < @Description       : Create Product system                                                         |                                                    |
 | < @return            : void                                                                          |                                            |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void CreateProductInit();
/*
 * 
 */

/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductGetLastIndex  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : ProductGetLastIndex                                                           |
 | < @Description       : get Last Index Value                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t ProductGetLastIndex();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductSetLastIndex  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : ProductSetLastIndex                                                           |
 | < @Description       : load Last Index Value From Memeory and set Into Variable                                                         |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void ProductSetLastIndex(uint8_t LastIndex);


#endif	/* CREATEPRODUCT_H */

