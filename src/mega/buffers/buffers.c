
/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : buffer.c                                                          |                                  
| < Author                   : Mahmmoud shoieb                                                   |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : total byte used  dependent of user                                |
| < PROGRAM USAGE            : total byte used  dependent of user                                |                                      
| < Hardware Usage           : no-used                                                           |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#include "../../../inc/mega/buffers.h"

/*
 --------------------------------------------------------------------------------------------------
 |                              < Basic function Definition  >                                    |
 --------------------------------------------------------------------------------------------------
 */
/*
 --------------------------------------------------------------------------------------------------
 |                                 < Buffer_Is_Empty >                                            |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t Buffer_Is_Empty                                                 |  
 | < @Description       : check byte buffer is empty or not                                       | 
 | < @Param Buf         : pointer of byte buffer descriptor                                       |   
 | < @return            : 0 when buffer is not empty                                              |
 |                      : 1 when buffer is empty                                                  |
 --------------------------------------------------------------------------------------------------
 */
static uint8_t Buffer_Is_Empty(stByteBufDescriptor_t* Buf);
/*
 --------------------------------------------------------------------------------------------------
 |                                 < Buffer_Is_Full >                                             |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t Buffer_Is_Full                                                  |  
 | < @Description       : check byte buffer is full or not                                        | 
 | < @Param Buf         : pointer of byte buffer descriptor                                       |   
 | < @return            : 0 when buffer is not full                                               |
 |                      : 1 when buffer is full                                                   |
 --------------------------------------------------------------------------------------------------
 */
static uint8_t Buffer_Is_Full(stByteBufDescriptor_t* Buf);

/*
 --------------------------------------------------------------------------------------------------
 |                              < Basic function implementions  >                                 |
 --------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------
 |                                 < Buffer_Is_Empty >                                            |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t Buffer_Is_Empty                                                 |  
 | < @Description       : check byte buffer is empty or not                                       | 
 | < @Param Buf         : pointer of byte buffer descriptor                                       |   
 | < @return            : 0 when buffer is not empty                                              |
 |                      : 1 when buffer is empty                                                  |
 --------------------------------------------------------------------------------------------------
 */
