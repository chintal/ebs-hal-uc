/* 
 * Copyright (c)
 *   (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
 *  
 * This file is part of
 * Embedded bootstraps : hal-uC
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

/**
 * @file hal_uc_adc.h
 * @brief HAL for uC Internal ADC interfaces
 *
 * This file is the hardware abstraction layer for uC internal ADC interfaces. 
 * 
 * The HAL API provided for ADCs follows a least-common-denominator approach.
 * ADC features that are less common are not necessarily supported by the HAL,
 * and must be directly used from the application layer. Over time, 
 * specialized ADC features which see common use _may_ be included in the HAL,
 * but no guarantees are made. 
 * 
 * Each internal ADC is considered a single Interface, and each interface may
 * have one or more channels associated with it. 
 * 
 * The HAL ADC interface understands the following ADC elements, in one form 
 * or the other. Many of these parameters will be as preprocessor definitions
 * provided by the uC support file in the bsp.
 * 
 *  - Number of channels
 *  - Single shot conversion of a single channel
 *
 * Note that the typical ADC interface is fairly involved and has a great many
 * options, making the HAL less useful for anything but the simplest or the 
 * most common approaches to ADC use. The implementations in the HAL can be 
 * extended when specific, clear cut use cases which are used widely enough
 * to warrant continuous maintenance, but in the general case, if you want to 
 * do anything special with the ADC, you would probably have to do so from the 
 * application layer directly. 
 * 
 */

#ifndef HAL_UC_ADC_H
#define HAL_UC_ADC_H

/**
 * @name ADC API Functions
 * 
 */
/**@{*/ 
void adc_init(uint8_t intfnum);

void adc_setup_channel(uint8_t intfnum, uint8_t chnum, uint16_t * rbuf);

void adc_trigger_single(uint8_t chnum);

// void adc_setup_autoscan(uint8_t intfnum, uint16_t chnmask);

// void adc_trigger_autoscan(void);


/**@}*/ 

// Set up the implementation
#include "uc/adc_impl.h"

#endif

