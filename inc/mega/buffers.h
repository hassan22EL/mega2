
/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   buffers.c
 * Author       :   Mahmmoud shoieb
 * Data Memory  :   total byte used  dependent of user
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   5-hour
 * Comments     :   no comment
 *  
 */

#ifndef DATA_STORE_H_
#define DATA_STORE_H_

#include "../mega.h"
/*
 * *******************************************************************
 *                              Byte Buffer struct                   *
 * *******************************************************************
 * @benfit               : byte struct 
 * @Uasge                : 6 Byte
 * @param Write          : Write Index
 * @param Read           : Read Index
 * @param  length        : number of byte
 * @param buffer         : max number of byte
 * @param DataBuffer     :pointer to buffer read or write
 * @param data: pointer to write buffer
 * 
 */

typedef struct {
    uint8_t Write;
    uint8_t Read;
    uint8_t Length;
    uint8_t Max_Length;
    uint8_t* Data_Buffer;
} stByteBufDescriptor_t;

/*
 * *******************************************************************
 *                               strcut buffer                       *
 * *******************************************************************
 * @benfit                             : Struct Buffer struct 
 * @Uasge                              : 9 Byte
 * @param StructSize                   : how many member Byte in strcut
 * @param stByteBufDescriptor_t        : byte buffer description
 */

typedef struct {
    uint8_t StructSize;
    stByteBufDescriptor_t stByteBufDescriptor;

} stBufferStructDescriptor_t;

/*W
 * *******************************************************************
 *                               tlv struct         *
 * *******************************************************************
 * @benfit                             : Twi struct 
 * @Uasge                              : 9 Byte
 * @param TlvCount                     : how may tlv used
 * @param stByteBufDescriptor_t        : byte buffer description
 */
typedef struct {
    uint8_t TlvCount;
    stByteBufDescriptor_t stByteBufDescriptor;
} stBufferTLVDescriptor_t;

/*
 * *******************************************************************
 *                               byteBufferInit                       *
 * *******************************************************************
 * @benfit                : assignment data of the buffer descriptor from store buffer and max size
 * @param Buf             : pointer of Byte buffer descriptor 
 * @param storeBuf        : pointer to store or read data
 * @param storeBufSize    : how many buffer used  size
 * @return                : void
 */
void byteBufferInit(stByteBufDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize);
\
/*
 * *******************************************************************
 *                               structBufferInit                       *
 * *******************************************************************
 * @benfit                : assignment data of the struct descriptor from store buffer and max size of buffer 
                          : and number of member of the data
 * @param Buf             : pointer of Byte buffer descriptor 
 * @param storeBuf        : pointer to store or read data
 * @param storeBufSize    : how many buffer used  size
 * @param structSize      : number of byte used in struct
 * @return                : void 
 */
void structBufferInit(stBufferStructDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize, uint8_t structSize);
/*
 * *******************************************************************
 *                               TLVBufferInit                       *
 * *******************************************************************
 * @benfit                : assignment data of the struct descriptor from store buffer and max size 
 * @param Buf             : pointer of Byte buffer descriptor 
 * @param storeBuf        : pointer to store or read data
 * @param storeBufSize    : how many buffer used  size
 * @return                : void 
 */
void TLVBufferInit(stBufferTLVDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize);
/*
 * *******************************************************************
 *                               getByte                             *
 * *******************************************************************
 * @benfit               : get one byte from byte buffer and store in pointer assignment
 * @param Buf            : pointer of Byte buffer descriptor 
 * @param Data_Ptr       : pointer of the byte read
 * @return               : 0 when buffer is empty and 1 when buffer can get data
 */
uint8_t getByte(stByteBufDescriptor_t* Buf, uint8_t* Data_Ptr);
/*
 * *******************************************************************
 *                               putByte                             *
 * *******************************************************************
 * @benfit               : put one byte from data and store into byte buffer 
 * @param Buf            : pointer of Byte buffer descriptor 
 * @param Data_Ptr       : data required stored
 * @return               : 0 when buffer is full and 1 when buffer can insert data
 */
uint8_t putByte(stByteBufDescriptor_t* Buf, uint8_t Data);
/*
 * *******************************************************************
 *                               getExistingLength                   *
 * *******************************************************************
 * @benfit               : get number of byte  into buffer
 * @param Buf            : pointer of Byte buffer descriptor 
 * @return               : number of byte in buffer
 */
uint8_t getExistingLength(stByteBufDescriptor_t* Buf);
/*
 * *******************************************************************
 *                               getTlvCount                         *
 * *******************************************************************
 * @benfit               : get number of Tlv  into buffer
 * @param Buf            : pointer of Byte buffer descriptor 
 * @return               : number of tlv in buffer
 */
uint8_t getTlvCount(stBufferTLVDescriptor_t* Buf);
/*
 * *******************************************************************
 *                               getStructCount                   *
 * *******************************************************************
 * @benfit               : get number of struct  into buffer
 * @param Buf            : pointer of Byte buffer descriptor 
 * @return               : number of struct in buffer
 */
uint8_t getStructCount(stBufferStructDescriptor_t* Buf);
/*
 * *******************************************************************
 *                               putStruct                   *
 * *******************************************************************
 * @benfit                     : store struct into buffer
 * @param structBuf            : pointer of struct buffer descriptor 
 * @param Struct_Ptr           : pointer to struct to store
 * @return      : 0 when buffer is full 1 when buffer can insert data
 */
uint8_t putStruct(stBufferStructDescriptor_t * structBuf, void* Struct_Ptr);
/*
 * *******************************************************************
 *                               getStruct                   *
 * *******************************************************************
 * @benfit                     : get struct form buffer
 * @param structBuf            : pointer of struct buffer descriptor 
 * @param Struct_Ptr           : pointer to struct to read
 * @return      : 0 when buffer is empty 1 when buffer can get data
 * 
 */
uint8_t getStruct(stBufferStructDescriptor_t* structBuf, void* Struct_Ptr);
/*
 * *******************************************************************
 *                               putTLV                   *
 * *******************************************************************
 * @benfit                     : store tlv into buffer
 * @param structBuf            : pointer of tlv buffer descriptor 
 * @param Struct_Ptr           : pointer to tlv to store
 * @return      : 0 when buffer is full 1 when buffer can insert data
 * 
 */
uint8_t putTLV(stBufferTLVDescriptor_t * TLVBuf, void* TLV_Ptr);
/*
 * *******************************************************************
 *                               getTLV                   *
 * *******************************************************************
 * @benfit                     : read tlv from buffer
 * @param structBuf            : pointer of tlv buffer descriptor 
 * @param Struct_Ptr           : pointer to tlv to read
 * @return      : 0 when buffer is empty or 1 when buffer is ready data
 * 
 */
uint8_t getTLV(stBufferTLVDescriptor_t* TLVBuf, void* TLV_Ptr);



#endif /* DATA_STORE_H_ */