
/* 
 * *****************************************************************************
 *                        Module  Definition                                   *
 * *****************************************************************************
 * File         :   gpio.h
 * Author       :   Hassan Elsaied
 * Data Memory  :   no data byte used
 * Program Space:   under upgrade
 * Version      :   Mega2v241022
 * Start Data   :   24-10-2022  20:00:00
 * End Data     :   24-10-2022  23:48:00
 * Work Time    :   5-hour
 * Comments     :   no comment
 *  
 */
#ifndef XC_GPIO_H
#define	XC_GPIO_H

#include "../mega.h"


/* 
 * ******************************************************************************
 *                        Macro  Definition                                     *
 * ******************************************************************************
 */


/* 
 * ******************************************************************************
 *                        Gpio Speed                                 *
 * ******************************************************************************
 */
#if GPIO2_PREFER_SPEED ==1
#define		GPIO2_USE_INLINE_FUNCTIONS	0
#else
#define		GPIO2_USE_INLINE_FUNCTIONS	1
#endif



/* 
 * ******************************************************************************
 *                        Gpio Atomic opton                                 *
 * ******************************************************************************
 */


#if GPIO2_IOREGS_ABOVEFF
#define	GPIO2_OPTIONAL_ATOMIC_BEGIN		ATOMIC_BEGIN
#define GPIO2_OPTIONAL_ATOMIC_END		ATOMIC_END
#else
#define	GPIO2_OPTIONAL_ATOMIC_BEGIN
#define	GPIO2_OPTIONAL_ATOMIC_END
#endif

/* 
 * ******************************************************************************
 *                        Gpio Encode Pin and Port                              *
 * ******************************************************************************
 * @benfit : Encode port address with pin mask
 * @param port : port address in sfr
 * @param pin  : bin mask in code
 */


#define	GPIO_Create_PIN(port, pin)         ((uint16_t)port > 0xFF ) ? \
		(((uint16_t)port & 0x00FF) | ((1<<pin) << 8) | 0x0080 ) : \
		(((uint16_t)port & 0x00FF) | ((1<<pin) << 8))


/* 
 * ******************************************************************************
 *                       get Port Address Form SFR                              *
 * ******************************************************************************
 */

#define     PORT_ADDR(Port)             (_SFR_ADDR(Port))

/* 
 * ******************************************************************************
 *                        Pin is not Found in this arch                         *
 * ******************************************************************************
 */
#define NOT_A_PIN     0




/* 
 * ******************************************************************************
 *                        PORT A Encode                                         *
 * ******************************************************************************
 */


#ifdef  PORTA
#ifdef PA0
#define GPIO_A0          GPIO_Create_PIN(PORT_ADDR(PORTA) , 0)
#else 
#define GPIO_A0          DP_INVALID
#endif
#ifdef PA1
#define GPIO_A1          GPIO_Create_PIN(PORT_ADDR(PORTA) , 1)
#else 
#define GPIO_A1          DP_INVALID
#endif
#ifdef PA2
#define  GPIO_A2          GPIO_Create_PIN(PORT_ADDR(PORTA) , 2)
#else 
#define GPIO_A2         DP_INVALID
#endif


#ifdef PA3
#define GPIO_A3 GPIO_Create_PIN(PORT_ADDR(PORTA), 3)
#else 
#define GPIO_A3         DP_INVALID
#endif

#ifdef PA4
#define GPIO_A4          GPIO_Create_PIN(PORT_ADDR(PORTA), 4)
#else 
#define GPIO_A4          DP_INVALID
#endif

#ifdef PA5
#define GPIO_A5 GPIO_Create_PIN(PORT_ADDR(PORTA), 5)
#else 
#define GPIO_A5          DP_INVALID
#endif
#ifdef PA6
#define GPIO_A6 GPIO_Create_PIN(PORT_ADDR(PORTA), 6)
#else 
#define GPIO_A6          DP_INVALID
#endif

