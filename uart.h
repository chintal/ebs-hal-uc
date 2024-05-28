/* 
   Copyright (c)
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
    
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
 * @file hal_uc_uart.h
 * @brief HAL for UART peripherals
 *
 * This file is the hardware abstraction layer for uC UART interfaces
 * 
 * @see uart_impl.h 
 * @see uart_impl.c
 */

#ifndef HAL_UC_UART_H
#define HAL_UC_UART_H

#include <stdarg.h>
#include <platform/transport.h>
#include <platform/types.h>
#include "map.h"

#ifdef uC_INCLUDE_UART_IFACE

/**
 * @name UART API Setup Functions
 */
/**@{*/ 

/**
 * Initialize UART. Config parameters for the UART are (currently) defined in UC_MAP.
 * @param intfnum Identifier of the UART interface
 */
void uart_init(uint8_t intfnum);

/**@}*/ 

/**
 * @name Main UART API Functions
 */
/**@{*/ 

/**
 * @brief Trigger UART Send over the specified interface.
 * @param intfnum Identifier of the UART interface
 * 
 * Trigger the transmission of data within the UART
 * transmit buffer. This buffer would typically be a ::bytebuf,
 * though the implentation could use whatever it wants.
 * 
 * This function should only be called when there is atleast
 * one valid byte in the transmit buffer. It is the callers 
 * responsibility to ensure this is so.
 * 
 * This function should be as optimized as possible. It 
 * should be small enough to be inlined, and should actually
 * be inlined. 
 * 
 * Buffer preparation should be done by other functions.
 * @see uart_vprintf_buf()
 * @see uart_putc_buf()
 */
static inline void uart_send_trigger(uint8_t intfnum);

static inline void uart_send_flush(uint8_t intfnum);

static inline uint8_t uart_reqlock(uint8_t intfnum, uint8_t len, uint8_t token);

/**
 * @brief TX buffer prep function - putchar
 * @param intfnum Identifier of the UART interface.
 * @param byte byte to be sent.
 * @param token token against which buffer lock should be obtained 
 *              and/or used.
 * @param handlelock If 1, the function will deal with interacting
 *              with the underlying locking mechanism. If not, it
 *              assumes you already hold the necessary locks and use 
 *              the provided token.
 * @warning If the locking is left to this function, it will give up
 *          immediately if the lock is held elsewhere. You should 
 *          check the return value of the function if the send is 
 *          critical.
 * @return 0 for error, 1 for success.
 * 
 * Send a single character via the specified UART interface using the bytebuf.
 * 
 * @see uart_send_trigger()
 */
static inline uint8_t uart_putc(uint8_t intfnum, uint8_t byte, uint8_t token, uint8_t handlelock);

static inline uint8_t uart_write(uint8_t intfnum, uint8_t *buffer, uint8_t len, uint8_t token);

/**
 * @brief TX buffer prep function - printf
 * @param intfnum Identifier of the UART interface.
 * @param format subset of the standard printf format.
 * @param args pointer to stdarg.h var_list instance.
 * @return 0 for error, number of characters written for success.
 * 
 * Print to the specified UART interface via a printf-like 
 * function. 
 * 
 * This function should not be used in bandwidth-limited transmissions. 
 * Both the implementation of printf and the locking mechanism 
 * are likely to be bottlenecks to data generation and transmission. 
 * The uart_putc_buf() function with caller managed buffer locking 
 * will be considerably more efficient.
 * 
 * This function should be callable identically to printf. 
 * If only a subset of the format strings are allowed, this 
 * should be documented by the implementation. The current 
 * implemetation of printf.h can be taken as the 
 * least-common-denominator implementation for the moment.
 * 
 * @note float should perhaps be added to the implementation.
 * 
 * @see uart_send_trigger()
 */
uint8_t uart_vprintf(uint8_t intfnum, const char *format, ...);


/**
 * @brief RX buffer status function - unread bytes
 * @param intfnum Identifier of the UART interface.
 * @return number of unread bytes in the recieve buffer.
 * 
 * Get number of unread bytes in the specified UART interface's rxbuffer.
 * 
 */
static inline uint8_t uart_population_rxb(uint8_t intfnum);

static inline void uart_discard_rxb(uint8_t intfnum);

static inline uint8_t uart_getc(uint8_t intfnum);

static inline uint8_t uart_read(uint8_t intfnum, uint8_t *buffer, uint8_t len);

void _uart0_irqhandler(void);
void _uart1_irqhandler(void);

extern uint16_t * uart0_overrun_counter;
extern uint16_t * uart1_overrun_counter;
/**@}*/ 

/**
 * @name Hardware Debug-Only UART API Functions
 */
/**@{*/ 
/**
 * @brief Send a single character over the specified UART interface
 * @param byte The character to be sent
 * @param intfnum Identifier of the UART interface
 * 
 * This function uses the simplest possible method
 * to send a single byte of data. It should not use 
 * buffers, interrupts, etc.
 * 
 * @warning In a general application, this function would only be used 
 * in special circumstances and with extreme care. Using this alongside 
 * bytebufs will cause data loss. If you intend to use this interface, 
 * the peripheral initialization may need to be changed to not enable 
 * interrupts.
 */
static inline void uart_putc_bare(uint8_t intfnum, uint8_t byte);

/**
 * @brief Recieve a single character from the specified UART interface
 * @param intfnum Identifier of the UART interface
 * 
 * This function uses the simplest possible method
 * to recieve a single byte of data. It should not use 
 * buffers, interrupts, etc. 
 * 
 * @warning In a general application, this function would only be used 
 * in special circumstances and with extreme care. Using this alongside 
 * bytebufs will cause data loss. If you intend to use this interface, 
 * the peripheral initialization may need to be changed to not enable 
 * interrupts.
 * 
 * @return Character recieved
 */
static inline uint8_t uart_getc_bare(uint8_t intfnum);
/**@}*/ 

extern const pluggable_transport_t ptransport_uart;

#endif

// Set up the implementation
#include <hal_platform/uart_impl.h>
#include <hal_platform/uart_handlers.h>
#endif
