/* 
 * File:   message.h
 * Author: hassa
 *
 * Created on February 26, 2023, 9:24 PM
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include "Memory.h"



/*
 *<@var MSG_PRODUCT_NAME String 1 Index
 */
#define  MSG_PRODUCT_NAME (0)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_PRODUCT_SELECT (2)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_PRODUCT_MODEL (1)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_PRODUCT_PLEASE_WAIT (3)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_PRODUCT_SAVE_PRODUCT (4)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_PRODUCT_EMPTY_BUFFER (5)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_PRODUCT_OPS         (6)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define MSG_PRODUCT_VERSION       (7)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define MSG_PRODUCT_SERIAL         (8)

/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_WORKTIME_SET         (9)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define MSG_LABLE_SITE            (10)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define MSG_LABLE_MADE            (11)
/*
 * Print Lable Message
 */
#define MSG_PRINT_LABLE           (12)
/*
 * Print Lable Message
 */
#define  MSG_MEM_INIT               (13)
/*
 * Print Lable Message
 */
#define  MSG_CONNECT_DECIVE1           (14)
/*
 * Print Lable Message
 */
#define  MSG_CONNECT_DECIVE2            (15)

#define   MSG_CONNECT_DECIVE3            (16)
#define   MSG_DEVICETYPE                 (17)
#define   MSG_DEVICETYPE2                (18)
#define   MSG_RD_CMD                     (20)
#define   MSG_OK_CMD                     (21)
#define   MSG_SD_CMD                     (22)
/*
 *<@var MSG_PRODUCT_SELECT String 2 Index
 */
#define  MSG_RESET_PATCH         (23)
#define  MSG_SYSTEM_DIABLED            (24)
/*
 --------------------------------------------------------------------------------------------------------
 |                            < WriteMessage  >                                                |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void  WriteMessage                                                   |
 | < @Description       : Write Message From message Buffer                                                    |                                                  |                                                           
 | < @return            : void                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
void WriteMessage(uint8_t lin, uint8_t Index);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintProductSerial  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintProductSerial                                                      |
  | < @Description       : Print Serial in Format xxxxxxxxxx-xxx-xxx                                     |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t PrintProductSerial(uint8_t *buf, uint8_t start, stProductPrint_t *ProductPrint);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < PrintMessage  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  PrintMessage                                                       |
  | < @Description       : Print Message Into Buffer Array                                                    |
  |                      : PrintMessage                                   |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t appPrintMessage(uint8_t *buf, uint8_t start, uint8_t MsgIndex);
/*
  --------------------------------------------------------------------------------------------------------
  |                            < messageCompareString  >                                                   |
  --------------------------------------------------------------------------------------------------------
  | < @Function          : void  messageCompareString                                                      |
  | < @Description       : compare buffer with string                                    |                                                  |                                                           
  | < @return            : void                                                                          |                     
  --------------------------------------------------------------------------------------------------------
 */
uint8_t messageCompareString(uint8_t *buf, uint8_t Index, uint8_t length);
#endif	/* MESSAGE_H */