#ifdef PA7
#define GPIO_A7 GPIO_Create_PIN(PORT_ADDR(PORTA), 7)
#else 
#define GPIO_A7          DP_INVALID
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT B Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTB
#ifdef PB0
#define GPIO_B0          GPIO_Create_PIN(PORT_ADDR(PORTB) , 0)
#else 
#define GPIO_B0          NOT_A_PIN
#endif
#ifdef PB1
#define GPIO_B1          GPIO_Create_PIN(PORT_ADDR(PORTB) , 1)
#else 
#define GPIO_B1          NOT_A_PIN
#endif
#ifdef PB2
#define  GPIO_B2          GPIO_Create_PIN(PORT_ADDR(PORTB) , 2)
#else 
#define GPIO_B2         NOT_A_PIN
#endif
#ifdef PB3
#define  GPIO_B3 GPIO_Create_PIN(PORT_ADDR(PORTB), 3)
#else 
#define GPIO_B3         NOT_A_PIN
#endif
#ifdef PB4
#define GPIO_B4 GPIO_Create_PIN(PORT_ADDR(PORTB), 4)
#else 
#define GPIO_B4          NOT_A_PIN
#endif
#ifdef PB5
#define GPIO_B5 GPIO_Create_PIN(PORT_ADDR(PORTB), 5)
#else 
#define GPIO_B5          NOT_A_PIN
#endif
#ifdef PB6
#define GPIO_B6 GPIO_Create_PIN(PORT_ADDR(PORTB), 6)
#else 
#define GPIO_B6          NOT_A_PIN
#endif
#ifdef PB7
#define  GPIO_B7 GPIO_Create_PIN(PORT_ADDR(PORTB), 7)
#else 
#define GPIO_B7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT C Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTC
#ifdef PC0
#define GPIO_C0          GPIO_Create_PIN(PORT_ADDR(PORTC) , 0)
#else 
#define GPIO_C0          NOT_A_PIN
#endif
#ifdef PC1
#define GPIO_C1          GPIO_Create_PIN(PORT_ADDR(PORTC) , 1)
#else 
#define GPIO_C1          NOT_A_PIN
#endif
#ifdef PC2
#define  GPIO_C2          GPIO_Create_PIN(PORT_ADDR(PORTC) , 2)
#else 
#define GPIO_C2         NOT_A_PIN
#endif


#ifdef PC3
#define  GPIO_C3 GPIO_Create_PIN(PORT_ADDR(PORTC), 3)
#else 
#define GPIO_C3         NOT_A_PIN
#endif

#ifdef PC4
#define GPIO_C4 GPIO_Create_PIN(PORT_ADDR(PORTC), 4)
#else 
#define GPIO_C4          NOT_A_PIN
#endif

#ifdef PC5
#define GPIO_C5 GPIO_Create_PIN(PORT_ADDR(PORTC), 5)
#else 
#define GPIO_C5          NOT_A_PIN
#endif
#ifdef PC6
#define GPIO_C6 GPIO_Create_PIN(PORT_ADDR(PORTC), 6)
#else 
#define GPIO_C6          NOT_A_PIN
#endif

#ifdef PC7
#define  GPIO_C7 GPIO_Create_PIN(PORT_ADDR(PORTC), 7)
#else 
#define GPIO_C7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT D Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTD
#ifdef PD0
#define GPIO_D0          GPIO_Create_PIN(PORT_ADDR(PORTD) , 0)
#else 
#define GPIO_D0          NOT_A_PIN
#endif
#ifdef PD1
#define GPIO_D1          GPIO_Create_PIN(PORT_ADDR(PORTD) , 1)
#else 
#define GPIO_D1          NOT_A_PIN
#endif
#ifdef PD2
#define  GPIO_D2          GPIO_Create_PIN(PORT_ADDR(PORTD) , 2)
#else 
#define GPIO_D2         NOT_A_PIN
#endif


#ifdef PD3
#define  GPIO_D3 GPIO_Create_PIN(PORT_ADDR(PORTD), 3)
#else 
#define GPIO_D3         NOT_A_PIN
#endif

#ifdef PD4
#define GPIO_D4 GPIO_Create_PIN(PORT_ADDR(PORTD), 4)
#else 
#define GPIO_D4          NOT_A_PIN
#endif

