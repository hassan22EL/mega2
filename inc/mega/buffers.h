/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : buffer.h                                                          |                                  
| < Author                   : Mahmmoud shoieb                                                   |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refence                                                        |
| < SRAM USAGE               : total byte used  dependent of user                                |
| < PROGRAM USAGE            : total byte used  dependent of user                                |                                      
| < Hardware Usage           : no-used                                                           |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */

#ifndef DATA_STORE_H_
#define DATA_STORE_H_

#include "../mega.h"

typedef struct {
    uint8_t Write;
    uint8_t Read;
    uint8_t Length;
    uint8_t Max_Length;
    uint8_t* Data_Buffer;
}
/*
 --------------------------------------------------------------------------------------------------
 |                                <byte buffer Descirption   >                                    |
 --------------------------------------------------------------------------------------------------
 | < Description                   : byte buffer struct                                           |
 | < Uasge                         : 6 Byte                                                       |
 | < param Write                   : Write Index                                                  |
 | < param Read                    : Read Index                                                   |
 | < param length                  : number of byte                                               |
 | < param Max_Length              : max number of byte                                           |
 | < param stByteBufDescriptor     : byte buffer description                                      |  
 | < param Data_Buffer             : pointer to buffer  or write or read                          |                                           |
 --------------------------------------------------------------------------------------------------
 */
stByteBufDescriptor_t;

/*
 --------------------------------------------------------------------------------------------------
 |                                <struct buffer Descirption   >                                  |
 --------------------------------------------------------------------------------------------------
 | < Description                   : struct buffer struct                                         |
 | < Uasge                         : 7 Byte                                                       |                                     |
 | < param StructSize              : how many member Byte in strcut                               |
 | < param stByteBufDescriptor     : byte buffer description                                      |              
 --------------------------------------------------------------------------------------------------
 */
typedef struct {
    uint8_t StructSize;
    stByteBufDescriptor_t stByteBufDescriptor;
} stBufferStructDescriptor_t;

/*
 --------------------------------------------------------------------------------------------------
 |                                <   tlv buffer Descirption   >                                  |
 --------------------------------------------------------------------------------------------------
 | < Description                   : Tlv struct                                                   |
 | < Uasge                         : 7 Byte                                                       |                                     |
 | < param TlvCount                : how may tlv used                                             |
 | < param stByteBufDescriptor     : byte buffer description                                      |              
 --------------------------------------------------------------------------------------------------
 */
typedef struct {
    uint8_t TlvCount;
    stByteBufDescriptor_t stByteBufDescriptor;
} stBufferTLVDescriptor_t;

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
void byteBufferInit(stByteBufDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize);

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
void structBufferInit(stBufferStructDescriptor_t* Buf, void* storeBuf, uint8_t storeBufSize, uint8_t structSize);
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
void TLVBufferInit(stBufferTLVDescriptor_t* Buf, uint8_t* storeBuf, uint8_t storeBufSize);

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
uint8_t getByte(stByteBufDescriptor_t* Buf, uint8_t* Data_Ptr);
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
uint8_t putByte(stByteBufDescriptor_t* Buf, uint8_t Data);
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
uint8_t getExistingLength(stByteBufDescriptor_t* Buf);
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
uint8_t getTlvCount(stBufferTLVDescriptor_t* Buf);
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
uint8_t getStructCount(stBufferStructDescriptor_t* Buf);
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
uint8_t putStruct(stBufferStructDescriptor_t * structBuf, void* Struct_Ptr);
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
uint8_t getStruct(stBufferStructDescriptor_t* structBuf, void* Struct_Ptr);
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
uint8_t putTLV(stBufferTLVDescriptor_t * TLVBuf, void* TLV_Ptr);
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
uint8_t getTLV(stBufferTLVDescriptor_t* TLVBuf, void* TLV_Ptr);



#endif /* DATA_STORE_H_ */