/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   macros.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   total byte used 0 Byte  
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   1-hour
 * Comments     :   no comment
 *  
 */

#ifndef XC_MACRO_H
#define	XC_MACRO_H


/* 
 * ******************************************************************************
 *                                                    *
 * ******************************************************************************
 */

#define CONCAT(A,B)         A ## B

/* 
 * ******************************************************************************
 *                                    Converts                *
 * ******************************************************************************
 */

#define clockCyclesPerMicrosecond()  ( F_CPU / 1000000UL )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )


/* 
 * ******************************************************************************
 *                           NO Operation                                        *
 * ******************************************************************************
 */
#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

/* 
 * ******************************************************************************
 *                             data constrains                                  *
 * ******************************************************************************
 */

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define     NotValid(x)      (((x) == 0) ? 1 : 0)

/* 
 * ******************************************************************************
 *               convert one data typed to min data type                        *
 * ******************************************************************************
 */

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
/* 
 * ******************************************************************************
 *               Bits Operation  assignment                                               *
 * ******************************************************************************
 */


#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &=  ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

/* 
 * ******************************************************************************
 *                  Bits Operation  checks                                      *
 * ******************************************************************************
 */
#define BitCheck(x, y)			(x &(1UL<<y)	? 1 : 0	)
#define bitIsSet(value, bit) (((value) >> (bit)) & 0x01)
#define bitIsClear(value, bit) (!(((value) >> (bit)) & 0x01))
/* 
 * ******************************************************************************
 *                assignment n bits of the byte by mask                         *
 * ******************************************************************************
 */
#define bitsValue(reg, value,mask)             (reg = ((reg & (~mask))   | value))

/* 
 * ******************************************************************************
 *                  u8 to BCD                                                   *
 * ******************************************************************************
 */
#define value_once(value)           (value % 10)
#define value_tanth(value)          (value /10)
#define decToBcd(value)             ((value_once(value) & (0x0F)) + ((value_tanth(value) << 4 ) & (0xF0)))
#define BcdToDec(value)              ((value & 0x0F) + (((value>>4) & (0x0F)) * 10))
/* 
 * ******************************************************************************
 *                  Convert to asii  Operation                                        *
 * ******************************************************************************
 */
#define ASII_NUMBER(x)               ('0'+x)


/* 
 * ******************************************************************************
 *                 Atomic operations                                             *
 * ******************************************************************************
 */

#define	ATOMIC_BEGIN		{ uint8_t matom_oldSREG = SREG; cli();
#define ATOMIC_END		  SREG = matom_oldSREG;	__asm__ volatile ("" ::: "memory"); }

/* 
 * ******************************************************************************
 *                 clear bit in sfr operations                                             *
 * ******************************************************************************
 */

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
/* 
 * ******************************************************************************
 *                 set bit in sfr operations                                    *
 * ******************************************************************************
 */


#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/* 
 * ******************************************************************************
 *                  Decoder Value                                               *
 * ******************************************************************************
 */
static inline uint8_t u8Decoder(uint8_t Value, uint8_t Number_of_outLine) {

    if (!Value) {
        return ((Number_of_outLine - 1) & 0x01);
    }

    for (uint8_t i = 0; i < Number_of_outLine; i++) {
        if (i == Value) {
            return ((Value & 0x01) << i) & (Number_of_outLine - 1);
        }
    }

}

static inline uint8_t map(uint32_t x, uint8_t in_min, uint32_t in_max, uint8_t out_min, uint8_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static inline uint8_t power2(uint8_t x) {
    uint8_t y = 1;
    if (x == 0) {
        return 1;
    }
    for (uint8_t i = 0; i < x; i++) {
        y *= 2;
    }
    return y;
}

static inline uint8_t Match_2BUF(volatile uint8_t *buf1, volatile uint8_t *buf2, volatile uint8_t Length) {
    for (uint8_t i = 0; i < Length; i++) {
        if (buf1[i] != buf2[i]) {
            return (0);
        }

    }
    return (1);
}
#endif	/* XC_MACRO_H */