#ifdef PD5
#define GPIO_D5      GPIO_Create_PIN(PORT_ADDR(PORTD), 5)
#else 
#define GPIO_D5          NOT_A_PIN
#endif
#ifdef PD6
#define GPIO_D6      GPIO_Create_PIN(PORT_ADDR(PORTD), 6)
#else 
#define GPIO_D6          NOT_A_PIN
#endif

#ifdef PD7
#define  GPIO_D7 GPIO_Create_PIN(PORT_ADDR(PORTD), 7)
#else 
#define GPIO_D7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT E Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTE
#ifdef PE0
#define GPIO_E0          GPIO_Create_PIN(PORT_ADDR(PORTE) , 0)
#else 
#define GPIO_E0          NOT_A_PIN
#endif
#ifdef PE1
#define GPIO_E1          GPIO_Create_PIN(PORT_ADDR(PORTE) , 1)
#else 
#define GPIO_E1          NOT_A_PIN
#endif
#ifdef PE2
#define  GPIO_E2          GPIO_Create_PIN(PORT_ADDR(PORTE) , 2)
#else 
#define GPIO_E2         NOT_A_PIN
#endif


#ifdef PE3
#define  GPIO_E3 GPIO_Create_PIN(PORT_ADDR(PORTE), 3)
#else 
#define GPIO_E3         NOT_A_PIN
#endif

#ifdef PE4
#define GPIO_E4 GPIO_Create_PIN(PORT_ADDR(PORTE), 4)
#else 
#define GPIO_E4          NOT_A_PIN
#endif

#ifdef PE5
#define GPIO_E5 GPIO_Create_PIN(PORT_ADDR(PORTE), 5)
#else 
#define GPIO_E5          NOT_A_PIN
#endif
#ifdef PE6
#define GPIO_E6 GPIO_Create_PIN(PORT_ADDR(PORTE), 6)
#else 
#define GPIO_E6          NOT_A_PIN
#endif

#ifdef PE7
#define  GPIO_E7 GPIO_Create_PIN(PORT_ADDR(PORTE), 7)
#else 
#define GPIO_E7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT F Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTF
#ifdef PF0
#define GPIO_F0          GPIO_Create_PIN(PORT_ADDR(PORTF) , 0)
#else 
#define GPIO_F0          NOT_A_PIN
#endif
#ifdef PF1
#define GPIO_F1          GPIO_Create_PIN(PORT_ADDR(PORTF) , 1)
#else 
#define GPIO_F1          NOT_A_PIN
#endif
#ifdef PF2
#define  GPIO_F2          GPIO_Create_PIN(PORT_ADDR(PORTF) , 2)
#else 
#define GPIO_F2         NOT_A_PIN
#endif


#ifdef PF3
#define  GPIO_F3 GPIO_Create_PIN(PORT_ADDR(PORTF), 3)
#else 
#define GPIO_F3         NOT_A_PIN
#endif

#ifdef PF4
#define GPIO_F4 GPIO_Create_PIN(PORT_ADDR(PORTF), 4)
#else 
#define GPIO_F4          NOT_A_PIN
#endif

#ifdef PF5
#define GPIO_F5 GPIO_Create_PIN(PORT_ADDR(PORTF), 5)
#else 
#define GPIO_F5          NOT_A_PIN
#endif
#ifdef PF6
#define GPIO_F6 GPIO_Create_PIN(PORT_ADDR(PORTF), 6)
#else 
#define GPIO_F6          NOT_A_PIN
#endif

#ifdef PF7
#define  GPIO_F7 GPIO_Create_PIN(PORT_ADDR(PORTF), 7)
#else 
#define GPIO_F7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT G Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTG
#ifdef PG0
#define GPIO_G0          GPIO_Create_PIN(PORT_ADDR(PORTG) , 0)
#else 
#define GPIO_G0          NOT_A_PIN
#endif
#ifdef PG1
#define GPIO_G1          GPIO_Create_PIN(PORT_ADDR(PORTG) , 1)
#else 
#define GPIO_G1          NOT_A_PIN
#endif
#ifdef PG2
#define  GPIO_G2          GPIO_Create_PIN(PORT_ADDR(PORTG) , 2)
#else 
#define GPIO_G2         NOT_A_PIN
#endif


