/* 
 * Copyright (c)
 *   (c) 2018 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
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
 * @file hal_uc_id.h
 * @brief HAL for uC ID
 *
 * This file is the hardware abstraction layer for acquring unique 
 * identification information from a uC, using the best available
 * mechanism for the platform.
 */

#ifndef HAL_UC_ID_H
#define HAL_UC_ID_H

#include <platform/types.h>
#include "map.h"

/**
 * @name ID API Functions
 * 
 */
/**@{*/ 

/**
 * Perform any startup initialization needed to support the ID API. 
 * Most implementations might not actually do anything here.
 */
void id_init(void);

/**
 * @brief Read the uC's unique identification.
 * @param maxlen Maximum length of the identifier to write to the buffer. 
 * @param buffer Pointer to a buffer into which the ID is to be written.
 * @return Number of bytes of the ID which were written to the buffer.
 * 
 * This obtains the best available identification information for the uC and 
 * writes it into the provided buffer. 
 * 
 * The nature of the identifier used is dependent on the uC family. In-silicon 
 * serial number is the ideal identifier when available. See the specific uC 
 * implementation for information about what is used for each platform.
 * 
 * If the identifier is longer than the specified maxlen, the identifier is 
 * truncated from the LSB side. Truncated identifiers should not be treated 
 * as valid, and the application must ensure that sufficient length is read 
 * out for each target platform.
 *
 */
uint8_t id_read(uint8_t maxlen, void * buffer);

/**
 * @brief Write the uC's unique identification.
 * @param len Length of the identifier to write to the uC. 
 * @param content Pointer to a buffer containing the ID to be written.
 * @return Number of bytes of the ID which was written to the uC.
 * 
 * Writes a unique ID to the uC. This is applicable only for platforms which 
 * allow writing an ID to the uC. Such a mechanism should only be provided 
 * when a uC does not itself provide a sufficient and readable identification 
 * mechanism. 
 * 
 * For platforms which do not require this functionality, this function should
 * return 0 for all provided inputs and not have any other effect.
 *
 */
uint8_t id_write(uint8_t len, uint8_t * content);
/**@}*/ 

// Set up the implementation
#include "uc/id_impl.h"

#endif