static uint8_t Buffer_Is_Empty(stByteBufDescriptor_t* Buf) {
    if ((Buf-> Length) == 0) return 1;
    return 0;
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < Buffer_Is_Full >                                             |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t Buffer_Is_Full                                                  |  
 | < @Description       : check byte buffer is full or not                                        | 
 | < @Param Buf         : pointer of byte buffer descriptor                                       |   
 | < @return            : 0 when buffer is not full                                               |
 |                      : 1 when buffer is full                                                   |
 --------------------------------------------------------------------------------------------------
 */
static uint8_t Buffer_Is_Full(stByteBufDescriptor_t* Buf) {
    if ((Buf-> Length) == (Buf-> Max_Length)) return 1;
    return 0;
}
/*
 --------------------------------------------------------------------------------------------------
 |                              < user function implementions  >                                  |
 --------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------
 |                              < byteBufferInit  >                                               |
 --------------------------------------------------------------------------------------------------
 | < @Function              : void TLVBufferInit                                                  | 
 | < @Description           : assignment data of the buffer descriptor                            |
                            : from store buffer and max size                                      |
 | < @Param Buf             : pointer of Byte buffer descriptor                                   |
 | < @Param storeBuf        : pointer to store or read data                                       |
 | < @Param storeBufSize    : how many buffer used  size                                          |
 | < @return                : void                                                                |
 --------------------------------------------------------------------------------------------------
 */
void byteBufferInit(stByteBufDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize) {
    Buf->Data_Buffer = storeBuf;
    Buf->Max_Length = storeBufSize;
    Buf->Length = 0;
    Buf->Write = 0;
    Buf->Read = 0;
}

/*
 --------------------------------------------------------------------------------------------------
 |                              < structBufferInit  >                                             |
 --------------------------------------------------------------------------------------------------
 | < @Function              : void TLVBufferInit                                                  | 
 | < @Description           : assignment data of the struct descriptor from store buffer          |
                            : and max size of buffer  and number of member of the data            |
 | < @Param Buf             : pointer of struct buffer descriptor                                 |
 | < @Param storeBuf        : pointer to store or read data                                       |
 | < @Param storeBufSize    : how many buffer used  size                                          |
 | < @Param structSize      : number of byte used in struct                                       |
 | < @return                : void                                                                |
 --------------------------------------------------------------------------------------------------
 */
void structBufferInit(stBufferStructDescriptor_t* Buf, void * storeBuf, uint8_t storeBufSize, uint8_t structSize) {
    Buf->StructSize = structSize;
    byteBufferInit((&(Buf->stByteBufDescriptor)), storeBuf, (storeBufSize * structSize));
}

/*
 --------------------------------------------------------------------------------------------------
 |                               <TLVBufferInit >                                                 |
 --------------------------------------------------------------------------------------------------
 | < @Function           : void TLVBufferInit                                                     | 
 | < @Description        : assignment data of the struct descriptor from store buffer and max size|
 | < @Param Buf          : pointer of tlv buffer descriptor                                       |
 | < @Param storeBuf     : pointer to store or read data                                          |
 | < @Param storeBufSize : how many buffer used  size                                             |
 | < @return             : void                                                                   |
 --------------------------------------------------------------------------------------------------
 */
void TLVBufferInit(stBufferTLVDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize) {
    byteBufferInit(&(Buf->stByteBufDescriptor), storeBuf, storeBufSize);
    Buf->TlvCount = 0;
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < getByte >                                                    |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t getByte                                                         |  
 | < @Description       : get one byte from byte buffer and store in pointer assignment           | 
 | < @Param Buf         : pointer of Byte buffer descriptor                                       |   
 | < @Param Data        : pointer of the byte  to assignment data read                            |
 | < @return            : 0 when buffer is empty                                                  |
 |                      : 1  when buffer is ready data to be read                                 |
 --------------------------------------------------------------------------------------------------
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
 --------------------------------------------------------------------------------------------------
 |                                 < putByte >                                                    |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putByte                                                         |  
 | < @Description       : put one byte from data and store into byte buffer                       | 
 | < @Param Buf         : pointer of Byte buffer descriptor                                       |   
 | < @Param Data        : data required stored                                                    |
 | < @return            : 0 when buffer is full                                                   |
 |                      : 1 when buffer can insert data                                           |
 --------------------------------------------------------------------------------------------------
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
 --------------------------------------------------------------------------------------------------
 |                                 < getExistingLength >                                          |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t getExistingLength                                               |  
 | < @Description       : get number of byte  into buffer                                         | 
 | < @Param Buf         : pointer of byte buffer descriptor                                       |   
 | < @return            : number of bytes in buffer                                               |
 --------------------------------------------------------------------------------------------------
 */
uint8_t getExistingLength(stByteBufDescriptor_t* Buf) {
    return (Buf-> Length);
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < getTlvCount >                                                |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t getTlvCount                                                     |  
 | < @Description       : get number of Tlv  into buffer                                          | 
 | < @Param Buf         : pointer of tlv buffer descriptor                                        |   
 | < @return            : number of struct in buffer                                              |
 --------------------------------------------------------------------------------------------------
 */
uint8_t getTlvCount(stBufferTLVDescriptor_t* Buf) {
    return Buf->TlvCount;
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < getStructCount >                                             |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t getStructCount                                                  |  
 | < @Description       : get number of the struct into buffer                                    | 
 | < @Param Buf         : pointer of struct buffer descriptor                                     |   
 | < @return            : number of struct in buffer                                              |
 --------------------------------------------------------------------------------------------------
 */
uint8_t getStructCount(stBufferStructDescriptor_t* Buf) {
    return (((Buf-> stByteBufDescriptor).Length) / (Buf->StructSize));
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < putStruct >                                                  |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putStruct                                                       |  
 | < @Description       : store struct into buffer                                                | 
 | < @Param structBuf   : pointer of struct buffer descriptor                                     |   
 | < @Param Struct_Ptr  : pointer to struct to store                                              |
 | < @return            : 0  when buffer is full                                                  |
 |                      : 1  when buffer can insert data                                          |
 --------------------------------------------------------------------------------------------------
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
 --------------------------------------------------------------------------------------------------
 |                                 < getStruct >                                                  |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t getStruct                                                       |  
 | < @Description       : read struct from buffer                                                 | 
 | < @Param structBuf   : pointer of struct buffer descriptor                                     |   
 | < @Param structBuf   : pointer to struct of struct to assign data to can be read               |
 | < @return            : 0  when buffer is empty                                                 |
 |                      : 1  when buffer is ready data to be read                                 |
 --------------------------------------------------------------------------------------------------
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
 --------------------------------------------------------------------------------------------------
 |                                 < putTLV >                                                     |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t putTLV                                                          |  
 | < @Description       : store tlv into buffer                                                   | 
 | < @Param TLVBuf      : pointer of tlv buffer descriptor                                        |   
 | < @Param TLV_Ptr     : pointer to tlv to store                                                 |
 | < @return            : 0  when buffer is full                                                  |
 |                      : 1  when buffer can insert data                                          |
 --------------------------------------------------------------------------------------------------
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
 --------------------------------------------------------------------------------------------------
 |                                 < getTLV >                                                     |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t getTLV                                                          |  
 | < @Description       : read tlv from buffer                                                    | 
 | < @Param TLVBuf      : pointer of tlv buffer descriptor                                        |   
 | < @Param TLV_Ptr     : pointer to struct of tlv to assign data to can be read                  |
 | < @return            : 0  when buffer is empty                                                 |
 |                      : 1  when buffer is ready data to be read                                 |
 --------------------------------------------------------------------------------------------------
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