#ifdef PG3
#define  GPIO_G3 GPIO_Create_PIN(PORT_ADDR(PORTG), 3)
#else 
#define GPIO_G3         NOT_A_PIN
#endif

#ifdef PG4
#define GPIO_G4 GPIO_Create_PIN(PORT_ADDR(PORTG), 4)
#else 
#define GPIO_G4          NOT_A_PIN
#endif

#ifdef PG5
#define GPIO_G5 GPIO_Create_PIN(PORT_ADDR(PORTG), 5)
#else 
#define GPIO_G5          NOT_A_PIN
#endif
#ifdef PG6
#define GPIO_G6 GPIO_Create_PIN(PORT_ADDR(PORTG), 6)
#else 
#define GPIO_G6          NOT_A_PIN
#endif

#ifdef PG7
#define  GPIO_G7 GPIO_Create_PIN(PORT_ADDR(PORTG), 7)
#else 
#define GPIO_G7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT H Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTH
#ifdef PH0
#define GPIO_H0          GPIO_Create_PIN(PORT_ADDR(PORTH) , 0)
#else 
#define GPIO_H0          NOT_A_PIN
#endif
#ifdef PH1
#define GPIO_H1          GPIO_Create_PIN(PORT_ADDR(PORTH) , 1)
#else 
#define GPIO_H1          NOT_A_PIN
#endif
#ifdef PH2
#define  GPIO_H2          GPIO_Create_PIN(PORT_ADDR(PORTH) , 2)
#else 
#define GPIO_H2         NOT_A_PIN
#endif


#ifdef PH3
#define  GPIO_H3 GPIO_Create_PIN(PORT_ADDR(PORTH), 3)
#else 
#define GPIO_H3         NOT_A_PIN
#endif

#ifdef PH4
#define GPIO_H4 GPIO_Create_PIN(PORT_ADDR(PORTH), 4)
#else 
#define GPIO_H4          NOT_A_PIN
#endif

#ifdef PH5
#define GPIO_H5 GPIO_Create_PIN(PORT_ADDR(PORTH), 5)
#else 
#define GPIO_H5          NOT_A_PIN
#endif
#ifdef PH6
#define GPIO_H6 GPIO_Create_PIN(PORT_ADDR(PORTH), 6)
#else 
#define GPIO_H6          NOT_A_PIN
#endif

#ifdef PH7
#define  GPIO_H7 GPIO_Create_PIN(PORT_ADDR(PORTH), 7)
#else 
#define GPIO_H7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT I Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTI
#ifdef PI0
#define GPIO_I0          GPIO_Create_PIN(PORT_ADDR(PORTI) , 0)
#else 
#define GPIO_I0          NOT_A_PIN
#endif
#ifdef PI1
#define GPIO_I1          GPIO_Create_PIN(PORT_ADDR(PORTI) , 1)
#else 
#define GPIO_I1          NOT_A_PIN
#endif
#ifdef PI2
#define  GPIO_I2          GPIO_Create_PIN(PORT_ADDR(PORTI) , 2)
#else 
#define GPIO_I2         NOT_A_PIN
#endif


#ifdef PI3
#define  GPIO_I3 GPIO_Create_PIN(PORT_ADDR(PORTI), 3)
#else 
#define GPIO_I3         NOT_A_PIN
#endif

#ifdef PI4
#define GPIO_I4 GPIO_Create_PIN(PORT_ADDR(PORTI), 4)
#else 
#define GPIO_I4          NOT_A_PIN
#endif

#ifdef PI5
#define GPIO_I5 GPIO_Create_PIN(PORT_ADDR(PORTI), 5)
#else 
#define GPIO_I5          NOT_A_PIN
#endif
#ifdef PI6
#define GPIO_I6 GPIO_Create_PIN(PORT_ADDR(PORTI), 6)
#else 
#define GPIO_I6          NOT_A_PIN
#endif

