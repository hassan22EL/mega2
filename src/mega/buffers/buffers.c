
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
#include "../../../inc/mega/buffers.h"

/*
 * *******************************************************************
 *                               Buffer_Is_Empty                     *
 * *******************************************************************
 * @benfit               : check the buffer is empty data or not
 * @param Buf            : pointer of Byte buffer descriptor 
 * 
 */
static uint8_t Buffer_Is_Empty(stByteBufDescriptor_t* Buf);
/*
 * *******************************************************************
 *                               Buffer_Is_Full                     *
 * *******************************************************************
 * @benfit               : check the buffer is full or not
 * @param Buf            : pointer of Byte buffer descriptor 
 * 
 */
static uint8_t Buffer_Is_Full(stByteBufDescriptor_t* Buf);

/*
 * *******************************************************************
 *                               Buffer_Is_Empty                     *
 * *******************************************************************
 * @benfit               : check the buffer is empty data or not
 * @param Buf            : pointer of Byte buffer descriptor 
 * 
 */
static uint8_t Buffer_Is_Empty(stByteBufDescriptor_t* Buf) {
    if ((Buf-> Length) == 0) return 1;
    return 0;
}

/*
 * *******************************************************************
 *                               Buffer_Is_Full                     *
 * *******************************************************************
 * @benfit               : check the buffer is full or not
 * @param Buf            : pointer of Byte buffer descriptor 
 * 
 */
static uint8_t Buffer_Is_Full(stByteBufDescriptor_t* Buf) {
    if ((Buf-> Length) == (Buf-> Max_Length)) return 1;
    return 0;
}

/*
 * *******************************************************************
 *                               byteBufferInit                       *
 * *******************************************************************
 * @benfit                : assignment data of the buffer descriptor from store buffer and max size
 * @param Buf             : pointer of Byte buffer descriptor 
 * @param storeBuf        : pointer to store or read data
 * @param storeBufSize    : how many buffer used  size
 * 
 */
void byteBufferInit(stByteBufDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize) {
    Buf->Data_Buffer = storeBuf;
    Buf->Max_Length = storeBufSize;
    Buf->Length = 0;
    Buf->Write = 0;
    Buf->Read = 0;
}

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
 * 
 */
void structBufferInit(stBufferStructDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize, uint8_t structSize) {
    Buf->StructSize = structSize;
    byteBufferInit((&(Buf->stByteBufDescriptor)), storeBuf, storeBufSize);
}

/*
 * *******************************************************************
 *                               TLVBufferInit                       *
 * *******************************************************************
 * @benfit                : assignment data of the struct descriptor from store buffer and max size 
 * @param Buf             : pointer of Byte buffer descriptor 
 * @param storeBuf        : pointer to store or read data
 * @param storeBufSize    : how many buffer used  size
 * 
 */
void TLVBufferInit(stBufferTLVDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize) {
    byteBufferInit(&(Buf->stByteBufDescriptor), storeBuf, storeBufSize);
    Buf->TlvCount = 0;
}

/*
 * *******************************************************************
 *                               getByte                             *
 * *******************************************************************
 * @benfit               : get one byte from byte buffer and store in pointer assignment
 * @param Buf            : pointer of Byte buffer descriptor 
 * @param Data_Ptr       : pointer of the byte read
 * 
 */
uint8_t getByte(stByteBufDescriptor_t* Buf, uint8_t* Data_Ptr) {
    if (Buffer_Is_Empty(Buf)) return 0;

    *Data_Ptr = *((Buf->Data_Buffer) + (Buf->Read));
    (Buf->Read)++;
    (Buf-> Length)--;

    if ((Buf-> Read) == (Buf-> Max_Length)) (Buf->Read) = 0;

    return 1;
}

/*
 * *******************************************************************
 *                               putByte                             *
 * *******************************************************************
 * @benfit               : put one byte from data and store into byte buffer 
 * @param Buf            : pointer of Byte buffer descriptor 
 * @param Data_Ptr       : data required stored
 * 
 */
uint8_t putByte(stByteBufDescriptor_t* Buf, uint8_t Data) {
    if (Buffer_Is_Full(Buf)) return 0;

    *((Buf-> Data_Buffer) + (Buf-> Write)) = Data;
    (Buf-> Write)++;
    (Buf-> Length)++;

    if ((Buf-> Write) == (Buf-> Max_Length)) (Buf-> Write) = 0;

    return 1;
}

