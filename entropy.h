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
 * @file hal_uc_entropy.h
 * @brief HAL for uC entropy source
 *
 * This file is the hardware abstraction layer for generation of entropy
 * from the uC. 
 * 
 * It must be noted that in most, if not all platforms, the actual entropy 
 * sources may not be available during program execution. Typical utilization 
 * of the Entropy API in most cases should be limited to an initial 
 * accumulation of sufficient entropy as needed by the application to 
 * initialize a PRNG. This period of entropy accumulation should occur before 
 * major subsystem initialization, and it should be assumed that during this 
 * period various peripherals would not behave as expected otherwise. 
 * 
 * For example, the MSP430 entropy sources will take over both ACLK and SMCLK, 
 * and anything depending on those clocks, including system time, for 
 * instance, will  misbehave. On other platforms, ADCs may be unavailable 
 * during accumulation.
 * 
 * The application must ensure to exit the entropy accumulation mode after it
 * has sufficient entropy and before any major initialization steps are takem.
 * 
 * This layer should not and does not do any hashing or heavy computation. 
 * Using such mathematical means to generate a byte stream is left to the 
 * application layer, which may use whatever algorithms or libraries to 
 * provide a bulk pseudo-random stream if needed.
 * 
 */

#ifndef HAL_UC_ENTROPY_H
#define HAL_UC_ENTROPY_H

#include "map.h"

/**
 * @name Entropy API Functions
 * 
 */
/**@{*/ 
/**
 * @brief Enter the entropy accumulation mode. 
 * 
 * This function will take over and reconfigure some peripherals in order 
 * to accumulate entropy. The implementation of this function should ensure
 * that it keeps a copy of everything it changes so that it can later be 
 * restored during deinitialization.
 * 
 * @warning You should make sure that doing this does not interfere with 
 *          any peripherals you may already have initialized on your 
 *          application and on your platform.
 * 
 * @see entropy_deinit()
 * 
 */
void entropy_init(void);

/**
 * @brief Get one byte of entropy.
 * 
 * When called when in the entropy accumulation mode, this function will 
 * accumulate and return one byte of entropy. This should be assumed to 
 * be a blocking call and is expected to be used only in the early stages 
 * of application initialization.
 * 
 */
uint8_t entropy_get_byte(void);

/**
 * @brief Leave the entropy accumulation mode. 
 * 
 * This function should also return everything that it changed to how it 
 * found it during initialization.
 * 
 * @warning This function should be called to exit the entropy accumulation
 *          mode before any major perhipheral or subsystem initialization. 
 * 
 * @see entropy_deinit()
 * 
 */
void entropy_deinit(void);
/**@}*/ 

// Set up the implementation
#include "uc/entropy_impl.h"

#endif