#ifdef PI7
#define  GPIO_I7 GPIO_Create_PIN(PORT_ADDR(PORTI), 7)
#else 
#define GPIO_I7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT J Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTJ
#ifdef PJ0
#define GPIO_J0          GPIO_Create_PIN(PORT_ADDR(PORTJ) , 0)
#else 
#define GPIO_J0          NOT_A_PIN
#endif
#ifdef PJ1
#define GPIO_J1          GPIO_Create_PIN(PORT_ADDR(PORTJ) , 1)
#else 
#define GPIO_J1          NOT_A_PIN
#endif
#ifdef PJ2
#define  GPIO_J2          GPIO_Create_PIN(PORT_ADDR(PORTJ) , 2)
#else 
#define GPIO_J2         NOT_A_PIN
#endif


#ifdef PJ3
#define  GPIO_J3 GPIO_Create_PIN(PORT_ADDR(PORTJ), 3)
#else 
#define GPIO_J3         NOT_A_PIN
#endif

#ifdef PJ4
#define GPIO_J4 GPIO_Create_PIN(PORT_ADDR(PORTJ), 4)
#else 
#define GPIO_J4          NOT_A_PIN
#endif

#ifdef PJ5
#define GPIO_J5 GPIO_Create_PIN(PORT_ADDR(PORTJ), 5)
#else 
#define GPIO_J5          NOT_A_PIN
#endif
#ifdef PJ6
#define GPIO_J6 GPIO_Create_PIN(PORT_ADDR(PORTJ), 6)
#else 
#define GPIO_J6          NOT_A_PIN
#endif

#ifdef PJ7
#define  GPIO_J7 GPIO_Create_PIN(PORT_ADDR(PORTJ), 7)
#else 
#define GPIO_I7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT K Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTK
#ifdef PK0
#define GPIO_K0          GPIO_Create_PIN(PORT_ADDR(PORTK) , 0)
#else 
#define GPIO_K0          NOT_A_PIN
#endif
#ifdef PK1
#define GPIO_K1          GPIO_Create_PIN(PORT_ADDR(PORTK) , 1)
#else 
#define GPIO_K1          NOT_A_PIN
#endif
#ifdef PK2
#define  GPIO_K2          GPIO_Create_PIN(PORT_ADDR(PORTK) , 2)
#else 
#define GPIO_K2         NOT_A_PIN
#endif


#ifdef PK3
#define  GPIO_K3 GPIO_Create_PIN(PORT_ADDR(PORTK), 3)
#else 
#define GPIO_K3         NOT_A_PIN
#endif

#ifdef PK4
#define GPIO_K4 GPIO_Create_PIN(PORT_ADDR(PORTK), 4)
#else 
#define GPIO_K4          NOT_A_PIN
#endif

#ifdef PK5
#define GPIO_K5 GPIO_Create_PIN(PORT_ADDR(PORTK), 5)
#else 
#define GPIO_K5          NOT_A_PIN
#endif
#ifdef PK6
#define GPIO_K6 GPIO_Create_PIN(PORT_ADDR(PORTK), 6)
#else 
#define GPIO_K6          NOT_A_PIN
#endif

#ifdef PK7
#define  GPIO_K7 GPIO_Create_PIN(PORT_ADDR(PORTK), 7)
#else 
#define GPIO_I7          NOT_A_PIN
#endif
#endif
/* 
 * ******************************************************************************
 *                        PORT L Encode                                         *
 * ******************************************************************************
 */

#ifdef  PORTL
#ifdef PL0
#define PORTL0          GPIO_Create_PIN(PORT_ADDR(PORTL) , 0)
#else 
#define PORTL0          NOT_A_PIN
#endif
#ifdef PL1
#define PORTL1          GPIO_Create_PIN(PORT_ADDR(PORTL) , 1)
#else 
#define PORTL1          NOT_A_PIN
#endif
#ifdef PL2
#define  PORTL2          GPIO_Create_PIN(PORT_ADDR(PORTL) , 2)
#else 
#define PORTL2         NOT_A_PIN
#endif


#ifdef PL3
#define  PORTL3 GPIO_Create_PIN(PORT_ADDR(PORTL), 3)
#else 
#define PORTL3         NOT_A_PIN
#endif

#ifdef PL4
#define PORTL4 GPIO_Create_PIN(PORT_ADDR(PORTL), 4)
#else 
#define PORTL4          NOT_A_PIN
#endif

