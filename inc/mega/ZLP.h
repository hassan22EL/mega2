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
 |                                 < ZLPDriver >                                                         |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPDriver                                                                 |  
 | < @Description       : background task                                                                | 
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPDriver();
/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPMediaType >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function          : void ZLPMediaType                                                              |  
 | < @Description       : Set Media Type  direct thermal media and thermal transfer media                | 
 | < @Param Type        : 0 Direct thermal media                                                         |                       
 |                      : 1 Thermal transfer media                                                       |
 | < @return            : void                                                                           |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPMediaType(uint8_t Type);
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
 |                                 < ZLPMediaType >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function             : void ZLPMediaType                                                           |  
 | < @Description          : Set Media Type  direct thermal media and thermal transfer media             | 
 | < @Param Fontsize       : set Font Size from 1 to 5                                                   |                       
 | < @Param FontResulation : set Font Size From 0 to 15                                                  |
 | < @return               : void                                                                        |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPFont(uint8_t Fontsize, uint8_t FontResulation);

/*
 ---------------------------------------------------------------------------------------------------------
 |                                 < ZLPPrintText >                                                      |
 ---------------------------------------------------------------------------------------------------------
 | < @Function             : void ZLPMediaType                                                           |  
 | < @Description          : Set Media Type  direct thermal media and thermal transfer media             | 
 | < @Param x              : Position  in x                                                              |                       
 | < @Param margin         : text margin in top and bottom                                               |
 | < @Param s              : Pointer to text Buffer                                                      |
 | < @Param Len            : Number of Char In Text Buffer                                               |
 | < @return               : void                                                                        |
 ---------------------------------------------------------------------------------------------------------
 */
void ZLPPrintText(uint16_t x, uint8_t margin, uint8_t *s, uint8_t Len);
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
#endif
#endif





#endif	/* ZLP_H */

