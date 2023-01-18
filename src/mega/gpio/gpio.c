/*
--------------------------------------------------------------------------------------------------
|                           < Module  Definition >                                               | 
--------------------------------------------------------------------------------------------------
| < FILE                     : gpio.c                                                             |                                  
| < Author                   : Hassan Elsaied                                                    |
| < Version                  : Mega2v241022                                                      |
| < Refences                 : no refences used                                                  |
| < SRAM USAGE               : no- byte used                                                     |
| < PROGRAM USAGE            : depent in application                                             |                                      
| < Hardware Usage           : GPIO                                                              |
| < File Created             : 24-10-2022                                                        |
--------------------------------------------------------------------------------------------------
 */
#include "../../../inc/mega.h"

/* 
 --------------------------------------------------------------------------------------------------
 |                        < Call Functions >                                                     |
 --------------------------------------------------------------------------------------------------
 */

/*
 --------------------------------------------------------------------------------------------------
 |                                 < _digitalpinMode >                                            |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void _digitalpinMode                                                    |  
 | < @Description       : select mode of the pin (output or input or input with enable pull up    | 
 | < @Param pin         : pin address of gpio  (GPIO_Px) x form 0 to 7 , P (A ,B,C,....)          |   
 | < @Param mode        : type of the mode select one mode form 3 mode                            |
 |                      : @MODE_INPUT set pin as input                                            |
 |                      : @MODE_OUTPUT set pin as output                                          |
 |                      : @MODE_INPUT_PULLUP set pin as input and enable pull up                  |
 | < @return            : void                                                                    |
 --------------------------------------------------------------------------------------------------
 */

void _digitalpinMode(gpio_t pin, uint8_t mode) {
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
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < _digitalPinRead >                                            |
 --------------------------------------------------------------------------------------------------
 | < @Function          : uint8_t _digitalPinRead                                                 |  
 | < @Description       : get pin state is high or low just                                       |
 | < @Param pin         : pin address of gpio  (GPIO_Px) x form 0 to 7 , P (A ,B,C,....)          |                    
 | < @return            : utput number GPIO_LOW is pin is low and GPIO_HIGH                       |
 --------------------------------------------------------------------------------------------------
 */
uint8_t _digitalPinRead(gpio_t pin) {
    if ((GPIO_PIN_REG(pin) & GPIO_PIN_MASK(pin)) != 0)
        return GPIO_HIGH;
    else
        return GPIO_LOW;
}

/*
 --------------------------------------------------------------------------------------------------
 |                                 < _digitalPinWrite >                                           |
 --------------------------------------------------------------------------------------------------
 | < @Function          : void _digitalPinWrite                                                   |  
 | < @Description       : write out of the pin (low or high or toggle)                            | 
 | < @Param pin         : pin address of gpio  (GPIO_Px) x form 0 to 7 , P (A ,B,C,....)          |   
 | < @Param mode        : type of the mode select one mode form 3 mode                            |
 |                      : @GPIO_LOW change pin state to low                                       |
 |                      : @GPIO_HIGH change pin state to high                                     |
 |                      : @GPIO_TGL  change current pin state form high to low or low to high     |
 | < @return            : void                                                                    |
 --------------------------------------------------------------------------------------------------
 */
void _digitalPinWrite(gpio_t pin, uint8_t value) {
    ATOMIC_BEGIN
    if (value == GPIO_HIGH) {
        GPIO_PORT_REG(pin) |= GPIO_PIN_MASK(pin);
    } else if (value == GPIO_TGL) {
        GPIO_PORT_REG(pin) ^= GPIO_PIN_MASK(pin);
    } else {
        GPIO_PORT_REG(pin) &= ~GPIO_PIN_MASK(pin);
    }
    ATOMIC_END
}

