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
 * @file hal_uc_core.h
 * @brief HAL for uC Core peripherals
 *
 * This file is the hardware abstraction layer for all core uC peripherals
 * and functions. 
 */

#ifndef HAL_UC_CORE_H
#define HAL_UC_CORE_H

#include "map.h"

/**
 * @name Watchdog API Functions
 * Various functions to control the primary watchdog. Implementation is 
 * left to the implementation layer at `core_impl.h`.
 */
/**@{*/ 
/** Hold the watchdog and prevent reset due to watchdog timeout.*/
static inline void watchdog_hold(void);

/** Start the watchdog timer.*/
static inline void watchdog_start(void);

/** Clear the watchdog timer.*/
void watchdog_clear(void);

/** 
 * Initialize the watchdog timer to some default interval.
 */
void watchdog_init(void);
/**@}*/ 

/**
 * @name Power Management API Functions
 * Various functions to control the power system. Implementation is 
 * left to the implementation layer at `core_impl.h`.
 */
/**@{*/ 
/** Set core voltage to the highest possible. The use of low power 
 modes will require exploring the common motifs of power system 
 selection and improving this API. For now, we don't care. Since this
 is a one-off thing, we'll also make it a regular function and not 
 bother about the overhead. */
void power_set_full(void);
/**@}*/ 

/**
 * @name Clock Management API Functions
 * Various functions to control the clock system. Implementation is 
 * left to the implementation layer at `core_impl.h`.
 */
/**@{*/ 
/** Set clock to some sane default. For now, we don't care about the 
 * details. Since this is a one-off thing, we'll also make it a regular 
 * function and not bother about the overhead. 
 */
void clock_set_default(void);
/**@}*/ 

// Set up the implementation
#include "uc/core_impl.h"

#endif

