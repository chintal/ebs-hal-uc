/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
    
   This file is part of
   Embedded bootstraps : hal-uC
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

/**
 * @file hal_uc_gpio.h
 * @brief HAL for uC GPIOs
 *
 * This file is the hardware abstraction layer for uC GPIOs
 */

#ifndef HAL_UC_GPIO_H
#define HAL_UC_GPIO_H

#include <platform/types.h>
#include "map.h"

/**
 * @name GPIO API Functions
 * Various functions to control the uC GPIOs.
 */
/**@{*/ 
/** 
 * @brief Configure pin / pins as output.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_conf_output(PORTSELECTOR_t port,
                                    PINSELECTOR_t  pin);

/** 
 * @brief Configure pin / pins as input.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_conf_input(PORTSELECTOR_t port,
                                   PINSELECTOR_t pin);

/** 
 * @brief Configure pin / pins for peripheral's use.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 * @param periph Peripheral. In platforms where it matters, the MSB determines whether 
 *               the pin is to be used as an input or output. The remaining 7 bits are 
 *               reserved for use in devices which allow configurable peripheral use. 
 */
static inline void gpio_conf_periph(PORTSELECTOR_t port,
                                    PINSELECTOR_t pin,
                                    uint8_t periph);


/** 
 * @brief Set pin / pins output to high.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_set_output_high(PORTSELECTOR_t port,
                                        PINSELECTOR_t pin);

/** 
 * @brief Set pin / pins output to low.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number, as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_set_output_low(PORTSELECTOR_t port,
                                       PINSELECTOR_t pin);

/** 
 * @brief Toggle output state of pin / pins.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_set_output_toggle(PORTSELECTOR_t port,
                                          PINSELECTOR_t pin);

/** 
 * @brief Configure pin / pins for input with pullup.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_conf_input_pullup(PORTSELECTOR_t port,
                                          PINSELECTOR_t pin);

/** 
 * @brief Configure pin / pins for input with pulldown.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_conf_input_pulldown(PORTSELECTOR_t port,
                                            PINSELECTOR_t pin);

/** 
 * @brief Configure pin / pins for high impedance input.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number(s), as a mask. This would usually be defined by something in PUM
 */
static inline void gpio_conf_input_hiz(PORTSELECTOR_t port,
                                       PINSELECTOR_t pin);

/** 
 * @brief Retrieve state of single input pin.
 * @param port Port number. This would usually be defined by something in PUM
 * @param pin Pin number, as a mask. This would usually be defined by something in PUM
 */
static inline HAL_BASE_t gpio_get_input(PORTSELECTOR_t port,
                                        PINSELECTOR_t pin);


/**@}*/ 

// Set up the implentation
#include <hal_platform/gpio_impl.h>

#endif

