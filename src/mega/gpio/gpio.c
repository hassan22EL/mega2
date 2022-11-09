
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
 */

#include "../../../inc/mega.h"

/* 
 * ******************************************************************************
 *                        Call Functions                                        *
 * ******************************************************************************
 */

/* 
 * ******************************************************************************
 *                        internal_pinMode2                                        *
 * ******************************************************************************
 * benfit       : select mode of the pin (output or input or input with enable pull up
 * @param pin   : pin address of gpio
 * @param mode  : type of the mode select from mode number (MODE_INPUT or MODE_INPUT_PULLUP or MODE_OUTPUT)
 * @return      : void
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
 * ******************************************************************************
 *                        internal_digitalRead2                                        *
 * ******************************************************************************
 * benfit       : get pin is high or low just return output number GPIO_LOW is pin is low and GPIO_HIGH pin is high
 * @param pin   : pin address of gpio
 * @return      : 0 or 1
 */

uint8_t _digitalPinRead(gpio_t pin) {
    if ((GPIO_PIN_REG(pin) & GPIO_PIN_MASK(pin)) != 0)
        return GPIO_HIGH;
    else
        return GPIO_LOW;
}

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

