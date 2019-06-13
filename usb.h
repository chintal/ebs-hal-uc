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
 * @file hal_uc_usb.h
 * @brief HAL for USB interface
 *
 * This file is the hardware abstraction layer for uC USB interfaces. Due to 
 * the complexity of the USB implentation, this layer is handled differently for
 * USB compared to the other peripherals. The HAL only has minimal control over
 * the interface, and most of the details are left to the underlying 
 * implementation. Most configuration details are not taken from the PUM and 
 * are instead hardcoded into the implementation. 
 * 
 * When porting to a different board/uc/product, care must be taken. The needed
 * configuration data should go into the underlying implementation. As such, it
 * is recommended that as far as possible, predefined USB configurations be used 
 * as far as possible. A separate protocol can be built on top of the USB layer. 
 * 
 * The only role of the implementation in `usb_impl.h` and `usb_impl.c` is to 
 * translate these function names to the names in the underlying manufacturer 
 * implementation.
 * 
 * The intent is to try and provide a unified, even if feature-incomplete, HAL 
 * interface to handle multiple USB device libraries across uC families. 
 * 
 * The application can use the underlying functions directly as well, for the cost 
 * of reduction in portablility.
 * 
 * @see [USB API Integration and Usage Notes](@ref usbhal)
 * 
 * @see usb_impl.h 
 * @see usb_impl.c
 */

#ifndef HAL_UC_USB_H
#define HAL_UC_USB_H

#include <stdarg.h>
#include <platform/types.h>
#include "map.h"

#ifdef uC_INCLUDE_USB_IFACE

/**
 * @name USB Connection Statuses 
 */
/**@{*/ 

/** \brief USB Host is not connected */
#define HUSB_ST_DISCONNECTED            ST_USB_DISCONNECTED

/** \brief USB Host is connected but not enumerated */
#define HUSB_ST_NOTENUMERATED           ST_USB_CONNECTED_NO_ENUM

/** \brief USB Enumeration in progress */
#define HUSB_ST_ENUMERATING             ST_ENUM_IN_PROGRESS

/** \brief USB is ready for use */
#define HUSB_ST_ACTIVE                  ST_ENUM_ACTIVE

/** \brief Host has placed the device in suspend */
#define HUSB_ST_SUSPENDED               ST_ENUM_SUSPENDED

/** \brief Device suspended before enumeration */
#define HUSB_ST_NOENUM_SUSPENDED        ST_NOENUM_SUSPENDED

/** \brief USB Error */
#define HUSB_ST_ERROR                   ST_ERROR
/**@}*/ 

/**
 * @name USB Core Management API Functions
 * 
 */
/**@{*/ 
/**
 * \brief Initialize USB and connect if possible.
 */
static inline void usb_init(void);

/**
 * \brief Enable the USB module. 
 * 
 * Needed only if USB is to be disabled intermittently. Otherwise, `usb_setup()` 
 * should also execute this function or equivalent.
 */
static inline void usb_enable(void);

/**
 * \brief Disable the USB module. 
 * 
 * Needed only if USB is to be disabled intermittently.
 */
static inline void usb_disable(void);

/**
 * \brief Connect to host. 
 * 
 * Needed only if USB is to be disabled intermittently. Otherwise, `usb_setup()` 
 * should also execute this function or equivalent.
 */
static inline void usb_connect(void);

/**
 * \brief Disconnect from host. 
 * 
 * Needed only if USB is to be disabled intermittently.
 */
static inline void usb_disconnect(void);

/**
 * \brief Get the current status of the USB subsystem.
 * 
 * \returns Status as specified as one of the allowed status defines.
 *          
 */
static inline uint8_t usb_status(void);

/**@}*/ 

#endif

#include "uc/usb_impl.h"
#include "uc/usb_handlers.h"
#endif