/*
 * *******************************************************************
 *                               getExistingLength                   *
 * *******************************************************************
 * @benfit               : get number of byte  into buffer
 * @param Buf            : pointer of Byte buffer descriptor 
 * 
 */
uint8_t getExistingLength(stByteBufDescriptor_t* Buf) {
    return (Buf-> Length);
}

/*
 * *******************************************************************
 *                               getTlvCount                         *
 * *******************************************************************
 * @benfit               : get number of Tlv  into buffer
 * @param Buf            : pointer of Byte buffer descriptor 
 * 
 */
uint8_t getTlvCount(stBufferTLVDescriptor_t* Buf) {
    return Buf->TlvCount;
}

/*
 * *******************************************************************
 *                               getStructCount                   *
 * *******************************************************************
 * @benfit               : get number of struct  into buffer
 * @param Buf            : pointer of Byte buffer descriptor 
 * 
 */
uint8_t getStructCount(stBufferStructDescriptor_t* Buf) {
    return (((Buf-> stByteBufDescriptor).Length) / (Buf->StructSize));
}

/*
 * *******************************************************************
 *                               putStruct                   *
 * *******************************************************************
 * @benfit                     : store struct into buffer
 * @param structBuf            : pointer of struct buffer descriptor 
 * @param Struct_Ptr           : pointer to struct to store
 * 
 */
uint8_t putStruct(stBufferStructDescriptor_t * structBuf, void* Struct_Ptr) {
    if ((((structBuf->stByteBufDescriptor).Max_Length) - ((structBuf->stByteBufDescriptor).Length)) < (structBuf->StructSize)) return 0;

    uint8_t* Data_Ptr;
    Data_Ptr = (uint8_t*) Struct_Ptr;

    for (uint8_t i = 0; i < (structBuf->StructSize); i++) {
        if ((putByte((&(structBuf->stByteBufDescriptor)), *(Data_Ptr + i))) == 0) return 0;
    }

    return 1;
}

/*
 * *******************************************************************
 *                               getStruct                   *
 * *******************************************************************
 * @benfit                     : get struct form buffer
 * @param structBuf            : pointer of struct buffer descriptor 
 * @param Struct_Ptr           : pointer to struct to read
 * 
 */
uint8_t getStruct(stBufferStructDescriptor_t* structBuf, void* Struct_Ptr) {
    uint8_t* Data_Ptr;
    Data_Ptr = (uint8_t*) Struct_Ptr;
    for (uint8_t i = 0; i < (structBuf->StructSize); i++) {
        if ((getByte((&(structBuf->stByteBufDescriptor)), (Data_Ptr + i))) == 0) return 0;
    }

    return 1;
}

/*
 * *******************************************************************
 *                               putTLV                   *
 * *******************************************************************
 * @benfit                     : store tlv into buffer
 * @param structBuf            : pointer of tlv buffer descriptor 
 * @param Struct_Ptr           : pointer to tlv to store
 * 
 */
uint8_t putTLV(stBufferTLVDescriptor_t * TLVBuf, void* TLV_Ptr) {
    uint8_t* Data_Ptr;
    Data_Ptr = (uint8_t*) TLV_Ptr;

    if ((((TLVBuf->stByteBufDescriptor).Max_Length) - ((TLVBuf->stByteBufDescriptor).Length)) < 2) return 0;
    if ((((TLVBuf->stByteBufDescriptor).Max_Length) - ((TLVBuf->stByteBufDescriptor).Length)) < ((*(Data_Ptr + 1)) + 2)) return 0;

    for (uint8_t i = 0; i < (*(Data_Ptr + 1) + 2); i++) {
        if ((putByte((&(TLVBuf->stByteBufDescriptor)), *(Data_Ptr + i))) == 0) return 0;
    }

    (TLVBuf->TlvCount)++;

    return 1;
}

/*
 * *******************************************************************
 *                               getTLV                   *
 * *******************************************************************
 * @benfit                     : read tlv from buffer
 * @param structBuf            : pointer of tlv buffer descriptor 
 * @param Struct_Ptr           : pointer to tlv to read
 * 
 */
uint8_t getTLV(stBufferTLVDescriptor_t* TLVBuf, void* TLV_Ptr) {
    uint8_t* Data_Ptr;
    Data_Ptr = (uint8_t*) TLV_Ptr;

    for (uint8_t i = 0; i < (*(Data_Ptr + 1) + 2); i++) {
        if ((getByte((&(TLVBuf->stByteBufDescriptor)), (Data_Ptr + i))) == 0) return 0;
    }

    (TLVBuf->TlvCount)--;

    return 1;
}