#ifdef PL5
#define PORTL5 GPIO_Create_PIN(PORT_ADDR(PORTL), 5)
#else 
#define PORTL5          NOT_A_PIN
#endif
#ifdef PL6
#define PORTL6 GPIO_Create_PIN(PORT_ADDR(PORTL), 6)
#else 
#define PORTL6          NOT_A_PIN
#endif

#ifdef PL7
#define  PORTL7 GPIO_Create_PIN(PORT_ADDR(PORTL), 7)
#else 
#define GPIO_I7          NOT_A_PIN
#endif
#endif

/* 
 * ******************************************************************************
 *                        Get Pin Mask From Pin address                         *
 * ******************************************************************************
 */
#define		GPIO_PIN_MASK(pin)		 ((uint8_t)((uint16_t)pin >> 8))

/* 
 * ******************************************************************************
 *                        Get Port Address From Pin address                     *
 * ******************************************************************************
 */


#if  defined(__AVR_ATmega128A__) || defined (__AVR_ATmega128__)
#define		GET_PORT_REG_ADR(pin)	  ((((pin) & 0x0080) == 0) ? \
			(((pin) & 0x00FF)) : \
			((((pin) & 0x007F) | 0x0100)))
#else
#define		GET_PORT_REG_ADR(pin)	  ((((pin) & 0x0080) == 0) ? \
			((volatile uint8_t*)((pin) & 0x00FF)) : \
			((volatile uint8_t*)(((pin) & 0x007F) | 0x0100)))
#endif

/* 
 * ******************************************************************************
 *                        Get PIN  address From Pin address                         *
 * ******************************************************************************
 */

#if  defined(__AVR_ATmega128A__) || defined (__AVR_ATmega128__)
#define		GET_PIN_REG_ADR(pin)        (volatile uint8_t*)(((GET_PORT_REG_ADR(pin)-2) != 0x0060)?(GET_PORT_REG_ADR(pin)-2) : 0x0020)
#else
#define		GET_PIN_REG_ADR(pin)		(GET_PORT_REG_ADR(pin)-2)
#endif
/* 
 * ******************************************************************************
 *                        Get DDR  address From Pin address                         *
 * ******************************************************************************
 */


#define		GET_DDR_REG_ADR(pin)		(GET_PORT_REG_ADR(pin)-1)

/* 
 * ******************************************************************************
 *                        Casting PIN address to address SFR                   *
 * ******************************************************************************
 */


#define   GPIO_PIN_REG(pin)    (*(volatile uint8_t*)GET_PIN_REG_ADR(pin) )

/* 
 * ******************************************************************************
 *                        Casting PORT address to address SFR                   *
 * ******************************************************************************
 */
#define   GPIO_PORT_REG(pin)    (*(volatile uint8_t*)GET_PORT_REG_ADR(pin))

/* 
 * ******************************************************************************
 *                        Casting DDR address to address SFR                   *
 * ******************************************************************************
 */

#define   GPIO_DDR_REG(pin)    (*(volatile uint8_t*)GET_DDR_REG_ADR(pin) )

/* 
 * ******************************************************************************
 *                        MODE Number                                            *
 * ******************************************************************************
 */


typedef enum {
    MODE_INPUT,
    MODE_INPUT_PULLUP,
    MODE_OUTPUT,
} EN_Mode_t;

/* 
 * ******************************************************************************
 *                        OUTPUT Number                                          *
 * ******************************************************************************
 */
typedef enum {
    GPIO_LOW,
    GPIO_HIGH,
    GPIO_TGL,
} EN_GPIO_t;

/* 
 * ******************************************************************************
 *                        inline Functions                                        *
 * ******************************************************************************
 */

/* 
 * ******************************************************************************
 *                        digitalpinMode                                        *
 * ******************************************************************************
 * benfit : select mode of the pin (output or input or input with enable pull up
 * @param pin : pin address of gpio
 * @param mode : type of the mode select from mode number (MODE_INPUT or MODE_INPUT_PULLUP or MODE_OUTPUT)
 * @return      : void
 */
