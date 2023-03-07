/* 
 * File:   ProductSelect.h
 * Author: hassa
 *
 * Created on February 27, 2023, 7:50 PM
 */

#ifndef PRODUCTSELECT_H
#define	PRODUCTSELECT_H

#include "appRes.h"

/*
 --------------------------------------------------------------------------------------------------------
 |                            < SelectProductCallBack  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : uint8  SelectProductCallBack                                                   |
 | < @Description       : run in menu system driver                                                     |                                                  |                                                           
 | < @return            : 1 or 0                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t SelectProductCallBack();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < LoadCurrentProduct  >                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  LoadCurrentProduct                                                      |
 | < @Description       : load current Product from memory                                               |                                                  |                                                           
 | < @return            : 1 or 0                                                                       |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t LoadCurrentProduct();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < getProductCurrentInex  >                                                  |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : getProductCurrentInex                                                           |
 | < @Description       : get Current Index Value                                                          |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t getProductCurrentInex();
/*
 --------------------------------------------------------------------------------------------------------
 |                            < ProductSetCurrentIndex  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : ProductSetCurrentIndex                                                        |
 | < @Description       : load current Index Value From Memeory and set Into Variable                                             |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void ProductSetCurrentIndex(uint8_t currentIndex);
/*
 --------------------------------------------------------------------------------------------------------
 |                            < CurrentProductSaveNewPatch  >                                               |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void CurrentProductSaveNewPatch                                                        |
 | < @Description       : save new time and patch number                                           |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t CurrentProductSaveNewPatch(stProductPrint_t *des);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintProductInLCD  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintProductInLCD                                                       |
  | < @Description       : Print Full Product in LCD                                                     |
  |                      : NURSE MASTER UNIT-MUV0.0-123456789-002-001                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void PrintProductInLCD();
/*
  --------------------------------------------------------------------------------------------------------
  |                            < clearScllorBuffer  >                                                    |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  clearScllorBuffer                                                       |
  | < @Description       : clear scoller buffer                                                          |                                            |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void clearScllorBuffer();
/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintCurrentProduct  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintCurrentProduct                                                      |
  | < @Description       : Print Product Call Back Action                                                 |                                            |                                                           
  | < @return            : 0 or not                                                                           |                     
  --------------------------------------------------------------------------------------------------------
 */
void PrintCurrentProduct();
/*
  --------------------------------------------------------------------------------------------------------
  |                            < LoadCurrentProductPrintIntoIntoPrint  >                                 |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  LoadCurrentProductPrintIntoIntoPrint                                    |
  | < @Description       :Load Last Print Into to Print struct to new Current Action                     |                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
void LoadCurrentProductPrintIntoIntoPrint(stProductPrint_t *des) ;
#endif	/* PRODUCTSELECT_H */

