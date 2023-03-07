/* 
 * File:   Memory.h
 * Author: hassa
 *
 * Created on February 26, 2023, 8:19 PM
 */

#ifndef MEMORY_H
#define	MEMORY_H
#include "../inc/appRes.h"

typedef struct ProductString_s {
    uint8_t ProductName[30];
    uint8_t LengthName;
    uint8_t VersionName[12];
    uint8_t LengthVersion;
} stProductString_t;

typedef struct ProductPrint_s {
    time_t Time;
    uint8_t Code;
    uint8_t PatchNumber;
    uint16_t PrintCode;
} stProductPrint_t;

typedef struct stProduct_s {
    stProductString_t ProductStrings;
    stProductPrint_t ProductPrint;
} stProduct_t;

typedef struct WorkingHour_s {
    uint8_t StartHour;
    uint8_t EndHour;
} stWorkingHour_t;

typedef struct WorkingTime_s {
    time_t StartTime;
    time_t EndTime;
} stWorkingtime_t;
/*
 *<@var MEMORY_VERIFIY_CODE_ONE       : Memeory verifiy code one    
 */
#define MEMORY_VERIFIY_CODE_ONE        (23)
/*
 *<@var MEMORY_VERIFIY_CODE_TWO       : Memeory verifiy code one    
 */
#define MEMORY_VERIFIY_CODE_TWO        (11)
/*
 *<@var MEMORY_VERIFIY_CODE_THREE       : Memeory verifiy code one    
 */
#define MEMORY_VERIFIY_CODE_THREE      (96)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define  LAST_PRODUCT_ADDRESS           (3)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define  CURRENT_PRODUCT_ADDRESS         (4)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Last Product Saved In memory
 */
#define  ADDREASSABLE_PRODUCT_ADDRESS    (5)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Current Working Time Address address 
 */
#define  CURRENT_LOGDATA_INDEX_ADDRESS    (6)
/*
 * <@marco LAST_PRODUCT_ADDRESS    : Current Working Time Address address 
 */
#define  CURRENT_WORKINGTIME_ADDRESS      (7)
/*
 *<@var Start Product Address       : Memeory verifiy code one    
 */
#define  MEMORY_START_PRODUCT_ADD      (24)
/*
 *<@var Start Product Address       : Memeory verifiy code one    
 */
#define  MEMORY_LOG_PRODUCT_ADD      (5120)
/*
 *<@var Start Product Address       : Memeory verifiy code one    
 */
#define  MEMORY_LOGO_ADDRESS         (0x1C00)            

#endif	/* MEMORY_H */