static inline void digitalpinMode(gpio_t pin, uint8_t mode);
/* 
 * ******************************************************************************
 *                        digitalPinRead                                        *
 * ******************************************************************************
 * benfit : get pin is high or low just return output number GPIO_LOW is pin is low and GPIO_HIGH pin is high
 * @param pin : pin address of gpio
 * @return      : 0 or 1
 */

static inline uint8_t digitalPinRead(gpio_t pin);
/* 
 * ******************************************************************************
 *                        digitalPinWrite                                        *
 * ******************************************************************************
 * benfit : write out of the pin (low or high or toggle) low write is GPIO_LOW and 
 *        : write GPIO_HIGH is pin high and write GPIO_TGL pin is toggle
 * @param pin   : pin address of gpio
 * @param value : type of out number (GPIO_LOW,GPIO_HIGH,GPIO_TGL)
 * @return      : void
 */

static inline void digitalPinWrite(gpio_t pin, uint8_t value);
/* 
 * ******************************************************************************
 *                        Call Functions                                        *
 * ******************************************************************************
 */


/* 
 * ******************************************************************************
 *                        internal_pinMode2                                        *
 * ******************************************************************************
 * benfit : select mode of the pin (output or input or input with enable pull up
 * @param pin : pin address of gpio
 * @param mode : type of the mode select from mode number (MODE_INPUT or MODE_INPUT_PULLUP or MODE_OUTPUT)
 * @return      : void
 */

void _digitalpinMode(gpio_t pin, uint8_t mode); // implemented in gpio.c
/* 
 * ******************************************************************************
 *                        internal_digitalRead2                                        *
 * ******************************************************************************
 * benfit : get pin is high or low just return output number GPIO_LOW is pin is low and GPIO_HIGH pin is high
 * @param pin : pin address of gpio
 * @return      : 0 or 1
 */

uint8_t _digitalPinRead(gpio_t pin); // implemented in gpio.c
/* 
 * ******************************************************************************
 *                        internal_digitalWrite2                                        *
 * ******************************************************************************
 * benfit : write out of the pin (low or high or toggle) low write is GPIO_LOW and 
 *        : write GPIO_HIGH is pin high and write GPIO_TGL pin is toggle
 * @param pin   : pin address of gpio
 * @param value : type of out number (GPIO_LOW,GPIO_HIGH,GPIO_TGL)
 * @return      : void
 */
void _digitalPinWrite(gpio_t pin, uint8_t value); // implemented in gpio.c

/* 
 * ******************************************************************************
 *                      implement of  inline Functions                                        *
 * ******************************************************************************
 */

/* 
 * ******************************************************************************
 *                        digitalpinMode                                        *
 * ******************************************************************************
 * benfit : select mode of the pin (output or input or input with enable pull up
 * @param pin : pin address of gpio
 * @param mode : type of the mode select from mode number (MODE_INPUT or MODE_INPUT_PULLUP or MODE_OUTPUT)
 * @return      : void
 */
static inline void digitalpinMode(gpio_t pin, uint8_t mode) __attribute__((always_inline, unused));

