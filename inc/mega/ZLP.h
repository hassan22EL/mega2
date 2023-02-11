/*
---------------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                                      | 
---------------------------------------------------------------------------------------------------------
| < FILE                     : ZLP.h                                                                   |                                  
| < Author                   : Hassan Elsaied                                                           |
| < Version                  : Mega2v241022                                                             |
| < Refences                 : no- ref                                                                  |  
| < SRAM USAGE               : 11 Byte Used by one Pin                                                  |
| < PROGRAM USAGE            : 430 Byte by One Pin Used                                                 |                                                                         |                                    
| < Hardware Usage           : GPIO                                                                     |
| < File Created             : 24-10-2022                                                               |
---------------------------------------------------------------------------------------------------------
 */

#ifndef ZLP_H
#define	ZLP_H
#include "../mega.h"
#if defined ZLP_MODULE
#if ZLP_MODULE
/*
 *@macro   _1IN_203DOTS                 : one inch have 152 dots
 */
#define      _1IN_152DOTS                              152

/*
 *@macro   _1IN_203DOTS                 : one inch have 203 dots
 */
#define      _1IN_203DOTS                              203
/*
 *@macro   _1IN_203DOTS                 : one inch have 300 dots
 */
#define      _1IN_300DOTS                              300

/*
 *@macro   _1IN_203DOTS                 : one inch have 608 dots
 */
#define      _1IN_608DOTS                              608 
/*
 * <@macro   ZLP_JM_CMD_A              : A = 24 dots/mm, 12 dots/mm, 8 dots/mm or 6 dots/mm
 */
#define     ZLP_JM_CMD_A                (0)
/*
 * <@macro   ZLP_JM_CMD_B             : B = 12 dots/mm, 6 dots/mm, 4 dots/mm or 3 dots/mm
 */
#define     ZLP_JM_CMD_B                (1)

/*
 * @macro  _2IN_PER_SEC                              Print Rate 2 inch / second 
 */
#define    _1IN_PER_SEC                                 (1)
/*
 * @macro  _2IN_PER_SEC                              Print Rate 2 inch / second 
 */
#define    _2IN_PER_SEC                                 (2)
/*
 * @macro  _3IN_PER_SEC                              Print Rate 3 inch / second 
 */
#define   _3IN_PER_SEC                                  (3)
/*
 * @macro  _4IN_PER_SEC                              Print Rate 4 inch / second 
 */
#define   _4IN_PER_SEC                                  (4)
/*
 * <@macro ZLP_TEXT                                  :Select to send Text
 */
#define  ZLP_TEXT                                       (0)  
/*
 * <@macro ZLP_BAR                                  :Select to send Bar
 */
#define  ZLP_BAR                                         (1)
/*
 * <@macro ZLP_TEXT                                  :Select to send Text
 */
#define  ZLP_ROTAION_0                                       (0)
/* 
 * <@macro ZLP_BAR                                  :Select to send Bar
 */
#define  ZLP_ROTAION_90                                      (1)
/*
 * <@macro ZLP_TEXT                                  :Select to send Text
 */
#define  ZLP_ROTAION_180                                     (2)
/*
 * <@macro ZLP_TEXT                                  :Select to send Text
 */
#define  ZLP_ROTAION_270                                      (3)
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPInit >                                                         |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPInit                                                                 |  
 | < @Description       : set Init Variables                                                           | 
 | < @return            : void                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPInit();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPMediaType >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPMediaType                                                              |  
 | < @Description       : Set Media Type  direct thermal media and thermal transfer media                | 
 | < @Param Type        : 0 Direct thermal media                                                         |                       
 |                      : 1 Thermal transfer media                                                       |
 | < @Param Resulation  : Reslation from 1-15
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPMediaType(uint8_t Type, uint8_t Resulation);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPLableSize >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPLableSize                                                              |  
 | < @Description       : Set Lable size per Inch                                                        | 
 | < @Param Length      : lable length per Inch                                                          |   
 | < @Param width       : lable Width Per Inch                                                           |                    
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPLableSize(uint8_t width, uint8_t Length);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintText >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function             : void ZLPMediaType                                                           |  
 | < @Description          : Set Media Type  direct thermal media and thermal transfer media             | 
 | < @Param s              : Pointer to text Buffer                                                      |
 | < @Param Len            : Number of Char In Text Buffer                                               |
 | < @return               : void                                                                        |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPrintText(uint8_t *s, uint8_t Len);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintState >                                                    |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t ZLPPrintState                                                         |  
 | < @Description       : pirent state is ready To print new data or not                                | 
 | < @return            : 0 ZLP Printer is Busy                                                         |                       
 |                      : 1 ZLP Printer is Ready                                                        |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
uint8_t ZLPPrintState();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintNOW >                                                       |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPrintNOW                                                               |  
 | < @Description       : Print after send Comand                                                        | 
 | < @Param Copies      : Number Of Lable Print                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPrintNOW(uint8_t LableCopies);
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPClearLastLable >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPClearLastLable                                                         |  
 | < @Description       : Clear last Print Before send Next Lable                                        |                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPClearLastLable();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPirentLOGO >                                                 |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPPirentLOGO                                                         |  
 | < @Description       : ZLP Custome Log                                       |                                                          |
 | < @return            : void                                                                           |                                                                         |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPirentLOGO();
/*
---------------------------------------------------------------------------------------------------------
|                                 < ZLPsetPos >                                                         |
---------------------------------------------------------------------------------------------------------
| < @Function          : void ZLPsetPos                                                                 |  
| < @Description       : set X,Y poision after send command                                             | 
| < @Param X           : Text Pos in X-Axis                                                             |
| < @Param Y           : Text Pos in Y-Axis                                                             |
| < @Param Font        : Font Size selct from '1' to '9' and a-z and A-Z                                |
| < @PAram Ration      : Select from 0 to 3 when 0 is normal , 1 is 90 and 2 = 180 , 3 =270             |
| < @Param Type        : Select From
| < @return            : void                                                                           |                                                                         |
---------------------------------------------------------------------------------------------------------
 */
void ZLPsetData(uint16_t x, uint16_t y, uint8_t Font, uint8_t Rotation, uint8_t Type);
#endif
#endif





#endif	/* ZLP_H */

