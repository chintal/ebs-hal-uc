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
 * @file hal_uc_usbcdc.h
 * @brief HAL for USB CDC interface
 * 
 * @see [USB API Integration and Usage Notes](@ref usbhal)
 * 
 * @see usbcdc_impl.h 
 * @see usbcdc_impl.c
 */

#ifndef HAL_UC_USBCDC_H
#define HAL_UC_USBCDC_H

#include <stdarg.h>
#include <platform/transport.h>
#include <platform/types.h>
#include "map.h"

#ifdef uC_INCLUDE_USB_IFACE

#if uC_USBCDC_ENABLED

/**
 * @name USB CDC Interface API Functions
 *      
 */
/**@{*/ 

/**
 * \brief Initialize the specified USBCDC Interface.
 * 
 * Initialize any driver level datastructures for the specified interface. 
 * 
 * The application should handle USB connection details. This function 
 * should be called only after the USB stack is fully initialzed and connected.
 * 
 * \param intfnum Interface Number
 */
static inline void usbcdc_init(uint8_t intfnum);

/**
 * \brief Trigger USBCDC Send over the specified interface.
 * @param intfnum Identifier of the USBCDC interface
 * 
 * Trigger the transmission of data within the USBCDC transmit buffer. 
 * 
 * This function should only be called when there is atleast one valid byte in 
 * the transmit buffer. It is the caller's responsibility to ensure this is so.
 * 
 * This function will only trigger transmission of the data, and need not 
 * ensure that _all_ data present in the buffer is transmitted. The underlying
 * implementation can / will use whatever heuristic it desires to repack the 
 * data into packets for maximal transmission bandwidth. In the case of USBCDC, 
 * this is typically likely to be in 64 byte packets.
 * 
 * In case partial packets should be transmitted, the application should flush 
 * the transmit buffer instead of triggering normal transmission.
 * 
 * @see usbcdc_send_flush()
 * 
 * The nature of the transmit buffer is dependent on the underlying 
 * implementation and is not specified by the HAL. To ensure portability, the 
 * functions provided by the HAL should be used to interact with the buffer.
 * 
 * @see usbcdc_reqlock()
 * @see usbcdc_putc()
 * @see usbcdc_write()
 * 
 * This function should be as optimized as possible. It should be small enough 
 * to be inlined, and should actually be inlined. 
 */
static inline void usbcdc_send_trigger(uint8_t intfnum);


/**
 * \brief Force USBCDC Send over the specified interface.
 * @param intfnum Identifier of the USBCDC interface
 * 
 * Force the transmission of data within the USBCDC transmit buffer, even if it
 * results in the transmission of partial length packets. Note that using this
 * will necessarily eat into the available USB bandwidth. Most applications would
 * instead benefit from the use of send triggers. 
 *
 * @see usbcdc_send_trigger()
 * 
 * This function should only be called when there is atleast one valid byte in 
 * the transmit buffer. It is the caller's responsibility to ensure this is so.
 * 
 * The nature of the transmit buffer is dependent on the underlying 
 * implementation and is not specified by the HAL. To ensure portability, the 
 * functions provided by the HAL should be used to interact with the buffer.
 * 
 * @see usbcdc_reqlock()
 * @see usbcdc_putc()
 * @see usbcdc_write()
 */
static inline void usbcdc_send_flush(uint8_t intfnum);


/**
 * \brief Request transmit buffer lock for the specified USBCDC interface.
 * \param intfnum Identifier of the USBCDC interface
 * \param len Length of the data to be transmitted
 * \param token Token against which the lock should be obtained
 */
static inline uint8_t usbcdc_reqlock(uint8_t intfnum, uint8_t len, uint8_t token);


/**
 * @brief TX buffer prep function - putchar
 * @param intfnum Identifier of the USBCDC interface.
 * @param byte byte to be sent.
 * @param token token against which buffer lock should be obtained and/or used
 * @param handlelock If 1, the function will deal with interacting with the 
 *              underlying locking mechanism. If not, it assumes you already 
 *              hold the necessary locks and use the provided token.
 * @warning If the locking is left to this function, it will give up 
 *          immediately if the lock is held elsewhere. You should check the 
 *          return value of the function if the send is critical.
 * @return 0 for error, 1 for success.
 * 
 * Send a single character via the specified USBCDC interface using the standard 
 * interface. The application must also subsequently send a trigger or a flush, 
 * depending on its requirements. 
 * 
 * @see usbcdc_send_trigger()
 * @see usbcdc_send_flush()
 */
static inline uint8_t usbcdc_putc(uint8_t intfnum, uint8_t byte, 
                                  uint8_t token, uint8_t handlelock);

/**
 * @brief TX buffer prep function - write
 * @param intfnum Identifier of the USBCDC interface.
 * @param buffer Pointer to the buffer to be sent.
 * @param len Number of bytes to send (upto 256).
 * @param token Token against which buffer lock should be obtained and/or used
 
 * @return Number of bytes sent.
 * 
 * Send a buffer via the specified USBCDC interface using the driver interface.
 * The application must also subsequently send a trigger or a flush, 
 * depending on its requirements. 
 * 
 * @see usbcdc_send_trigger()
 * @see usbcdc_send_flush()
 */
static inline uint8_t usbcdc_write(uint8_t intfnum, uint8_t *buffer, uint8_t len, 
                                   uint8_t token);

/**
 * \brief Get the current status of a specific USB CDC TX interface.
 * 
 * \warning This function for MSP430 USB API will report USB CDC TX ready even 
 * before the last transaction is completed and the txdone handlers are called. 
 * 
 * \param intfNum Interface Number
 * \returns 0 if CDC TX is in use or otherwise not available, 1 if CDC TX is
 *          ready to recieve additional data from a user buffer.
 */
static inline uint8_t usbcdc_txready(uint8_t intfNum);

static inline uint8_t usbcdc_getc(uint8_t intfnum);

static inline uint8_t usbcdc_read(uint8_t intfnum, uint8_t *buffer, uint8_t len);

/**
 * \brief Get number of unhandled bytes of a specific USB CDC RX interface.
 * \param intfNum Interface Number
 * \returns Number of unhandled bytes waiting in the interface API buffer.
 */
static inline uint8_t usbcdc_population_rxb(uint8_t intfNum);

/**
 * \brief Discard all unhandled bytes of a specific USB CDC RX interface.
 * \param intfNum Interface Number
 */
static inline void usbcdc_discard_rxb(uint8_t intfNum);

/**@}*/

extern const pluggable_transport_t ptransport_usbcdc;

#endif 
#endif

#include "uc/usbcdc_impl.h"
#endif