static inline void digitalpinMode(gpio_t pin, uint8_t mode) {
    if (__builtin_constant_p(pin) && __builtin_constant_p(mode)) {
        GPIO2_OPTIONAL_ATOMIC_BEGIN
        if (mode == MODE_OUTPUT) {
            GPIO_DDR_REG(pin) |= GPIO_PIN_MASK(pin);
        } else {
            if (mode == MODE_INPUT_PULLUP) {
                GPIO_DDR_REG(pin) &= ~GPIO_PIN_MASK(pin);
                GPIO_PORT_REG(pin) |= GPIO_PIN_MASK(pin);
            } else {
                // input mode without pull-up
                GPIO_DDR_REG(pin) &= ~GPIO_PIN_MASK(pin);
                GPIO_PORT_REG(pin) &= ~GPIO_PIN_MASK(pin);
            }
        }
        GPIO2_OPTIONAL_ATOMIC_END
    } else {
        // The pin or mode are not know at compile-time but the user wants
        // inline code (GPIO2_PREFER_SPEED = 1)
#if	GPIO2_USE_INLINE_FUNCTIONS
        if (mode == MODE_OUTPUT) {
            ATOMIC_BEGIN
            GPIO_DDR_REG(pin) |= GPIO_PIN_MASK(pin);
            ATOMIC_END
        } else {
            if (mode == MODE_INPUT_PULLUP) {
                ATOMIC_BEGIN
                GPIO_DDR_REG(pin) &= ~GPIO_PIN_MASK(pin);
                GPIO_PORT_REG(pin) |= GPIO_PIN_MASK(pin);
                ATOMIC_END
            } else {
                // input mode without pull-up
                ATOMIC_BEGIN
                GPIO_DDR_REG(pin) &= ~GPIO_PIN_MASK(pin);
                GPIO_PORT_REG(pin) &= ~GPIO_PIN_MASK(pin);
                ATOMIC_END
            }
        }

#else
        // Call non-inline 
        _digitalpinMode(pin, mode);
#endif

    }
}
/* 
 * ******************************************************************************
 *                        digitalPinRead                                        *
 * ******************************************************************************
 * benfit : get pin is high or low just return output number GPIO_LOW is pin is low and GPIO_HIGH pin is high
 * @param pin : pin address of gpio
 * @return      : 0 or one 
 */
static inline uint8_t digitalPinRead(gpio_t pin) __attribute__((always_inline, unused));

static inline uint8_t digitalPinRead(gpio_t pin) {

    if (__builtin_constant_p(pin)) {
        if ((GPIO_PIN_REG(pin) & GPIO_PIN_MASK(pin)) != 0)
            return GPIO_HIGH;
        else
            return GPIO_LOW;
    } else {

#if	GPIO2_USE_INLINE_FUNCTIONS
        if ((GPIO_PIN_REG(pin) & GPIO_PIN_MASK(pin)) != 0)
            return GPIO_HIGH;
        else
            return GPIO_LOW;

#else
        return _digitalPinRead(pin);
#endif

    }
}

/* 
 * ******************************************************************************
 *                        digitalPinWrite                                        *
 * ******************************************************************************
 * benfit : write out of the pin (low or high or toggle) low write is GPIO_LOW and 
 *        : write GPIO_HIGH is pin high and write GPIO_TGL pin is toggle
 * @param pin   : pin address of gpio
 * @param value : type of out number (GPIO_LOW,GPIO_HIGH,GPIO_TGL)
 * @return      : void
 */

static inline void digitalPinWrite(gpio_t pin, uint8_t value) __attribute__((always_inline, unused));

static inline void digitalPinWrite(gpio_t pin, uint8_t value) {
    // If we know the pin number and value at compile-time, the compiler
    // will compute everything during compilation and resulting code will
    // be single instruction - which does not need disabled interrupts	 
    if (__builtin_constant_p(pin) && __builtin_constant_p(value)) {
        GPIO2_OPTIONAL_ATOMIC_BEGIN
        if (value == GPIO_HIGH) {
            GPIO_PORT_REG(pin) |= GPIO_PIN_MASK(pin);
        } else if (value == GPIO_TGL) {
            GPIO_PORT_REG(pin) ^= GPIO_PIN_MASK(pin);
        } else {
            GPIO_PORT_REG(pin) &= ~GPIO_PIN_MASK(pin);
        }
        GPIO2_OPTIONAL_ATOMIC_END
    } else {
        // If pin or value must be computed in runtime, resulting code
        // will always require disabled interrupts.
#if GPIO2_USE_INLINE_FUNCTIONS

        // NOTE: if you make change here, make it also in internal_digitalWrite2()!
        ATOMIC_BEGIN
        if (value == GPIO_HIGH) {
            GPIO_PORT_REG(pin) |= GPIO_PIN_MASK(pin);
        } else if (value == GPIO_TGL) {
            GPIO_PORT_REG(pin) ^= GPIO_PIN_MASK(pin);
        } else {
            GPIO_PORT_REG(pin) &= ~GPIO_PIN_MASK(pin);
        }
        ATOMIC_END

#else
        _digitalPinWrite(pin, value);
#endif
    }
}







#endif	/* XC_GPIO_V2_H */